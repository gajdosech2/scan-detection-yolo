/*
  Copyright (C) Skeletex Research, s.r.o. - All Rights Reserved
  Unauthorized copying of this file, via any medium is strictly prohibited
  Proprietary and confidential
*/
#ifndef HIRO_DRAW_MESH_RENDERER_H
#define HIRO_DRAW_MESH_RENDERER_H
#include <GLW/Texture.h>
#include <HIRO_DRAW/renderers/GeometryRenderer.h>



namespace cogs { struct Mesh; }

namespace hiro::draw
{

  //! Stylization of the rendered mesh.
  using MeshStyle = hiro::draw::GeometryStyle;



  //! Renderer used for rendering meshes.
  class HIRO_DRAW_API MeshRenderer : public hiro::draw::GeometryRenderer
  {
  public:
    //! Creates a renderer with the specified mesh.
    MeshRenderer(const cogs::Mesh &mesh);

    MeshRenderer(const hiro::draw::MeshRenderer &source) = delete;
    MeshRenderer &operator=(const hiro::draw::MeshRenderer &source) = delete;
    MeshRenderer(hiro::draw::MeshRenderer &&) noexcept = delete;
    MeshRenderer &operator=(hiro::draw::MeshRenderer &&) noexcept = delete;
    virtual ~MeshRenderer() = default;

    //! Set custom color for every point in the mesh. Used when color source set to ColorSource::custom.
    void SetCustomColors(const std::vector<cogs::Color3f> &colors);
    //! Test whether specified style is compatible with the object.
    bool IsCompatibileWithStyle(const hiro::draw::Style *style) override;

  private:
    //! Array buffer object that holds the mesh vertices.
    glw::PArrayObject array_object_;
    //! Name of the buffer that holds custom colors.
    glw::ArrayObject::BufferName color_buffer_ { glw::ArrayObject::INVALID_NAME };
  };



  //! Shared pointer to an object of the type MeshStyle.
  using PMeshStyle = std::shared_ptr<hiro::draw::MeshStyle>;
  //! Shared pointer to an object of the type MeshRenderer.
  using PMeshRenderer = std::shared_ptr<hiro::draw::MeshRenderer>;

}

#endif /* !HIRO_DRAW_MESH_RENDERER_H */