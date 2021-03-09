/*
  Copyright (C) Skeletex Research, s.r.o. - All Rights Reserved
  Unauthorized copying of this file, via any medium is strictly prohibited
  Proprietary and confidential
*/
#ifndef COGS_POINT_CLOUD_PROPERTY_H
#define COGS_POINT_CLOUD_PROPERTY_H
#include <string>
#include <COGS/DataType.h>

namespace cogs
{
  //! Type used to store information about property.
  struct PointCloudProperty
  {
    //! Type used to identify cloud property record.
    using Key = std::string;
    //! Unique property identifier.
    Key key;
    //! Number of bytes for each point.
    size_t bytes_per_point{ 0 };
    //! Data type of property. Optional.
    DataType type{ DataType::UNKNOWN };
    //! Pointer to property data buffer.
    void *data{ nullptr };
    //! Compares if this data type is equivalent to other. Data and key are not tested.
    bool HasEquivalentType(const PointCloudProperty &other) const;
  };
}

#endif /* !COGS_POINT_CLOUD_PROPERTY_H */