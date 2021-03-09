#ifndef HIRO_GUI_HELPERS_H
#define HIRO_GUI_HELPERS_H
#include <HIRO/gui/GuiTypes.h>
#include <HIRO_DRAW/ShaderApi.h>
#include <COGS/Color.h>

namespace hiro
{
  class GuiGenerator;

  namespace gui
  {
    //! Adds color selection elements to gui. Object color should not be destroyed while gui exists.
    void AddColorGui(hiro::GuiGenerator &gui, cogs::Color3f &color);
    //! Adds material parameters to gui. Object color should not be destroyed while gui exists.
    void AddMaterialGui(hiro::GuiGenerator &gui, hiro::shader::Material &material, bool include_color = true);
    //! Adds droplist control iwth items corresponding to cogs::ColorMap elements.
    hiro::gui::Droplist *AddColorMapSelector(hiro::GuiGenerator &gui, const std::string &title = "Color map");
  }
}
#endif /* !HIRO_GUI_HELPERS_H */