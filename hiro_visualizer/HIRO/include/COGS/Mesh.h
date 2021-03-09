/*
  Copyright (C) Skeletex Research, s.r.o. - All Rights Reserved
  Unauthorized copying of this file, via any medium is strictly prohibited
  Proprietary and confidential
*/
#ifndef COGS_MESH_H
#define COGS_MESH_H
#include <memory>

#include <COGS/PointCloud.h>
#include <COGS/Triangulation.h>
#include <COGS/MaterialModel.h>
#include <COGS/API.h>

namespace cogs
{
  /*!
    \brief A Mesh is structure containing a point-cloud a triangulation and a material. Not all of these are required.
    \note Each of the point-cloud, faces or material may be undefined.
  */
  struct COGS_API Mesh
  {
  public:
    std::shared_ptr<PointCloud> points;
    std::shared_ptr<Triangulation> faces;
    std::shared_ptr<MaterialModel> material;

    //! Returns true when mesh has points assigned - non nullptr.
    [[nodiscard]] bool HasPoints() const;

    //! Returns true when mesh has faces assigned - non nullptr.
    [[nodiscard]] bool HasFaces() const;

    //! Returns true when mesh has material assigned - non nullptr.
    [[nodiscard]] bool HasMaterial() const;

    //! Import from a file. Return success.
    virtual bool Import(const std::string &filename);

    //! Import to a file. Create a directory hierarchy if necessary. Return success.
    virtual bool Export(const std::string &filename) const;
  };

  /*!
    \brief Calculates tangent vectors for each point of an input mesh.

    \returns
        Array of size equal to the point count of an input mesh.
        Each element of the array contains tangent vector in its xyz components.
        Component w holds information about bi-tangent orientation.
        If w is negative, bi-tangent is equal to the cross(T,N), otherwise cross(N,T).
  */
  std::vector<glm::vec4> COGS_API CalculateTangentArray(const cogs::Mesh &mesh);


  cogs::Mesh COGS_API JoinMeshes(const std::vector<cogs::Mesh> &meshes_to_join);

}

#endif /* !COGS_MESH_H */