/*
  Copyright (C) Skeletex Research, s.r.o. - All Rights Reserved
  Unauthorized copying of this file, via any medium is strictly prohibited
  Proprietary and confidential
*/
#ifndef UTILS_LOG_WRITER_H
#define UTILS_LOG_WRITER_H

#include <Utils/Time.h>
#include <Utils/ExtGLM.h>
#include <Utils/LogReader.h>
#include <Utils/Notifier.h>
#include <Utils/Filesystem.h>
#include <Utils/NamedClass.h>


namespace utils
{

  using LogEntryNotifier = DelegatedNotifier<const LogEntry::Type>;
  using ProgressNotifier = DelegatedNotifier<const ProgressPercentage>;

  /*!
    \brief Extension to LogReader. Provide write access to the log.
  */
  class LogWriter
    : public LogReader
    , public LogEntryNotifier
    , public ProgressNotifier
  {
  public:
    LogWriter() = default;
    ~LogWriter() = default;

    LogWriter(const LogWriter &) = delete;
    LogWriter &operator=(const LogWriter &) = delete;
    LogWriter(utils::LogWriter &&) = delete;
    LogWriter &operator=(utils::LogWriter &&) = delete;



    //! Reset percentage value and disable it optionally.
    void ResetPercentage(bool enable_percentage = true)
    {
      percentage_ = enable_percentage ? std::optional<float>(0.0f) : std::nullopt;
      ProgressNotifier::Notify(percentage_);
    }

    //! Set amount of percentage to defined value. Clamped to range <0,1>
    void SetPercentage(float value)
    {
      std::lock_guard<std::mutex> lock(percentage_access_);
      percentage_ = glm_ext::Clamp01(value);

      ProgressNotifier::Notify(percentage_);
    }

    //! Increment progress-bar value by an amount of percentage.
    LogWriter &operator+=(const float percentage_increment)
    {
      if (percentage_.HasValue())
      {
        std::lock_guard<std::mutex> lock(percentage_access_);
        percentage_ = glm_ext::Clamp01(percentage_.Value() + percentage_increment);

        ProgressNotifier::Notify(percentage_);
      }
      return *this;
    }


    //! Add a log entry to the log. If output stream enabled, print to output stream.
    LogWriter &operator<<(const std::shared_ptr<LogEntry> entry);

    //! Add an entry to the log. If output stream enabled, print to output stream.
    LogWriter &Add(const LogEntry &&entry);

    //! Add an entry to the log. If output stream enabled, print to output stream.
    LogWriter &Add(const std::shared_ptr<LogEntry> entry);

    //! Add an entry to the log. If output stream enabled, print to output stream.
    template <typename ...Params>
    LogWriter &AddEntry(Params &&... params);


    //! Add a Info entry to the log. If output stream enabled, print to output stream.
    LogWriter &Inform(const std::string &message, const std::string &caller_name)
    {
      return AddEntry(LogEntry::Type::info, message, caller_name);
    }

    //! Add a Warning entry to the log. If output stream enabled, print to output stream.
    LogWriter &Warn(const std::string &message, const std::string &caller_name)
    {
      return AddEntry(LogEntry::Type::warning, message, caller_name);
    }

    //! Add a Error entry to the log. If output stream enabled, print to output stream.
    LogWriter &Fail(const std::string &message, const std::string &caller_name)
    {
      return AddEntry(LogEntry::Type::error, message, caller_name);
    }

    //! Add a Critical entry to the log. If output stream enabled, print to output stream.
    LogWriter &Crash(const std::string &message, const std::string &caller_name)
    {
      return AddEntry(LogEntry::Type::critical, message, caller_name);
    }

    //! Add a Info entry to the log. If output stream enabled, print to output stream. Pass caller to get its name.
    template<class CT>
    LogWriter &Inform(const std::string &message, const utils::NamedClass<CT> *caller)
    {
      return AddEntry(LogEntry::Type::info, message, caller->GetClassName());
    }

    //! Add a Warning entry to the log. If output stream enabled, print to output stream. Pass caller to get its name.
    template<class CT>
    LogWriter &Warn(const std::string &message, const utils::NamedClass<CT> *caller)
    {
      return AddEntry(LogEntry::Type::warning, message, caller->GetClassName());
    }

    //! Add a Error entry to the log. If output stream enabled, print to output stream. Pass caller to get its name.
    template<class CT>
    LogWriter &Fail(const std::string &message, const utils::NamedClass<CT> *caller)
    {
      return AddEntry(LogEntry::Type::error, message, caller->GetClassName());
    }

    //! Add a Critical entry to the log. If output stream enabled, print to output stream. Pass caller to get its name.
    template<class CT>
    LogWriter &Crash(const std::string &message, const utils::NamedClass<CT> *caller)
    {
      return AddEntry(LogEntry::Type::critical, message, caller->GetClassName());
    }


    //! Copy all unread entries from another LogReader.
    LogWriter &CopyUnreadEntries(const LogReader &other);


    //! Start time measurement + print to log
    void StartTimeMeasure(const std::string &measurement_name)
    {
      std::lock_guard<std::mutex> lock(time_measurement_access_);
      time_logger_.MeasureStart(measurement_name);
    }

    //! End time measurements + print to log
    void StopTimeMeasure()
    {
      std::lock_guard<std::mutex> lock(time_measurement_access_);
      std::stringstream ss;
      time_logger_.MeasureEnd(&ss);

      const auto ss_str = ss.str();
      if(!ss_str.empty())
      {
        Inform(ss.str(), "Time measurement");
      }
    }

    //! Save all log messages to a file.
    bool SaveToFile(const std::string &file_path)
    {
      std::lock_guard<std::mutex> lock(log_access_);
      const auto entry_messages = std_ext::Transformed(log_entries_, [](const auto & entry) { return entry->ToString(); });
      fs::StringToFile(file_path, std_ext::ToString(entry_messages, "\n"));
      return true;
    }

    //! Read all unread messages from log with the selected types and display them supplied message dialog function.
    bool DisplayUnread(const utils::EnumFlags<utils::LogEntry::Type> &types, const std::function<void(const std::wstring &, const std::wstring &)> &ShowMessageBox = nullptr)
    {
      const auto unread_log = ReadUnread(types);
      if (!unread_log.empty())
      {
        const auto entry_messages = std_ext::Transformed(unread_log, [](const auto & entry) { return entry->ToString(); });
        const std::string message_str = std_ext::ToString(entry_messages, "\n");
        const std::wstring message_wstr(message_str.begin(), message_str.end());

        if (ShowMessageBox)
        {
          ShowMessageBox(message_wstr, L"Warning");
        }
        else
        {
          std::cout << (L"Warning : " + message_wstr).c_str() << std::endl;
        }
      }

      return !unread_log.empty();
    }


  private:
    //! Time logger.
    time_m::TimeLogger time_logger_;
    //! mutex to ensure thread safety of the Log.
    mutable std::mutex time_measurement_access_;
  };



  inline LogWriter &utils::LogWriter::operator<<(const std::shared_ptr<LogEntry> entry)
  {
    return Add(entry);
  }

  inline LogWriter &utils::LogWriter::Add(const LogEntry &&entry)
  {
    return Add(std::make_shared<LogEntry>(std::move(entry)));
  }

  inline LogWriter &utils::LogWriter::Add(const std::shared_ptr<LogEntry> entry)
  {
    log_access_.lock();
    log_entries_.emplace_back(entry);
    log_access_.unlock();

    if (output_stream_)
    {
      *(output_stream_) << entry->ToString() << "\n";
    }

    LogEntryNotifier::Notify(entry->GetType());
    return *this;
  }

  template <typename ...Params>
  inline LogWriter &utils::LogWriter::AddEntry(Params &&... params)
  {
    return Add(LogEntry(std::forward<Params>(params)...));
  }

  inline LogWriter &utils::LogWriter::CopyUnreadEntries(const LogReader &other)
  {
    for (const auto &entry : other.ViewUnread(utils::LogEntry::GetIWECTypes()))
    {
      this->Add(entry);
    }
    return *this;
  }

}
#endif /* !UTILS_LOG_WRITER_H */