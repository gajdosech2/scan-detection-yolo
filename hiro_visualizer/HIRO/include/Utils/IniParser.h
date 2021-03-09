/*
  Copyright (C) Skeletex Research, s.r.o. - All Rights Reserved
  Unauthorized copying of this file, via any medium is strictly prohibited
  Proprietary and confidential
*/
#ifndef UTILS_INI_PARSER_H
#define UTILS_INI_PARSER_H
#include <fstream>
#include <Utils/ExtSTD.h>
#include <Utils/ExtGLM.h>
#include <Utils/Dictionary.h>
#include <Utils/Ulog.h>

namespace utils
{

  class IniParser
  {
  public:

    IniParser() = default;

    IniParser(const std::string &filename)
    {
      LoadFile(filename);
    };

    //! Returns the error log as a string.
    std::string PopErrorLog()
    {
      auto log = error_log_;
      error_log_.clear();
      return log;
    }

    //! Get skipped unreadable (most likely non-ASCII) records.
    const std::unordered_set<std::string> &GetUnreadableRecords() const
    {
      return unreadable_records_;
    }

    //! Reads INI values from a file.
    bool LoadFile(const std::string &file_name)
    {
      std::ifstream ifs(file_name);

      if (!ifs.is_open())
      {
        ulog::Fail("Config file \"" + file_name + "\" was not found.");
        return false;
      }

      std::string line;
      std::string section;
      while (std::getline(ifs, line))
      {
        std_ext::Trim(line);
        if (line.empty() || line[0] == '#')
        {
          continue;
        }
        if (line.front() == '[' && line.back() == ']')
        {
          section = line.substr(1, line.length() - 2);
          continue;
        }
        Record record = GetRecord(line);
        if (!record.first.empty())
        {
          if (!std_ext::IsASCII(record.first) || !std_ext::IsASCII(record.second))
          {
            unreadable_records_.emplace(record.first + " : " + record.second);
            continue;
          }

          if (!section.empty())
          {
            record.first = section + "/" + record.first;
          }
          dictionary_.Set(record.first.c_str(), record.second.c_str());
        }
      }

      return true;
    }

    //! Clears config data.
    void Clear()
    {
      error_log_.clear();
      dictionary_.Clear();
    }

    //! If the key does exist in the singletons data, returns true.
    bool Exists(const std::string &key) const
    {
      return dictionary_.IsAvailable(key.c_str());
    }

    //! Returns a string value for the key, if the exists.
    std::string GetStr(const std::string &key, const std::string &default_val = "") const
    {
      if (!Exists(key))
      {
        LogStandardError(key, "'" + default_val + "'");
        return default_val;
      }
      return dictionary_.Get(key.c_str());
    }

    //! Returns a bool value for the key if the key does exist.
    bool GetBool(const std::string &key, const bool default_val = false) const
    {
      if (!Exists(key))
      {
        LogStandardError(key, std_ext::BoolToString(default_val));
        return default_val;
      }
      const std::string val = dictionary_.Get(key.c_str());
      return !(val == "0" || std_ext::Lowercase(val) == "false");
    }

    //! Returns a size_t value for the key if the key does exist.
    size_t GetSizeT(const std::string &key, const size_t default_val = 0) const
    {
      return static_cast<size_t>(GetInt(key, static_cast<int>(default_val)));
    }

    //! Returns a uint value for the key if the key does exist.
    template<typename Type>
    Type GetUint(const std::string &key, const Type default_val = 0) const
    {
      return static_cast<Type>(GetInt(key, static_cast<int>(default_val)));
    }

    //! Returns an int value for the key if the key does exist.
    int GetInt(const std::string &key, const int default_val = 0) const
    {
      if (!Exists(key))
      {
        LogStandardError(key, std::to_string(default_val));
        return default_val;
      }
      return std::stoi(dictionary_.Get(key.c_str()));
    }

    //! Returns an float value for the key if the key does exist.
    float GetFloat(const std::string &key, const float default_val = 0.0f) const
    {
      if (!Exists(key))
      {
        LogStandardError(key, std::to_string(default_val));
        return default_val;
      }
      return std::stof(dictionary_.Get(key.c_str()));
    }

    //! Returns a double value for the key if the key does exist.
    double GetDouble(const std::string &key, const double default_val = 0.0) const
    {
      if (!Exists(key))
      {
        LogStandardError(key, std::to_string(default_val));
        return default_val;
      }
      return std::stod(dictionary_.Get(key.c_str()));
    }

    //! Returns a glm::vec value for the key if the key does exist.
    template <glm::length_t N, typename Type>
    glm::vec<N, Type, glm::highp> GetVec(const std::string &key, const glm::vec<N, Type, glm::highp> default_val = glm::vec<N, Type, glm::highp>(0))
    {
      if (!Exists(key))
      {
        LogStandardError(key, "(" + glm_ext::to_string(default_val, ",") + ")");
        return default_val;
      }
      auto elements = std_ext::Parse(dictionary_.Get(key.c_str()), " ");
      if (elements.size() != N)
      {
        auto el0 = std::to_string(N);
        auto el1 = std::to_string(elements.size());
        error_log_ += "[" + key + "] key contains invalid value.";
        error_log_ += "Expected vector of " + el0 + " elements, not " + el1 + ".";
        error_log_ += "Using (" + glm_ext::to_string(default_val, ", ") + ")\n";
        return default_val;
      }
      glm::vec<N, Type, glm::highp> result;
      for (glm::length_t i = 0; i < N; ++i)
      {
        result[i] = Type(std::stod(elements[i]));
      }
      return result;
    }

    //! Returns a std::vector<float> value for the key if the key does exist.
    std::vector<float> GetFloatArray(const std::string &key, const std::vector<float> &default_val = {}) const
    {
      const auto result = std_ext::Transformed(GetArray(key), [this, key](std::string number_as_string)
      {
        return std::stof(number_as_string);
      });

      return result.empty() ? default_val : result;
    }

    //! Returns a std::vector<int> value for the key if the key does exist.
    std::vector<int> GetIntArray(const std::string &key, const std::vector<int> &default_val = {}) const
    {
      const auto result = std_ext::Transformed(GetArray(key), [this, key](std::string number_as_string)
      {
        return std::stoi(number_as_string);
      });

      return result.empty() ? default_val : result;
    }

    //! Returns a std::vector<bool> value for the key if the key does exist.
    std::vector<bool> GetBoolArray(const std::string &key, const std::vector<bool> &default_val = {}) const
    {
      const auto result = std_ext::Transformed(GetArray(key), [this, key](std::string number_as_string)
      {
        return !(number_as_string == "0" || std_ext::Lowercase(number_as_string) == "false");
      });

      return result.empty() ? default_val : result;
    }

    //! Returns a std::vector<std::string> value for the key if the key does exist.
    std::vector<std::string> GetArray(const std::string &key, const std::vector<std::string> &default_val = {}) const
    {
      std::string next_arr_key = key + "[0]";
      std::vector<std::string> result;
      if (!Exists(next_arr_key))
      {
        LogStandardError(next_arr_key, "empty array");
        return default_val;
      }
      uint32_t next_i = 1;
      while (Exists(next_arr_key))
      {
        result.emplace_back(dictionary_.Get(next_arr_key.c_str()));
        next_arr_key = key + "[" + std::to_string(next_i) + "]";
        ++next_i;
      }
      return result;
    }

  protected:
    std::map<std::string, std::string> replacement_map_;
    const bool is_replacement_map_enabled_ = false;
    utils::Dictionary dictionary_;
    mutable std::string error_log_;
    mutable std::unordered_set<std::string> unreadable_records_;

    void LogStandardError(const std::string &key, const std::string &val) const
    {
      error_log_ += "[" + key + "] key not found, using " + val + ".\n\r";
    }

    using Record = std::pair<std::string, std::string>;

    virtual Record GetRecord(const std::string &line)
    {
      Record record;
      size_t delim_pos = line.find_first_of("=");
      if (delim_pos == std::string::npos)
      {
        record = Record(line, "0");
      }
      else
      {
        record.first = line.substr(0, delim_pos);
        record.second = line.substr(delim_pos + 1, line.size());
      }
      std_ext::Trim(record.first);
      std_ext::Trim(record.second);

      if (record.second.size() >= 2 && record.second.front() == '"' && record.second.back() == '"')
      {
        record.second = record.second.substr(1, record.second.length() - 2);
      }

      if (is_replacement_map_enabled_)
      {
        record.second = std_ext::Replace(record.second, replacement_map_);
      }

      return record;
    }

  };

}
#endif /* !UTILS_INI_PARSER_H */