#ifndef UTILS_EIGEN_CONVERSIONS_H
#define UTILS_EIGEN_CONVERSIONS_H
#include <Eigen/Core>
#include <Eigen/Eigen>
#include <bullet3/LinearMath/btVector3.h>
#include <bullet3/LinearMath/btQuaternion.h>
#include <glm/vec3.hpp>
#include <glm/gtc/quaternion.hpp>


namespace utils
{
  //! Converts Eigen matrix to glm matrix.
  template<typename T, int m, int n, typename OutT = float>
  inline glm::mat<m, n, OutT, glm::precision::highp> EigenToGlmMat(const Eigen::Matrix<T, m, n> &em)
  {
    glm::mat<m, n, OutT, glm::precision::highp> mat;
    for (int i = 0; i < m; ++i)
    {
      for (int j = 0; j < n; ++j)
      {
        mat[j][i] = static_cast<OutT>(em(i, j));
      }
    }
    return mat;
  }

  //! Converts glm matrix to Eigen matrix.
  template<typename T, int m, int n>
  inline Eigen::Matrix<T, m, n> GlmToEigenMat(const glm::mat<m, n, float, glm::precision::highp> &glm_mat)
  {
    Eigen::Matrix<T, m, n> eigen_mat;
    for (int i = 0; i < m; ++i)
    {
      for (int j = 0; j < n; ++j)
      {
        eigen_mat(j, i) = static_cast<T>(glm_mat[i][j]);
      }
    }
    return eigen_mat;
  }

  //! Converts Eigen matrix to glm vector.
  template<typename T, int m>
  inline glm::vec<m, float, glm::precision::highp> EigenToGlmVec(const Eigen::Matrix<T, m, 1> &em)
  {
    glm::vec<m, float, glm::precision::highp> v;
    for (int i = 0; i < m; ++i)
    {
      v[i] = static_cast<float>(em(i));
    }
    return v;
  }

  //! Converts Eigen quaternion to glm quaternion.
  template<typename T>
  inline glm::quat EigenToGlmQuat(const Eigen::Quaternion<T> &q)
  {
    return glm::quat(
        static_cast<float>(q.w()),
        static_cast<float>(q.x()),
        static_cast<float>(q.y()),
        static_cast<float>(q.z()));
  }

  //! Converts glm vector to Eigen vector.
  inline Eigen::Vector3d GlmToEigenVec(const glm::vec3 &glm_vec)
  {
    Eigen::Vector3d eigen_vec;
    for (int j = 0; j < 3; ++j)
    {
      eigen_vec(j) = glm_vec[j];
    }
    return eigen_vec;
  }

  //! Converts glm quaternion to Eigen quaternion.
  template<typename T>
  Eigen::Quaternion<T> GlmToEigenQuat(const glm::quat &q)
  {
    return Eigen::Quaternion<T>(
        static_cast<T>(q.w),
        static_cast<T>(q.x),
        static_cast<T>(q.y),
        static_cast<T>(q.z));
  }

  //! Converts Eigen vector to bullet vector.
  inline btVector3 EigenToBulletVec(const Eigen::Vector3d &eigen_vec)
  {
    return btVector3(
        static_cast<btScalar>(eigen_vec.x()),
        static_cast<btScalar>(eigen_vec.y()),
        static_cast<btScalar>(eigen_vec.z()));
  }

  //! Converts Eigen quaternion to bullet quaternion.
  template<typename T>
  inline btQuaternion EigenToBulletQuat(const Eigen::Quaternion<T> &eigen_quat)
  {
    return btQuaternion(
        static_cast<btScalar>(eigen_quat.x()),
        static_cast<btScalar>(eigen_quat.y()),
        static_cast<btScalar>(eigen_quat.z()),
        static_cast<btScalar>(eigen_quat.w()));
  }

}
#endif /* !UTILS_EIGEN_CONVERSIONS_H */