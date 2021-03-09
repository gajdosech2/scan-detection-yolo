/*
  Copyright (C) Skeletex Research, s.r.o. - All Rights Reserved
  Unauthorized copying of this file, via any medium is strictly prohibited
  Proprietary and confidential
*/
#ifndef HIRO_API_H
#define HIRO_API_H

#ifdef _WIN32
# ifdef HIRO_EXPORT
#   define HIRO_API __declspec(dllexport)
# else
#   define HIRO_API __declspec(dllimport)
# endif
#else
# define HIRO_API __attribute__ ((visibility("default")))
#endif

//! Global engine namespace containing core definitions.
namespace hiro
{
  //! Default modules included directly in the library.
  namespace modules {}

  //! Control structures for customization and automatic generation of GUI.
  namespace gui {}
}

#endif /* !HIRO_API_H */