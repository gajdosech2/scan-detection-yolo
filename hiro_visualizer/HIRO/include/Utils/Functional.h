/*
  Copyright (C) Skeletex Research, s.r.o. - All Rights Reserved
  Unauthorized copying of this file, via any medium is strictly prohibited
  Proprietary and confidential
*/
#ifndef UTILS_FUNCTIONAL_H
#define UTILS_FUNCTIONAL_H

#include <cstddef>

//! Contains common lambda functions.
namespace func
{
  /*!
    \brief Lambda function that uses 'GetId' function to get object's id.
    \note Applies to any object that has a GetId() function.
  */
  const auto GetId = [](const auto &obj) { return obj.GetId(); };

  /*!
    \brief Lambda function that uses 'GetId' function to get object's id.
    \note Applies to any pointer to an object that has a GetId() function.
  */
  const auto GetPtrId = [](const auto &obj) { return obj->GetId(); };

  /*!
    \brief Lambda function that gets std::optional's value.
    \note Applies to std::optional.
  */
  const auto OptValue = [](const auto &obj) { return obj.value(); };

  /*!
    \brief Lambda function that returns whether a std::optional has value.
    \note Applies to std::optional.
  */
  const auto OptHasValue = [](const auto &obj) { return obj.has_value(); };

  /*!
    \brief Lambda function that casts the object to bool.
    \note Applies to all objects that can be cast/compared to bool.
  */
  const auto Is = [](const auto &obj)->bool { return obj; };

  /*!
    \brief Lambda function that return whether the object is null pointer.
    \note Applies to pointers.
  */
  const auto IsNullptr = [](const auto &obj)->bool { return obj == nullptr; };

  /*!
    \brief Lambda function that return whether the object is not a null pointer.
    \note Applies to pointers.
  */
  const auto IsNotNullptr = [](const auto &obj)->bool { return obj != nullptr; };

  /*!
    \brief Lambda function that returns whether the object is empty.
    \note Applies to any object that has an empty() function. (std::vector, std::string...).
  */
  const auto IsEmpty = [](const auto &obj)->bool { return obj.empty(); };

  /*!
    \brief Lambda function that returns whether the object is not empty.
    \note Applies to any object that has an empty() function. (std::vector, std::string...).
  */
  const auto IsNotEmpty = [](const auto &obj)->bool { return !obj.empty(); };

  /*!
    \brief Lambda function that returns the size of an object.
    \note Applies to any object that has a size() function. (std::vector...).
  */
  const auto GetSize = [](const auto &obj)->std::size_t { return obj.size(); };

  /*!
    \brief Lambda function that returns the first element in a pair.
    \note applies to std::pair.
  */
  const auto GetFirst = [](const auto &pair) { return pair.first; };

  /*!
    \brief Lambda function that returns the second element in a pair.
    \note applies to std::pair.
  */
  const auto GetSecond = [](const auto &pair) { return pair.second; };

  /*!
    \brief Lambda function that performs a callback on an if it is nor null. Otherwise it ignores it.
  */
  const auto IfNotNull = [](const auto &obj_ptr, const auto Func) { if (obj_ptr != nullptr) { Func(*obj_ptr); } };

  //! \brief Lambda function that return the x value of an object.
  const auto GetX = [](const auto &o) { return o.x; };

  //! \brief Lambda function that return the x value of an object.
  const auto GetY = [](const auto &o) { return o.y; };

  //! \brief StaticCast a value to a different type.
  template<typename TypeIn, typename TypeOut>
  const auto StaticCast = [](const TypeIn &value) { return static_cast<TypeOut>(value); };
}

#endif /* !UTILS_FUNCTIONAL_H */