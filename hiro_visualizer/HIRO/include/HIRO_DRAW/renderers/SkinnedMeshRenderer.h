/*
  Copyright (C) Skeletex Research, s.r.o. - All Rights Reserved
  Unauthorized copying of this file, via any medium is strictly prohibited
  Proprietary and confidential
*/
#ifndef HIRO_DRAW_SKINNED_MESH_RENDERER_H
#define HIRO_DRAW_SKINNED_MESH_RENDERER_H
#include <COGS/Armature.h>
#include <GLW/UniformBuffer.h>
#include <HIRO_DRAW/renderers/MeshRenderer.h>



namespace cogs
{
  struct SkeletonPose;
}

namespace hiro::draw
{

  using SkinnedMeshStyle = hiro::draw::MeshStyle;



  class HIRO_DRAW_API SkinnedMeshRenderer : public hiro::draw::MeshRenderer
  {
  public:
    SkinnedMeshRenderer(const cogs::Armature &armature);
    SkinnedMeshRenderer(const hiro::draw::SkinnedMeshRenderer &object_ptr) = delete;
    virtual ~SkinnedMeshRenderer() = default;

    void SetPose(const cogs::SkeletonPose &pose);

  protected:
    void LoadRequiredShaderPrograms(glw::ProgramList *programs) override;
    bool IsCompatibileWithStyle(const hiro::draw::Style *style) override;
    void Render(const std::string &program) override;

  private:
    const uint32_t kBoneCount;
    const std::string kMyProgramPoints, kMyProgram;
    cogs::Armature skeleton_;
    glw::UniformBuffer<glm::mat4> bindpose_transforms_;
    glw::UniformBuffer<glm::mat4> pose_transforms_;
  };



  using PSkinnedMeshStyle = std::shared_ptr<hiro::draw::SkinnedMeshStyle>;
  using PSkinnedMeshRenderer = std::shared_ptr<hiro::draw::SkinnedMeshRenderer>;

}

#endif /* !HIRO_DRAW_SKINNED_MESH_RENDERER_H */