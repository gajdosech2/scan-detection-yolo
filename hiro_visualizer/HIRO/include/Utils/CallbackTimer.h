/*
  Copyright (C) Skeletex Research, s.r.o. - All Rights Reserved
  Unauthorized copying of this file, via any medium is strictly prohibited
  Proprietary and confidential
*/
#ifndef UTILS_CALLBACK_TIMER_H
#define UTILS_CALLBACK_TIMER_H

#include <atomic>
#include <thread>

#include <Utils/Threading.h>



namespace utils
{
  /*
    \brief
      An async timer executes given function every time interval.
    \note
      Runs every time interval until callback either returns false or the timer is stopped.
      Accepts only a single callback. Running Start with a new callback stops the old one.
  */
  class CallbackTimer
  {
  public:
    //! Initialize without execution.
    CallbackTimer()
      : execute_(false)
    {}

    //! Stop execution on destruction.
    ~CallbackTimer()
    {
      if (execute_.load(std::memory_order_acquire))
      {
        Stop();
      };
    }

    /*!
      \brief
        Start the provided callback.
      \note
        Runs each timer tick until it either returns false or the timer is stopped.
      \param interval
        Timer interval of the type std::chrono::duration. Passed by value since it is a primitive.
      /params callback
        A callback function to be executed every tick. Returns bool to signal stopping.
    */
    template<typename DurationType>
    void Start(DurationType interval, std::function<bool(void)> callback)
    {
      if (execute_.load(std::memory_order_acquire))
      {
        Stop();
      };

      execute_.store(true, std::memory_order_release);
      thread_ = std::thread([this, interval, callback]()
      {
        utils::SetThisThreadName("CallbackTimer_thread");
        while (execute_.load(std::memory_order_acquire))
        {
          execute_.store(callback(), std::memory_order_release);
          std::this_thread::sleep_for(interval);
        }
      });
    }

    //! Manually stop execution.
    void Stop()
    {
      execute_.store(false, std::memory_order_release);
      if (thread_.joinable())
      {
        thread_.join();
      }
    }

    //! Check whether there is a callback being executed.
    bool IsRunning() const noexcept
    {
      return (execute_.load(std::memory_order_acquire) && thread_.joinable());
    }

  private:
    //! Execute flag
    std::atomic<bool> execute_;
    //! Execution thread
    std::thread thread_;
  };
}

#endif /* !UTILS_CALLBACK_TIMER_H */