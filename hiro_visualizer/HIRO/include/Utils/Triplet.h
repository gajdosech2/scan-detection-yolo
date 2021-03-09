/*
  Copyright (C) Skeletex Research, s.r.o. - All Rights Reserved
  Unauthorized copying of this file, via any medium is strictly prohibited
  Proprietary and confidential
*/
#ifndef UTILS_TRIPLET_H
#define UTILS_TRIPLET_H
#include <array>
#include <Utils/ExtSTD.h>

namespace utils
{

  //! Structure which holds three variables of same type.
  template <typename Type>
  class Triplet
  {
  public:

    Triplet() = default;

    Triplet(Type val_1, Type val_2, Type val_3)
    {
      Set(val_1, val_2, val_3);
    };

    //! Sets values.
    virtual void Set(Type val_1, Type val_2, Type val_3)
    {
      data_ = { val_1, val_2, val_3 };
    };

    //! Checks if at least one of the three is equal to the value.
    virtual bool Contains(const Type value) const
    {
      return std_ext::Contains(value, data_);
    };

    //! Returns reference to the value by a specified index.
    virtual Type &operator[] (size_t idx)
    {
      return data_[idx];
    };

#ifdef _WIN32
    __declspec(property(get = GetFirst, put = SetFirst)) Type a;
    __declspec(property(get = GetSecond, put = SetSecond)) Type b;
    __declspec(property(get = GetThird, put = SetThird)) Type c;
#endif // _WIN32

    //! Returns the first value.
    Type GetFirst() const
    {
      return data_[0];
    };

    //! Sets the first value.
    void SetFirst(Type value)
    {
      data_[0] = value;
    };

    //! Returns the second value.
    Type GetSecond() const
    {
      return data_[1];
    };

    //! Sets the second value.
    void SetSecond(Type value)
    {
      data_[1] = value;
    };

    //! Returns the third value.
    Type GetThird() const
    {
      return data_[2];
    };

    //! Sets the third value.
    void SetThird(Type value)
    {
      data_[2] = value;
    };

    //! Compares two triplets. The order of values is not important.
    virtual bool operator== (const Triplet<Type> &obj) const
    {
      for (const auto &val : this->data_)
      {
        if (!obj.Contains(val))
        {
          return false;
        }
      }
      return true;
    };

    //! Compares two triplets. The order of values is not important.
    virtual bool operator!= (const Triplet<Type> &obj) const
    {
      return !operator==(obj);
    };

    //! Increases all values by a specific amount.
    Triplet &operator+=(const Type val)
    {
      for (auto &data : this->data_)
      {
        data = data + val;
      }
      return *this;
    }

    //! Multiples all values with a specific value.
    Triplet &operator*=(const Type val)
    {
      for (auto &data : this->data_)
      {
        data = data * val;
      }
      return *this;
    }

  private:
    std::array<Type, 3> data_;
  };

}
#endif /* !UTILS_TRIPLET_H */