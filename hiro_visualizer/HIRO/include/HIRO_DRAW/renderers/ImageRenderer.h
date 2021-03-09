/*
  Copyright (C) Skeletex Research, s.r.o. - All Rights Reserved
  Unauthorized copying of this file, via any medium is strictly prohibited
  Proprietary and confidential
*/
#ifndef HIRO_DRAW_IMAGE_RENDERER_H
#define HIRO_DRAW_IMAGE_RENDERER_H
#include <GLW/Texture.h>
#include <COGS/Color.h>
#include <HIRO_DRAW/Renderer.h>
#include <HIRO_DRAW/Scene.h>



namespace hiro::draw
{

  //! Structure specifying how the Image should be rendered.
  struct HIRO_DRAW_API ImageStyle : public Style
  {
    //! Denotes, whether to use nearest or linear filtering when rendering Image.
    bool use_nearest_filtering{ false };
    //! When set to true, Image is rendered in a sizing that can be displayed in a viewport.
    bool fit_to_viewport{ true };
    //! Only when fit_to_viewport is enabled. Adds blank space around Image, so that it is not deformed.
    bool keep_aspect_ratio{ true };
    //! Image will be mirrored along defined axes when rendered.
    glm::bvec2 mirror{ false, false };
    //! Specify which image color channels are enabled. When false, RGB channels are set to 0 and alpha to 1.
    glm::bvec4 is_channel_enabled{ true, true, true, true };
    //! Custom color space transformation. Final color is computed as: (original_color + offset) * multiplier.
    glm::vec4 channel_offset{ 0.0f, 0.0f, 0.0f, 0.0f };
    //! Custom color space transformation. Final color is computed as: (original_color + offset) * multiplier.
    glm::vec4 channel_multiplier{ 1.0f, 1.0f, 1.0f, 1.0f };
    //! When set to true, image pixels with zero alpha channel are not rendered.
    bool discard_transparent_pixels{ false };
    //! When set to true, image is rendered at a position and scale obtained from transform.
    bool use_trasform{ false };
    //! Import state from stream.
    virtual bool ReadFromStream(std::istream &str) override;
    //! Export state to stream.
    virtual void WriteToStream(std::ostream &str) override;
  };



  /*!
    \brief Image image which can have individual pixels set.

    Default resolution is 1x1, the default pixel color is black.
    If one of the dimensions provided to resolution is 0, nothing is rendered.

    Internally the renderer uses two buffers - texture buffer and work buffer.
    Texture buffer is used for rendering and it is located in the video memory.
    Work buffer is stored in RAM. When user manipulates with the pixels/resolution, the work buffer
    is changed and texture buffer invalidated. Before the rendering, if a texture buffer
    is invalid, the changes from work buffer are automatically introduced to the texture buffer.
  */
  class HIRO_DRAW_API ImageRenderer : public hiro::draw::Renderer
  {
  public:

    ImageRenderer() = default;

    explicit ImageRenderer(const glw::PTexture2D &image_texture);

    explicit ImageRenderer(const std::string &image_file);

    void SetImage(const glw::PTexture2D &image_texture);

    void LoadImageFile(const std::string &image_file);

    glw::PTexture2D GetTexture() const;

    //! Returns the current Image resolution.
    virtual glm::uvec2 GetResolution() const;

    //! Returns transformation from image texels to screen pixels.
    glm::mat4 GetImageToPixelTransform(const ImageStyle &style, const hiro::draw::ProjectionParams &params) const;

    //! Returns transformation from image texels to viewport screen pixels.
    glm::mat4 GetImageToViewportPixelTransform(const ImageStyle &style, const hiro::draw::ProjectionParams &params) const;

  protected:
    //! Texture buffer for the Image.
    glw::PTexture2D texture_buffer_{ nullptr };

    //! Describes rendering behavior in 2D rendering pass.
    void Render2D(const std::string &program) override;

    //! Test whether specified style is compatible with object.
    bool IsCompatibileWithStyle(const Style *style) override;

    //! Loads shader programs required by this renderer.
    void LoadRequiredShaderPrograms(glw::ProgramList *programs) override;

    virtual void FillTextRenderer(hiro::draw::TextRenderer *t_renderer) override;

    //! Sets the texture filtering based on the style preference.
    void SetupFiltering();
  };



  //! Shared pointer to an object of the type ImageStyle.
  using PImageStyle = std::shared_ptr<ImageStyle>;
  //! Shared pointer to an object of the type ImageRenderer.
  using PImageRenderer = std::shared_ptr<ImageRenderer>;

}

#endif /* !HIRO_DRAW_IMAGE_RENDERER_H */