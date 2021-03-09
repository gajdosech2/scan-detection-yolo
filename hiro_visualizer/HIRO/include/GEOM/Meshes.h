/*
  Copyright (C) Skeletex Research, s.r.o. - All Rights Reserved
  Unauthorized copying of this file, via any medium is strictly prohibited
  Proprietary and confidential
*/
#ifndef GEOM_MESHES_H
#define GEOM_MESHES_H

#include <vector>
#include <set>
#include <memory>
#include <limits>

#include <glm/glm.hpp>
//#include <Utils/Meshes.h>
#include <Utils/GeometryStructures.h>

#include <GEOM/API.h>

namespace geom
{
  //GEOM_API void ScaleMesh(meshes::IndexedFace &mesh, const glm::vec3 &scale);
  //GEOM_API void ScaleMesh(meshes::IndexedFace &mesh, const float scale);
  //GEOM_API void TranslateMesh(meshes::IndexedFace &mesh, const glm::vec3 &translation);

// calculates v surface volume of 2D triangle
  GEOM_API float GetTriangleVolume(const glm::vec2 &a, const glm::vec2 &b, const glm::vec2 &c);

// calculates v surface volume of 3D triangle
  GEOM_API float GetTriangleVolume(const glm::vec3 &a, const glm::vec3 &b, const glm::vec3 &c);

// calculate normal of triangle
  GEOM_API glm::vec3 GetTriangleNormalCW(glm::vec3 p0, glm::vec3 p1, glm::vec3 p2);
  GEOM_API glm::vec3 GetTriangleNormalCCW(glm::vec3 p0, glm::vec3 p1, glm::vec3 p2);

  //GEOM_API void CalculateTangents(std::shared_ptr<meshes::IndexedFace> &mesh);

  //GEOM_API std::vector<unsigned> GetShortestCut(const meshes::IndexedFace &mesh, const unsigned start_vert, const unsigned end_vert);
  //GEOM_API std::vector<unsigned> GetShortestCutWeighted(const meshes::IndexedFace &mesh, const unsigned start_vert, const unsigned end_vert);

  GEOM_API bool LineTriangleIntersection(const geom::Triangle3 triangle, const geom::Line3 &line, glm::vec3 &out_intersection);

  GEOM_API glm::vec3 GetCentroid(std::vector<float> &vertices);
  GEOM_API glm::vec3 GetVertexLowestY(std::vector<float> &vertices);
}
#endif /* !GEOM_MESHES_H */