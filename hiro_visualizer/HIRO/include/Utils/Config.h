/*
  Copyright (C) Skeletex Research, s.r.o. - All Rights Reserved
  Unauthorized copying of this file, via any medium is strictly prohibited
  Proprietary and confidential
*/
#ifndef UTILS_CONFIG_H
#define UTILS_CONFIG_H
#include <Utils/IniParser.h>
#include <Utils/Ulog.h>



//! Singleton for holding and requesting configuration file parameters.
class Config
{
public:

  //! Returns the error log as a string.
  static std::string PopErrorLog()
  {
    return GetParser().PopErrorLog();
  }

  //! Get skipped unreadable (most likely non-ASCII) records.
  static const std::unordered_set<std::string> &GetUnreadableRecords()
  {
    return GetParser().GetUnreadableRecords();
  }

  //! Loads config file into the config singleton.
  static bool LoadFile(const std::string &file_name)
  {
    return GetParser().LoadFile(file_name);
  }

  //! Clears config data.
  static void Clear()
  {
    GetParser().Clear();
  }

  //! If the key does exist in the singletons data, returns true.
  static bool Exists(const std::string &key)
  {
    return GetParser().Exists(key);
  }

  //! Returns a string value for the key, if the exists.
  static std::string GetStr(const std::string &key, const std::string &default_val = "")
  {
    auto str = GetParser().GetStr(key, default_val);
    if (!std_ext::IsASCII(str))
    {
      ulog::Warn("Unsupported non-international character in config file: '" + key + "'. Using default value '" + default_val + "'.", "Config::GetStr");
      return default_val;
    }

#if defined(REPO_DIR) && !defined(_DEPLOY)
    str = std_ext::Replace(str, "$REPO_DIR$", REPO_DIR);
#endif
    return str;
  }

  //! Returns a bool value for the key if the key does exist.
  static bool GetBool(const std::string &key, const bool default_val = false)
  {
    return GetParser().GetBool(key, default_val);
  }

  //! Returns a size_t value for the key if the key does exist.
  static size_t GetSizeT(const std::string &key, const size_t default_val = 0)
  {
    return GetParser().GetSizeT(key, default_val);
  }

  //! Returns an unsigned integer value for the key if the key does exist.
  template<typename T>
  static T GetUint(const std::string &key, const T default_val = 0)
  {
    return GetParser().GetUint<T>(key, default_val);
  }

  //! Returns an int value for the key if the key does exist.
  static int GetInt(const std::string &key, const int default_val = 0)
  {
    return GetParser().GetInt(key, default_val);
  }

  //! Returns an float value for the key if the key does exist.
  static float GetFloat(const std::string &key, const float default_val = 0.0f)
  {
    return GetParser().GetFloat(key, default_val);
  }

  //! Returns a double value for the key if the key does exist.
  static double GetDouble(const std::string &key, const double default_val = 0.0)
  {
    return GetParser().GetDouble(key, default_val);
  }

  //! Returns a glm::vec value for the key if the key does exist.
  template <glm::length_t N, typename Type>
  static glm::vec<N, Type, glm::highp> GetVec(const std::string &key, const glm::vec<N, Type, glm::highp> default_val = glm::vec<N, Type, glm::highp>(0))
  {
    return GetParser().GetVec(key, default_val);
  }

  //! Returns a std::vector<std::string> value for the key if the key does exist.
  static std::vector<std::string> GetArray(const std::string &key, const std::vector<std::string> &default_val = {})
  {
    return GetParser().GetArray(key, default_val);
  };

  //! Returns a std::vector<float> value for the key if the key does exist.
  static std::vector<float> GetFloatArray(const std::string &key, const std::vector<float> &default_val = {})
  {
    return GetParser().GetFloatArray(key, default_val);
  };

  //! Returns a std::vector<int> value for the key if the key does exist.
  static std::vector<int> GetIntArray(const std::string &key, const std::vector<int> &default_val = {})
  {
    return GetParser().GetIntArray(key, default_val);
  };

  //! Returns a std::vector<bool> value for the key if the key does exist.
  static std::vector<bool> GetBoolArray(const std::string &key, const std::vector<bool> &default_val = {})
  {
    return GetParser().GetBoolArray(key, default_val);
  };

private:

  utils::IniParser parser_;

  Config() = default;

  static Config &Self()
  {
    static Config instance; // Guaranteed to be destroyed.
    // Instantiated on first use.
    return instance;
  }

  static utils::IniParser &GetParser()
  {
    return Self().parser_;
  }
};
#endif /* !UTILS_CONFIG_H */