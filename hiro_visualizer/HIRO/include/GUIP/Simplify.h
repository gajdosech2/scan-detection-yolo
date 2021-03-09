#ifndef GUIP_SIMPLIFY_H
#define GUIP_SIMPLIFY_H
#include <glm/glm.hpp>
#ifdef __GNUC__
#undef True
#undef False
#undef None
#endif
#include <CEGUI/CEGUI.h>
#include <Utils/Filesystem.h>
#include <GUIP/API.h>

//! Extensions to the CEGUI library.
namespace guip
{

  enum class PushButtonTheme
  {
    gray,
    red,
    green,
    blue,
    turquoise
  };

  //! Changes a color theme of a DarkHiro/PushButton element.
  GUIP_API void SetTheme(PushButtonTheme theme, CEGUI::Window *btn);

  //! Sets position for the widget.
  GUIP_API void SetPosition(CEGUI::Window *widget, float x_perc, float x_px, float y_perc, float y_px);

  //! Sets size for the widget.
  GUIP_API void SetSize(CEGUI::Window *widget, float w_perc, float w_px, float h_perc, float h_px);

  //! Sets widgets destination as rectangle in pixels.
  GUIP_API void SetDestRect(CEGUI::Window *widget, float x_px, float y_px, float w_px, float h_px);

  //! Returns a pointer to the WigetType as a handle object.
  template <typename WidgetType = CEGUI::Window>
  WidgetType * GetHandledObject(const CEGUI::EventArgs &e)
  {
    auto event = static_cast<const CEGUI::WindowEventArgs *>(&e);
    return static_cast<WidgetType *>(event->window);
  }

  //! Creates new widget and, if parent is not nullptr, assigns as a child to another widget.
  template <typename WidgetType = CEGUI::Window>
  WidgetType * CreateWidget(const std::string &type, const std::string &name, CEGUI::Window *parent = nullptr)
  {
    CEGUI::Window *new_widget = CEGUI::WindowManager::getSingleton().createWindow(type, name);
    if (parent)
    {
      parent->addChild(new_widget);
    }
    return static_cast<WidgetType *>(new_widget);
  }

  //! Creates new widget from layout xml and, if parent is not nullptr, assigns as a child to another widget.
  template <typename WidgetType = CEGUI::Window>
  WidgetType * CreateWidgetFromXml(const std::string &look_xml, CEGUI::Window *parent = nullptr)
  {
    auto new_widget = CEGUI::WindowManager::getSingleton().loadLayoutFromString(look_xml);
    if (parent)
    {
      parent->addChild(new_widget);
    }
    return static_cast<WidgetType *>(new_widget);
  }

  //! Creates new widget from layout file and, if parent is not nullptr, assigns as a child to another widget.
  template <typename WidgetType = CEGUI::Window>
  WidgetType * CreateWidgetFromFile(const std::string &look_file, CEGUI::Window *parent = nullptr)
  {
    auto file_xml = fs::FileToString(look_file);
    return CreateWidgetFromXml<WidgetType>(file_xml, parent);
  }

  //! Return child of specified widget with exact name.
  template <typename WidgetType = CEGUI::Window>
  WidgetType * GetChild(const std::string &name, CEGUI::Window *parent)
  {
    return static_cast<WidgetType *>(parent->getChild(name));
  }

  //! Returns child of specified widget and all its sub-widgets with exact name.
  template <typename WidgetType = CEGUI::Window>
  WidgetType * GetChildRecursive(const std::string &name, CEGUI::Window *parent)
  {
    return static_cast<WidgetType *>(parent->getChildRecursive(name));
  }

  //! Find a child of a CEGUI container that passes given predicate function.
  template<class C, class P>
  inline CEGUI::Window *FindChild(const C &container, const P &Predicate)
  {
    for (size_t i = 0; i < container.getChildCount(); ++i)
    {
      const auto obj = container.getChildAtPosition(i);
      if (obj != nullptr && Predicate(obj))
      {
        return obj;
      }
    }
    return nullptr;
  }

  //! Returns child widget of a specified window.
  GUIP_API std::vector<CEGUI::Window *> GetChildWidgets(CEGUI::Window *widget, bool exclude_auto_widgets = true);

  //! Removes child widgets of a specified window.
  GUIP_API void RemoveChildWidgets(CEGUI::Window *widget, bool exclude_auto_widgets = true);

  //! Removes and destroys child widgets of a specified window.
  GUIP_API void DestroyChildWidgets(CEGUI::Window *widget, bool exclude_auto_widgets = true);

  //! Select or un-select specified ToggleButton without calling any events.
  GUIP_API void SetSelectedMuted(const bool state, CEGUI::ToggleButton *button);

  /*!
      \brief
          Loads a single image to CEGUI.
      \param internal_image_name
          Image set and image name in format [imageset name]/[image name].
      \param img_path
          Path to the image.
      \param resolution
          Resolution of the image.
  */
  GUIP_API bool ImportImage(const std::string &internal_image_name, const std::string &img_path, const glm::uvec2 &resolution);

  //! Prints window hierarchy to output stream.
  GUIP_API void PrintHierarchy(const CEGUI::Window *window, std::ostream &outs, size_t indent = 0);

  //! Prints all properties of a specified widget to output stream.
  GUIP_API void PrintProperties(const CEGUI::Window *window, std::ostream &outs);

}


#endif /* !GUIP_SIMPLIFY_H */