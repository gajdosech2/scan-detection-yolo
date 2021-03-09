/*
  Copyright (C) Skeletex Research, s.r.o. - All Rights Reserved
  Unauthorized copying of this file, via any medium is strictly prohibited
  Proprietary and confidential
*/

#ifndef UTILS_INTRINSIC_PARAMS_H
#define UTILS_INTRINSIC_PARAMS_H

#include <string>
#include <glm/common.hpp>
#include <glm/trigonometric.hpp>

#include <Utils/API.h>
#include <Utils/SerializableJson.h>

namespace utils
{
  /*!
    \brief Holds camera intrinsic projection parameters.

    More information about intrinsic camera parameters can be found on Wikipedia
    https://en.wikipedia.org/wiki/Camera_resectioning and distortion coefficients
    at https://docs.opencv.org/2.4/doc/tutorials/calib3d/camera_calibration/camera_calibration.html
  */
  struct UTILS_API IntrinsicParams : public utils::SerializableJson
  {
    //! Focal length in terms of pixels.
    float fx{ 0.0f }, fy{ 0.0f };
    //! Principal point coordinates. Ideally in the center of the image.
    float cx{ 0.0f }, cy{ 0.0f };

    IntrinsicParams() = default;
    IntrinsicParams(float t_fx, float t_fy, float t_cx, float t_cy)
      : fx(t_fx), fy(t_fy), cx(t_cx), cy(t_cy) {}

    //! Calculates horizontal field of view. In radians.
    float GetFovX() const
    {
      return 2.0f * glm::atan(cx / fx);
    }
    //! Calculates vertical field of view. In radians.
    float GetFovY() const
    {
      return 2.0f * glm::atan(cy / fy);
    }
    //! Fill data of this to json node.
    virtual void AddToJsonNode(nlohmann::json &node) const override;
    //! \brief Read json node and initialize this.
    //! \throws nlohmann::json::exception when required keys are missing.
    virtual bool ReadFromJsonNode(const nlohmann::json &node) override;
  };

  //! Returns intrinsic cx, cy parameters for defined projection depth and field of view angles.
  inline glm::vec2 GetPrincipalPoint(float focal_length, float fovx, float fovy)
  {
    return glm::vec2(
        focal_length * glm::tan(0.5f * fovx),
        focal_length * glm::tan(0.5f * fovy)
      );
  }

  //! Calculates intrinsic projection parameters from resolution and field of view angles.
  inline IntrinsicParams GetIntrinsicParamsFromResolution(const glm::uvec2 &resolution, float fovx, float fovy)
  {
    const auto cx = 0.5f * static_cast<float>(resolution.x);
    const auto cy = 0.5f * static_cast<float>(resolution.y);
    const auto fx = cx / glm::tan(0.5f * fovx);
    const auto fy = cy / glm::tan(0.5f * fovy);
    return IntrinsicParams(fx, fy, cx, cy);
  }

  //! Calculates intrinsic projection parameters from projection depth and field of view angles.
  inline IntrinsicParams GetIntrinsicParamsFromDepth(float focal_length, float fovx, float fovy)
  {
    const auto c = GetPrincipalPoint(focal_length, fovx, fovy);
    const auto fx = c.x / glm::tan(0.5f * fovx);
    const auto fy = c.y / glm::tan(0.5f * fovy);
    return IntrinsicParams(fx, fy, c.x, c.y);
  }

  //! Compare equality of two parameter structures.
  UTILS_API bool operator==(const IntrinsicParams &p1, const IntrinsicParams &p2);
  //! Compare unequality of two parameter structures.
  UTILS_API bool operator!=(const IntrinsicParams &p1, const IntrinsicParams &p2);

}
#endif /* !UTILS_INTRINSIC_PARAMS_H */