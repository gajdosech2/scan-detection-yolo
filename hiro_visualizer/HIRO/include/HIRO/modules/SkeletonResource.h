/*
  Copyright (C) Skeletex Research, s.r.o. - All Rights Reserved
  Unauthorized copying of this file, via any medium is strictly prohibited
  Proprietary and confidential
*/
#ifndef HIRO_SKELETON_RESOURCE_H
#define HIRO_SKELETON_RESOURCE_H
#include <string>

#include <COGS/Skeleton.h>
#include <COGS/SkeletonAction.h>
#include <HIRO/Resource.h>



namespace hiro::modules
{

  //! Resource that allows visualization of a cogs::Skeleton structure.
  class HIRO_API SkeletonResource : public hiro:: Resource
  {
  public:
    const geom::Aabb3 AABB;
    //! Creates new resource from the specified skeleton.
    SkeletonResource(
      const std::string &name,
      const cogs::Skeleton &skeleton);
    //! Creates new resource from the specified skeleton and  assigns it an action.
    SkeletonResource(
      const std::string &name,
      const cogs::Skeleton &skeleton,
      const cogs::SkeletonAction &action);
    //! Returns rest pose of a skeleton.
    const cogs::SkeletonPose &GetRestPose() const;
    //! Changes the pose applied to the skeleton.
    void SetPose(const cogs::SkeletonPose &pose);
    //! Returns pose that is currently applied to the skeleton.
    const cogs::SkeletonPose &GetPose() const;
    //! Returns currently assigned skeleton.
    const cogs::Skeleton &GetSkeleton() const;
    //! Returns assigned skeleton action.
    const cogs::SkeletonAction *GetAction() const;
  protected:
    SkeletonResource(const hiro::ResourceId &dataid, const cogs::Skeleton &skeleton);
    virtual hiro::PGadget CreateGadget() override;
    cogs::SkeletonPose restpose_, pose_;
    cogs::Skeleton skeleton_;
    std::unique_ptr<cogs::SkeletonAction> skeleton_action_;
  };

  //! Shared pointer to an object of the type SkeletonResource.
  using PSkeletonResource = std::shared_ptr<hiro::modules::SkeletonResource>;

  //! Creates new skeleton resource from the specified cogs::Skeleton and adds it to HIRO.
  HIRO_API PSkeletonResource AddSkeleton(
    const std::string &name,
    const cogs::Skeleton &skeleton);

  //! Creates new skeleton resource from the specified cogs::Skeleton, assigns it an action and adds it to HIRO.
  HIRO_API PSkeletonResource AddSkeleton(
    const std::string &name,
    const cogs::Skeleton &skeleton,
    const cogs::SkeletonAction &action);

}

#endif /* !HIRO_SKELETON_RESOURCE_H */