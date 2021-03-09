/*
  Copyright (C) Skeletex Research, s.r.o. - All Rights Reserved
  Unauthorized copying of this file, via any medium is strictly prohibited
  Proprietary and confidential
*/
#ifndef HIRO_DRAW_GRAPH_RENDERER_H
#define HIRO_DRAW_GRAPH_RENDERER_H
#include <optional>

#include <Utils/GeometryStructures.h>
#include <GLW/Texture.h>
#include <HIRO_DRAW/Renderer.h>
#include <HIRO_DRAW/TextRenderer.h>



namespace hiro::draw
{

  //! Stylization of the rendered graph.
  struct HIRO_DRAW_API GraphStyle : public hiro::draw::Style
  {
    //! Graph name label.
    std::string caption{ "" };
    //! Color of the text labels.
    cogs::Color3f text_color{ cogs::color::GRAY60 };
    //! Color of the graph line.
    cogs::Color3f line_color{ cogs::color::GOLD };
    //! Width of the graph line.
    int32_t line_width{ 2 };
    //! Pixel size of the graph data points.
    int32_t point_size{ 5 };
    //! 2D area defining the screen region in which the graph will be displayed.
    geom::IRect target_area{ geom::IRect(50, 50, 250, 250) };

    //! Imports state from stream.
    bool ReadFromStream(std::istream &str) override;
    //! Exports state to stream.
    void WriteToStream(std::ostream &str) override;
  };



  //! Renderer used for rendering 2D graphs.
  class HIRO_DRAW_API GraphRenderer : public hiro::draw::Renderer
  {
  public:
    //! Creates a graph with data points of specified y values.
    GraphRenderer(const std::vector<float> &values_y);
    //! Creates a graph with data points of specified values. Sorted by x value before used.
    GraphRenderer(std::vector<glm::vec2> values);

    GraphRenderer(const hiro::draw::GraphRenderer &source) = delete;
    GraphRenderer &operator=(const hiro::draw::GraphRenderer &source) = delete;
    GraphRenderer(hiro::draw::GraphRenderer &&) noexcept = delete;
    GraphRenderer &operator=(hiro::draw::GraphRenderer &&) noexcept = delete;
    virtual ~GraphRenderer() = default;

    //! Test whether specified style is compatible with the object.
    bool IsCompatibileWithStyle(const hiro::draw::Style *style) override;

  protected:
    //! Defines 2d rendering behavior.
    void Render2D(const std::string &program) override;
    //! DEfines texts to be rendered.
    void FillTextRenderer(hiro::draw::TextRenderer *t_renderer) override;
    //! Loads shader programs required by this renderer.
    virtual void LoadRequiredShaderPrograms(glw::ProgramList *programs) override;

  private:
    //! Buffer that contains graph data points.
    std::shared_ptr<glw::ArrayObject> data_buffer_;
    //! Buffer that contains vertical grid lines.
    std::shared_ptr<glw::ArrayObject> grid_buffer_ver_;
    //! Buffer that contains horizontal grid lines.
    std::shared_ptr<glw::ArrayObject> grid_buffer_hor_;

    //! Pairs of points defining vertical grid lines.
    std::vector<glm::vec2> vertical_line_pos_;
    //! Pairs of points defining horizontal grid lines.
    std::vector<glm::vec2> horizontal_line_pos_;
    //! X positions of grid labels for vertical lines.
    std::vector<float> label_positions_x_;
    //! Y positions of grid labels for horizontal lines.
    std::vector<float> label_positions_y_;
    //! Minimal coordinates of data points.
    glm::vec2 data_min_{ std::numeric_limits<float>::max() };
    //! Maximal coordinates of data points.
    glm::vec2 data_max_{ std::numeric_limits<float>::lowest() };

    //! Initializes all required properties.
    void Initialize(const std::vector<glm::vec2> &values);
    //! Calculates graph grids and steps.
    void CalculateGridPoints(uint8_t hor_grid_steps_count, uint8_t ver_grid_steps_count);
    //! Transforms point in graph data space to screen space.
    glm::vec2 GraphToScreen(const glm::vec2 &point, const geom::IRect &screen_rect);
  };



  //! Shared pointer to an object of the type GraphStyle.
  using PGraphStyle = std::shared_ptr<hiro::draw::GraphStyle>;
  //! Shared pointer to an object of the type GraphRenderer.
  using PGraphRenderer = std::shared_ptr<hiro::draw::GraphRenderer>;
}

#endif /* !HIRO_DRAW_GRAPH_RENDERER_H */