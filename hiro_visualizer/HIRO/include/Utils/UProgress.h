/*
  Copyright (C) Skeletex Research, s.r.o. - All Rights Reserved
  Unauthorized copying of this file, via any medium is strictly prohibited
  Proprietary and confidential
*/
#ifndef UTILS_UPROGRESS_H
#define UTILS_UPROGRESS_H
#include <functional>
#include <Utils/API.h>

namespace uprogress
{
  //! Reset percentage value and enable/disable it.
  UTILS_API void Reset(bool percentage_enabled = true);

  //! Check whether percentage is enabled at this time.
  UTILS_API bool IsEnabled();

  //! Set amount of percentage to defined value. Clamped to range <0,1>.
  UTILS_API void Set(float percentage_value);

  //! Returns current percentage value of progress.
  UTILS_API float Get();

  //! Increment progress value by an amount of percentage. Clamped to range <0,1>.
  UTILS_API void Add(float percentage_increment);

  //! Subscribes a function that will be called whenever a percentage has changed. For later unsubscription, you can set an id.
  UTILS_API void Subscribe(std::function<void()> subscriber, const std::string &id = "default");

  //! Unsubscribe all functions with the input id.
  UTILS_API void UnSubscribe(const std::string &id);

  //! Unsubscribe all functions.
  UTILS_API void UnSubscribeAll();
}

#endif /* !UTILS_UPROGRESS_H */