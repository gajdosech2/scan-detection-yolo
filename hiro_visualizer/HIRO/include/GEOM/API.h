#ifndef GEOM_API_H
#define GEOM_API_H

#ifdef _WIN32
# ifdef GEOM_STATIC
#   define GEOM_API
# elif GEOM_EXPORT
#   define GEOM_API __declspec(dllexport)
# else
#   define GEOM_API __declspec(dllimport)
# endif
#else
# define GEOM_API __attribute__ ((visibility("default")))
#endif
#endif /* !GEOM_API_H */