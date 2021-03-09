/*
  Copyright (C) Skeletex Research, s.r.o. - All Rights Reserved
  Unauthorized copying of this file, via any medium is strictly prohibited
  Proprietary and confidential
*/
#ifndef UTILS_EXT_GLM_H
#define UTILS_EXT_GLM_H

#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/epsilon.hpp>
#include <glm/gtx/norm.hpp>
#include <glm/gtx/polar_coordinates.hpp>
#include <Utils/ExtSTD.h>



#ifndef PI
//! Archimedes constant.
constexpr float PI = glm::pi<float>();
#endif

#ifndef TWO_PI
//! PI*2.
constexpr float TWO_PI = glm::two_pi<float>();
#endif

#ifndef HALF_PI
//! PI/2.
constexpr float HALF_PI = glm::half_pi<float>();
#endif

#ifndef QUAT_PI
//! PI/4.
constexpr float QUAT_PI = glm::quarter_pi<float>();
#endif

constexpr float FLT_GLM_CALC_EPSILON = 0.000001f;

//! Extensions to the glm library.
namespace glm_ext
{

  //! Template wrapper for glm matrix holding matrix and its inverse.
  template<int N>
  class TransMat
  {
    using MyMat = glm::mat<N, N, float, glm::highp>;
  public:
    //! Creates identity.
    TransMat() = default;
    //! Creates matrix with a defined value.
    TransMat(const MyMat &new_mat)
    {
      Set(new_mat);
    }
    //! Sets matrix to a defined value.
    void Set(const MyMat &new_mat)
    {
      matrix_ = new_mat;
      inverse_ = glm::inverse(new_mat);
    }
    //! Sets inverse of the matrix.
    void SetInverse(const MyMat &inv_mat)
    {
      matrix_ = glm::inverse(inv_mat);
      inverse_ = inv_mat;
    }
    //! Returns matrix.
    const MyMat &Get() const { return matrix_; };
    //! Returns inverse of matrix.
    const MyMat &GetInverse() const { return inverse_; };
  private:
    MyMat matrix_ = MyMat(1.0f);
    MyMat inverse_ = MyMat(1.0f);
  };
  //! Wrapper glm::mat3 holding matrix and its inverse.
  using TransMat3 = TransMat<3>;
  //! Wrapper glm::mat4 holding matrix and its inverse.
  using TransMat4 = TransMat<4>;

  //! Converts the input vector into a string with predefined delimiter.
  template <int N, typename genType>
  inline std::string to_string(const glm::vec<N, genType, glm::highp> &vec, const std::string &delim = ", ")
  {
    std::string result;
    for (int i = 0; i < N; i++)
    {
      result += std::to_string(vec[i]);
      if (i < N - 1)
      {
        result += delim;
      }
    }
    return result;
  }

  //! Converts matrix into a string using defined delimiters.
  template <int N, int M, typename genType>
  inline std::string to_string(const glm::mat<N, M, genType, glm::highp> &mat, const std::string &delim_col = ", ", const std::string &delim_row = "\n")
  {
    std::string result;
    for (int i = 0; i < N; i++)
    {
      const auto &v = mat[i];
      result += to_string(v, delim_col);
      if (i < N - 1)
      {
        result += delim_row;
      }
    }
    return result;
  }

  //! Converts the input quaternion into a string with predefined delimiter.
  inline std::string to_string(const glm::quat &q, const std::string &delim = ", ")
  {
    return std::to_string(q.x) + delim + std::to_string(q.y) + delim + std::to_string(q.z) + delim + std::to_string(q.w);
  }

  //! Parses a string to a glm vector using defined delimiters or fails.
  template <int N, typename genType>
  [[nodiscard]]
  inline bool parse_string(const std::string &str, glm::vec<N, genType, glm::highp> &out_vec, const std::string &delim = ", ")
  {
    const auto vals = std_ext::Parse(str, delim);
    if (vals.size() != N)
    {
      return false;
    }
    for (glm::length_t i = 0; i < N; ++i)
    {
      std_ext::StringTo(vals[i], out_vec[i]);
    }
    return true;
  }

  //! Parses a string to a matrix using defined delimiters or fails.
  template <int N, int M, typename genType>
  [[nodiscard]]
  inline bool parse_string(const std::string &str, glm::mat<N, M, genType, glm::highp> &out_mat, const std::string &delim_col = ", ", const std::string &delim_row = "\n")
  {
    const auto rows = std_ext::Parse(str, delim_row);
    std::vector<std::string> vals;
    vals.reserve(N * M);
    for (const auto &row : rows)
    {
      std_ext::InsertBack(vals, std_ext::Parse(row, delim_col));
    }

    if (vals.size() != N * M)
    {
      return false;
    }

    for (glm::length_t r = 0; r < N; ++r)
    {
      for (glm::length_t c = 0; c < M; ++c)
      {
        out_mat[r][c] = std::stof(vals[r * M + c]);
      }
    }

    return true;
  }

  //! Parses a string to a glm quaternion using defined delimiters or fails.
  [[nodiscard]]
  inline bool parse_string(const std::string &str, glm::quat &out_quat, const std::string &delim = ", ")
  {
    const size_t N = 4;
    const auto vals = std_ext::Parse(str, delim);
    if (vals.size() != N)
    {
      return false;
    }

    for (glm::length_t i = 0; i < static_cast<glm::length_t>(N); ++i)
    {
      out_quat[i] = std::stof(vals[i]);
    }
    return true;
  }

  //! Returns square of a value or vector.
  template <typename genType>
  genType sqr(genType value)
  {
    return static_cast<genType>(glm::pow(value, 2));
  }

  //! Returns minimal value component of a vector.
  template <typename Type, glm::length_t N>
  Type min(const glm::vec<N, Type> &vec)
  {
    Type val = vec[0];
    for (auto i = 1; i < N; i++)
    {
      if (vec[i] < val)
      {
        val = vec[i];
      }
    }
    return val;
  }

  //! Returns maximal value component of a vector.
  template <typename Type, glm::length_t N>
  Type max(const glm::vec<N, Type> &vec)
  {
    Type val = vec[0];
    for (auto i = 1; i < N; i++)
    {
      if (vec[i] > val)
      {
        val = vec[i];
      }
    }
    return val;
  }

  //! Returns minimum of three values or individual vector components.
  template <typename genType>
  genType min(genType p1, genType p2, genType p3)
  {
    return (glm::min)(p1, (glm::min)(p2, p3));
  }

  //! Returns maximum of three values or individual vector components.
  template <typename genType>
  genType max(genType p1, genType p2, genType p3)
  {
    return (glm::max)(p1, (glm::max)(p2, p3));
  }

  //! Clamps a value or individual vector components to the range 0-1.
  template <typename genType>
  genType Clamp01(genType x)
  {
    return glm::clamp(x, genType(0.0f), genType(1.0f));
  }

  //! Returns true if vector is normalized in <0,1> interval.
  template <int N>
  inline bool IsNormalized(const glm::vec<N, float> &vector)
  {
    return glm::abs(glm::length2(vector) - 1.f) < 0.000001f;
  }

  //! Returns true if two values are equal within defined epsilon threshold.
  template <typename T>
  inline bool AreEqual(const T val1, const T val2, const T epsilon = std::numeric_limits<T>::epsilon())
  {
    return glm::epsilonEqual(val1, val2, epsilon);
  }

  //! Returns true if all components of two vectors are equal within defined epsilon threshold.
  template <typename T, int N>
  inline bool AreEqual(const glm::vec<N, T> &vec1, const glm::vec<N, T> &vec2, const  T epsilon = std::numeric_limits<T>::epsilon())
  {
    const auto not_equal = glm::epsilonNotEqual(vec1, vec2, epsilon);
    return !glm::any(not_equal);
  }

  //! Returns true if two quaternions are equal within defined epsilon threshold.
  inline bool AreEqual(const glm::quat &q1, const glm::quat &q2, const float epsilon = FLT_EPSILON)
  {
    const auto not_equal = glm::epsilonNotEqual(q1, q2, epsilon);
    return !glm::any(not_equal);
  }

  //! Returns true if all elements of two matrices are equal within defined epsilon threshold.
  template <typename T, int N, int M>
  inline bool AreEqual(const glm::mat<N, M, T> &mat1, const glm::mat<N, M, T> &mat2, const T epsilon = std::numeric_limits<T>::epsilon())
  {
    for (auto i = 0; i < M; ++i)
    {
      const auto not_equal = glm::epsilonNotEqual(mat1[i], mat2[i], epsilon);
      if (glm::any(not_equal))
      {
        return false;
      }
    }
    return true;
  }

  //! Returns true if a value is equal to zero within defined epsilon threshold.
  inline bool IsZero(const float val, const float epsilon = FLT_EPSILON)
  {
    return AreEqual(val, 0.0f, epsilon);
  }

  /*!
    \brief Checks a variable number of elements for equality with a given precision.
    \note Since the number of elements is variadic, the precision argument must be specified first.
    \warning Performs comparison on consecutive elements.
  */
  template <typename T, typename... TS>
  inline bool AllEqual(const float precision, const T a, const T b, const TS ... elements)
  {
    return AreEqual(a, b, precision) && AllEqual(precision, b, elements ...);
  }

  //! Checks a variable number of elements for equality with a given precision.  Boundary case for the variadic number of elements case.
  template <typename T, typename... TS>
  inline bool AllEqual(const float precision, const T a)
  {
    return true;
  }

  //! Return whether any element in the matrix is NaN.
  template <int N, int M, typename genType>
  [[nodiscard]]
  inline bool IsAnyNan(const glm::mat<N, M, genType, glm::highp> &mat)
  {
    for (glm::length_t r = 0; r < N; ++r)
    {
      if (glm::any(glm::isnan(mat[r])))
      {
        return true;
      }
    }
  }

  //! Returns true if all components of vector are equal to zero within defined epsilon threshold.
  template <typename Type, glm::length_t N>
  inline bool IsZero(const glm::vec<N, Type> &vec, const float epsilon = FLT_EPSILON)
  {
    for (glm::length_t i = 0; i < N; ++i)
    {
      if (!AreEqual(vec[i], 0.0f, epsilon))
      {
        return false;
      }
    }
    return true;
  }

  //! Returns true if all components of vec1 are less then vec2 within defined epsilon threshold.
  template <int N>
  inline bool IsLess(const glm::vec<N, float> &vec1, const glm::vec<N, float> &vec2, const float epsilon = FLT_EPSILON)
  {
    for (int i = 0; i < N; i++)
    {
      if ((vec1[i] - vec2[i]) > -(epsilon * glm::max(1.0f, (glm::abs)(vec1[i]), (glm::abs)(vec2[i]))))
      {
        return false;
      }
    }
    return true;
  }

  //! Returns true if val1 is less then val2 within defined epsilon threshold.
  inline bool IsLess(const float val1, const float val2, const float epsilon = FLT_EPSILON)
  {
    return (val1 - val2) < -(epsilon * glm_ext::max(1.0f, (glm::abs)(val1), (glm::abs)(val2)));
  }

  //! Returns true if all components of vec1 are less or equal then vec2 within defined epsilon threshold.
  template <int N>
  inline bool IsLequal(const glm::vec<N, float> &vec1, const glm::vec<N, float> &vec2, const float epsilon = FLT_EPSILON)
  {
    for (int i = 0; i < N; i++)
    {
      if ((vec1[i] - vec2[i]) > epsilon * glm_ext::max(1.0f, (glm::abs)(vec1[i]), (glm::abs)(vec2[i])))
      {
        return false;
      }
    }
    return true;
  }

  //! Returns true if val1 is less or equal then val2 within defined epsilon threshold.
  inline bool IsLequal(const float val1, const float val2, const float epsilon = FLT_EPSILON)
  {
    return (val1 - val2) < epsilon * glm_ext::max(1.0f, (glm::abs)(val1), (glm::abs)(val2));
  }

  //! Returns true if all components of vec1 are grater then vec2 within defined epsilon threshold.
  template <int N>
  inline bool IsGreater(const glm::vec<N, float> &vec1, const glm::vec<N, float> &vec2, const float epsilon = FLT_EPSILON)
  {
    for (int i = 0; i < N; i++)
    {
      if ((vec1[i] - vec2[i]) < epsilon * glm_ext::max(1.0f, (glm::abs)(vec1[i]), (glm::abs)(vec2[i])))
      {
        return false;
      }
    }
    return true;
  }

  //! Returns true if val1 is greater then val2 within defined epsilon threshold.
  inline bool IsGreater(const float val1, const float val2, const float epsilon = FLT_EPSILON)
  {
    return (val1 - val2) > epsilon * glm_ext::max(1.0f, (glm::abs)(val1), (glm::abs)(val2));
  }

  //! Returns true if all components of vec1 are grater or equal then vec2 within defined epsilon threshold.
  template <int N>
  inline bool IsGequal(const glm::vec<N, float> &vec1, const glm::vec<N, float> &vec2, const float epsilon = FLT_EPSILON)
  {
    for (int i = 0; i < N; i++)
    {
      if ((vec1[i] - vec2[i]) < -(epsilon * glm_ext::max(1.0f, (glm::abs)(vec1[i]), (glm::abs)(vec2[i]))))
      {
        return false;
      }
    }
    return true;
  }

  //! Returns true if val1 is greater or equal then val2 within defined epsilon threshold.
  inline bool IsGequal(const float val1, const float val2, const float epsilon = FLT_EPSILON)
  {
    return (val1 - val2) > -(epsilon * glm_ext::max(1.0f, (glm::abs)(val1), (glm::abs)(val2)));
  }

  //! Dot product of two integer vectors.
  inline int doti(const glm::ivec2 &x, const glm::ivec2 &y)
  {
    return x[0] * y[0] + x[1] * y[1];
  }

  //! Function that maps the input value in the input interval into an output value inside the output interval.
  inline float map(float val, float in_min, float in_max, float out_min, float out_max)
  {
    float perc = (val - in_min) / (in_max - in_min);
    return out_min + perc * (out_max - out_min);
  }

  /*!
    \brief
      Calculates function value f(x) of normal distribution function.
    \param x
      Value for which to calculate functional value.
    \param mean
      Mean value of normal distribution function.
    \param sigma
      Standard deviation of distribution. Note: interval <-3*sigma, 3*sigma> around mean value covers 99.72% of gauss distribution.
  */
  inline float Gaussian(float x, float mean, float sigma)
  {
    return (glm::exp)(-0.5f * (glm_ext::sqr)((x - mean) / sigma));
  }

  //! Returns random number in interval <0,1>, with specified precision (defaults to 3 digits).
  inline float Rand01(int precision = 1000)
  {
    return float(rand() % (precision + 1)) / precision;
  }

  //! Returns random number in specified interval, with specified precision (defaults to 3 digits).
  inline float RandomInRange(float min, float max, int precision = 1000)
  {
    return min + Rand01(precision) * (max - min);
  }

  inline glm::vec3 RandomVec3()
  {
    const auto polar_angle = glm::vec2(
        glm_ext::RandomInRange(-HALF_PI, HALF_PI),
        glm_ext::RandomInRange(-PI, PI)
      );
    return glm::euclidean(polar_angle);
  }

  inline glm::quat RandomQuat()
  {
    return glm::rotate(glm::quat(), RandomInRange(0, TWO_PI), RandomVec3());
  }

  inline glm::mat4 CreateProjectionMatrix(const glm::uvec2 &resolution, const float fx, const float fy, const float cx, const float cy, const float near_plane = 0.01f, const float far_plane = 1000.0f)
  {
    glm::mat4 projection;

    const auto width = float(resolution.x);
    const auto height = float(resolution.y);

    projection[0][0] = 2.0f * fx / width;
    projection[0][1] = 0.0f;
    projection[0][2] = 0.0f;
    projection[0][3] = 0.0f;

    projection[1][0] = 0.0f;
    projection[1][1] = -2.0f * fy / height;
    projection[1][2] = 0.0f;
    projection[1][3] = 0.0f;

    projection[2][0] = 1.0f - 2.0f * cx / width;
    projection[2][1] = 1.0f - 2.0f * cy / height;
    projection[2][2] = (far_plane + near_plane) / (near_plane - far_plane);
    projection[2][3] = -1.0f;

    projection[3][0] = 0.0f;
    projection[3][1] = 0.0f;
    projection[3][2] = 2.0f * far_plane * near_plane / (near_plane - far_plane);
    projection[3][3] = 0.0f;

    return projection;
  }

  template <typename T>
  bool IsInRange(T value, T min, T max)
  {
    return value >= min && value <= max;
  }
}

#endif /* !UTILS_EXT_GLM_H */