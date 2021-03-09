/*
  Copyright (C) Skeletex Research, s.r.o. - All Rights Reserved
  Unauthorized copying of this file, via any medium is strictly prohibited
  Proprietary and confidential
*/
#ifndef HIRO_DRAW_ELEMENT_RENDERER_H
#define HIRO_DRAW_ELEMENT_RENDERER_H
#include <GLW/Texture.h>
#include <GLW/UniformBuffer.h>
#include <HIRO_DRAW/Renderer.h>
#include <HIRO_DRAW/ShaderApi.h>



namespace hiro::draw
{

  //! Available sources of color information.
  enum class ColorSource : int32_t
  {
    material = 0, //!< Color is taken from the material.
    positions = 1, //!< Raw 3D positions are used to represent colors.
    normals = 2, //!< Raw 3D normals are used to represent colors.
    custom = 3, //! Vertex color attribute used to get colors.
    normals_n = 4, //!< 3D normals mapped to the visible color range.
    checkerboard = 5, //!< Checkerboard texture used to get colors.
    albedo_texture = 6 //!< Albedo texture used to get colors.
  };



  //! Point rendering stylization.
  struct PointsStyle
  {
    //! Material setting for the points.
    hiro::shader::Material material;
    //! When enabled, points with normal vector turned away from the camera are hidden.
    bool back_face_culling = false;
    //! Size of point in screen pixels.
    float point_size = 10.0f;
    //! Color source used to colorize the points.
    hiro::draw::ColorSource color_source = hiro::draw::ColorSource::material;
  };



  //! Face rendering stylization.
  struct FacesStyle
  {
    //! Available sources of normal vector.
    enum class NormalSource
    {
      flat_normals = 0, //!< Normals are calculated from face orientations.
      point_normals = 1, //!< Per vertex normals are used. Requires normal attribute for vertices.
      normal_texture = 2 //!< Normals are picked from the normal texture. Requires normal texture.
    };

    //! When enabled, faces with flat normal vector turned away from the camera are hidden.
    bool back_face_culling = false;
    //! When enabled, only face edges are rendered.
    bool wireframe = false;

    //! Material setting for the faces.
    hiro::shader::Material material;
    //! Color source used to colorize the faces.
    hiro::draw::ColorSource color_source = hiro::draw::ColorSource::material;
    //! Albedo texture. To use, set color source to ColorSource::albedo_map.
    glw::PTexture2D albedo_texture = nullptr;

    //! Normal source used to calculate the lighting.
    hiro::draw::FacesStyle::NormalSource normal_source = hiro::draw::FacesStyle::NormalSource::flat_normals;
    //! Normal texture. To use, set normal source to NormalSource::normal_map.
    glw::PTexture2D normal_texture = nullptr;

    //! When enabled, color and lighting is picked from matcap sampler texture.
    bool use_matcap = false;
    //! Matcap sampler. Used only when matcap rendering is enabled.
    glw::PTexture2D matcap_sampler = nullptr;
  };



  //! Normal vector rendering stylization.
  struct NormalsStyle
  {
    //! Color of the normal vector tip.
    cogs::Color3f color = cogs::color::BLACK;
    //! Length of the normal vector.
    float length = 0.1f;
  };



  /*!
    \brief Base class for rendering of geometry data.

    If you wish to specify your rendering override desired "OnRender" method and render inside it.

    Your own method for point rendering can be implemented something like this:
    \code{.cpp}
      void hiro::draw::GeometryRenderer::OnRenderPoints()
      {
        const auto style = GetStyle<GeometryStyle>();
        if (style->render_mode == GeometryStyle::RenderMode::points
          || style->render_mode == GeometryStyle::RenderMode::wired_points)
        {
          PointsStyle ps;
          ps.back_face_culling = style->back_face_culling;
          ps.color_source = style->color_source;
          ps.material = style->material;
          ps.point_size = style->point_size;

          vao_->Bind();
          RenderPoints(ps, [&]() { vao_->DrawVertices(glw::DrawMode::points); });
          vao_->Unbind();
        }
      }
    \endcode
  */
  class HIRO_DRAW_API ElementRenderer : public hiro::draw::Renderer
  {
  public:
    ElementRenderer(const hiro::draw::ElementRenderer &source) = delete;
    ElementRenderer &operator=(const hiro::draw::ElementRenderer &source) = delete;
    ElementRenderer(hiro::draw::ElementRenderer &&) noexcept = delete;
    ElementRenderer &operator=(hiro::draw::ElementRenderer &&) noexcept = delete;
    virtual ~ElementRenderer() = default;

  protected:
    //! Protected constructor, since this class should serve only as a base class.
    ElementRenderer();

    //! Loads shader programs required by this renderer.
    void LoadRequiredShaderPrograms(glw::ProgramList *programs) override;
    //! Specifies what happens during render.
    void Render(const std::string &program) override;

    //! Override if you wish to render points. Use the method RenderPoints to actually render.
    virtual void OnRenderPoints();
    //! Override if you wish to render faces. Use the method RenderFaces to actually render.
    virtual void OnRenderFaces();
    //! Override if you wish to render normals. Use the method RenderNormals to actually render.
    virtual void OnRenderNormals();

    //! Prepares shader according to the style and renders points using the specified render_func.
    void RenderPoints(const hiro::draw::PointsStyle &style, std::function<void(void)> render_func);
    //! Prepares shader according to the style and renders faces using the specified render_func.
    void RenderFaces(const hiro::draw::FacesStyle &style, std::function<void(void)> render_func);
    //! Prepares shader according to the style and renders normals using the specified render_func.
    void RenderNormals(const hiro::draw::NormalsStyle &style, std::function<void(void)> render_func);

  private:
    //! Uniform buffer containing material information.
    glw::UniformBuffer<hiro::shader::Material> material_ubo_;
  };

}

#endif /* !HIRO_DRAW_ELEMENT_RENDERER_H */