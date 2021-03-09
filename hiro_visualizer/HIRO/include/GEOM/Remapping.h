/*
  Copyright (C) Skeletex Research, s.r.o. - All Rights Reserved
  Unauthorized copying of this file, via any medium is strictly prohibited
  Proprietary and confidential
*/
#ifndef GEOM_REMAPPING_H
#define GEOM_REMAPPING_H

#include <iostream>
#include <vector>
#include <map>

#include <glm/glm.hpp>
#include <Eigen/Dense>
//#include <Utils/Meshes.h>
#include <Utils/ExtGLM.h>

#include <GEOM/API.h>
#include <GEOM/Geometry.h>

namespace geom
{

  /*typedef std::vector<float>(*WeightFunc)(const meshes::IndexedFace &region, const unsigned &vertex_index, const std::vector<unsigned> &neighbours);

    namespace weightFunc
    {
    GEOM_API std::vector<float> DefaultBarycentric(const meshes::IndexedFace &region, const unsigned &vertex_index, const std::vector<unsigned> &neighbours);
    GEOM_API std::vector<float> CorrectedBarycentric(const meshes::IndexedFace &region, const unsigned &vertex_index, const std::vector<unsigned> &neighbours);
    GEOM_API std::vector<float> CorrectedBarycentric2(const meshes::IndexedFace &region, const unsigned &vertex_index, const std::vector<unsigned> &neighbours);
    GEOM_API std::vector<float> CorrectedBarycentric3(const meshes::IndexedFace &region, const unsigned &vertex_index, const std::vector<unsigned> &neighbours);
    GEOM_API std::vector<float> MeanValue(const meshes::IndexedFace &region, const unsigned &vertex_index, const std::vector<unsigned> &neighbours);
    GEOM_API std::vector<float> DiscreteLaplacian(const meshes::IndexedFace &region, const unsigned &vertex_index, const std::vector<unsigned> &neighbours);
    }

    GEOM_API bool RefineRegionUVs(meshes::IndexedFace &region, WeightFunc weight_function);

    GEOM_API void RefineRegionUVsHolidayBarycentric(meshes::IndexedFace &region, const float &max_tolerated_error);*/
}

#endif /* !GEOM_REMAPPING_H */