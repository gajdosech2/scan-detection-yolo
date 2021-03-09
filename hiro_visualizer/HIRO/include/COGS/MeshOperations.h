/*
  Copyright (C) Skeletex Research, s.r.o. - All Rights Reserved
  Unauthorized copying of this file, via any medium is strictly prohibited
  Proprietary and confidential
*/

#ifndef COGS_MESH_OPERATIONS_H
#define COGS_MESH_OPERATIONS_H

#include <COGS/API.h>
#include <COGS/Mesh.h>



namespace cogs
{
  /*!
    \brief A class that provides common operations over cogs::Mesh.
  */
  struct COGS_API MeshOperations
  {
    //! Check Mesh for whether it has points that are not vertices of its triangulation.
    [[nodiscard]]
    static bool HasDisconnectedPoints(const cogs::Mesh &mesh);

    /*!
      \brief
        Remove all points from the point-cloud of a specified Mesh
        so that only those that are vertices in the Mesh triangulation remain.
      \note
        Method changes the ordering of points.
      \warning
        Function does not remove invalid triangles. Its execution may still result in an invalid Mesh.
      \returns
        Success flag.
    */
    static bool RemoveDisconnectedPoints(cogs::Mesh &mesh);
  };

}

#endif /* !COGS_MESH_OPERATIONS_H */