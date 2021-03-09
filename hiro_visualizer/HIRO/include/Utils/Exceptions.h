/*
  Copyright (C) Skeletex Research, s.r.o. - All Rights Reserved
  Unauthorized copying of this file, via any medium is strictly prohibited
  Proprietary and confidential
*/
#ifndef UTILS_EXCEPTIONS_H
#define UTILS_EXCEPTIONS_H

#include <stdexcept>
#include <Utils/Ulog.h>



//! Extensions to the standard libraries.
namespace std_ext
{

  class NotImplementedError : public std::logic_error
  {
  public:
    NotImplementedError() : std::logic_error{ "Function not implemented yet." } {}
  };

  class UnhandledConditionError : public std::logic_error
  {
  public:
    UnhandledConditionError() : std::logic_error{ "Unhandled condition." } {}
  };

  class AuthenticationError : public std::runtime_error
  {
  public:
    AuthenticationError(const std::string &description) : std::runtime_error(description) {}
  };

  class OutOfBounds : public std::out_of_range
  {
  public:
    OutOfBounds(size_t x, size_t y, std::string caller)
      : std::out_of_range("Grid element index (" + std::to_string(x) + ", " + std::to_string(y) + ") out of bounds")
    {
      ulog::Crash(what(), caller);
    }
  };

}

#endif /* !UTILS_EXCEPTIONS_H */