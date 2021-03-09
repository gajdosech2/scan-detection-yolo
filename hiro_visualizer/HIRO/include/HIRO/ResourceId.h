/*
  Copyright (C) Skeletex Research, s.r.o. - All Rights Reserved
  Unauthorized copying of this file, via any medium is strictly prohibited
  Proprietary and confidential
*/
#ifndef HIRO_RESOURCE_ID_H
#define HIRO_RESOURCE_ID_H
#include <string>
#include <HIRO/API.h>



namespace  hiro
{

  /*!
    \brief Unique identifier for every Resource object.

    Name of identifier can be composed of a hierarchy, where each hierarchy
    object is separated by "/". For example "group/subgroup/item".
    Can be equivalently represented by an id string in format "category:name".
  */
  struct HIRO_API ResourceId
  {
    static const hiro::ResourceId INVALID; //!< Denotes invalid identifier.

    std::string name { "" };     //!< Name of a specific Resource.
    std::string category { "" }; //!< Unique identifier for each Resource class derivate.

    //! Creates an invalid identifier.
    ResourceId() = default;

    //! Creates an identifier with specified name and category.
    ResourceId(const std::string &name, const std::string &categ);

    //! Creates an identifier from id string.
    ResourceId(const std::string &string_id);

    //! Converts this to id string.
    std::string ToString() const;

    //! Checks if this is a valid identifier.
    bool IsValid() const;

    //! Makes this identifier invalid.
    void Invalidate();

    /*!
      \brief Returns name stripped of hierarchy.

      For example, returns "item" when full name is "group/subgroup/item".
    */
    std::string GetNameWithoutPath() const;

    /*!
      \brief Returns only hierarchy without a name.

      For example, returns "group/subgroup" when full name is "group/subgroup/item".
    */
    std::string GetNamePath() const;

    //! Checks whether the provided identifier is equivalent.
    bool operator==(const hiro::ResourceId &other) const;

    //! Checks whether the provided identifier is different.
    bool operator!=(const hiro::ResourceId &other) const;

    //! Checks whether the provided identifier ordering rank is higher.
    bool operator<(const hiro::ResourceId &other) const;
  };

}
#endif /* !HIRO_RESOURCE_ID_H */