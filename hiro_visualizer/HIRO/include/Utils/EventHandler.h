/*
  Copyright (C) Skeletex Research, s.r.o. - All Rights Reserved
  Unauthorized copying of this file, via any medium is strictly prohibited
  Proprietary and confidential
*/
#ifndef UTILS_EVENT_HANDLER_H
#define UTILS_EVENT_HANDLER_H
#include <Utils/AtomicQueue.h>
#include <memory>

namespace utils
{

  /*!
    \brief Provides an interface for registering and processing events for inherited classes.

    Children of this class can register events at any time,
    but process them together when user requests to.

    This class is thread safe and can be called from asynchronous processes.
  */
  class EventHandler
  {
  public:
    //! Request to process all registered events.
    virtual void PollEvents()
    {
      while (!events_.IsEmpty())
      {
        auto ev = events_.Pop();
        ProcessEvent(ev.get());
      }
    };
  protected:
    //! Unique identifier of event.
    using EventId = std::string;
    //! Default event. Inherit this structure to create custom event.
    struct Event
    {
      Event(const std::string &_id) : id(_id) {};
      std::string id;
    };
    //! Process a single event during polling.
    virtual void ProcessEvent([[maybe_unused]] const Event *e) {};
    //! Adds new event to the event queue.
    template<typename T = Event, typename... Args>
    void RegisterEvent(Args... args)
    {
      events_.Push(std::make_shared<T>(args...));
    }
  private:
    std_ext::AtomicQueue<std::shared_ptr<Event>> events_;
  };

}
#endif /* !UTILS_EVENT_HANDLER_H */