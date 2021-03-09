/*
  Copyright (C) Skeletex Research, s.r.o. - All Rights Reserved
  Unauthorized copying of this file, via any medium is strictly prohibited
  Proprietary and confidential
*/
#ifndef COGS_BONE_H
#define COGS_BONE_H
#include <Utils/GeometryStructures.h>

#include <COGS/API.h>
#include <COGS/BoneTransform.h>

namespace cogs
{

  class Skeleton;

  class COGS_API Bone
  {
  public:

    //! Returns bone index in skeleton structure.
    uint32_t GetId() const;

    //! Returns bone name.
    std::string GetName() const;

    //! Position of bone start point.
    glm::vec3 GetHead() const;

    //! Position of bone end point.
    glm::vec3 GetTail() const;

    //! Rotates bone by shortest possible path and changes its length, so that its tail lays in specified position.
    void SetTail(glm::vec3 tail);

    enum PropertyType
    {
      HEAD_RADIUS, TAIL_RADIUS,
      SEP_WEIGHT,
      SEP_LINE_DIRX, SEP_LINE_DIRY, SEP_LINE_DIRZ,
      IGNORED_NEIGHBOUR
    };

    //! Returns the specific bone property. If the property do not exist, returns zero.
    float GetProperty(const PropertyType prop) const;

    //! Returns the specific bone property. If the property do not exist, returns default value.
    float GetProperty(const PropertyType prop, const float default_value) const;

    //! Sets the specific bone property. If the property do not exist yet, creates new property record.
    void SetProperty(const PropertyType prop, const float value);

    //! Checks if the property exist.
    bool HasProperty(const PropertyType prop) const;

    //! Distance from head to tail.
    float GetLength() const;

    //! Set distance from head to tail.
    void SetLength(const float new_length);

    //! Normalized direction of bone. Equivalent to GetBasisVector(geom::Axis::X).
    glm::vec3 GetDirection() const;

    //! Returns bone basis vectors in a matrix representation.
    glm::mat4 GetBasisMat4() const;

    //! Returns bone basis vectors in a matrix representation.
    glm::mat3 GetBasisMat3() const;

    //! Specified vector component of bone basis.
    glm::vec3 GetBasisVector(const geom::Axis axis) const;

    //! Returns actual transformation from global space to bone space at head position.
    glm::mat4 GetGlobalTransformHead() const;

    //! Returns actual transformation from global space to bone space at tail position.
    glm::mat4 GetGlobalTransformTail() const;

    //! Returns local transformation of bone according to parent.
    const BoneTransform &GetTransform() const;

    //! Rotates by angle in radians right-handily around X basis axis.
    void Roll(const float &angle);

    //! Rotates by angle in radians right-handily around X basis axis.
    void LocalRoll(const float &angle);

    //! Rotates by angle in radians right-handily around Y basis axis.
    void Pitch(const float &angle);

    //! Rotates by angle in radians right-handily around Z basis axis.
    void Yaw(const float &angle);

    //! Check whether the bone is first in skeleton hierarchy = has no parent bone.
    bool IsRoot() const;

    //! Check whether the bone is last in skeleton hierarchy.
    bool IsLeaf() const;

    //! Hierarchical parent bone of this node.
    Bone *GetParent() const;

    //! Number of children which this bone has.
    uint32_t GetChildrenCount() const;

    //! Array of this bone's children.
    std::vector<Bone *> GetChildren() const;

    //! Array of bones which are connected by head. If bone has parent, it is always first.
    std::vector<Bone *> GetHeadNeigbours() const;

    //! Array of bones ids which are connected by head. If bone has parent, it is always first.
    glm::ivec4 GetHeadNeigbourIds() const;

    //! Array of bones which are connected by tail.
    std::vector<Bone *> GetTailNeigbours() const;

    //! Array of bone ids which are connected by tail.
    glm::ivec4 GetTailNeigbourIds() const;

    //! Recursively applies rotation on bone.
    void Rotate(const glm::quat &rotation);

    //! Recursively rotates bone to the specified direction, by a shortest rotation possible.
    void RotateToDirection(glm::vec3 new_bone_direction);

    //! Converts bone to oriented vector with length equal to bone's length.
    glm::vec3 ToVector() const;

    //! Converts bone to line segment.
    geom::LineSegment3 ToLineSegment() const;

    //! Converts bone to non ending line with direction of a bone.
    geom::Line3 ToLine() const;

    //! Converts bone with its radiuses to conical capsule.
    geom::ConicalCapsule ToConicalCapsule() const;

    //! Recursively, changes order of child bones, so that they match order of specified bone.
    void SortChildrenByBone(const Bone &bone);

  protected:
    friend Skeleton;

    explicit Bone(const uint32_t id, const std::string caption);

    uint32_t id_;
    std::string caption_;

    Skeleton *skeleton_owner_ = nullptr;
    Bone *parent_ = nullptr;
    std::vector<Bone *> children_;

    std::unordered_map<PropertyType, float> properties_;

    BoneTransform transform_;
    BoneTransform bindpose_transform_;

    struct Cache
    {
      glm::mat4 global_transform_head;
      glm::mat4 global_transform_tail;
      glm::vec3 head;
      glm::vec3 tail;
      glm::mat3 basis;
    } cache_;

    glm::mat4 GetParentTransform();

    void ApplyBindpose();
    void ApplyCurrentPoseAsBindpose();

    void UpdateTransformCache();

    void UpdateTransformCacheRecursive();

    void ResetBindposeTransform(const BoneTransform &new_transform);
    void ResetBindposeTransformRecursive(const BoneTransform &new_transform);

  };

  std::vector<geom::LineSegment3> BonesToLines(const std::vector<cogs::Bone *> &bones);
}
#endif /* !COGS_BONE_H */