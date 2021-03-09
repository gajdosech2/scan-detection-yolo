#ifndef GEOM_PROCEDURAL_H
#define GEOM_PROCEDURAL_H
#include <vector>
#include <glm/common.hpp>
#include <GEOM/API.h>

namespace geom
{
  //! Generator of UV sphere geometry.
  class GEOM_API UvSphereGenerator
  {
  public:
    //! Construct generator. Higher values of smoothness parameter increase the vertex count.
    UvSphereGenerator(uint32_t smoothness = 8);
    //! Generates point positions for a specified sphere center and radius.
    std::vector<glm::vec3> GenVertices(const glm::vec3 &center, float radius) const;
    //! Generates triangle indices defining point connectivity.
    std::vector<glm::uvec3> GenIndices() const;
  private:
    uint32_t smoothness_{ 8 };
  };
}
#endif /* !GEOM_PROCEDURAL_H */