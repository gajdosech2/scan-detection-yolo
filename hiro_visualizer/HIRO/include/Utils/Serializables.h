/*
  Copyright (C) Skeletex Research, s.r.o. - All Rights Reserved
  Unauthorized copying of this file, via any medium is strictly prohibited
  Proprietary and confidential
*/
#ifndef UTILS_SERIALIZABLES_H
#define UTILS_SERIALIZABLES_H

#include <cereal/cereal.hpp>

#include <glm/vec3.hpp>
#include <glm/gtc/quaternion.hpp>



namespace utils
{

  //! Serializable extension of glm::vec3.
  class GlmVec3Serializable
  {
    friend class cereal::access;

  public:
    float x, y, z;

    GlmVec3Serializable() : GlmVec3Serializable(glm::vec3()) {}
    explicit GlmVec3Serializable(const glm::vec3 &v) : x(v.x), y(v.y), z(v.z) {}

    glm::vec3 ToVec3() const { return glm::vec3(x, y, z); }

  private:
    template <class Archive>
    void serialize(Archive &ar)
    {
      ar(CEREAL_NVP(x), CEREAL_NVP(y), CEREAL_NVP(z));
    }
  };



  //! Serializable extension of glm::quat.
  class GlmQuatSerializable
  {
    friend class cereal::access;

  public:
    float x, y, z, w;

    GlmQuatSerializable() : GlmQuatSerializable(glm::quat()) {}
    explicit GlmQuatSerializable(const glm::quat &q) : x(q.x), y(q.y), z(q.z), w(q.w) {}

    glm::quat ToQuat() const { return glm::quat(w, x, y, z); }

  private:
    template <class Archive>
    void serialize(Archive &ar)
    {
      ar(CEREAL_NVP(x), CEREAL_NVP(y), CEREAL_NVP(z), CEREAL_NVP(w));
    }
  };

}
#endif /* !UTILS_SERIALIZABLES_H */