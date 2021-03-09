#ifndef GUIP_COMBOBOX_H
#define GUIP_COMBOBOX_H
#include <CEGUI/widgets/Combobox.h>
#include <GUIP/API.h>

namespace guip
{
  //! Widget that allows user to pick an item from the dropdown list. Each item can have an index assigned.
  class GUIP_API Combobox : public CEGUI::Combobox
  {
  public:
    //! Unique gui system identifier.
    static CEGUI::String WidgetTypeName;

    Combobox(const CEGUI::String &type, const CEGUI::String &name);
    //! Selects first item which has defined text.
    void SetSelectedByText(const std::string &text);
    //! Returns text of selected item.
    std::string GetTextOfSelected() const;
    //! Selects first item which has defined value.
    void SetSelectedByValue(const int32_t value);
    //! Returns value of selected item. If no item is selected, returns -1.
    int32_t GetValueOfSelected() const;
    //! Adds a single item to the list. Position in the list determines value of item.
    void AddItem(const std::string &name);
    //! Adds a single item to the list.
    void AddValueItem(const std::string &name, int32_t value);
    //! Adds multiple items by name. Position in the list determines value of item.
    void AddItems(const std::vector<std::string> &items);
    //! Adds multiple items by pair <name,value>.
    void AddValueItems(const std::vector<std::pair<std::string, int32_t>> &items);
    //! Removes all items from selection list.
    void ClearItems();

  private:
    bool OnEnabled();
    bool OnDisabled();
    void onDropListDisplayed(CEGUI::WindowEventArgs &e) override;
  };

}
#endif /* !GUIP_COMBOBOX_H */