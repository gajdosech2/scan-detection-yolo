/*
  Copyright (C) Skeletex Research, s.r.o. - All Rights Reserved
  Unauthorized copying of this file, via any medium is strictly prohibited
  Proprietary and confidential
*/
#ifndef CONVERSIONS_PCL_CONVERSIONS_H
#define CONVERSIONS_PCL_CONVERSIONS_H

#include <pcl/recognition/point_types.h>
#include <glm/common.hpp>
#include <Utils/ExtGLM.h>
#include <COGS/API.h>
#include <COGS/Scan.h>


namespace cogs
{
  namespace conversions
  {

    //! Extract position from pcl point.
    inline glm::vec3 PclToPosition(const pcl::PointXYZINormal &point)
    {
      return glm::vec3(point.x, point.y, point.z);
    }

    //! Extract normal vector from pcl point.
    inline glm::vec3 PclToNormal(const pcl::PointXYZINormal &point)
    {
      return glm::vec3(point.normal_x, point.normal_y, point.normal_z);
    }

    //! Extract intensity from pcl point.
    inline float PclToIntensity(const pcl::PointXYZINormal &point)
    {
      return point.intensity;
    }

    //! Convert cogs::Scan to pcl::PointCloud.
    COGS_API pcl::PointCloud<pcl::PointXYZINormal> CogsScanToPcl(const cogs::Scan &scan);

    //! Converts pcl::PointCloud to cogs::PointCloud.
    COGS_API void PclToCogsPointCloud(
      const pcl::PointCloud<pcl::PointXYZINormal> &pcl_cloud,
      std::optional<utils::SpaceDefinition> space_definition,
      cogs::PointCloud &out_cloud);

    //! Converts pcl::PointCloud to cogs::Scan.
    COGS_API bool PclToCogsScan(
      const pcl::PointCloud<pcl::PointXYZINormal> &pcl_cloud,
      utils::SpaceDefinition camera_space_definition,
      const cogs::ScanCameraParams &camera_params,
      cogs::Scan &out_scan);
  }
}
#endif /* !CONVERSIONS_PCL_CONVERSIONS_H */