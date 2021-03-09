/*
  Copyright (C) Skeletex Research, s.r.o. - All Rights Reserved
  Unauthorized copying of this file, via any medium is strictly prohibited
  Proprietary and confidential
*/
#ifndef COGS_SCAN_CAMERA_PARAMS_H
#define COGS_SCAN_CAMERA_PARAMS_H
#include <Utils/IntrinsicParams.h>
#include <COGS/API.h>

namespace cogs
{
  //! Parameters of a camera used to capture Scan.
  struct ScanCameraParams : public utils::IntrinsicParams
  {
    ScanCameraParams() = default;
    //! Distortion radial coefficient k1.
    float k1 = 0.0f;
    //! Distortion radial coefficient k2.
    float k2 = 0.0f;
    //! Distortion radial coefficient k3.
    float k3 = 0.0f;
    //! Distortion tangential coefficient p1.
    float p1 = 0.0f;
    //! Distortion tangential coefficient p2.
    float p2 = 0.0f;
    //! Transformation to view space of camera.
    glm::mat4 view = glm::mat4(1.0f);
  };
}

#endif /* !COGS_SCAN_CAMERA_PARAMS_H */