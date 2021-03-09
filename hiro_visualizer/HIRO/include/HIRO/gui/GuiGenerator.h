/*
  Copyright (C) Skeletex Research, s.r.o. - All Rights Reserved
  Unauthorized copying of this file, via any medium is strictly prohibited
  Proprietary and confidential
*/
#ifndef HIRO_GUI_GENERATOR_H
#define HIRO_GUI_GENERATOR_H
#include <HIRO/ResourceId.h>
#include <HIRO/gui/GuiTypes.h>



namespace hiro
{

  /*!
    \brief Interface for automatic generating GUI elements to side panel.

    Elements are sequentially sorted in the order in which they were created.
    See namespace hiro::gui for the full list of available elements and their interface.
  */
  class HIRO_API GuiGenerator
  {
  public:
#ifdef HIRO_ENABLE_CEGUI
    GuiGenerator(const hiro::ResourceId &id, CEGUI::Window *client);
    GuiGenerator(CEGUI::Window *client);
#endif
    virtual ~GuiGenerator();

    /*!
      \brief Sets up whether tidy up should be performed automatically when something changes in GUI.

      Used by the system. Not to be called by a user.
    */
    void SetAutoTestConditionsEnabled(bool enabled);

    /*!
      \brief Hides the elements whose conditions are not met.

      Called by the system automatically.
    */
    void TestElementConditions();

    /*!
      \brief Creates a text label.
      \note Properties of element can be edited using returned object.
    */
    hiro::gui::Label *AddLabel(const std::string &text);

    /*!
      \brief Creates a button.
      \note Properties of element can be edited using returned object.
    */
    hiro::gui::Button *AddButton(const std::string &caption);

    /*!
      \brief Creates a checkbox.
      \note Properties of element can be edited using returned object.
    */
    hiro::gui::Checkbox *AddCheckbox(const std::string &title);

    /*!
      \brief Creates a drop list for selecting items.
      \note Properties of element can be edited using returned object.
    */
    hiro::gui::Droplist *AddDroplist(const std::string &title);

    /*!
      \brief Creates a numeric edit box for integer values.
      \note Properties of element can be edited using returned object.
    */
    hiro::gui::NumericInt *AddNumericInt(const std::string &title);

    /*!
      \brief Creates a numeric edit box for real values.
      \note Properties of element can be edited using returned object.
    */
    hiro::gui::NumericFloat *AddNumericFloat(const std::string &title);

    /*!
      \brief Creates slider on a real scale.
      \note Properties of element can be edited using returned object.
    */
    hiro::gui::SlidingFloat *AddSlidingFloat(const std::string &title);

    /*!
      \brief Creates slider on an integer scale.
      \note Properties of element can be edited using returned object.
    */
    hiro::gui::SlidingInt *AddSlidingInt(const std::string &title);

    /*!
      \brief Creates group of checkbox elements.
      \note Properties of element can be edited using returned object.
    */
    hiro::gui::CheckboxList *AddCheckboxList();

    //! Creates vertical separator.
    void AddSeparator();

    /*!
      \brief Begins a new panel.

      Any element added after this call will be added to the panel, until the PanelEnd
      function is not called. Panels can not be added recursively - sequential call of PanelBegin
      without calling PanelEnd is not allowed.
    */
    gui::Panel *PanelBegin();

    //! Ends the panel previously started using PanelBegin method.
    void PanelEnd();

  private:
    struct Impl;
    std::unique_ptr<hiro::GuiGenerator::Impl> m;
#ifdef HIRO_ENABLE_CEGUI
    void Construct(CEGUI::Window *client);
    void OnValueChange(const hiro::gui::Element *el);
#endif
  };

}
#endif /* !HIRO_GUI_GENERATOR_H */