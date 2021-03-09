#ifndef GLW_API_H
#define GLW_API_H

#ifdef _WIN32
# ifdef GLW_STATIC
#   define GLW_API
# elif GLW_EXPORT
#   define GLW_API __declspec(dllexport)
# else
#   define GLW_API __declspec(dllimport)
# endif
#else
# define GLW_API __attribute__ ((visibility("default")))
#endif

//! OpenGL wrapper library namespace. Provides simplified interface for using OpenGL features.
namespace glw {}

#endif /* !GLW_API_H */