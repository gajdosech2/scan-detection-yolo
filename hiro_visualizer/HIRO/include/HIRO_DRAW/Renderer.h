/*
  Copyright (C) Skeletex Research, s.r.o. - All Rights Reserved
  Unauthorized copying of this file, via any medium is strictly prohibited
  Proprietary and confidential
*/
#ifndef HIRO_DRAW_RENDERER_H
#define HIRO_DRAW_RENDERER_H
#include <set>
#include <memory>

#include <glm/glm.hpp>

#include <GLW/ShaderProgramList.h>
#include <COGS/Color.h>
#include <COGS/MaterialModel.h>
#include <COGS/Transform.h>
#include <HIRO_DRAW/PrimitiveDatabase.h>



namespace hiro::draw
{
  class TextRenderer;
  class Scene;

  //! Base class for setting rendering style of an arbitrary render object.
  struct HIRO_DRAW_API Style
  {
    //! Whether the renderer that uses this style should be skipped during the rendering.
    bool visible = true;
    //! Model transformation applied to the renderer. In shader will appear as MODEL_MATRIX.
    cogs::Transform transform;

    virtual ~Style() = default;
    //! Imports state from stream.
    virtual bool ReadFromStream(std::istream &str);
    //! Exports state to stream.
    virtual void WriteToStream(std::ostream &str);
  protected:
    //! Read uint32_t version from stream and check if it is equal to the expected version.
    bool ReadVersion(std::istream &str, const uint32_t expected_version);
  };



  //! Abstract base class for an arbitrary renderer object.
  class HIRO_DRAW_API Renderer
  {
    friend class RenderSystem;
  public:
    Renderer();
    //! Test whether specified style is compatible with object.
    virtual bool IsCompatibileWithStyle(const hiro::draw::Style *style) = 0;

  protected:
    //! Override this method to load specialized shader programs for your object.
    virtual void LoadRequiredShaderPrograms(glw::ProgramList *programs);
    //! Override this method to specify custom rendering behavior in 3D rendering pass.
    virtual void Render(const std::string &program);

    /*!
      \brief Provides the possibility to render shapes using a simple color shader.

      <b>Vertex attributes:</b><br/>
      vec3 in_position; at location 0
      vec3 in_color;    at location 1

      <b>Uniforms:</b><br/>
      bool use_uniform_color = false;   at location ULOC_CUSTOM_0
      vec3 uniform_color = vec3(0,0,0); at location ULOC_CUSTOM_1
    */
    virtual void OnRenderSimple();

    //! Override this method to specify custom rendering behavior in 2D rendering pass.
    virtual void Render2D(const std::string &program);
    /*!
      \brief Provides the possibility to render shapes using a simple color shader.

      <b>Vertex attributes:</b><br/>
      vec3 in_position; at location 0
      vec3 in_color;    at location 1

      <b>Uniforms:</b><br/>
      bool use_uniform_color = false;   at location ULOC_CUSTOM_0
      vec3 uniform_color = vec3(0,0,0); at location ULOC_CUSTOM_1
    */
    virtual void OnRenderSimple2D();

    //! Override this method to define texts to be rendered.
    virtual void FillTextRenderer(hiro::draw::TextRenderer *t_renderer);

    //! Obtain currently set object style of specific type. Can be used only in Update-Render stage!
    template <typename StyleType>
    const StyleType *GetStyle() const;

    const Scene *GetScene() const;

  private: // changes to this section are made only by RenderSystem
    const Style *style_;
    const Scene *scene_;
  };

  template <typename StyleType>
  const StyleType *hiro::draw::Renderer::GetStyle() const
  {
    return static_cast<const StyleType *>(style_);
  }



  using PStyle = std::shared_ptr<hiro::draw::Style>;
  using PRenderer = std::shared_ptr<hiro::draw::Renderer>;

}

#endif /* !HIRO_DRAW_RENDERER_H */