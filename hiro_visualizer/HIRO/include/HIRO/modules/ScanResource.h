/*
  Copyright (C) Skeletex Research, s.r.o. - All Rights Reserved
  Unauthorized copying of this file, via any medium is strictly prohibited
  Proprietary and confidential
*/
#ifndef HIRO_SCAN_RESOURCE_H
#define HIRO_SCAN_RESOURCE_H
#include <string>

#include <COGS/Scan.h>
#include <HIRO/modules/PointCloudResource.h>



namespace hiro::modules
{

  //! Resource that allows visualization of a cogs::PointCloud structure.
  class HIRO_API ScanResource final : public PointCloudResource
  {
  public:

    //! Constructor of Scan resource object.
    ScanResource(const std::string &name, const cogs::Scan &sc);

    //! Creates ScanGadget. Function is handled by HIRO, non accessible by user.
    PGadget CreateGadget() override;

    const glm::uvec2 &GetResolution() const;
    const cogs::ScanCameraParams &GetCameraParams() const;
    const glm::vec3 &GetCameraPosition() const;
    const glm::vec3 &GetCameraUp() const;
    const glm::mat3 &GetCameraBasis() const;
    const utils::BasisDefinition &GetBasisDefinition() const;

  private:
    glm::uvec2 resolution_;
    cogs::ScanCameraParams camera_params_;
    glm::vec3 camera_up_;
    glm::vec3 camera_pos_;
    glm::mat3 camera_basis_;
    utils::BasisDefinition camera_basis_definition_;
  };

  //! Shared pointer to an object of the type ScanResource.
  using PScanResource = std::shared_ptr<ScanResource>;

  //! Creates new point cloud resource from the specified and adds it to HIRO.
  HIRO_API PScanResource AddScan(const std::string &name, const cogs::Scan &sc);

}

#endif /* !HIRO_SCAN_RESOURCE_H */