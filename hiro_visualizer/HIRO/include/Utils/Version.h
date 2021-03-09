#ifndef UTILS_VERSION_H
#define UTILS_VERSION_H
#include <Utils/ExtSTD.h>

//major and minor are macros in glibc <sys/sysmacros.h>
//The dependency on <sys/sysmacros.h> should be removed in future releases of glibc.
#undef major
#undef minor

namespace utils
{


  //! Holder for project version.
  struct Version
  {
    Version() = default;

    Version(uint32_t maj, uint32_t min = 0, uint32_t pat = 0) : major(maj), minor(min), patch(pat) {};

    Version(const std::string &version_str)
    {
      const auto version_nums = std_ext::Parse(version_str, ".");
      major = version_nums.empty() ? 0 : std::stoul(version_nums[0]);
      minor = version_nums.size() <= 1 ? 0 : std::stoul(version_nums[1]);
      patch = version_nums.size() <= 2 ? 0 : std::stoul(version_nums[2]);
    };

    //! Returns version in string form. Major, minor and patch numbers separated by dots.
    std::string ToString() const
    {
      return std::to_string(major) + "." + std::to_string(minor) + "." + std::to_string(patch);
    };

    uint32_t major{ 0u };
    uint32_t minor{ 0u };
    uint32_t patch{ 0u };
  };

  inline bool operator<(const Version &a, const Version &b)
  {
    if (a.major == b.major)
    {
      if (a.minor == b.minor)
      {
        return a.patch < b.patch;
      }
      return a.minor < b.minor;
    }
    return a.major < b.major;
  }

  inline bool operator>(const Version &a, const Version &b)
  {
    if (a.major == b.major)
    {
      if (a.minor == b.minor)
      {
        return a.patch > b.patch;
      }
      return a.minor > b.minor;
    }
    return a.major > b.major;
  }

  inline bool operator<=(const Version &a, const Version &b)
  {
    return !(a > b);
  }

  inline bool operator>=(const Version &a, const Version &b)
  {
    return !(a < b);
  }

  inline bool operator==(const Version &a, const Version &b)
  {
    return (a.major == b.major) && (a.minor == b.minor) && (a.patch == b.patch);
  }

  inline bool operator!=(const Version &a, const Version &b)
  {
    return !(a == b);
  }

}
#endif /* !UTILS_VERSION_H */