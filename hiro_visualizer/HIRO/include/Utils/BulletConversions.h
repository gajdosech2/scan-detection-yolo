#ifndef UTILS_BULLET_CONVERSIONS_H
#define UTILS_BULLET_CONVERSIONS_H
#include <bullet3/LinearMath/btVector3.h>
#include <bullet3/LinearMath/btQuaternion.h>
#include <glm/vec3.hpp>
#include <glm/gtc/quaternion.hpp>
#include <Eigen/Eigen>

namespace utils
{

  //! Converts bullet vector to glm vector.
  inline glm::vec3 BulletToGlmVec(const btVector3 &bt_vec)
  {
    return glm::vec3(bt_vec.x(), bt_vec.y(), bt_vec.z());
  }

  //! Converts bullet quaternion to glm quaternion.
  inline glm::quat BulletToGlmQuat(const btQuaternion &bt_quat)
  {
    return glm::quat(
        static_cast<float>(bt_quat.w()),
        static_cast<float>(bt_quat.x()),
        static_cast<float>(bt_quat.y()),
        static_cast<float>(bt_quat.z())
      );
  }

  //! Converts bullet vector to Eigen vector.
  inline Eigen::Vector3d BulletToEigenVec(const btVector3 &bt_vec)
  {
    return Eigen::Vector3d(bt_vec.x(), bt_vec.y(), bt_vec.z());
  }

  //! Converts bullet quaternion to Eigen quaternion.
  inline Eigen::Quaterniond BulletToEigenQuat(const btQuaternion &bt_quat)
  {
    return Eigen::Quaterniond(bt_quat.w(), bt_quat.x(), bt_quat.y(), bt_quat.z());
  }

  //! Converts glm vector to bullet vector.
  inline btVector3 GlmToBulletVec(const glm::vec3 &vec)
  {
    return btVector3(vec.x, vec.y, vec.z);
  }

  //! Converts glm quaternion to bullet quaternion.
  inline btQuaternion GlmToBulletQuat(const glm::quat &glm_quat)
  {
    return btQuaternion(glm_quat.w, glm_quat.x, glm_quat.y, glm_quat.z);
  }

}
#endif /* !UTILS_BULLET_CONVERSIONS_H */