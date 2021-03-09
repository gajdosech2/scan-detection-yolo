/*
  Copyright (C) Skeletex Research, s.r.o. - All Rights Reserved
  Unauthorized copying of this file, via any medium is strictly prohibited
  Proprietary and confidential
*/
#ifndef UTILS_ENUM_FLAGS_H
#define UTILS_ENUM_FLAGS_H

#include <string>
#include <vector>
#include <stdexcept>
#include <cmath>

namespace utils
{

  /*!
    \brief Template implementation of Enum Flags.
    Allows the setting and checking of enum values.

    Example usage:
    \code{.cpp}
      Initialization:
        auto flags = utils::EnumFlags<EnumType>(EnumType::val1, EnumType::val2, ...);
      Setting and checking:
        flags.Set(EnumType::val3);
        bool is_val4 = flags.IsSet(EnumType::val4);
    \endcode

    The underlying enum class should have its values starting with 0 and incrementing by 1, i.e. default.
    In case of enum classes with many values, consider using a larger storage type for the bit mask - template argument TMask.
  */
  template <class T, class TMask = uint32_t>
  class EnumFlags
  {
  private:
    //! Enum type.
    using EnumType = T;
    //! Type of the bit mask that represents the flags.
    using MaskType = TMask;

  public:
    //! Constructor with no flags to be set.
    EnumFlags()
      : mask_(0)
    {
    }

    //! Variadic constructor with a variable amount of flags to be set.
    template<typename... Types>
    EnumFlags(const EnumType val1, Types ... valn)
      : mask_(initializeMask(valueToMask(val1), valueToMask(valn) ...))
    {
    }

    //! Construct from std::vector.
    EnumFlags(const std::vector<EnumType> &values)
      : EnumFlags()
    {
      for (const auto &value : values)
      {
        Set(value);
      }
    }

    //! Set a single flag.
    inline void Set(const T val);

    //! Checks whether a given flag is set.
    inline bool IsSet(const T val) const;

    //! Returns the number of flags set.
    inline uint8_t CountSet() const;

    //! Return whether there is at least one flag set.
    inline bool IsAnySet() const
    {
      return CountSet() > 0;
    }

    //! Creates a vector containing all elements set.
    inline std::vector<T> ToVector() const
    {
      std::vector<T> result;
      for (size_t i = 0; i < sizeof(TMask) * 8; ++i)
      {
        if (IsSet(static_cast<T>(i)))
        {
          result.emplace_back(static_cast<T>(i));
        }
      }
      return result;
    }

    //! Check whether the flags are exactly one single value.
    bool operator==(const T &value) const
    {
      return CountSet() == 1 && IsSet(value);
    }

    //! Check whether the flags are not exactly one single value.
    bool operator!=(const T &value) const
    {
      return !(*this == value);
    }

    //! Add other flags.
    EnumFlags<T, TMask> &operator+=(const EnumFlags<T, TMask> &other)
    {
      for (const auto value : other.ToVector())
      {
        Set(value);
      }
      return *this;
    }

  private:
    //! Compute the mask from a single enum value.
    inline typename EnumFlags<T, MaskType>::MaskType valueToMask(const T val) const
    {
      return static_cast<MaskType>(1) << static_cast<MaskType>(val);
    }

    template<typename Type>
    inline Type initializeMask(const Type val) const
    {
      CheckFlagInBounds(val, "initialize");
      return val;
    }

    template<typename Type, typename... Types>
    inline Type initializeMask(const Type val1, const Type val2, const Types ... vals) const
    {
      return initializeMask(val1 | val2, vals...);
    }

  private:
    //! Verifies that a flag can be stored within the capacity of the mask.
    template<typename Type>
    inline void CheckFlagInBounds(const Type val, const std::string &action_name) const
    {
      const auto val_t = static_cast<size_t>(val);
      if (val_t >= pow(2, sizeof(TMask) * 8))
      {
        throw std::logic_error("EnumFlags Error: attempting to " + action_name + " a flag with value out of bounds.");
      }
    }

  private:
    //! Bit mask.
    TMask mask_;
  };

  template <class T, class TMask>
  inline void EnumFlags<T, TMask>::Set(const T val)
  {
    CheckFlagInBounds(val, "set");
    mask_ |= valueToMask(val);
  }

  template <class T, class TMask>
  inline bool EnumFlags<T, TMask>::IsSet(const T val) const
  {
    CheckFlagInBounds(val, "check");
    return (mask_ & valueToMask(val)) != 0;
  }

  template <class T, class TMask>
  inline uint8_t EnumFlags<T, TMask>::CountSet() const
  {
    uint8_t count = 0;
    for (size_t i = 0; i < sizeof(TMask) * 8; ++i)
    {
      if (IsSet(static_cast<T>(i)))
      {
        ++count;
      }
    }
    return count;
  }

}
#endif /* !UTILS_ENUM_FLAGS_H */