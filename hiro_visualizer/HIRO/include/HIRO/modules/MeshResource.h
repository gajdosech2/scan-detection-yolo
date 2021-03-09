/*
  Copyright (C) Skeletex Research, s.r.o. - All Rights Reserved
  Unauthorized copying of this file, via any medium is strictly prohibited
  Proprietary and confidential
*/
#ifndef HIRO_MESH_RESOURCE_H
#define HIRO_MESH_RESOURCE_H
#include <string>

#include <COGS/Mesh.h>
#include <HIRO_DRAW/renderers/MeshRenderer.h>
#include <HIRO/Resource.h>


namespace hiro::modules
{

  //! Resource that allows visualization of a cogs::Mesh structure.
  class HIRO_API MeshResource final : public hiro::Resource
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
      \brief
        Constructor of mesh resource
      \param name
        The name of the mesh.
      \param mesh
        Input mesh data.
    */
    MeshResource(const std::string &name, const cogs::Mesh &mesh);

    //! Returns number of faces.
    uint32_t GetFaceCount() const;

    //! Returns material assigned to mesh.
    const cogs::MaterialModel *GetMaterial() const;

    //! Creates Gadget for this Resource object.
    hiro::PGadget CreateGadget() override;

    //! Returns number of points.
    uint32_t GetPointCount() const;

    //! Returns a PointCloudObject pointer.
    const hiro::draw::PMeshRenderer &GetRenderer() const;

    //! Returns calculated center of mass.
    const glm::vec3 &GetCenterOfMass() const;

    //! Returns camera position based on center of mass.
    const glm::vec3 &GetCameraPos() const;

    //! Returns if uvs are available for a mesh.
    bool IsUvMappingAvailable() const;

    //! Returns if coloring options for points are available.
    bool IsColoringAvailable() const;

    /*!
      \brief Returns current coloring option.
      It returns available RGB color values for one point with given id.
      \param id
      id of the given point
    */
    const std::vector<cogs::Color3f> &GetColoringOption(const size_t id) const;

    //! Returns names of coloring properties.
    const std::vector<std::string> &GetColoringOptionNames() const;

    //! Returns if float data for points is available.
    bool IsFDataAvailable() const;

    /*!
      \brief Returns a DataRecord value for point.
      It returns available DataRecord value for one point with given id.
      \param id
      id of the given point
    */
    const hiro::modules::MeshResource::DataRecord &GetFDataOption(const size_t id) const;

    //! Returns names of float data properties.
    const std::vector<std::string> &GetFDataOptionNames() const;

    //! Returns string id of point space.
    std::string GetSpaceId() const;

    //! Returns point space if defined.
    std::optional<utils::SpaceDefinition> GetSpace() const;


  protected:

    uint32_t face_count_{ 0u };
    uint32_t point_count_{ 0u };
    std::unique_ptr<cogs::MaterialModel> material_;

    bool is_uv_mapping_available_;
    glm::vec3 center_of_mass_, camera_pos_;
    std::vector<std::vector<cogs::Color3f>> coloring_options_;
    std::vector<std::string> coloring_option_names_;
    std::vector<hiro::modules::MeshResource::DataRecord> fdata_options_;
    std::vector<std::string> fdata_option_names_;
    std::optional<utils::SpaceDefinition> space_;

    hiro::draw::PMeshRenderer renderer_;

    void StoreNeededData(const cogs::Mesh &mesh);
    void CalculateCenterOfMass(const cogs::Mesh &mesh);
  };

  //! Shared pointer to an object of the type MeshResource.
  using PMeshResource = std::shared_ptr<hiro::modules::MeshResource>;

  //! Creates new mesh resource from the specified and adds it to HIRO.
  HIRO_API hiro::modules::PMeshResource AddMesh(const std::string &name, const cogs::Mesh &mesh);

}

#endif /* !HIRO_MESH_RESOURCE_H */