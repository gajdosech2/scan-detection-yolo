/*
  Copyright (C) Skeletex Research, s.r.o. - All Rights Reserved
  Unauthorized copying of this file, via any medium is strictly prohibited
  Proprietary and confidential
*/
#ifndef HIRO_GUI_PANEL_H
#define HIRO_GUI_PANEL_H
#include <functional>
#include <CEGUI/CEGUI.h>
#include <COGS/Color.h>
#include <HIRO/API.h>



namespace hiro
{

  //! Base class for panels in gui system.
  class GuiPanel
  {
  public:

    GuiPanel();

    virtual ~GuiPanel();

    //! Sets the height of panel to the new value in pixels.
    virtual void SetHeight(uint32_t pixel_height);

    //! Sets callback which is evoked when user requests panel to close.
    void SetCallbackClose(const std::function<void(void)> &callback);

    //! Sets callback which is evoked when user requests panel to pin.
    void SetCallbackPin(const std::function<void(void)> &callback);

    //! Places this to the children list of specified container.
    void Embed(CEGUI::VerticalLayoutContainer *parent_containter);

    //! Toggles visibility for this panel. Adds and removes it to/from parent container.
    void SetVisible(bool visible);

    bool IsVisible();

    //! Sets callback which is evoked when user requests panel to focus.
    void SetCallbackFocus(const CEGUI::Event::Subscriber &subscriber);

    //! Returns pointer to the frame window.
    CEGUI::Window *GetWidget();

    //! Sets the title name in the header.
    void SetTitle(const std::string &title);

    //! Enables/disables focus button in the header. Initially disabled.
    void SetFocusButtonEnabled(bool enabled);

    //! Enables/disables pin button in the header. Initially disabled.
    void SetPinButtonEnabled(bool enabled);

    //! Enables/disables close button in the header. Initially enabled.
    void SetCloseButtonEnabled(bool enabled);

  protected:

    static const float DEFAULT_LEFT_MARGIN;
    static const float DEFAULT_BOTTOM_MARGIN;

    //! Creates custom client window element in the panel body.
    void CreateClientWindow(const std::string &layout_xml = "");

    //! Sets custom client window element in the panel body.
    void SetClientWindow(CEGUI::Window *client_window);

    //! Changes color of the header bar.
    void SetHeaderColor(const cogs::Color4hex &color);

    //! Returns pointer to the client window in the panel body.
    CEGUI::Window *GetClientWindow();

    //! Sets left and bottom margins for this.
    void SetMargins(float left, float bottom);

  private:
    CEGUI::Window *header_ = nullptr;
    CEGUI::Window *client_win_ = nullptr;
    CEGUI::Window *panel_ = nullptr;

    bool is_visible_ = true;
    bool is_rolledup_ = false;
    float true_height_;

    CEGUI::VerticalLayoutContainer *container_ = nullptr;

    std::function<void(void)> close_callback_;
    std::function<void(void)> pin_callback_;

    bool OnRollClick(const CEGUI::EventArgs &e);
    bool OnPinClick(const CEGUI::EventArgs &e);
    bool OnRemoveClick(const CEGUI::EventArgs &e);
    bool OnClientSizeChange(const CEGUI::EventArgs &e);
  };

}
#endif /* !HIRO_GUI_PANEL_H */