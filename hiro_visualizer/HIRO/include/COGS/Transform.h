/*
  Copyright (C) Skeletex Research, s.r.o. - All Rights Reserved
  Unauthorized copying of this file, via any medium is strictly prohibited
  Proprietary and confidential
*/
#ifndef COGS_TRANSFORM_H
#define COGS_TRANSFORM_H
#include <functional>

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

#include <COGS/API.h>


namespace cogs
{

  /*!
    \brief
    Class used for effective management of transformation matrix
    by handling translation, rotation and scaling separately.

    Final transformation is computed in order: scaling > rotation > translation.
  */
  class COGS_API Transform
  {
  public:

    //! Creates an identity instance.
    Transform() = default;

    //! Creates an instance from a given matrix.
    Transform(const glm::mat4 &matrix);

    //! Creates an identity instance which notifies whenever its state changes.
    Transform(const std::function<void(void)> &notifier_func);

    virtual ~Transform() = default;

    Transform(const Transform &) = default;
    Transform &operator=(const Transform &) = default;
    Transform(Transform &&) noexcept = default;
    Transform &operator=(Transform &&) noexcept = default;

    //! Changes position by a given vector.
    void Translate(const glm::vec3 &move_vector);

    //! Removes current position and replaces with specified position.
    void SetPosition(const glm::vec3 &position);

    //! Returns position defined by transformation.
    const glm::vec3 GetPosition() const;

    //! Applies additional rotation to transform, relative to current rotation.
    void Rotate(const glm::quat &rotation);

    //! Removes current rotation and replaces with specified quaternion.
    void SetRotation(const glm::quat &rotation);

    //! Returns rotation defined by transformation.
    const glm::quat GetRotation() const;

    //! Applies scale to transform, accumulated with previous scaling.
    void Scale(const glm::vec3 &scale);

    //! Resets scaling of transform.
    void SetScaling(const glm::vec3 &scale);

    //! Returns scaling defined by transformation.
    const glm::vec3 GetScaling() const;

    //! Resets current transform so that it represents specified matrix
    void Set(const glm::mat4 &trans_mat);

    //! Returns composed matrix of final transformation: scaling > rotation > translation.
    virtual const glm::mat4 &GetMat4() const;

    //! Multiply this transform by a given one.
    void AddTransform(const Transform &transform);

    /*!
      \brief
          Interpolates current transform with another, in a specific mix ratio.

          Transformations are disassembled into translation, scale and rotation components.
          Translation and scale components are then interpolated linearly, rotation with SLERP function.
      \param target
          The Transform which to interpolate to.
      \param target_weight
          Defines how much of target should be taken.
          Value 0 results in 100% of this transform, value 1 results in 100% of target.
      \param out_transform
          A pointer to an object where the computed transformation will be stored.
    */
    void InterpolateWith(
      const Transform &target,
      const float target_weight,
      Transform *out_transform
    ) const;

    //! Writes relevant information to stream.
    virtual void SaveToStream(std::ostream &ostr) const;

    //! Reads relevant information from stream.
    virtual void LoadFromStream(std::istream &istr);

    //! Multiply two transforms equivalently to matrix multiplication.
    Transform operator*(const Transform &t) const;

    operator glm::mat4() const { return GetMat4(); };

  protected:

    //! Function called each time a change on position, rotation or scaling is performed.
    virtual void OnInvariantChange();

  private:
    glm::vec3 position = glm::vec3(0.0f);
    glm::quat rotation = glm::quat();
    glm::vec3 scaling = glm::vec3(1.0f);
    mutable bool is_matrix_invalid = false;     // whether matrix should be re-calculated
    mutable glm::mat4 matrix = glm::mat4(1.0f); // cached transformation matrix, re-calculated only when required
    std::function<void(void)> on_change_notifier = nullptr;
  };

}
#endif /* !COGS_TRANSFORM_H */