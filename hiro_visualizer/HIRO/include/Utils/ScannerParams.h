/*
  Copyright (C) Skeletex Research, s.r.o. - All Rights Reserved
  Unauthorized copying of this file, via any medium is strictly prohibited
  Proprietary and confidential
*/

#ifndef UTILS_SCANNER_PARAMS_H
#define UTILS_SCANNER_PARAMS_H

#include <Utils/API.h>
#include <Utils/IntrinsicParams.h>

namespace utils
{
  //! Parameters of a virtual scanner.
  struct UTILS_API ScannerParams : public utils::IntrinsicParams
  {
    //! Resolution of device.
    glm::uvec2 resolution;
    //! Distance between camera and projector.
    float baseline{ 350.0f };
    //! The amount of angular deviation (degrees) of camera from being orthogonal to the device.
    float camera_angle{ 11.75f };
    //! The amount of angular deviation (degrees) of projector from being orthogonal to the device.
    float projector_angle{ 11.75f };
    //! Field of view of projection volume in x direction.
    float projector_fovx{ 47.50f };
    //! Field of view of projection volume in y direction.
    float projector_fovy{ 36.00f };
    //! The minimal distance that can be captured by scanner.
    float near_range{ 458.0f };
    //! The maximal distance that can be captured by scanner.
    float far_range{ 1118.0f };
    //! Checks validity of parameters values. If they are incorrect returns false and logs errors.
    bool IsValid() const;
    //! Fill data of this to json node.
    virtual void AddToJsonNode(nlohmann::json &node) const override;
    //! \brief Read json node and initialize this.
    //! \throws nlohmann::json::exception when required keys are missing.
    virtual bool ReadFromJsonNode(const nlohmann::json &node) override;
  };

  //! Compare equality of two parameter structures.
  UTILS_API bool operator==(const ScannerParams &p1, const ScannerParams &p2);
  //! Compare unequality of two parameter structures.
  UTILS_API bool operator!=(const ScannerParams &p1, const ScannerParams &p2);

}

#endif /* !UTILS_SCANNER_PARAMS_H */