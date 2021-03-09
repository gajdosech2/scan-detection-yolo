/*
  Copyright (C) Skeletex Research, s.r.o. - All Rights Reserved
  Unauthorized copying of this file, via any medium is strictly prohibited
  Proprietary and confidential
*/
#ifndef HIRO_DRAW_RASTER_RENDERER_H
#define HIRO_DRAW_RASTER_RENDERER_H
#include <GLW/Texture.h>
#include <COGS/Color.h>
#include <HIRO_DRAW/renderers/ImageRenderer.h>



namespace hiro::draw
{

  //! Structure specifying how the raster should be rendered.
  using RasterStyle = ImageStyle;



  /*!
    \brief Raster image which can have individual pixels set.

    Default resolution is 1x1, the default pixel color is black.
    If one of the dimensions provided to resolution is 0, nothing is rendered.

    Internally the renderer uses two buffers - texture buffer and work buffer.
    Texture buffer is used for rendering and it is located in the video memory.
    Work buffer is stored in RAM. When user manipulates with the pixels/resolution, the work buffer
    is changed and texture buffer invalidated. Before the rendering, if a texture buffer
    is invalid, the changes from work buffer are automatically introduced to the texture buffer.
  */
  class HIRO_DRAW_API RasterRenderer : public ImageRenderer
  {
  public:

    //! Sets current raster dimensions.
    glm::uvec2 GetResolution() const override;
    //! Sets the raster dimensions and clear it to the clearcolor.
    void SetResolution(
      const glm::uvec2 &resolution,
      const cogs::Color3b &clearcolor = cogs::color::BLACK
    );
    //! Gets the pixel at given pixel coordinates.
    const cogs::Color3b &GetPixel(size_t x, size_t y) const;
    //! Sets a pixel in a working buffer at a given position to the given color.
    void SetPixel(size_t x, size_t y, const cogs::Color3b &color);
    //! Clears the working pixel buffer to the defined color.
    void Clear(const cogs::Color3b &color = cogs::color::BLACK);
    //! When sync flag is set, copies data from working to display raster and resets the flag.
    void SyncRastersIfNeeded();

  protected:
    //! Describes rendering behavior in 2D rendering pass.
    void Render2D(const std::string &program) override;
    //! Test whether specified style is compatible with object.
    bool IsCompatibileWithStyle(const hiro::draw::Style *style) override;

  private:
    //! When the changes are introduced to the work buffer, sync is set to true.
    bool sync_buffers_on_next_render_{ true };
    //! Resolution of the work buffer.
    glm::uvec2 work_buffer_resolution_{ glm::uvec2(1, 1) };
    //! Work buffer for the raster.
    std::vector<cogs::Color3b> work_buffer_{ cogs::color::BLACK };

    using ImageRenderer::SetImage;
    using ImageRenderer::LoadImageFile;
  };



  //! Shared pointer to an object of the type RasterStyle.
  using PRasterStyle = std::shared_ptr<hiro::draw::RasterStyle>;
  //! Shared pointer to an object of the type RasterRenderer.
  using PRasterRenderer = std::shared_ptr<hiro::draw::RasterRenderer>;

}

#endif /* !HIRO_DRAW_RASTER_RENDERER_H */