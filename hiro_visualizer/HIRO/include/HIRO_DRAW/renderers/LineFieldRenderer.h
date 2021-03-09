/*
  Copyright (C) Skeletex Research, s.r.o. - All Rights Reserved
  Unauthorized copying of this file, via any medium is strictly prohibited
  Proprietary and confidential
*/
#ifndef HIRO_DRAW_LINE_FIELD_RENDERER_H
#define HIRO_DRAW_LINE_FIELD_RENDERER_H
#include <Utils/GeometryStructures.h>
#include <HIRO_DRAW/Renderer.h>



namespace hiro::draw
{

  //! Stylization of the rendered line field.
  struct HIRO_DRAW_API LineFieldStyle : public hiro::draw::Style
  {
    //! Possible sources of line color information.
    enum class ColorSource
    {
      fixed = 0,  //!< Line colors are uniform and set by default_cl parameter.
      length = 1, //!< Color is set by relative length of line.
      custom = 2, //!< Line colors are set using custom color buffer.
      velocity = 3, //!< Lines are colored using a gradient from first point to second.
    };
    //! Specifies thickness of a lines.
    float thickness{ 1.0f };
    //! Specifies, from where line colors should be obtained.
    hiro::draw::LineFieldStyle::ColorSource color_source{ hiro::draw::LineFieldStyle::ColorSource::fixed };
    //! Default fixed color for the lines. Used when color source set to ColorSource::fixed.
    cogs::Color3f fixed_color { cogs::color::GRAY50 };
    //! Name of buffer used to get custom colors. Used when color source set to ColorSource::custom.
    glw::ArrayObject::BufferName custom_cl_buf{ glw::ArrayObject::INVALID_NAME };
    //! Imports state from stream.
    virtual bool ReadFromStream(std::istream &str) override;
    //! Exports state to stream.
    virtual void WriteToStream(std::ostream &str) override;
  };



  //! Renderer used for rendering array of lines.
  class HIRO_DRAW_API LineFieldRenderer : public hiro::draw::Renderer
  {
  public:
    //! Creates a renderer with an empty line array.
    LineFieldRenderer() = default;
    //! Creates a renderer with the specified 2D line array.
    LineFieldRenderer(const std::vector<geom::LineSegment2> &line_array);
    //! Creates a renderer with the specified line array.
    LineFieldRenderer(const std::vector<geom::LineSegment3> &line_array);

    LineFieldRenderer(const hiro::draw::LineFieldRenderer &source) = delete;
    LineFieldRenderer &operator=(const hiro::draw::LineFieldRenderer &source) = delete;
    LineFieldRenderer(hiro::draw::LineFieldRenderer &&) noexcept = delete;
    LineFieldRenderer &operator=(hiro::draw::LineFieldRenderer &&) noexcept = delete;
    virtual ~LineFieldRenderer() = default;

    //! Replace the currently used line array with a new one.
    void SetLines(const std::vector<geom::LineSegment3> &line_array);
    //! Replace the currently used line array with a new one.
    void SetLines(const std::vector<geom::LineSegment2> &line_array);
    //! Returns number of lines in currently set line array.
    size_t GetLineCount() const;
    /*!
      \brief Creates a buffer with given colors.
      \returns The name of the created buffer. If creation failed -1.
    */
    glw::ArrayObject::BufferName AddColors(std::vector<cogs::Color3f> data);

    //! Test whether specified style is compatible with the object.
    bool IsCompatibileWithStyle(const hiro::draw::Style *style) override;

  protected:
    //! Specifies what happens when simple rendering is done.
    void OnRenderSimple() override;

    //! Specifies what happens when simple 2d rendering is done.
    virtual void OnRenderSimple2D() override;

  private:
    bool is_2d_mode_enabled_{ false };
    //! Current number of lines.
    size_t line_count_{ 0u };
    //! Vertex buffer containing line array.
    glw::PArrayObject line_buffer_;
    //! Buffer that holds colors by length. Used when color source set to ColorSource::length.
    glw::ArrayObject::BufferName color_by_length_buf { glw::ArrayObject::INVALID_NAME };
    //! Buffer that holds colors by velocity. Used when color source set to ColorSource::velocity.
    glw::ArrayObject::BufferName color_by_velocity_buf{ glw::ArrayObject::INVALID_NAME };

    void RenderLines();
  };



  //! Shared pointer to an object of the type LineFieldStyle.
  using PLineFieldStyle = std::shared_ptr<hiro::draw::LineFieldStyle>;
  //! Shared pointer to an object of the type LineFieldRenderer.
  using PLineFieldRenderer = std::shared_ptr<hiro::draw::LineFieldRenderer>;

}

#endif /* !HIRO_DRAW_LINE_FIELD_RENDERER_H */