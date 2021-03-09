/*
  Copyright (C) Skeletex Research, s.r.o. - All Rights Reserved
  Unauthorized copying of this file, via any medium is strictly prohibited
  Proprietary and confidential
*/
#ifndef UTILS_CLR_THREAD_HOLDER_H
#define UTILS_CLR_THREAD_HOLDER_H
#ifdef _WIN32
#include <windows.h>
#include <process.h>
#include <functional>

namespace utils
{

  //! Thread wrapper for applications using CLR.
  class ClrThreadHolder
  {
  public:

    //! Create thread controller object.
    ClrThreadHolder() = default;

    //! Set a function which will be called in loop until SyncStop is called.
    void SetFuncLoop(std::function<void(void)> _func)
    {
      isLoopFunc = true;
      pFunc = _func;
    };

    //! Set a function which will be executed once.
    void SetFunc(std::function<void(void)> _func)
    {
      isLoopFunc = false;
      pFunc = _func;
    };

    //! Create a thread which will call a function.
    void Start()
    {
      hThread = (HANDLE)_beginthreadex(0, 0, &ClrThreadHolder::func_wrapper, static_cast<void *>(this), 0, 0);
    };

    //! Check if the thread function is running yet.
    bool IsRunning() const
    {
      return isRunning;
    };

    //! Waits until a thread function is finished (and stops if it is loop func).
    void SyncStop()
    {
      isStopRequested = true;

      // actually wait for the thread to exit
      WaitForSingleObject(hThread, INFINITE);

      // get the thread's exit code
      DWORD exitcode;
      GetExitCodeThread(hThread, &exitcode);

      // cleanup the thread.
      CloseHandle(hThread);
      hThread = nullptr;
    };

    //! Destroys thread controller object.
    ~ClrThreadHolder() {};

  private:

    unsigned int iThreadID = 0;
    HANDLE hThread = nullptr;

    std::function<void(void)> pFunc = nullptr;
    bool isLoopFunc = false;
    bool isStopRequested = false;
    bool isRunning = false;

    // Main thread function.
    unsigned MyThreadFunc()
    {
      if (pFunc == nullptr) { return 1; }
      isRunning = true;
      do { pFunc(); }
      while (isLoopFunc && !isStopRequested);
      isRunning = false;
      return 0;
    }

    // Thread cast compatibility function.
    static unsigned __stdcall func_wrapper(void *o)
    {
      return static_cast<ClrThreadHolder *>(o)->MyThreadFunc();
    }
  };

}

#endif
#endif /* !UTILS_CLR_THREAD_HOLDER_H */