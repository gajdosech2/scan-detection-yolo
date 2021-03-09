/*
  Copyright (C) Skeletex Research, s.r.o. - All Rights Reserved
  Unauthorized copying of this file, via any medium is strictly prohibited
  Proprietary and confidential
*/
#ifndef GEOM_TRIANGULATION_H
#define GEOM_TRIANGULATION_H
#include <vector>

#include <glm/glm.hpp>

#include <GEOM/API.h>

namespace cogs
{
  class IndexedFace;
}

namespace geom
{
#ifdef FADE_ENABLE
  GEOM_API std::vector<glm::uvec3> ComputeLocalDelaunayTriangulation(int i, const std::vector<glm::vec2> &points, const std::vector<uint32_t> &local_neighbours);
  GEOM_API std::vector<glm::uvec3> GetDelaunayTrinagulation(const std::vector<glm::vec3> &points, const std::vector<std::vector<uint32_t>> &point_neighbours);
#endif // FADE_ENABLE
}
#endif /* !GEOM_TRIANGULATION_H */