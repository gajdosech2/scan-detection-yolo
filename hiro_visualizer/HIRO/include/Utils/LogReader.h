/*
  Copyright (C) Skeletex Research, s.r.o. - All Rights Reserved
  Unauthorized copying of this file, via any medium is strictly prohibited
  Proprietary and confidential
*/
#ifndef UTILS_LOG_READER_H
#define UTILS_LOG_READER_H

#include <ostream>
#include <mutex>

#include <Utils/EnumFlags.h>
#include <Utils/LogEntry.h>
#include <Utils/StrongOptionalType.h>



namespace utils
{

  using ProgressPercentage = utils::StrongOptionalType<float, class LogReader>;

  /*!
    \brief
      Log - accumulate typed messages reported by the application.
      Includes percentage value in range <0,1>.

      Is not a singleton. Multiple individual components of the application may have their own log.

      Includes the functionality to inform about progress of processing functions.
      Whenever a function is run, this class provides thread-safe getters
      which can be used to inform user about current state of the function.
  */
  class LogReader
  {
  public:
    LogReader()
      : percentage_(std::nullopt)
    {}
    ~LogReader() = default;

    LogReader(const LogReader &) = delete;
    LogReader &operator=(const LogReader &) = delete;
    LogReader(LogReader &&) = delete;
    LogReader &operator=(LogReader &&) = delete;



    /*! \brief
      Returns true if percentage is currently enabled.
      Some processing functions may not support percentage values.
    */
    [[nodiscard]]
    bool IsPercentageEnabled() const
    {
      return percentage_.HasValue();
    }

    //! Returns current percentage value of progress in range 0, 1.
    [[nodiscard]]
    float GetPercentage() const
    {
      if (percentage_.HasValue())
      {
        std::lock_guard<std::mutex> lock(percentage_access_);
        return percentage_.Value();
      }
      return 0.0f;
    }

    /*! \brief
      Allows user to specify custom output stream to receive
      verbose information about progress. Default value is nullptr.
    */
    void SetOutputStream(std::ostream *output_log_stream)
    {
      output_stream_ = output_log_stream;
    }

    //! Returns pointer to currently active output stream.
    [[nodiscard]]
    std::ostream *GetOutputStream()
    {
      return output_stream_;
    }

    //! Get all unread messages specified by their types and return them.
    std::vector<std::shared_ptr<LogEntry>> ViewUnread(const utils::EnumFlags<LogEntry::Type> &types = LogEntry::GetWECTypes()) const
    {
      std::lock_guard<std::mutex> lock(log_access_);
      return std_ext::SelectIf(log_entries_, [&types](const auto entry) { return entry != nullptr && types.IsSet(entry->GetType()) && !entry->IsRead(); });
    }

    //! Get all unread messages specified by their types and return them and output as std::string.
    std::string ViewUnreadToString(const utils::EnumFlags<LogEntry::Type> &types = LogEntry::GetIWECTypes()) const
    {
      const auto unread = ViewUnread(types);
      std::stringstream ss;
      ss << unread;
      return ss.str();
    }

    //! Get all unread messages specified by their types, set them to read, and return them.
    [[nodiscard]]
    std::vector<std::shared_ptr<LogEntry>> ReadUnread(const utils::EnumFlags<LogEntry::Type> &types)
    {
      const auto unread = ViewUnread(types);
      for (const auto &entry : unread)
      {
        entry->Read();
      }
      return unread;
    }


  protected:
    std::ostream *output_stream_ = nullptr;

    ProgressPercentage percentage_;
    mutable std::mutex percentage_access_;

    //! Saved log entries.
    std::vector<std::shared_ptr<LogEntry>> log_entries_;
    //! mutex to ensure thread safety of the Log.
    mutable std::mutex log_access_;
  };

}

#endif /* !UTILS_LOG_READER_H */