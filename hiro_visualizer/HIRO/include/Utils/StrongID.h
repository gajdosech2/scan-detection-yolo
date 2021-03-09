/*
  Copyright (C) Skeletex Research, s.r.o. - All Rights Reserved
  Unauthorized copying of this file, via any medium is strictly prohibited
  Proprietary and confidential
*/
#ifndef UTILS_STRONG_ID_H
#define UTILS_STRONG_ID_H
#include <vector>
#include <string>
#include <Utils/StrongType.h>
#include <Utils/ExtSTD.h>



namespace utils
{
  /*!
    \brief
      Template class implementation of a Named Strong Id (a Strong Type with an underlying unsigned integer type (uint32_t)).
    \note
      https://www.fluentcpp.com/2016/12/08/strong-types-for-strong-interfaces/
      Strong Id is an integral type (uint32_t) specific for the given usage (usually as an id of a class).
      It prevents implicit conversions to and from other types, as well as comparisons to other types.

    \tparam PhantomType An unused type specific for each Strong Type to ensure the Strong Type is different from every other type.
  */
  template <typename PhantomType>
  struct StrongId : public StrongType<uint32_t, PhantomType>
  {
  public:
    using ValueType = uint32_t;

    //! Use base class constructor.
    using StrongType<ValueType, PhantomType>::StrongType;

    //! Construct from size_t.
    explicit StrongId(size_t value)
      : StrongType<ValueType, PhantomType>(static_cast<ValueType>(value))
    {}

    //! Construct from int.
    explicit StrongId(int value)
      : StrongType<ValueType, PhantomType>(static_cast<ValueType>(value))
    {}


    //! An id following this one. Incremented by 1.
    inline StrongId Next() const
    {
      return StrongId(this->template As<ValueType>() + 1);
    }

    //! Convert the id to string.
    inline std::string ToString() const
    {
      return std::to_string(this->template As<ValueType>());
    }


    //! Creates vector of specific strong ids values from the vector of unsigned values.
    static inline std::vector<StrongId<PhantomType>> CreateIds(const std::vector<unsigned> &ids)
    {
      return std_ext::Transformed(ids, [](const auto & id) { return StrongId<PhantomType>(id); });
    }
  };
}

#endif /* !UTILS_STRONG_ID_H */