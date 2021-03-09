/*
  Copyright (C) Skeletex Research, s.r.o. - All Rights Reserved
  Unauthorized copying of this file, via any medium is strictly prohibited
  Proprietary and confidential
*/
#ifndef UTILS_LOG_ENTRY_H
#define UTILS_LOG_ENTRY_H
#include <string>
#include <vector>
#include <Utils/API.h>
#include <Utils/Time.h>


namespace utils
{

  //! A single entry for the logging system.
  class UTILS_API LogEntry
  {
  public:
    //! Defines the character of a LogEntry.
    enum class Type
    {
      debug,        // debug entry
      info,         // informative entry
      warning,      // warning entry of an invalid action, input or caller state
      error,        // a valid application state to report an error detected by the caller - will not affect the correct functioning of a program
      critical,     // an invalid application state that may cause the program to crash
      _unspecified
    };

    static std::vector<Type> GetWECTypes();

    static std::vector<Type> GetIWECTypes();

    explicit LogEntry(const std::string &message);

    LogEntry(Type type, const std::string &message, const std::string &caller_name);

    [[nodiscard]] static std::string TypeToString(Type type);
    [[nodiscard]] static std::wstring TypeToWstring(Type type);

    [[nodiscard]] Type GetType() const;

    [[nodiscard]] const std::string &GetMessage() const;

    [[nodiscard]] const std::string &GetCaller() const;

    //! Print a LogEntry to output stream.
    friend std::ostream &operator<< (std::ostream &os, const LogEntry &entry)
    {
      return os << entry.ToString();
    }

    //! Print a vector of LogEntries to output stream.
    friend std::ostream &operator << (std::ostream &os, const std::vector<LogEntry> &v)
    {
      for (typename std::vector<LogEntry>::const_iterator ii = v.begin(); ii != v.end(); ++ii)
      {
        os << *ii << "\n";
      }
      return os;
    }

    //! Print a vector of LogEntries to output stream.
    friend std::ostream &operator << (std::ostream &os, const std::vector<std::shared_ptr<LogEntry>> &v)
    {
      for (typename std::vector<std::shared_ptr<LogEntry>>::const_iterator ii = v.begin(); ii != v.end(); ++ii)
      {
        os << **ii << "\n";
      }
      return os;
    }

    /*!
      \brief Print the entry to a string.
      \note The string format is "[type] caller: message".
    */
    [[nodiscard]] virtual std::string ToString(const std::string &time_format = "%Y-%m-%d %H:%M:%S") const;

    [[nodiscard]] bool IsRead() const;

    //! Set the entry to is_read.
    void Read();

  private:
    Type type_;
    std::string message_;
    std::string caller_name_;
    time_m::DateTime time_;
    bool is_read_;
  };

}

#endif /* !UTILS_LOG_ENTRY_H */