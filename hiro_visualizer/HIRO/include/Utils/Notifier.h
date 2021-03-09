/*
  Copyright (C) Skeletex Research, s.r.o. - All Rights Reserved
  Unauthorized copying of this file, via any medium is strictly prohibited
  Proprietary and confidential
*/
#ifndef UTILS_NOTIFIER_H
#define UTILS_NOTIFIER_H

#include <vector>
#include <functional>
#include <mutex>
#include <condition_variable>



namespace utils
{

  //! A notifier is a mechanism to allow inter-object notifications.
  template <typename... Args>
  class Notifier
  {
  public:
    //! The callback is a void function taking the variadic templated arguments of the Notifier class.
    using CallbackType = std::function<void(Args...)>;

    //! Add a single callback function.
    inline void AddCallback(CallbackType callback)
    {
      std::lock_guard<std::mutex> lock(notifier_access_);
      if (callback)
      {
        callbacks_.push_back(callback);
      }
    }

    //! Send all notifications at this moment.
    inline virtual void Notify(Args... args)
    {
      std::lock_guard<std::mutex> lock(notifier_access_);
      for (auto &callback : callbacks_)
      {
        callback(args...);
      }
    }

    //! Returns whether it has any callback registered.
    inline bool HasCallback() const
    {
      return !callbacks_.empty();
    }

  protected:
    //! The callbacks
    std::vector<CallbackType> callbacks_;
    //! mutex to ensure thread safety.
    mutable std::mutex notifier_access_;
  };


  /*!
    \brief
      An extension to Notifier - does not notify by itself. Instead it collects notifications and allows external code to call them when it pleases.
    \note
      The motivation is thread safety.
      The usage is that the owner (to whom the notification functionality is delegated), must call the SendAllNotifications function at the appropriate moment.
  */
  template <typename... Args>
  class DelegatedNotifier
    : public Notifier<Args...>
  {
  public:
    //! Notify does not execute all notifications - it merely collects the arguments and allows the Owner to execute them when it pleases.
    inline virtual void Notify(Args... args) override
    {
      std::lock_guard<std::mutex> lock(this->notifier_access_);
      if (!this->callbacks_.empty())
      {
        tuples_.emplace_back(std::tuple<Args...>(args...));
      }
      notifier_condition_.notify_all();
    }

    //! Send all collected notifications at this moment.
    virtual void SendAllNotifications()
    {
      std::lock_guard<std::mutex> lock(this->notifier_access_);
      for (const auto &tuple : tuples_)
      {
        for (auto &callback : this->callbacks_)
        {
          callback(std::get<Args>(tuple) ...);
        }
      }
      tuples_.clear();
      notifier_condition_.notify_all();
    }

    //! Wait until all notifications are sent.
    virtual void WaitUntilAllSent()
    {
      std::unique_lock<std::mutex> lock(this->notifier_access_);
      notifier_condition_.wait(lock, [this]() { return tuples_.empty(); });
    }

  protected:
    //! The collected arguments to be executed on the next execution loop call.
    std::vector<std::tuple<Args...>> tuples_;
    //! Condition variable to trigger rechecking conditions.
    std::condition_variable notifier_condition_;
  };
}

#endif /* !UTILS_NOTIFIER_H */