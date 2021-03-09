#ifndef COGS_SKELETON_POSE_H
#define COGS_SKELETON_POSE_H
#include <COGS/BoneTransform.h>

namespace cogs
{
  //! Structure used for storage of specific configuration of bone transformations in a skeleton.
  struct COGS_API SkeletonPose
  {
    //! Transformation matrix used for all bones in the skeleton.
    Transform root_transform;
    //! Per-bone specific transformations.
    std::vector<BoneTransform> bone_transforms;

    /*! \brief
      Interpolates between this pose and target pose.

      Target pose must be designed for same skeleton.
      cogs::Transform::InterpolateWith is used for each
      corresponding pair of transformations.
    */
    void InterpolateWith(const SkeletonPose &target_pose, float target_weight, SkeletonPose *out_pose) const;
  };
}
#endif /* !COGS_SKELETON_POSE_H */