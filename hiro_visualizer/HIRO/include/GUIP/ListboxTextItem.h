#ifndef GUIP_LISTBOX_TEXT_ITEM_H
#define GUIP_LISTBOX_TEXT_ITEM_H
#include <CEGUI/widgets/ListboxTextItem.h>
#include <GUIP/API.h>

namespace guip
{
  //! A single item of a combobox drop list.
  class GUIP_API ListboxTextItem : public CEGUI::ListboxTextItem
  {
  public:
    //! Unique gui system identifier.
    static CEGUI::String WidgetTypeName;
    ListboxTextItem(const std::string &text, uint32_t item_id = 0);
    //! Sets padding on top and bottom of the item.
    void SetVertPadding(float padding);
    //! Returns padding on top and bottom of the item.
    float GetVertPadding();

    //! Returns size of item in pixels.
    CEGUI::Sizef getPixelSize(void) const override;
    //! Draws an item. This function is called automatically by a gui system.
    void draw(CEGUI::GeometryBuffer &buffer, const CEGUI::Rectf &targetRect,
      float alpha, const CEGUI::Rectf *clipper) const override;
  protected:
    float padding_ = 0.0f;
  };

}
#endif /* !GUIP_LISTBOX_TEXT_ITEM_H */