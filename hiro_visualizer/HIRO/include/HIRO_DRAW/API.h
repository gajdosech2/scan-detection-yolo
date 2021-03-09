#ifndef HIRO_DRAW_API_H
#define HIRO_DRAW_API_H

#ifdef _WIN32
# ifdef HIRO_DRAW_STATIC
#   define HIRO_DRAW_API
# elif HIRO_DRAW_EXPORT
#   define HIRO_DRAW_API __declspec(dllexport)
# else
#   define HIRO_DRAW_API __declspec(dllimport)
# endif
#else //_WIN32
# define HIRO_DRAW_API __attribute__ ((visibility("default")))
#endif //_WIN32


namespace hiro
{
  //! Extensions for object visualization. Implements a higher level of OpenGL rendering.
  namespace draw {}

  //! Interface for writing shaders. Contains C++ definitions equivalent to GLSL definitions.
  namespace shader {}
}

#endif /* !HIRO_DRAW_API_H */