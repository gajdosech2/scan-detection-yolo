/*
  Copyright (C) Skeletex Research, s.r.o. - All Rights Reserved
  Unauthorized copying of this file, via any medium is strictly prohibited
  Proprietary and confidential
*/
#ifndef GEOM_GRAPHS_H
#define GEOM_GRAPHS_H

#include <vector>

#include <glm/glm.hpp>
//#include <Utils/Meshes.h>

#include <GEOM/API.h>

namespace geom
{

  struct GEOM_API Graph
  {
    std::vector<glm::vec3> vertices;
    std::vector<std::vector<bool>> edges;
  };

  //GEOM_API Graph MeshToGraph(const meshes::IndexedFace &mesh);

  GEOM_API void DijkstraAlgorithm(const Graph &graph, const unsigned int start_vertex, std::vector<float> &distances, std::vector<unsigned int> &previous);
  GEOM_API void DijkstraAlgorithm(const Graph &graph, const unsigned start_vertex, const std::vector<float> &vertex_weights, std::vector<float> &out_distances, std::vector<unsigned int> &out_previous);

  /* struct GEOM_API AdvancedGraph
    {
     struct Vertex
     {
       glm::vec3 position;
       std::set<Vertex *> edges;
     };

     std::vector<Vertex> vertices;

     void AddEdge(const UINT32 source, const UINT32 dest)
     {
       if (edges.find(vertices[source]))
         vertices[source].edges
       };
     void AddSymEdge(const UINT32 vert1, const UINT32 vert2);
    };*/
}


#endif /* !GEOM_GRAPHS_H */