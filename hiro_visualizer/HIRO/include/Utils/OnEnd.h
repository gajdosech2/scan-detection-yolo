/*
  Copyright (C) Skeletex Research, s.r.o. - All Rights Reserved
  Unauthorized copying of this file, via any medium is strictly prohibited
  Proprietary and confidential
*/
#ifndef UTILS_ON_END_H
#define UTILS_ON_END_H
#include <functional>

namespace utils
{
  /*!
    \brief Helper class that performs an action when it is destroyed.

    Motivation:
      - When a function has many boundary conditions and returns in multiple places.

    Example usage:
    \code{.cpp}
      bool Init()
      {
        m->device->LockGUI();                         // Locks GUI
        OnEnd _([&]() { m->device->UnlockGUI(); });

        if (condition_1)
          return false;                               // GUI is unlocked

        if (condition_2)
          return false;                               // GUI is unlocked

        return true;                                  // GUI is unlocked
      }
    \endcode
  */
  class OnEnd
  {
  public:
    //! Callback is a void function taking 0 arguments.
    using Callback = std::function<void()>;

    //! Constructor sets Callback.
    explicit OnEnd(Callback F)
      : F_(F)
    {
    }

    //! Destructor calls Callback.
    ~OnEnd()
    {
      F_();
    }

    // No copying permitted.
    OnEnd(const OnEnd &) = delete;
    OnEnd &operator=(const OnEnd &) = delete;
    OnEnd(OnEnd &&) = delete;
    OnEnd &operator=(OnEnd &&) = delete;

  private:
    Callback F_;
  };
}
#endif /* !UTILS_ON_END_H */