/*
  Copyright (C) Skeletex Research, s.r.o. - All Rights Reserved
  Unauthorized copying of this file, via any medium is strictly prohibited
  Proprietary and confidential
*/
#pragma once
#include <nlohmann/json.hpp>
#include <Utils/API.h>



namespace utils
{
  /*!
     \brief Abstration of a class that supports serialization to json strings.

     When inheriting this class, be sure to overload methods AddToJsonNode and ReadFromJsonNode,
     that should contain implementation of your json serialization.
  */
  struct UTILS_API SerializableJson
  {
    //! Stores object to json string.
    [[nodiscard]] std::string Serialize() const;
    //! Loads object from json string.
    bool Deserialize(const std::string &json_string);
    //! Fill data of this to json node.
    virtual void AddToJsonNode(nlohmann::json &parent_node) const = 0;
    //! \brief Read json node and initialize this.
    //! \throws nlohmann::json::exception when required keys are missing.
    virtual bool ReadFromJsonNode(const nlohmann::json &parent_node) = 0;
  };
}