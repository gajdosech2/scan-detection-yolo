/*
  Copyright (C) Skeletex Research, s.r.o. - All Rights Reserved
  Unauthorized copying of this file, via any medium is strictly prohibited
  Proprietary and confidential
*/
#ifndef HIRO_GEOMETRY_RESOURCE_H
#define HIRO_GEOMETRY_RESOURCE_H
#include <HIRO_DRAW/renderers/GeometryRenderer.h>
#include <HIRO/Resource.h>



namespace hiro::modules
{

  //! Resource that holds and visualizes geometry.
  class HIRO_API GeometryResource final : public hiro::Resource
  {
  public:
    //! Creates new resource object that displays default geometry.
    explicit GeometryResource(const std::string &name);
    //! Creates new resource object that displays specified geometry.
    GeometryResource(const std::string &name, hiro::draw::GeometryName geom_name);
    //! Changes geometry currently being used.
    void SetGeometry(hiro::draw::GeometryName geom_name);
    //! Returns name of geometry currently being used.
    hiro::draw::GeometryName GetGeometry() const;
  private:
    hiro::PGadget CreateGadget() override;
    hiro::draw::PGeometryRenderer renderer_;
    hiro::draw::GeometryName current_geometry_{ hiro::draw::GeometryName::cube };
  };

}

#endif /* !HIRO_GEOMETRY_RESOURCE_H */