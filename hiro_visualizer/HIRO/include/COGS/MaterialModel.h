/*
  Copyright (C) Skeletex Research, s.r.o. - All Rights Reserved
  Unauthorized copying of this file, via any medium is strictly prohibited
  Proprietary and confidential
*/
#ifndef COGS_MATERIAL_MODEL_H
#define COGS_MATERIAL_MODEL_H
#include <array>

#include <COGS/Color.h>
#include <COGS/API.h>

namespace cogs
{

  enum class MaterialTextures : uint8_t
  {
    diffuse,
    normal,
    displace,
    _count
  };

  enum class MaterialColors : uint8_t
  {
    ambient,
    diffuse,
    specular,
    _count
  };

  struct COGS_API Material
  {
    Material();
    Material(const cogs::Color4b &color, uint32_t shininess);
    cogs::Color4b GetColor(const MaterialColors &type);
    // sets all available colors to a defined value
    void SetAllColors(const cogs::Color4b &new_color);
    std::array<cogs::Color4b, size_t(MaterialColors::_count)> color;
    uint32_t shininess = 60;
  };

  class COGS_API MaterialModel
  {
  public:
    cogs::Color4b GetMaterialColor(const MaterialColors &c_type) const;
    void SetMaterialColor(const MaterialColors &c_type, const cogs::Color4b &new_color);
    void SetMaterialColors(const cogs::Color4b &new_color);

    uint32_t GetMaterialShininess() const;
    void SetMaterialShininess(const uint32_t value);

    std::string GetTextureFile(const MaterialTextures &t_type) const;
    void SetTextureFile(const MaterialTextures &t_type, const std::string &texture);

  private:
    Material material_;
    std::array<std::string, size_t(MaterialTextures::_count)> textures_;
  };

}
#endif /* !COGS_MATERIAL_MODEL_H */