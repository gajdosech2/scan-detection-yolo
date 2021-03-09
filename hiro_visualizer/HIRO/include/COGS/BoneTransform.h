/*
  Copyright (C) Skeletex Research, s.r.o. - All Rights Reserved
  Unauthorized copying of this file, via any medium is strictly prohibited
  Proprietary and confidential
*/
#ifndef COGS_BONE_TRANSFORM_H
#define COGS_BONE_TRANSFORM_H
#include <glm/glm.hpp>
#include <Utils/GeometryStructures.h>
#include <COGS/Transform.h>


namespace cogs
{

  /*!
    \brief
    Class used for effective management and manipulation
    with bone transformation.

    Position represents offset from parent tail node in parent space.
    All the transformations are relative to parent bone transformation.
  */
  class COGS_API BoneTransform : public Transform
  {
  public:

    //! Creates identity bone with unit length.
    BoneTransform() = default;

    /*!
      \brief
          Creates child bone, oriented and stretched in length. Relative to the parent.
      \param global_tail
          Global position of tail node of bone.
      \param global_parent_tail_transform
          Transformation matrix which describes parent space at its tail.
      \param basis_roll_angle
          Angular parameter which influences initial roll of generated y bone basis.
    */
    BoneTransform(
      const glm::vec3 &global_tail,
      const glm::mat4 &global_parent_tail_transform,
      const float basis_roll_angle = 0.0f
    );

    BoneTransform(const BoneTransform &) = default;
    BoneTransform &operator=(const BoneTransform &) = default;
    BoneTransform(BoneTransform &&) noexcept = default;
    BoneTransform &operator=(BoneTransform &&) noexcept = default;

    //! Changes length of bone by multiplying current length.
    void StretchLength(const float &length_change);

    //! Resets bone length to the new value.
    void SetLength(const float &new_length);

    //! Returns bone length.
    [[nodiscard]] const float &GetLength() const;

    //! Returns local transformation matrix, with origin according to the bone head position.
    [[nodiscard]] const glm::mat4 &GetHeadMat4() const;

    //! Returns local transformation matrix, with origin according to the bone tail position.
    [[nodiscard]] const glm::mat4 &GetTailMat4() const;

    /*!
      \brief
          Interpolates current transform with another, in a specific mix ratio.
      \param target
          The Transform which to interpolate to.
      \param target_weight
          Defines how much of target should be taken.
          Value 0 results in 100% of this transform, value 1 results in 100% of target.
      \param out_transform
          A pointer to an object where the computed transformation will be stored.
    */
    void InterpolateTo(const BoneTransform &target_transform, const float target_weight, BoneTransform *out_transform) const;

    //! Writes relevant information to stream.
    virtual void SaveToStream(std::ostream &ostr) const override;

    //! Reads relevant information from stream.
    virtual void LoadFromStream(std::istream &istr) override;

  protected:

    //! Function called each time a change on position, rotation or scaling is performed.
    void OnInvariantChange() override;

  private:

    using Transform::GetMat4; // hides inherited implementation, uses GetHeadMat4() method instead

    float length = 1.0f;
    mutable bool is_tailmat_invalid = true; // whether tail matrix should be re-calculated
    mutable glm::mat4 tail_matrix;          // cached tail transformation, re-calculated only when required
  };

}

#endif /* !COGS_BONE_TRANSFORM_H */