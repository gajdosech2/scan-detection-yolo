/*
  Copyright (C) Skeletex Research, s.r.o. - All Rights Reserved
  Unauthorized copying of this file, via any medium is strictly prohibited
  Proprietary and confidential
*/
#ifndef HIRO_GEOMETRY_GADGET_H
#define HIRO_GEOMETRY_GADGET_H
#include <modules/GeometryResource.h>



namespace hiro::modules
{

  //! Gadget that renders geometry using hiro::draw::GeometryRenderer.
  class HIRO_API GeometryGadget : public hiro::Gadget
  {
  public:
    GeometryGadget(
      const hiro::Resource *res,
      const hiro::draw::PGeometryRenderer &renderer);
    GeometryGadget(
      const hiro::Resource *res,
      const hiro::draw::PGeometryRenderer &renderer,
      const hiro::draw::PGeometryStyle &style_);
    void Initialize() override;
    void GenerateGui(hiro::GuiGenerator &gui) override;

  protected:
    hiro::draw::PGeometryStyle GetStyle();

    bool ReadFromStream(std::istream &str) override;
    void WriteToStream(std::ostream &str) const override;

    void AddGuiRenderMode(hiro::GuiGenerator &gui);
    void AddGuiMaterialOptions(hiro::GuiGenerator &gui);
    void AddGuiCullBackFacning(hiro::GuiGenerator &gui);
    void AddGuiColorSource(hiro::GuiGenerator &gui);
    void AddGuiDisplayNormals(hiro::GuiGenerator &gui);
    void AddGuiWireParameters(hiro::GuiGenerator &gui);

  private:
    const hiro::draw::PGeometryRenderer renderer_;
    int32_t loaded_matcap_sampler_id_ = 5;
    hiro::draw::PGeometryStyle style_;
    gui::Checkbox *matcap_enabled_;
    gui::Droplist *matcap_selector_;
    void LoadMatcapSampler();
    void AddGuiMatcapSelector(hiro::GuiGenerator &gui);
  };

}

#endif /* !HIRO_GEOMETRY_GADGET_H */