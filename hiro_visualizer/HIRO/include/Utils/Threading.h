/*
  Copyright (C) Skeletex Research, s.r.o. - All Rights Reserved
  Unauthorized copying of this file, via any medium is strictly prohibited
  Proprietary and confidential
*/
#ifndef UTILS_THREADING_H
#define UTILS_THREADING_H

#include <string>

#ifdef _WIN32
#include <Windows.h>
#endif // _WIN32


namespace utils
{

#if defined _WIN32 && defined _MSC_VER

#include <windows.h>

  const DWORD MS_VC_EXCEPTION = 0x406D1388;

#pragma pack(push,8)
  typedef struct tagTHREADNAME_INFO
  {
    DWORD dwType; // Must be 0x1000.
    LPCSTR szName; // Pointer to name (in user addr space).
    DWORD dwThreadID; // Thread ID (-1=caller thread).
    DWORD dwFlags; // Reserved for future use, must be zero.
  } THREADNAME_INFO;
#pragma pack(pop)

  /*!
    \brief Name a specified thread for debugging purposes (WINDOWS ONLY).
    \note https://docs.microsoft.com/en-us/visualstudio/debugger/how-to-set-a-thread-name-in-native-code?view=vs-2019
  */
  inline void SetThreadName(DWORD dwThreadID, const char *threadName)
  {
    THREADNAME_INFO info;
    info.dwType = 0x1000;
    info.szName = threadName;
    info.dwThreadID = dwThreadID;
    info.dwFlags = 0;
#pragma warning(push)
#pragma warning(disable: 6320 6322)
    __try
    {
      RaiseException(MS_VC_EXCEPTION, 0, sizeof(info) / sizeof(ULONG_PTR), (ULONG_PTR *)& info);
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
    }
#pragma warning(pop)
  }

  /*!
    \brief Name the current thread for debugging purposes (WINDOWS ONLY).
    \note https://docs.microsoft.com/en-us/visualstudio/debugger/how-to-set-a-thread-name-in-native-code?view=vs-2019
  */
  inline void SetThisThreadName(const std::string &threadName)
  {
    SetThreadName(GetCurrentThreadId(), threadName.c_str());
  }

#elif __linux__
  //! Name a specified thread for debugging purposes.
  inline void SetThreadName(long, const char *)
  {
    // can not name a thread on Linux
  }

  //! Name the current thread for debugging purposes.
  inline void SetThisThreadName(const std::string &)
  {
    // can not name a thread on Linux
  }

#else
#error "platform not supported"
#endif

}

#endif /* !UTILS_THREADING_H */