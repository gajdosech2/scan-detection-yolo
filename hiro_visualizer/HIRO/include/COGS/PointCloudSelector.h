/*
  Copyright (C) Skeletex Research, s.r.o. - All Rights Reserved
  Unauthorized copying of this file, via any medium is strictly prohibited
  Proprietary and confidential
*/
#ifndef COGS_POINT_CLOUD_SELECTOR_H
#define COGS_POINT_CLOUD_SELECTOR_H

#include <COGS/Octree.h>
#include <COGS/PointCloud.h>

namespace cogs
{
  //! API for selecting points from a point cloud by ray-casting.
  class COGS_API PointCloudSelector
  {
  public:
    //! Default constructor.
    PointCloudSelector() = default;
    /*!
      \brief
         Prepares the selector to be used over the given point cloud.
      \param pointcloud
         Selector will work with this point cloud.
    */
    PointCloudSelector(std::shared_ptr<cogs::PointCloud> pointcloud);
    /*!
      \brief
         Initializes the selector over new point cloud, forgetting the reference and selected points of old one (if any).
      \param pointcloud
         Selector will work with this point cloud.
    */
    void Initialize(std::shared_ptr<cogs::PointCloud> pointcloud);
    //! Returns current number of selected points.
    size_t CountSelected() const;
    /*!
      \brief
        Selects a point of point cloud based on the ray intersection with it.
      \param ray
        3D ray in the point cloud space.
      \param selection_radius
        When greater then zero, also points around the intersected point are selected up to the distance.
      \return
        Index of the intersected point, -1 if no point was intersected.
    */
    int32_t SelectPoint(const geom::Ray3 &ray);
    /*!
      \brief
        Deselects a point of point cloud based on the ray intersection with it.
      \param ray
        3D ray in the point cloud space.
      \param selection_radius
        When greater then zero, also points around the intersected point are deselected up to the distance.
      \return
        Index of the intersected point, -1 if no point was intersected.
    */
    int32_t DeselectPoint(const geom::Ray3 &ray);
    /*!
      \brief
        Internally selects the point with given index.
      \param point_index
        Index of the point to select.
    */
    void SelectPoint(int32_t point_index);
    /*!
      \brief
        Internally deselects the point with given index.
      \param point_index
        Index of the point to deselect.
    */
    void DeselectPoint(int32_t point_index);
    /*!
      \brief
        Selects the points around the target point in a specified radius,
    		including the target point.
      \param point_index
        Index of the point to select.
    	\param selection_radius
        Maximal distance from target point.
    */
    void SelectPointsAround(int32_t point_index, float selection_radius);
    /*!
      \brief
        Deselects the points around the target point in a specified radius,
    		including the target point.
      \param point_index
        Index of the point to deselect.
    	\param selection_radius
        Maximal distance from target point.
    */
    void DeselectPointsAround(int32_t point_index, float deselection_radius);
    //! Deselect all previously selected points.
    void DeselectAllPoints();
    /*!
      \brief
        Returns the list of all previously selected points.
      \return
        Vector of selected points.
    */
    const std::set<int32_t> &GetSelectedPoints() const;

  private:
    std::shared_ptr<cogs::PointCloud> pointcloud_;
    cogs::Octree octree_;
    std::set<int32_t> selected_points_;
  };
}

#endif /* !COGS_POINT_CLOUD_SELECTOR_H */