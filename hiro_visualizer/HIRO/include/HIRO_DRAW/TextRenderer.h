/*
  Copyright (C) Skeletex Research, s.r.o. - All Rights Reserved
  Unauthorized copying of this file, via any medium is strictly prohibited
  Proprietary and confidential
*/
#ifndef HIRO_DRAW_TEXT_RENDERER_H
#define HIRO_DRAW_TEXT_RENDERER_H
#include <string>

#include <glm/glm.hpp>
#include <Utils/NamedClass.h>

#include <GLW/ShaderProgramList.h>
#include <COGS/Color.h>

#include <HIRO_DRAW/Scene.h>



namespace hiro::draw
{

  //! Defined alignment origin of the text.
  enum class TextAlignment : uint8_t
  {
    top_left,
    top_center,
    top_right,
    center_left,
    center,
    center_right,
    bottom_left,
    bottom_center,
    bottom_right
  };


  /*!
    \brief Responsible for rendering texts.

    TextRenderer has an active state which includes font, color, alignment etc.
    and all Print calls use current active state for the rendering.

    Instance of this object stores all print calls and state changes,
    and renders texts automatically at the same time.
  */
  class HIRO_DRAW_API TextRenderer
  {
    friend class RenderSystem;
  public:
    TextRenderer();
    TextRenderer(const hiro::draw::TextRenderer &) = delete;
    ~TextRenderer();
    //! Load TTF font file from disk and returns unique identifier of the font.
    size_t LoadFont(const std::string &font_file, float font_height);
    //! Sets an active font by its identifier.
    void SetFont(const size_t font_id);
    //! Sets active color for the text.
    void SetColor(const cogs::Color4b &color);
    //! Sets active text alignment for the text.
    void SetAlignment(hiro::draw::TextAlignment alignment);
    //! Prints specified text with the alignment origin at the specified position.
    void Print(glm::ivec2 pos, const std::string &text);
    //! Sets active rendering context for the text. Not to be called by a user.
    void SetSceneContext(const hiro::draw::PScene &scene);

  private:
    struct Impl;
    std::unique_ptr<hiro::draw::TextRenderer::Impl> m;

    glm::ivec2 AlignCoords(const std::string &text, glm::ivec2 coords) const;
    void LoadShaderPrograms(glw::ProgramList *program_list);
    void Render(glw::ProgramList *program_list, const glm::uvec2 &resolution);
  };



  /*!
    \brief Helper class for easier state printing to the top left corner of the viewport.

    Outputs text records line by line, for every print call.
    Use this class by wrapping hiro::draw::TextRenderer in your code, before printing:
    \code{.cpp}
      hiro::draw::StatePrinter printer(text_renderer);
      printer.PrintStr("Hello World!");
    \endcode
  */
  class HIRO_DRAW_API TextPrinter
  {
  public:
    TextPrinter(hiro::draw::TextRenderer *t_renderer);
    //! Print custom text line.
    void PrintStr(const std::string &text);
    //! Print text and boolean value. Text color changes according to the boolean state.
    void PrintBool(const std::string &text, bool state);
    //! Print text and value. Type of value parameter must be supported by any of the std::to_string overloads.
    template<typename T> void PrintValue(const std::string &text, T value);

  private:
    float current_line_y_{ 10.0f };
    hiro::draw::TextRenderer *renderer_{ nullptr };
    void NewLine();
    glm::vec2 GetCurrentLineOrigin() const;
  };

  template<typename T> void TextPrinter::PrintValue(const std::string &text, T value)
  {
    PrintStr(text + " : " + std::to_string(value));
  }


}

#endif /* !HIRO_DRAW_TEXT_RENDERER_H */