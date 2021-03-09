/*
  Copyright (C) Skeletex Research, s.r.o. - All Rights Reserved
  Unauthorized copying of this file, via any medium is strictly prohibited
  Proprietary and confidential
*/
#ifndef GEOM_GEOMETRY_H
#define GEOM_GEOMETRY_H

#include <Utils/GeometryStructures.h>

#include <GEOM/API.h>

namespace geom
{
  //! Inflate each side of the rectangle by specified margin.
  template <typename T>
  void InflateRectangle(geom::TRect<T> &rect, const T margin)
  {
    rect.x -= margin;
    rect.y -= margin;
    rect.width += static_cast<T>(2) * margin;
    rect.height += static_cast<T>(2) * margin;
  }

  //! Deflate each side of the rectangle by specified margin.
  template <typename T>
  void DeflateRectangle(geom::TRect<T> &rect, const T margin)
  {
    rect.x += margin;
    rect.y += margin;
    rect.width -= static_cast<T>(2) * margin;
    rect.height -= static_cast<T>(2) * margin;
  }

  //! Fit a 3D plane to the point set.
  GEOM_API Plane FitPlane(const std::vector<glm::vec3> &points);

  //! Calculate mean point of the point set.
  GEOM_API glm::vec3 GetCentroid(const std::vector<glm::vec3> &points);

  /*!
      \brief    Calculate interpolation parameter of point projection onto the line segment.
      \return   Parameter value between -inf and inf.

      Resulting parameter of value 0 tells the projection lays on segment line point1,
      and value 1 tells the projection lays on segment line point2.
      Anything between 0 and 1 tells the point projection lays directly on line segment */
  GEOM_API float GetProjectionParameter(const glm::vec3 &point, const geom::LineSegment3 &line_segment);

  /*!
      \brief    Calculate interpolation parameter of point projection onto the line segment.
      \return   Parameter value between 0 and 1.

      Resulting parameter of value 0 tells the projection lays on segment line point1,
      and value 1 tells the projection lays on segment line point2.
      Anything between 0 and 1 tells the point projection lays directly on line segment */
  GEOM_API float GetProjectionParameterClamped(const glm::vec3 &point, const geom::LineSegment3 &line_segment);

  //! Calculates the oriented distance of point to a plane. The value is positive if the point lies in the half-space pointed to by the plane normal.
  GEOM_API float GetOrientedDistance(const glm::vec3 &point, const Plane &plane);

  //! Calculates a distance of the point to the 3D line segment.
  GEOM_API float GetDistance(const glm::vec3 &point, const geom::LineSegment3 &line);

  //! Calculate the distance of the point from the plane.
  GEOM_API float GetDistance(const glm::vec3 &point, const Plane &plane);

  //! Calculate the distance of the point from the 3D line.
  GEOM_API float GetDistance(const glm::vec3 &point, const geom::Line3 &line);

  /*!
    \brief    Calculate distance of point to the capsule surface.
    \return   Negative distance when point is inside capsule,
              zero when it is on surface and positive value otherwise. */
  GEOM_API float GetDistance(const glm::vec3 &point, const ConicalCapsule &conical_capsuile);

  //! Calculate projection of point onto a plane.
  GEOM_API glm::vec3 GetProjection(const glm::vec3 &point, const Plane &plane);

  //! Calculate projection of point onto a line segment in 3D.
  GEOM_API glm::vec3 GetProjection(const glm::vec3 &point, const LineSegment3 &line_segment);

  //! Calculate projection of point onto a line in 3D.
  GEOM_API glm::vec3 GetProjection(const glm::vec3 &point, const Line3 &line);

  //! Calculate projection of point onto a ConicalCapsule.
  GEOM_API glm::vec3 GetProjection(const glm::vec3 &point, const ConicalCapsule &capsule);

  //! Get intersection point between two 2D planes.
  GEOM_API std::optional<glm::vec2> GetIntersection(const geom::Line2 &line1, const geom::Line2 &line2);

  GEOM_API bool GetIntersection(const geom::Line2 &line1, const geom::Line2 &line2, glm::vec2 *out_intersection_point);
  GEOM_API bool GetIntersection(const geom::Line3 &line, const geom::Plane &plane, glm::vec3 *out_intersection_point);
  GEOM_API bool GetIntersection(const geom::LineSegment3 &linesegment, const geom::Plane &plane, glm::vec3 *out_intersection_point);
  GEOM_API bool GetIntersection(const geom::Line3 &line, const geom::HalfPlane &half_plane, glm::vec3 *out_intersection_point);
  GEOM_API bool GetIntersection(const geom::LineSegment3 &linesegment, const geom::HalfPlane &half_plane, glm::vec3 *out_intersection_point);
  GEOM_API bool GetIntersection(const geom::Triangle3 &triangle, const geom::HalfPlane &halfplane, geom::LineSegment3 *out_intersection = nullptr);
  GEOM_API bool GetIntersection(const geom::Line3 &line, const geom::Aabb3 &aabb);

  GEOM_API glm::vec3 Barycentric(const glm::vec3 &p, const Triangle3 &triangle);

  struct CollisionResult
  {
  public:
    bool is_collision;
    glm::vec3 point1;
    glm::vec3 point2;
    float param1;
    float param2;
    float depth;
  };

  GEOM_API CollisionResult GetCollision(const geom::Capsule &capsule_1, const geom::Capsule &capsule_2);

  GEOM_API bool IsTriangleFacingToPoint(const glm::vec3 &point, const geom::Triangle3 &triangle);
}
#endif /* !GEOM_GEOMETRY_H */