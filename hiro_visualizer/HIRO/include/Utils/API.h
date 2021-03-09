#ifndef UTILS_API_H
#define UTILS_API_H

#ifdef _WIN32
# ifdef UTILS_STATIC
#   define UTILS_API
# elif UTILS_EXPORT
#   define UTILS_API __declspec(dllexport)
# else
#   define UTILS_API __declspec(dllimport)
# endif
#else
# define UTILS_API __attribute__ ((visibility("default")))
#endif
#endif /* !UTILS_API_H */