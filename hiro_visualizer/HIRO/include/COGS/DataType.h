#ifndef COGS_DATA_TYPE_H
#define COGS_DATA_TYPE_H
#include <COGS/API.h>
#include <cstddef>



namespace cogs
{
  //! Identifier of data types.
  enum class DataType
  {
    //! undefined type
    UNKNOWN,
    //! standard float.
    FLOAT,
    //! 2*float = glm::vec2.
    FVEC3,
    //! 3*float = glm::vec3.
    FVEC2,
    //! cogs::Color3f
    COLOR3F,
    //! cogs::Color4f
    COLOR4F
  };

  //! Returns size of type denoted by DataType identifier.
  COGS_API std::size_t GetDataTypeSize(const DataType &dtype);
}
#endif /* !COGS_DATA_TYPE_H */