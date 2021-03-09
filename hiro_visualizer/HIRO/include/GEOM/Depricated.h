/*
  Copyright (C) Skeletex Research, s.r.o. - All Rights Reserved
  Unauthorized copying of this file, via any medium is strictly prohibited
  Proprietary and confidential
*/
#ifndef GEOM_DEPRICATED_H
#define GEOM_DEPRICATED_H

#include <vector>
#include <memory>

#include <glm/glm.hpp>

#include <GEOM/API.h>

namespace geom
{
  GEOM_API void CalculatePCA(const std::vector<glm::vec3> &vertices, std::vector<glm::vec3> &principalComponents, glm::vec3 &pointCloudCenter);
  GEOM_API void GetTangentPlanePCA(const std::vector<glm::vec3> &points, glm::vec3 &nn, glm::vec3 &ev_1, glm::vec3 &ev_2, glm::vec3 &ev_3);

  GEOM_API void PlaneProjectionUsingPCA(const std::vector<glm::vec3> &points, std::vector<float> &pointsInPlane, std::vector<float> &vec1, std::vector<float> &vec2);
  GEOM_API glm::vec3 ProjectPointIntoPlane(const glm::vec3 &q, const glm::vec3 &o, const glm::vec3 &n);
  GEOM_API glm::vec2 Space2Plane(const glm::vec3 &q, const glm::vec3 &o, const glm::vec3 &e1, const glm::vec3 &e2);
  GEOM_API glm::vec3 Plane2Space(const glm::vec2 &q, const glm::vec3 &o, const glm::vec3 &e1, const glm::vec3 &e2);

  GEOM_API float DeterminantInPlane(const glm::vec3 &vVector1, const glm::vec3 &vVector2, const glm::vec3 &vVector3);
}
#endif /* !GEOM_DEPRICATED_H */