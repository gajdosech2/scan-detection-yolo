/*
  Copyright (C) Skeletex Research, s.r.o. - All Rights Reserved
  Unauthorized copying of this file, via any medium is strictly prohibited
  Proprietary and confidential
*/
#ifndef COGS_OCTREE_H
#define COGS_OCTREE_H
#include <COGS/PointCloud.h>

namespace cogs
{
  //! Used internally to store the nodes of the octree.
  class OctreeNode;

  //! Space-partitioning data structure for point clouds.
  class COGS_API Octree
  {
  public:
    //! When an octree node contains this number of points or less, it does not subdivide further.
    static const uint8_t POINTS_THRESHOLD = 64;
    //! Octree destructor.
    ~Octree();
    //! Default constructor.
    Octree() = default;
    /*!
      \brief
        Constructs Octree over the given cloud.
      \param cloud
        Octree will be constructed over points of this cloud.
    */
    Octree(const cogs::PointCloud &cloud);
    /*!
      \brief
        Constructs Octree over the given vector of points.
      \param positions
        Octree will be constructed over these points.
    */
    Octree(const std::vector<glm::vec3> &positions);
    /*!
      \brief
        Adds points of the input cloud into the Octree.
      \param positions
        Points of this cloud will be included in the octree.
    */
    void Include(const cogs::PointCloud &cloud);
    /*!
      \brief
        Adds points of input clouds into the Octree.
      \param positions
        Points from all the clouds in this vector will be included in the octree.
    */
    void Include(const std::vector<const cogs::PointCloud *> &clouds);
    /*!
      \brief
        Get the string representation of this octree.
      \return
        String representation of this octree.
    */
    std::string ToString() const;
    /*!
      \brief
        Get the number of nodes in the octree.
      \return
        Node count.
    */
    size_t GetNodeCount() const;
    /*!
      \brief
        Returns the vector of bounding boxes of all internal nodes.
      \return
        Vector of bounding boxes.
    */
    std::vector<geom::Aabb3> GetNodeCubes() const;
    /*!
      \brief
        Whether any of the points exist in the range from the given location.
      \param location
        Location in the world around which will be searched.
      \param radius
        Radius range of the search area.
      \return
        True if any point is in range, false otherwise.
    */
    bool HasPointIn(const glm::vec3 &location, float_t radius) const;
    /*!
      \brief
        Whether any of the points exist inside the input AABB.
      \param search_range
        Area of this axis aligned box will be searched for points.
      \return
        True if any point is included in the input AABB, false otherwise.
    */
    bool HasPointIn(const geom::Aabb3 &search_range) const;
    /*!
      \brief
        Get indices of points in the radius from the given location.
      \param location
        Location in the world around which will be searched.
      \param radius
        Radius range of the search area.
      \return
        Vector of point indices in the area.
    */
    std::vector<uint32_t> Find(const glm::vec3 &location, float_t radius) const;
    /*!
      \brief
        Get indices of points that are inside the input AABB.
      \param search_range
        Area of this axis aligned box will be searched for points.
      \return
        Vector of point indices inside the input AABB.
    */
    std::vector<uint32_t> Find(const geom::Aabb3 &search_range) const;
    /*!
      \brief
        Check whether the input ray hits any of the points and if yes, returns the one closest to the origin.
      \param ray
        Ray casted in the world.
      \param tolerance
        Maximal distance between point and ray in order to intersect it. When set tu nullopt, automatic value is used.
      \return
        Index of the intersected point closest to the origin of the ray, -1 otherwise.
    */
    int32_t GetIntersectedPoint(const geom::Ray3 &ray, std::optional<float> tolerance = std::nullopt) const;

  private:
    //! Reference to the root of this octree.
    OctreeNode *root_ = nullptr;
    //! Initializes the root and constructs the tree.
    void InitializeRoot(const std::vector<glm::vec3> &positions);
    //! Find the maximum coordinate of the given positions.
    float_t GetMaximumExtent(const std::vector<glm::vec3> &positions) const;
    //! Find the minimum coordinate of the given positions.
    float_t GetMinimumExtent(const std::vector<glm::vec3> &positions) const;
    /*!
      \brief Whether ray intersects point at given location.

      This function compares the distance of the point to the ray and returns
      if it is under the accepted threshold. The threshold can be manually overridden.
    */
    bool RayIntersectsPoint(const geom::Ray3 &ray, const glm::vec3 &point, std::optional<float> tolerance = std::nullopt) const;
  };
}
#endif /* !COGS_OCTREE_H */