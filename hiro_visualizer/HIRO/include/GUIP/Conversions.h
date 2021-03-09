#ifndef GUIP_CONVERSIONS_H
#define GUIP_CONVERSIONS_H
#include <glm/glm.hpp>
#ifdef __GNUC__
#undef True
#undef False
#undef None
#endif
#include <CEGUI/CEGUI.h>
#include <GUIP/API.h>

//! Extensions to the CEGUI library.
namespace guip
{

  //! Converts CEGUI Vector2f to glm::tvec2.
  template <typename CastType = float>
  inline glm::vec<2, CastType> ToVec(const CEGUI::Vector2f &vector)
  {
    return glm::vec<2, CastType>(CastType(vector.d_x), CastType(vector.d_y));
  }

  //! Converts CEGUI Sizef to glm::tvec2.
  template <typename CastType = float>
  inline glm::vec<2, CastType> ToVec(const CEGUI::Sizef &size)
  {
    return glm::vec<2, CastType>(CastType(size.d_width), CastType(size.d_height));
  }

  //! Converts UDim to a string form.
  GUIP_API std::string ToString(const CEGUI::UDim &dim);

  //! Converts UVector to a string form.
  GUIP_API std::string ToString(const CEGUI::UVector2 &vec);

  //! Converts USize to a string form.
  GUIP_API std::string ToString(const CEGUI::USize &siz);

}

#endif /* !GUIP_CONVERSIONS_H */