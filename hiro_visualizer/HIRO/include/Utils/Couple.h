/*
  Copyright (C) Skeletex Research, s.r.o. - All Rights Reserved
  Unauthorized copying of this file, via any medium is strictly prohibited
  Proprietary and confidential
*/
#ifndef UTILS_COUPLE_H
#define UTILS_COUPLE_H
#include <array>

namespace utils
{

  //! Structure holding two variables of the same type.
  template <typename Type>
  class Couple
  {
  public:

    Couple() = default;

    Couple(Type val_1, Type val_2)
    {
      Set(val_1, val_2);
    };

    //! Sets values.
    void Set(Type val_1, Type val_2)
    {
      data_ = { val_1, val_2 };
    };

    //! Checks if at least one of the two is equal to the value.
    bool Contains(const Type value) const
    {
      return data_[0] == value || data_[1] == value;
    };

    //! Returns reference to the value by a specified index.
    Type &operator[] (size_t idx)
    {
      return data_[idx];
    };

#ifdef _WIN32
    __declspec(property(get = GetFirst, put = SetFirst)) Type a;
    __declspec(property(get = GetSecond, put = SetSecond)) Type b;
#endif // _WIN32

    //! Returns the first value.
    const Type &GetFirst() const
    {
      return data_[0];
    };

    //! Sets the first value.
    void SetFirst(Type value)
    {
      data_[0] = value;
    };

    //! Returns the second value.
    const Type &GetSecond() const
    {
      return data_[1];
    };

    //! Sets the second value.
    void SetSecond(Type value)
    {
      data_[1] = value;
    };

    //! Compares two couples. The order of values is not important.
    bool operator== (const Couple<Type> &other)
    {
      for (auto val : data_)
      {
        if (!other.Contains(val))
        {
          return false;
        }
      }
      return true;
    };

    //! Compares two couples. The order of values is not important.
    bool operator!= (const Couple<Type> &other)
    {
      return !operator==(other);
    };

    //! Increases both values by a specific amount.
    Couple &operator+=(const Type val)
    {
      for (auto &data : this->data_)
      {
        data = data + val;
      }
      return *this;
    }

    //! Multiples both values with a specific value.
    Couple &operator*=(const Type val)
    {
      for (auto &data : this->data_)
      {
        data = data * val;
      }
      return *this;
    }

  private:
    std::array<Type, 2> data_;
  };

}
#endif /* !UTILS_COUPLE_H */