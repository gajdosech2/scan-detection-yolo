/*
  Copyright (C) Skeletex Research, s.r.o. - All Rights Reserved
  Unauthorized copying of this file, via any medium is strictly prohibited
  Proprietary and confidential
*/
#ifndef HIRO_DRAW_CIRCLE_RENDERER_H
#define HIRO_DRAW_CIRCLE_RENDERER_H
#include <Utils/GeometryStructures.h>
#include <HIRO_DRAW/Renderer.h>


namespace hiro::draw
{

  //! Stylization of the rendered mesh.
  class CircleStyle : public Style
  {

  };



  //! Renderer used for rendering meshes.
  class HIRO_DRAW_API CircleRenderer : public Renderer
  {
  public:
    CircleRenderer();
    CircleRenderer(const CircleRenderer &source) = delete;
    CircleRenderer &operator=(const CircleRenderer &source) = delete;
    CircleRenderer(CircleRenderer &&) noexcept = delete;
    CircleRenderer &operator=(CircleRenderer &&) noexcept = delete;
    virtual ~CircleRenderer() = default;

    void ClearCircles();
    void AddCircle(const geom::Circle &circle, const cogs::Color3f &color);
    void AddCircles(const std::vector<glm::vec2> &centers, float radius, const cogs::Color3f &color);
    void SetCircles(const std::vector<glm::vec2> &centers, float radius, const cogs::Color3f &color);

    //! Test whether specified style is compatible with the object.
    bool IsCompatibileWithStyle(const Style *style) override;

  protected:
    virtual void Render2D(const std::string &program) override;
    virtual void LoadRequiredShaderPrograms(glw::ProgramList *programs) override;
  private:
    bool circles_changed_{false};
    std::vector<glm::vec2> circle_centers_;
    std::vector<float> circle_radii_;
    std::vector<cogs::Color3f> circle_colors_;
    //! Array buffer object that holds the mesh vertices.
    glw::PArrayObject array_object_;
    //! Name of the buffer that holds custom colors.
    glw::ArrayObject::BufferName color_buffer_ { glw::ArrayObject::INVALID_NAME };
    void ResetArrayObject();

  };


  //! Shared pointer to an object of the type CircleStyle.
  using PCircleStyle = std::shared_ptr<CircleStyle>;
  //! Shared pointer to an object of the type CircleRenderer.
  using PCircleRenderer = std::shared_ptr<CircleRenderer>;

}

#endif /* !HIRO_DRAW_CIRCLE_RENDERER_H */