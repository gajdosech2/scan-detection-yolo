/*
  Copyright (C) Skeletex Research, s.r.o. - All Rights Reserved
  Unauthorized copying of this file, via any medium is strictly prohibited
  Proprietary and confidential
*/
#ifndef UTILS_STRONG_OPTIONAL_TYPE_H
#define UTILS_STRONG_OPTIONAL_TYPE_H

#include <optional>

#include <Utils/StrongType.h>

namespace utils
{
  /*!
    \brief
      std::optional specialization of the Strong type pattern.
    \note
      Contains value() and has_value() functions to access the underlying optional.
  */
  template <typename ValueType, typename PhantomType>
  struct StrongOptionalType
    : public utils::StrongType<std::optional<ValueType>, PhantomType>
  {
    using OptionalValueType = std::optional<ValueType>;

  public:
    using StrongType<OptionalValueType, PhantomType>::StrongType;

    StrongOptionalType<ValueType, PhantomType> &operator= (const OptionalValueType &value)
    {
      this->value_ = value;
      return *this;
    }

    //! Proxy function to access the underlying optional's has_value() function.
    bool HasValue() const { return this->value_.has_value(); }
    //! Proxy function to access the underlying optional's value() function.
    const ValueType &Value() const { return this->value_.value(); }
  };
}

#endif /* !UTILS_STRONG_OPTIONAL_TYPE_H */