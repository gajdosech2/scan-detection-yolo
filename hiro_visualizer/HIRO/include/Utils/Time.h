/*
  Copyright (C) Skeletex Research, s.r.o. - All Rights Reserved
  Unauthorized copying of this file, via any medium is strictly prohibited
  Proprietary and confidential
*/
#ifndef UTILS_TIME_H
#define UTILS_TIME_H
#include <string>
#include <ctime>
#include <chrono>
#include <list>
#include <assert.h>

#define __STDC_WANT_LIB_EXT1__ 1
#include <time.h>
#include <stdio.h>

#include <Utils/ExtSTD.h>

//! Set of functions and structures for measuring time.
namespace time_m
{

  using DateTime = std::chrono::system_clock::time_point;

  //! Returns current time point.
  inline DateTime Now()
  {
    return std::chrono::system_clock::now();
  }


  //! Returns current time, as number of milliseconds since epoch start.
  inline double NowMs()
  {
    return (double)std::chrono::duration_cast<std::chrono::milliseconds>
      (Now().time_since_epoch()).count();
  }


  //! Returns current time, as number of seconds since epoch start.
  inline double NowS()
  {
    return (double)std::chrono::duration_cast<std::chrono::milliseconds>
      (Now().time_since_epoch()).count() * 0.001f;
  }


  /*!
    \brief Returns specified time in string form.
    \param date_time The DateTime to be formatted.
    \param format Defines string format. For options see documentation of strftime() at https://en.cppreference.com/w/c/chrono/strftime.
  */
  inline std::string ToString(const DateTime &date_time, const std::string &format = "%Y_%m_%d_%H_%M_%S")
  {
    time_t rawtime = std::chrono::system_clock::to_time_t(date_time);
    char buffer[80];

    // https://stackoverflow.com/a/38034148/2621721
    std::tm timeinfo{};
#if defined(__unix__)
    localtime_r(&rawtime, &timeinfo);
#elif defined(_MSC_VER)
    localtime_s(&timeinfo, &rawtime);
#else
    static std::mutex mtx;
    std::lock_guard<std::mutex> lock(mtx);
    timeinfo = *std::localtime(&rawtime);
#endif

    strftime(buffer, 80, format.c_str(), &timeinfo);
    return std::string(buffer);
  }


  /*!
    \brief Returns current time in string form.
    \param format Defines string format. For options see documentation of strftime() at https://en.cppreference.com/w/c/chrono/strftime.
  */
  inline std::string NowStr(const std::string &format = "%Y_%m_%d_%H_%M_%S")
  {
    return ToString(std::chrono::system_clock::now(), format);
  }


  //! Returns duration between two time points in microseconds.
  inline int64_t MicrosecondsBetween(const DateTime &datetime1, const DateTime &datetime2)
  {
    return abs(std::chrono::duration_cast<std::chrono::microseconds>(datetime1 - datetime2).count());
  }


  //! Returns duration between two time points in seconds.
  inline double SecondsBetween(const DateTime &datetime1, const DateTime &datetime2)
  {
    return 0.000001 * (double)MicrosecondsBetween(datetime1, datetime2);
  }

  class FPSCounter
  {
  public:
    FPSCounter()
    {
      lastFrameTime = Now();
    };
    void RegisterFrame()
    {
      const DateTime now = Now();
      fps = 1.0 / SecondsBetween(lastFrameTime, now);
      lastFrameTime = now;
    };
    double Get() { return fps; };
    const double *GetPtr() { return &fps; };
  private:
    DateTime lastFrameTime;
    double fps = 0.0;
  };



  //! Class for measuring time in milliseconds [ms].
  class StopWatch
  {
  public:
    //! Creates stopwatch and starts time measurement.
    StopWatch() = default;
    //! Resets time on stopwatch.
    void Reset() { start_time_ = NowMs(); };
    //! Returns current watch time. [ms]
    double GetTime() { return NowMs() - start_time_; };
    //! Returns current watch time as a text. [ms]
    std::string GetTimeStr() { return std::to_string(GetTime()); };
  private:
    double start_time_{ NowMs() };
  };



  //! Measures duration of program parts and logs times into a stream.
  class TimeLogger
  {
  private:
    struct Measurement
    {
      Measurement(const std::string &n, const double t) : name(n), start_time(t) {};
      std::string name;
      double start_time;
      double duration = -1.0f;
      Measurement *parent = nullptr;
      std::list<Measurement> children;
    };
  public:
    TimeLogger() = default;

    virtual void MeasureStart(const std::string &measurement_name)
    {
      auto start_time = (double)std::chrono::duration_cast<std::chrono::milliseconds>
        (Now().time_since_epoch()).count();
      if (root_measure_ == nullptr)
      {
        root_measure_ = std::make_unique<Measurement>(measurement_name, start_time);
        active_measure_ = root_measure_.get();
      }
      else
      {
        active_measure_->children.emplace_back(measurement_name, start_time);
        active_measure_->children.back().parent = active_measure_;
        active_measure_ = &active_measure_->children.back();
      }
    };

    virtual void MeasureEnd(std::ostream *output_log)
    {
      assert(active_measure_); // no matching MeasureStart() was called

      auto end_time = (double)std::chrono::duration_cast<std::chrono::milliseconds>
        (Now().time_since_epoch()).count();

      active_measure_->duration = end_time - active_measure_->start_time;

      if (active_measure_->parent)
      {
        active_measure_ = active_measure_->parent;
        return;
      }
      WriteMeasurementRecursive(active_measure_, output_log);
      root_measure_.reset();
      active_measure_ = nullptr;
    }

    TimeLogger(const TimeLogger &) = delete;
    TimeLogger &operator=(const TimeLogger &) = delete;

    ~TimeLogger()
    {
      assert(active_measure_ == nullptr); // not enough calls of MeasureEnd()
    };

  private:
    std::unique_ptr<Measurement> root_measure_;
    Measurement *active_measure_ = nullptr;

    void WriteMeasurement(const Measurement *msr, std::ostream *output_log, uint8_t level = 0)
    {
      *output_log << std::string(level, '\t')
        << msr->duration << " ms"
        << " - "
        << msr->name
        << std::endl;
    }

    void WriteMeasurementRecursive(const Measurement *msr, std::ostream *output_log, const uint8_t level = 0)
    {
      WriteMeasurement(msr, output_log, level);
      for (const auto &child : msr->children)
      {
        WriteMeasurementRecursive(&child, output_log, level + 1);
      }
    }
  };



  //! Measures duration of program parts and logs times into a file.
  class FileTimeLogger : public TimeLogger
  {
  public:
    void SessionStart(const std::string &export_file_name = "timing_log.local.txt")
    {
      export_file_.open(export_file_name);
      is_session_ = true;
    }

    void SessionEnd()
    {
      export_file_.close();
      is_session_ = false;
    }

    bool IsSession() const
    {
      return is_session_;
    };

    virtual void MeasureStart(const std::string &measurement_name) override
    {
      if (IsSession())
      {
        TimeLogger::MeasureStart(measurement_name);
      }
    }

    void MeasureEnd()
    {
      if (IsSession())
      {
        TimeLogger::MeasureEnd(&export_file_);
      }
    }

  private:
    std::ofstream export_file_;
    bool is_session_ = false;

    using TimeLogger::MeasureEnd;
  };



  //! The result of profiling function execution. Contains the actual result and the run time.
  template<typename T>
  struct ProfilingResult
  {
    T result;
    std::chrono::milliseconds time;

    ProfilingResult(const T &r, std::chrono::milliseconds t)
      : result(r)
      , time(t)
    {}
  };

  //! Execute and profile a function.
  template<typename T>
  inline ProfilingResult<T> ProfileFunctionRun(std::function<T()> Function)
  {
    StopWatch stop_watch;
    const auto result = Function();
    const auto time = std::chrono::milliseconds(static_cast<uint32_t>(std::round(stop_watch.GetTime())));
    return time_m::ProfilingResult(result, time);
  }
}

#endif /* !UTILS_TIME_H */