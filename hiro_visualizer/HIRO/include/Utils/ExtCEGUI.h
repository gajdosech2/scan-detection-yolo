/*
  Copyright (C) Skeletex Research, s.r.o. - All Rights Reserved
  Unauthorized copying of this file, via any medium is strictly prohibited
  Proprietary and confidential
*/
#ifndef UTILS_EXT_CEGUI_H
#define UTILS_EXT_CEGUI_H
#include <CEGUI/CEGUI.h>
#include <Utils/ExtSTD.h>

//! Extensions to the CEGUI library.
namespace cegui_ext
{
  //! Check CEGUI String for non-ASCII characters.
  inline bool IsASCII(const CEGUI::String &str)
  {
    return str.length() == str.utf8_stream_len();
  }

  //! Check Multiple CEGUI Strings for non-ASCII characters.
  inline bool AreAllASCII(const std::vector<CEGUI::String> &strings)
  {
    return std_ext::AllOf(strings, [](const CEGUI::String & str) { return IsASCII(str); });
  }
}

#endif /* !UTILS_EXT_CEGUI_H */