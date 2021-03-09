/*
  Copyright (C) Skeletex Research, s.r.o. - All Rights Reserved
  Unauthorized copying of this file, via any medium is strictly prohibited
  Proprietary and confidential
*/
#ifndef UTILS_EXT_CV_H
#define UTILS_EXT_CV_H
#include <opencv2/opencv.hpp>
#include <COGS/Color.h>



//! Extensions to the OpenCV library.
namespace cv_ext
{

  inline glm::vec3 ToVec3(const cv::Point3f &vec)
  {
    return glm::vec3(vec.x, vec.y, vec.z);
  }

  inline cv::Point3f ToCvPoint3f(const glm::vec3 &vec)
  {
    return cv::Point3f(vec.x, vec.y, vec.z);
  }

  inline cv::Point3f ToCvPoint3f(const cogs::Color3f &color)
  {
    return cv::Point3f(color.r, color.g, color.b);
  }

}

#endif /* !UTILS_EXT_CV_H */