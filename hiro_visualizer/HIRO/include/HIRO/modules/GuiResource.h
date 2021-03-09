/*
  Copyright (C) Skeletex Research, s.r.o. - All Rights Reserved
  Unauthorized copying of this file, via any medium is strictly prohibited
  Proprietary and confidential
*/
#ifndef HIRO_GUI_RESOURCE_H
#define HIRO_GUI_RESOURCE_H
#include <CEGUI/CEGUI.h>
#include <HIRO/Resource.h>



namespace hiro::modules
{

  //! Enables creation of custom gui objects. Soon will be deprecated.
  class HIRO_API GuiResource final : public hiro::Resource
  {
  public:
    GuiResource(const std::string &name);
    hiro::PGadget CreateGadget() override;
    void Setup(const std::string &layout_xml);
    CEGUI::Window *GetWindow(const std::string &name);
    CEGUI::Window *GetRootWindow();
    CEGUI::Window *GetMainRootWindow();
    template <typename T>
    T *GetWindow(const std::string &name)
    {
      return static_cast<T *>(GetWindow(name));
    }
  protected:
    CEGUI::Window *window_root_ = nullptr;
    GuiResource(const hiro::ResourceId &id);
  };

}

#endif /* !HIRO_GUI_RESOURCE_H */