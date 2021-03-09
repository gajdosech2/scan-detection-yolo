/*
  Copyright (C) Skeletex Research, s.r.o. - All Rights Reserved
  Unauthorized copying of this file, via any medium is strictly prohibited
  Proprietary and confidential
*/
#ifndef HIRO_DRAW_FRUSTUM_RENDERER_H
#define HIRO_DRAW_FRUSTUM_RENDERER_H
#include <COGS/Frustum.h>
#include <GLW/ArrayObject.h>
#include <HIRO_DRAW/Renderer.h>



namespace hiro::draw
{

  //! Stylization of the rendered frustum.
  struct HIRO_DRAW_API FrustumStyle : public hiro::draw::Style
  {
    //! Specifies thickness of a lines.
    float line_thickness{ 1.0f };
    //! Color of the frustum visualization on near plane.
    cogs::Color3f near_color{ cogs::color::GRAY50 };
    //! Color of the frustum visualization on far plane.
    cogs::Color3f far_color{ cogs::color::GRAY50 };
    //! Whether lines from eye should be rendered.
    bool draw_eye_lines{ true };
    //! Color of the frustum visualization on far plane.
    cogs::Color3f eye_lines_color{ cogs::color::GRAY50 };
    //! Imports state from stream.
    virtual bool ReadFromStream(std::istream &str) override;
    //! Exports state to stream.
    virtual void WriteToStream(std::ostream &str) override;
  };



  //! Renderer used for rendering cogs::Frustum.
  class HIRO_DRAW_API FrustumRenderer : public hiro::draw::Renderer
  {
  public:
    //! Creates a renderer without a frustum defined.
    FrustumRenderer() = default;
    //! Creates a renderer with the specified frustum.
    FrustumRenderer(const cogs::Frustum &frustum);

    FrustumRenderer(const hiro::draw::FrustumRenderer &) = delete;
    FrustumRenderer &operator=(const hiro::draw::FrustumRenderer &) = delete;
    FrustumRenderer(hiro::draw::FrustumRenderer &&) noexcept = delete;
    FrustumRenderer &operator=(hiro::draw::FrustumRenderer &&) noexcept = delete;
    virtual ~FrustumRenderer() = default;

    //! Replace the currently used frustum with a new one.
    void SetFrustum(const cogs::Frustum &frustum);
    //! Test whether specified style is compatible with the object.
    bool IsCompatibileWithStyle(const hiro::draw::Style *style) override;

  protected:
    //! Specifies what happens when simple rendering is performed.
    void OnRenderSimple() override;

  private:
    glw::PArrayObject line_vao_;
    glw::ArrayObject::BufferName color_buffer_;
    std::vector<cogs::Color3f> colors_;
    void UpdateColors(const FrustumStyle *style);
  };



  //! Shared pointer to an object of the type FrustumStyle.
  using PFrustumStyle = std::shared_ptr<hiro::draw::FrustumStyle>;
  //! Shared pointer to an object of the type FrustumRenderer.
  using PFrustumRenderer = std::shared_ptr<hiro::draw::FrustumRenderer>;

}

#endif /* !HIRO_DRAW_FRUSTUM_RENDERER_H */