/*
  Copyright (C) Skeletex Research, s.r.o. - All Rights Reserved
  Unauthorized copying of this file, via any medium is strictly prohibited
  Proprietary and confidential
*/
#ifndef HIRO_POINT_CLOUD_RESOURCE_H
#define HIRO_POINT_CLOUD_RESOURCE_H
#include <string>

#include <COGS/PointCloud.h>
#include <HIRO_DRAW/renderers/PointCloudRenderer.h>
#include <HIRO/Resource.h>



namespace hiro::modules
{

  //! Resource that allows visualization of a cogs::PointCloud structure.
  class HIRO_API PointCloudResource : public hiro::Resource
  {
  public:

    //! Holds information about a vertex float data  record.
    struct DataRecord
    {
      //! Data array.
      std::vector<float> data;
      //! Minimal value from the data array.
      float min;
      //! Maximal value from the data array.
      float max;
    };

    /*!
      \brief Constructor of PointcloudUnit
      \param name
      The name of the point cloud.
      \param pc
      Input data as PointCloud.
    */
    PointCloudResource(const std::string &name, const cogs::PointCloud &pc);

    //! Creates PointCloudGadget. Function is handled by HIRO, non accessible by user.
    hiro::PGadget CreateGadget() override;

    //! Returns number of points.
    uint32_t GetPointCount() const;

    //! Returns a PointCloudObject pointer.
    hiro::draw::PPointCloudRenderer GetRenderer() const;

    //! Returns calculated center of mass.
    glm::vec3 GetCenterOfMass() const;

    //! Returns approximation of object radius around center of mass.
    float GetApproxRadius() const;

    //! Returns if coloring options for points are available.
    bool IsColoringAvailable() const;

    /*!
      \brief Returns current coloring option.
      It returns available RGB color values for one point with given id.
      \param id
      id of the given point
    */
    const std::vector<cogs::Color3f> *GetColoringOption(const uint32_t id) const;

    //! Returns names of coloring properties.
    const std::vector<std::string> GetColoringOptionNames() const;

    //! Returns if any float data for points are available.
    bool HasFloatData() const;

    /*!
      \brief Returns a DataRecord value for point.
      It returns available DataRecord value for one point with given id.
      \param id
      id of the given point
    */
    const hiro::modules::PointCloudResource::DataRecord *GetFDataOption(const uint32_t id) const;

    //! Returns names of float data properties.
    const std::vector<std::string> GetFDataOptionNames() const;

    //! Returns if normal vectors for points are available.
    bool HasNormals() const;

    //! Returns string id of point cloud space.
    std::string GetSpaceId() const;

    //! Returns point space if defined.
    std::optional<utils::SpaceDefinition> GetSpace() const;


  protected:
    PointCloudResource(const hiro::ResourceId &id);
    hiro::draw::PPointCloudRenderer vis_object_{ nullptr };
    uint32_t point_count_{ 0u };
    void StoreData(const cogs::PointCloud &pc);

  private:
    void CalculateCenterOfMass(const cogs::PointCloud &pc);
    std::optional<utils::SpaceDefinition> space_;
    bool has_normals_;
    glm::vec3 center_of_mass_;
    float aprox_radius_;
    std::vector<std::vector<cogs::Color3f>> coloring_options_;
    std::vector<std::string> coloring_option_names_;
    std::vector<hiro::modules::PointCloudResource::DataRecord> fdata_options_;
    std::vector<std::string> fdata_option_names_;
  };

  //! Shared pointer to an object of the type PointCloudResource.
  using PPointCloudResource = std::shared_ptr<hiro::modules::PointCloudResource>;

  //! Creates new point cloud resource from the specified and adds it to HIRO.
  HIRO_API PPointCloudResource AddPointCloud(const std::string &name, const cogs::PointCloud &pc);

}

#endif /* !HIRO_POINT_CLOUD_RESOURCE_H */