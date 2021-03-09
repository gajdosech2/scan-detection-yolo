#ifndef COGS_AABB_HIERARCHY_H
#define COGS_AABB_HIERARCHY_H
#include <memory>

#include <Utils/GeometryStructures.h>
#include <COGS/API.h>

namespace cogs
{
  //template<typename T>
  //! Space-partitioning data structure for point clouds.
  class COGS_API AabbHierarchy
  {
  public:
    //typedef int(*DistributionFunc)(const T &elem1, const T &elem2); // 0 == left subtree, 1 == right_subtree, -1 == both
    //AabbHierarchy(const std::vector<T> &elements, const DistributionFunc function);
    AabbHierarchy(std::vector<geom::Triangle3> &triangles, const geom::Aabb3 &aabb);

    //! Computes first intersection of each node with the input ray and resulting intersections returns as a vector.
    void GetIntersections(const geom::Line3 &ray, std::vector<glm::vec3> *intersections) const;

  private:
    struct TreeNode
    {
      TreeNode(std::vector<geom::Triangle3> &triangles, const geom::Aabb3 &aabb, const uint8_t depth = 0, const uint8_t cycle_counter = 0);

      void GetIntersections(const geom::Line3 &ray, std::vector<glm::vec3> *intersections) const;

    private:
      const geom::Aabb3 aabb_;
      std::unique_ptr<TreeNode> l_node_ = nullptr, r_node_ = nullptr;
      std::vector<geom::Triangle3> triangles_;

      const uint8_t kMinLeafElements = 10;
    };

    std::unique_ptr<TreeNode> tree;
  };
}
#endif /* !COGS_AABB_HIERARCHY_H */