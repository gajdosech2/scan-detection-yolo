#ifndef GUIP_ARRAY_PANEL_H
#define GUIP_ARRAY_PANEL_H
#include <CEGUI/Window.h>
#include <GUIP/API.h>

namespace guip
{

  //! Sequentially sorts its children in a column.
  class GUIP_API ArrayPanel : public CEGUI::Window
  {
  public:
    //! Unique gui system identifier.
    static CEGUI::String WidgetTypeName;

    ArrayPanel(const CEGUI::String &type, const CEGUI::String &name);

    //! Changes spacing - vertical pixel space between two consequential children windows.
    void SetElementSpacing(double spacing);
    //! Returns current spacing - vertical pixel space between two consequential children windows.
    double GetElementSpacing() const;

    //! Changes padding. Padding defines spacing on top, right and left of panel.
    void SetPadding(double padding);
    //! Returns current padding. Padding defines spacing on top, right and left of panel.
    double GetPadding() const;

    /*!
      \brief Allows automatic layout updating whenever a child is added/removed. Default true.

      When disabled, you must call UpdateLayout() when you finish adding/removing children.
    */
    void SetAutoUpdateLayoutEnabled(bool is_enabled);
    //! Whether automatic layout updating is enabled.
    bool IsAutoUpdateLayoutEnabled() const;
    //! Updates layout manually. Should be used only when auto update layout is disabled.
    void UpdateLayout();

  protected:
    virtual void addChild_impl(CEGUI::Element *element) override;

  private:
    float element_spacing_ = 0.0f;
    float padding_ = 0.0f;
    bool is_auto_update_layout_enabled_ = true;
    void OnContentChanged();
  };

}
#endif /* !GUIP_ARRAY_PANEL_H */