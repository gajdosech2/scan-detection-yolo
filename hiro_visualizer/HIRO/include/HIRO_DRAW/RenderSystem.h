/*
  Copyright (C) Skeletex Research, s.r.o. - All Rights Reserved
  Unauthorized copying of this file, via any medium is strictly prohibited
  Proprietary and confidential
*/
#ifndef HIRO_DRAW_RENDER_SYSTEM_H
#define HIRO_DRAW_RENDER_SYSTEM_H
#include <array>

#include <GLW/FrameBuffer.h>
#include <GLW/UniformBuffer.h>
#include <Utils/GeometryStructures.h>

#include <HIRO_DRAW/Renderer.h>
#include <HIRO_DRAW/Scene.h>
#include <HIRO_DRAW/ShaderApi.h>
#include <HIRO_DRAW/PrimitiveDatabase.h>
#include <HIRO_DRAW/TextRenderer.h>



namespace hiro::draw
{
  enum class AntiAliasing : uint8_t
  {
    none,
    msaa2x,
    msaa4x,
    msaa8x,
    msaa16x,
    fxaa
  };


  const uint8_t DEFAULT_AXIS_OVERLAY_LAYER = 128;
  const uint8_t DEFAULT_GROUND_OVERLAY_LAYER = 0;


  /*!
    \brief Class responsible for rendering loop implementation and its optimization.
  */
  class HIRO_DRAW_API RenderSystem
  {
  public:

    enum class Mode
    {
      /*!
        System renders scenes and calculates lighting and other effects.
        Final imagery is rendered to the currently bound frame buffer.
      */
      visualizer,
      /*!
        System renders scenes and write them to the G-buffer that can be downloaded.
        No multi sample buffers are used in this mode, and no visual feedback is provided.
      */
      deferred_only,
    };

    RenderSystem(const glm::uvec2 &size, Mode mode = Mode::visualizer);

    //! Creates instance with shared shader program list.
    RenderSystem(const glm::uvec2 &size, const glw::PProgramList &programlist_ptr, Mode mode);

    //! Set up size of output buffer, targeted for render.
    void SetFramebufferSize(const glm::uvec2 &size);

    //! Set up directory from where render objects load their shaders.
    void SetShaderBuildDirectory(const std::string &directory);

    //! Set up initial buffer color. Only used if enabled in Render method.
    void SetBackgroundColor(const cogs::Color3f &color);

    //! Returns handle to the TextRenderer class.
    hiro::draw::TextRenderer *GetTextRenderer();

    //! Add a scene to the list of scenes to be rendered. Returns scene index.
    uint32_t AddScene(const hiro::draw::PScene &scene);

    //! Removes the scene from the list of scenes to be rendered.
    void RemoveScene(const hiro::draw::PScene &scene);

    //! Returns scene from the list of scenes to be rendered, by scene index.
    hiro::draw::PScene GetScene(const uint32_t scene_id);

    //! Add light to the renderer, returns index of the added light.
    uint32_t AddLight(const hiro::shader::Light &light);

    //! Chenge light with the specified id in the renderer.
    void SetLight(uint32_t light_id, const hiro::shader::Light &light);

    //! Loads all not-loaded shaders required by renderer and all objects from added scenes.
    void LoadShaders();

    //! Forces reload of all shaders required by renderer and all objects from added scenes.
    void ReloadShaders();

    //! Render all objects from all added scenes.
    void Render();

    //! Set whether The renderer should use MSAA. Disabled by default.
    void SetAntiAliasingMethod(AntiAliasing method);

    //! Checks whether is MSAA currently in use.
    AntiAliasing GetAntiAliasingMethod();

    //! Returns current resolution of render frame buffer.
    glm::uvec2 GetFrameBufferSize();

    //! Enables shadow mapping and initializes shadow map buffer with specified resolution.
    void EnableShadowing(const glm::uvec2 &shadowmap_buffer_resolution, bool light_areas_outside_shadowmap = true);

    //! Disables shadow mapping.
    void DisableShadowing();

    //! Check if shadow mapping is enabled.
    bool IsShadowingEnabled() const;

    //! Returns the layer on which is axis overlay feature rendered.
    uint8_t GetAxisLayer() const;

    //! Changes the layer on which is axis overlay feature rendered. Default is equal to hiro::draw::DEFAULT_GROUND_OVERLAY_LAYER.
    void SetAxisLayer(uint8_t layer);

    //! Returns the layer on which is ground grid overlay feature rendered.
    uint8_t GetGroundLayer() const;

    //! Changes the layer on which is ground grid overlay feature rendered. Default is equal to hiro::draw::DEFAULT_AXIS_OVERLAY_LAYER.
    void SetGroundLayer(uint8_t layer);

    /*!
      \brief Returns 4-channel texture of position and shininess parameters.

      Stored data is of type float32. First 3 channels are position x, y, z.
      The last channels is material shininess parameter.
    */
    glw::PTexture2D GetPositionsAndShininessTex() const;

    /*!
      \brief Returns 4-channel texture of normal and intensity parameters.

      Stored data is of type float32. First 3 channels are normal vector x, y, z.
      The last channels is material specular intensity parameter.
    */
    glw::PTexture2D GetNormalsAndSpecularTex() const;

    /*!
      \brief Returns 4-channel texture of color and lighting parameters.

      Stored data is of type uint8. First 3 channels are albedo color r,g,b.
      The last channels is boolean parameter telling whether lighting is use for the pixel.
    */
    glw::PTexture2D GetColorsAndLightingTex() const;

    /*!
      \brief Returns 1-channel texture of shadow mask.

      Stored data is of type uint8_norm.
    */
    glw::PTexture2D GetShadowMaskTex() const;

    /*!
      \brief When shadowmapping is enabled, returns shadow depth map.

      This method will return nullptr until EnableShadowing is called.
    */
    glw::PTexture2D GetShadowmapTex() const;


    /*!
      \brief Returns 1-channel texture representing segmentation labels.

      Stored data is of type uint32.
    */
    glw::PTexture2D GetLabelTex() const;

  private:

    using RenderPassSceneFunc = std::function<void(const PScene &, uint8_t, const std::string &)>;

    struct SceneData
    {
      glm::mat4 projection;
      glm::mat4 projection_inverse;
      int32_t camera_id;
      glm::vec3 padding0;
      glm::ivec4 light_ids;
      glm::ivec2 resolution;
      glm::vec2 padding1;
    };

    enum class RenderPass
    {
      other = 0,
      shadow = 1,
    };

    enum class ShadowingMethod
    {
      disabled = 0, // No shadows are generated.
      shadowed_scene = 1, // Scene is shadowed using the shadow map. Regions outside shadow map have no shadow.
      lighten_scene = 2,  // Scene is lighten using the shadow map. Regions outside shadow map are fully shadowed.
    };

    hiro::draw::TextRenderer text_renderer_;

    glw::PProgramList programs_;
    glw::PFrameBuffer deferred_buffer_;
    glw::PFrameBuffer combined_buffer_;
    glw::PFrameBuffer fxaa_buffer_;
    glw::PFrameBuffer shadowmap_buffer_;
    AntiAliasing antialiasing_method_ = AntiAliasing::none;

    const Mode mode_ = Mode::visualizer;
    glm::uvec2 framebuffer_size_;
    cogs::Color3b back_color_ = cogs::color::WHITE;
    std::vector<PScene> scenes_;

    glw::UniformBuffer<glm_ext::TransMat4> cameraview_buffer_;

    uint8_t axis_layer_ = DEFAULT_AXIS_OVERLAY_LAYER;
    uint8_t ground_layer_ = DEFAULT_GROUND_OVERLAY_LAYER;

    uint32_t added_light_count_ = 0u;
    glw::UniformBuffer<hiro::shader::Light> light_buffer_;

    glw::UniformBuffer<hiro::draw::RenderSystem::SceneData> scenedata_buffer_;
    glw::PArrayObject grid_buffer_;

    std::vector<uint8_t> occupied_layers_;

    RenderPass current_pass_{ RenderPass::other };
    ShadowingMethod shadowing_method_{ ShadowingMethod::disabled };

    void CreateGridBuffer();

    void UpdateCameraBuffers(bool use_2d);
    void UpdateSceneDataBuffers(bool use_2d_projection);

    void UpdateOccupiedLayers();

    void PrepareSceneForRender(const uint32_t scene_id);

    void RenderGrid(GroundGrid orientation, float scale);
    void RenderAxes(const PScene &scene);

    SceneData GetSceneData(const uint32_t scene_id, bool use_2d_projection);

    void LoadSceneShaders(const uint32_t scene_id);

    //! Re-create frame buffers for deferred rendering.
    void ResetFrameBuffers();

    //! Render specified buffer to currently bound, using the specified shader.
    void RenderBufferPass(const glw::FrameBuffer &source_buffer, const std::string &shader);

    void RenderPassLayer(uint8_t layer, const RenderPassSceneFunc &RenderPassScene);

    void RenderPassAllLayers(const RenderPassSceneFunc &RenderPassScene);

    //! Bind the G-Buffer to render into.
    void InitDeferredRendering();

    void Render3D(const PScene &scene, uint8_t layer, const std::string &shader);

    void Render2D(const PScene &scene, uint8_t layer, const std::string &shader);
  };

}

#endif /* !HIRO_DRAW_RENDER_SYSTEM_H */