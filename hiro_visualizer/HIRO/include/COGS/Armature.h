/*
  Copyright (C) Skeletex Research, s.r.o. - All Rights Reserved
  Unauthorized copying of this file, via any medium is strictly prohibited
  Proprietary and confidential
*/
#ifndef COGS_ARMATURE_H
#define COGS_ARMATURE_H
#include <COGS/Mesh.h>
#include <COGS/Skeleton.h>
#include <COGS/SkeletonAction.h>
#include <COGS/API.h>

namespace cogs
{

  struct COGS_API VertexSkinData
  {
    glm::ivec4 ids = glm::ivec4(-1);
    glm::vec4 weights = glm::vec4(0.0f);
  };

  using SkinningData = std::vector<cogs::VertexSkinData>;



  class COGS_API Armature : public cogs::Skeleton
  {
  public:
    Armature() = default;
    void ConvertSkinDataFromNodeToBoneIds(std::unordered_map<int, cogs::Bone *> bone_for_nodeid);

    void SetMesh(const Mesh &mesh, const SkinningData &skindata);

    const Mesh *GetMesh() const;
    const SkinningData *GetSkinningData() const;

  private:
    int32_t anim_frame_ = 0;
    Mesh mesh_;
    SkinningData skin_data_;

  };


}

#endif /* !COGS_ARMATURE_H */