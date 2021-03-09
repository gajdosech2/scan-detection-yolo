/*
  Copyright (C) Skeletex Research, s.r.o. - All Rights Reserved
  Unauthorized copying of this file, via any medium is strictly prohibited
  Proprietary and confidential
*/
#ifndef UTILS_EXT_OMP_H
#define UTILS_EXT_OMP_H

#include <functional>



//! Extensions to OpenMP.
namespace omp_ext
{

  /*!
    \brief Transforms a container in parallel by passing each element through a callable object (function/functor).
    \note The usage is the same as std_ext::Transformed(...).
  */
  template<class C, class F>
  [[nodiscard]]
  auto Transformed(const C &container, F Function)
  {
    using RT = std::vector<decltype(Function(std::declval<typename C::value_type>()))>;

    const size_t size = container.size();
    RT result(size);

    #pragma omp parallel for
    for (int i = 0; i < static_cast<int>(size); ++i)
    {
      result[i] = Function(container[i]);
    }

    return result;
  }
}

#endif /* !UTILS_EXT_OMP_H */