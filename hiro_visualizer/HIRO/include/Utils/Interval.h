/*
  Copyright (C) Skeletex Research, s.r.o. - All Rights Reserved
  Unauthorized copying of this file, via any medium is strictly prohibited
  Proprietary and confidential
*/
#ifndef UTILS_INTERVAL_H
#define UTILS_INTERVAL_H

#include "ExtGLM.h"



namespace utils
{

  //! Holds float interval and performs operations on it.
  class Interval
  {
  public:
    //! Creates a default interval <0,1>.
    Interval()
      : Interval(0.0f, 1.0f)
    {
    }

    //! Creates an interval <a,b> with custom numerical precision (epsilon).
    Interval(const float a, const float b, const float epsilon)
      : min_(glm::min(a, b))
      , max_(glm::max(a, b))
      , epsilon_(epsilon)
    {
    }

    //! Creates an interval <a,b>.
    Interval(const float left, const float right)
      : Interval(left, right, 0.0001f)
    {
    }

    //! Compares if two intervals are identical.
    bool operator==(const Interval &o) const
    {
      const float max_common_epsilon = std_ext::Max(epsilon_, o.epsilon_);
      return
        glm_ext::AreEqual(min_, o.min_, max_common_epsilon) &&
        glm_ext::AreEqual(max_, o.max_, max_common_epsilon);
    }

    //! Compares if two intervals are different.
    bool operator!=(const Interval &o) const
    {
      return !(*this == o);
    }

    //! Clamps a value to the interval endpoints.
    float GetClamped(const float val) const
    {
      return glm::clamp(val, min_, max_);
    }

    //! Returns real value from the normalized interval parameter.
    float NormToValue(const float t) const
    {
      return min_ + t * GetRange();
    }

    //! Returns normalized interval parameter from the real value.
    float ValueToNorm(const float val) const
    {
      return (val - min_) / GetRange();
    }

    //! Returns a distance between interval endpoints.
    float GetRange() const
    {
      return max_ - min_;
    }

    //! Check whether the range of interval is zero.
    bool IsEmpty() const
    {
      return glm_ext::AreEqual(min_, max_, epsilon_);
    }

    //! Returns value of a minimal endpoint of the interval.
    float GetMin() const
    {
      return min_;
    }

    //! Returns value of a maximal endpoint of the interval.
    float GetMax() const
    {
      return max_;
    }

    //! Returns numerical precision of the interval.
    float GetEpsilon() const
    {
      return epsilon_;
    }

  protected:
    float min_;
    float max_;
    float epsilon_;
  };

}

#endif /* !UTILS_INTERVAL_H */