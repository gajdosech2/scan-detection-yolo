/*
  Copyright (C) Skeletex Research, s.r.o. - All Rights Reserved
  Unauthorized copying of this file, via any medium is strictly prohibited
  Proprietary and confidential
*/
#ifndef UTILS_SERIALIZER_H
#define UTILS_SERIALIZER_H

#include <fstream>
#include <cereal/archives/json.hpp>
#include <cereal/types/vector.hpp>

#include <Utils/ExtSTD.h>



namespace utils
{

  /*!
    \brief
      Serialization utility class. Can perform automatic read and write.

      Uses the "cereal" serialization library - https://uscilab.github.io/cereal/index.html.
      Cereal allows the possibility to save-load in formats:
        - Binary
        - JSON
        - XML
      So far this library only makes use of the "JSON" option.
  */
  template <typename Type, typename SerializableType>
  class Serializer
  {

  public:

    explicit Serializer(const std::string &root_name)
      : root_name_(root_name)
    {
    }



    //! Read JSON string.
    [[nodiscard]]
    std::vector<Type> FromJsonString(const std::string &json_string) const
    {
      return FromString<cereal::JSONInputArchive>(json_string);
    }

    //! Read JSON string, return as shared pointers.
    [[nodiscard]]
    std::vector<std::shared_ptr<Type>> FromJsonStringAsPtr(const std::string& json_string) const
    {
      return std_ext::Transformed(FromJsonString(json_string), [](const auto& val){ return std::make_shared<Type>(val); });
    }

    //! Serialize to JSON string.
    [[nodiscard]]
    std::string ToJsonString(const std::vector<Type> &objects) const
    {
      return ToString<cereal::JSONOutputArchive>(objects);
    }

    //! Read from JSON file by path.
    [[nodiscard]]
    std::vector<Type> FromJsonFile(const std::string &file_path) const
    {
      return FromFile<cereal::JSONInputArchive>(file_path);
    }

    //! Read from JSON file by path, return as shared pointers.
    [[nodiscard]]
    std::vector<std::shared_ptr<Type>> FromJsonFileAsPtr(const std::string& file_path) const
    {
      return std_ext::Transformed(FromJsonFile(file_path), [](const auto& val) { return std::make_shared<Type>(val); });
    }

    //! Serialize to JSON string and save to file.
    [[nodiscard]]
    bool ToJsonFile(const std::vector<Type> &objects, const std::string &file_path) const
    {
      return ToFile<cereal::JSONOutputArchive>(objects, file_path);
    }



  private:
    //! Read from string.
    template <typename ArchiveType>
    [[nodiscard]]
    std::vector<Type> FromString(const std::string &json_string) const
    {
      try
      {
        std::stringstream ss;
        ss << json_string;
        std::vector<SerializableType> serializables;
        ArchiveType archive(ss);
        archive >> serializables;
        return std_ext::Transformed(serializables, [](const auto & s) { return s.To(); });
      }
      catch (const std::exception &e)
      {
        std::cout << e.what();
        return std::vector<Type>();
      }
    }

    //! Serialize to string.
    template <typename ArchiveType>
    [[nodiscard]]
    std::string ToString(const std::vector<Type> &objects) const
    {
      std::stringstream ss;
      {
        ArchiveType archive(ss);
        const std::vector<SerializableType> serializables = std_ext::Transformed(objects, [](const auto & s) { return SerializableType(s); });
        archive << ::cereal::make_nvp(root_name_, serializables);
      }

      return ss.str();
    }

    //! Serialize from file by path.
    template <typename ArchiveType>
    [[nodiscard]]
    std::vector<Type> FromFile(const std::string &file_path) const
    {
      try
      {
        std::ifstream is(file_path.c_str());

        if (is.is_open())
        {
          ArchiveType archive(is);
          std::vector<SerializableType> serializables;
          archive >> serializables;
          return std_ext::Transformed(serializables, [](const auto & s) { return s.To(); });
        }
        else
        {
          std::cout << "Could not open file: " << file_path << '\n';
          return std::vector<Type>();
        }
      }
      catch (const std::exception &e)
      {
        std::cout << e.what();
        return std::vector<Type>();
      }
    }

    //! Serialize and save to file.
    template <typename ArchiveType>
    [[nodiscard]]
    bool ToFile(const std::vector<Type> &objects, const std::string &file_path) const
    {
      try
      {
        std::ofstream os(file_path);
        if (os.is_open())
        {
          ArchiveType archive(os);
          const std::vector<SerializableType> serializables = std_ext::Transformed(objects, [](const auto & s) { return SerializableType(s); });
          archive << ::cereal::make_nvp(root_name_, serializables);
          return true;
        }
        else
        {
          std::cout << "Could not open file: " << file_path << '\n';
          return false;
        }
      }
      catch (const std::exception &e)
      {
        std::cout << e.what();
        return false;
      }

      return false;
    }


    //! The name of root element when saving to file/string/...
    const std::string root_name_;
  };

}

#endif /* !UTILS_SERIALIZER_H */