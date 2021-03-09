#ifndef COGS_KD_TREE_H
#define COGS_KD_TREE_H
#include <memory>
#include <Utils/GeometryStructures.h>

#include <COGS/PointCloud.h>

namespace cogs
{
  //! Space-partitioning data structure for point clouds.
  class COGS_API KdTree
  {
  public:
    KdTree() = default;
    KdTree(const cogs::PointCloud &cloud);
    KdTree(const std::vector<const cogs::PointCloud *> clouds);
    //! Initializes the KdTree with points of the input cloud.
    void Initialize(const cogs::PointCloud &cloud);
    //! Initializes the KdTree with points of the input clouds.
    void Initialize(const std::vector<const cogs::PointCloud *> clouds);
    //! Returns true if any of included points is included in the input AABB, else returns false.
    bool IsPointInRange(const geom::Aabb3 &search_range) const;
    //! Returns vector of points that are included in the input AABB.
    void GetPointsInRange(const geom::Aabb3 &search_range, std::vector<uint32_t> *output) const;

  private:
    struct TreeNode
    {
      TreeNode() = default;
      void Include(std::vector<std::pair<uint32_t, glm::vec3>> &points, uint8_t dimension = 0);
      bool QueryRange(const geom::Aabb3 &search_range, std::vector<uint32_t> *output = nullptr) const;
    private:
      glm::vec3 value_;
      uint32_t index_;
      uint8_t depth_mod_;
      std::unique_ptr<TreeNode> l_node_ = nullptr, r_node_ = nullptr;
    };

    std::unique_ptr<TreeNode> tree_;
    uint32_t point_count_;
  };
}
#endif /* !COGS_KD_TREE_H */