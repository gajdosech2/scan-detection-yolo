/*
  Copyright (C) Skeletex Research, s.r.o. - All Rights Reserved
  Unauthorized copying of this file, via any medium is strictly prohibited
  Proprietary and confidential
*/
#ifndef COGS_SKELETON_ACTION_H
#define COGS_SKELETON_ACTION_H
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include <COGS/Interpolator.h>
#include <COGS/API.h>

namespace cogs
{
  class Skeleton;
  struct SkeletonPose;
  class BoneTransform;



  struct COGS_API SkeletonAction
  {
    struct RootChannels
    {
      Interpolator<glm::quat> rotation;
      Interpolator<glm::vec3> position;
      //! Checks whether all channels are empty.
      [[nodiscard]] bool IsEmpty() const;
    };

    struct BoneChannels
    {
      Interpolator<glm::quat> rotation;
      Interpolator<glm::vec3> offset;
      Interpolator<glm::vec3> scaling;
      Interpolator<float> length;
      //! Checks whether all channels are empty.
      [[nodiscard]] bool IsEmpty() const;
      //! Adjusts bone transform using data from non empty channels.
      void AdjustTransformToTime(float time, BoneTransform *out_trans) const;
      //! Returns time of last existing key frame.
      [[nodiscard]] float GetDuration() const;
    };

    //! Returns time of last existing key frame.
    [[nodiscard]] float GetDuration() const;

    //! Checks whether all channels are empty.
    [[nodiscard]] bool IsEmpty() const;

    //! Adjusts pose using data from non empty channels.
    void AdjustPoseToTime(float time, const Skeleton &target_skeleton, SkeletonPose *out_pose) const;

    //! Builds all frames of pose animation for specified skeleton.
    [[nodiscard]] std::vector<SkeletonPose> BakePoseAnimation(const Skeleton &target_skeleton) const;

    std::string name;
    std::string target;
    float fps{ 1.0f };
    RootChannels root_channels;
    std::map<std::string, BoneChannels> bone_channels;
  };

}
#endif /* !COGS_SKELETON_ACTION_H */