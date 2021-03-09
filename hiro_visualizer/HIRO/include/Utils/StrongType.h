/*
  Copyright (C) Skeletex Research, s.r.o. - All Rights Reserved
  Unauthorized copying of this file, via any medium is strictly prohibited
  Proprietary and confidential
*/
#ifndef UTILS_STRONG_TYPE_H
#define UTILS_STRONG_TYPE_H

#include <type_traits>
#include <ostream>

namespace utils
{
  /*!
    \brief
      Template class implementation of a Named Strong Type.
    \note
      https://www.fluentcpp.com/2016/12/08/strong-types-for-strong-interfaces/
      "A strong type is a type used in place of another type to carry specific meaning through its name.
      As opposed to strong types would be general-use types, like native types such as ints and double for example.
      Often, native types do not tell much about the meaning of their instances."
      It prevents implicit conversions to and from other types, as well as comparisons to other types.

    \tparam ValueType The type of the underlying value.
    \tparam PhantomType An unused type specific for each Strong Type to ensure the Strong Type is different from every other type.
  */
  template <typename ValueType, typename PhantomType>
  struct StrongType
  {

  public:
    StrongType()
      : StrongType(static_cast<ValueType>(0))
    {}

    explicit StrongType(ValueType value)
      : value_(value)
    {}

    //! Cast to a specified type. Only work for arithmetic types.
    template <typename RT>
    inline typename std::enable_if_t<std::is_arithmetic_v<RT>, RT> As() const
    {
      return static_cast<RT>(value_);
    }

    bool operator == (const StrongType &other) const { return (value_ == other.value_); }
    bool operator != (const StrongType &other) const { return !(value_ == other.value_); }
    bool operator < (const StrongType &other) const { return (value_ < other.value_); }
    bool operator > (const StrongType &other) const { return (value_ > other.value_); }

    //! Get underlying value using the * operator.
    const ValueType &operator*() const { return value_; }

    friend std::ostream &operator<< (std::ostream &out, const StrongType<ValueType, PhantomType> &id)
    {
      out << id.value_;
      return out;
    }

  protected:
    //! The actual underlying value.
    ValueType value_;
  };
}

#endif /* !UTILS_STRONG_TYPE_H */