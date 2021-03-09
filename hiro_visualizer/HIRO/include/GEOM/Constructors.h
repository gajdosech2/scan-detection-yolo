/*
  Copyright (C) Skeletex Research, s.r.o. - All Rights Reserved
  Unauthorized copying of this file, via any medium is strictly prohibited
  Proprietary and confidential
*/
#include <GEOM/API.h>
#include <Utils/GeometryStructures.h>

namespace geom
{
  //! Get Aabb3 that covers every point in the point set.
  GEOM_API Aabb3 GetAabb(const std::vector<glm::vec3> &points);

  //! Get Aabb3 that covers the entire ConicalCapsule.
  GEOM_API Aabb3 GetAabb(const ConicalCapsule &conical_capsule);

  //! Convert 3D LineSegment object to 3D Line.
  GEOM_API Line3 ToLine(const LineSegment3 &segment);

  //! Convert HalfPlane object to Plane.
  GEOM_API Plane ToPlane(const HalfPlane &halfplane);

  //! Convert 3D Triangle primitive to Plane.
  GEOM_API Plane ToPlane(const Triangle3 &triangle);
}
