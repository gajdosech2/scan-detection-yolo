/*
  Copyright (C) Skeletex Research, s.r.o. - All Rights Reserved
  Unauthorized copying of this file, via any medium is strictly prohibited
  Proprietary and confidential
*/
/*
  Copyright (C) Skeletex Research, s.r.o. - All Rights Reserved
  Unauthorized copying of this file, via any medium is strictly prohibited
  Proprietary and confidential
*/
#ifndef UTILS_PROPERTY_H
#define UTILS_PROPERTY_H

#include <iostream>

namespace utils
{

    template<typename C, typename T, T (C::*getter)() const, void (C::*setter)(const T &)>
    struct Property
    {
        C *instance;

        Property(C *instance)
                : instance(instance)
        {
        }

        operator T() const
        {
            return (instance->*getter)();
        }

        Property &operator=(const T &value)
        {
            (instance->*setter)(value);
            return *this;
        }

        template<typename C2, typename T2,
                T2 (C2::*getter2)(), void (C2::*setter2)(const T2 &)>
        Property &operator=(const Property<C2, T2, getter2, setter2> &other)
        {
            return *this = (other.instance->*getter2)();
        }

        Property &operator=(const Property &other)
        {
            return *this = (other.instance->*getter)();
        }
    };

    template<typename C, typename T, T (C::*getter)() const, void (C::*setter)(T)>
    struct PropertyByValue
    {
        C *instance;

        PropertyByValue(C *instance)
                : instance(instance)
        {
        }

        operator T() const
        {
            return (instance->*getter)();
        }

        PropertyByValue &operator=(const T &value)
        {
            (instance->*setter)(value);
            return *this;
        }

        template<typename C2, typename T2,
                T2 (C2::*getter2)(), void (C2::*setter2)(T2)>
        PropertyByValue &operator=(const PropertyByValue<C2, T2, getter2, setter2> &other)
        {
            return *this = (other.instance->*getter2)();
        }

        PropertyByValue &operator=(const PropertyByValue &other)
        {
            return *this = (other.instance->*getter)();
        }
    };

}
#endif /* !UTILS_PROPERTY_H */