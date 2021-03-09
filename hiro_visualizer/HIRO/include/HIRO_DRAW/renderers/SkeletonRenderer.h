/*
  Copyright (C) Skeletex Research, s.r.o. - All Rights Reserved
  Unauthorized copying of this file, via any medium is strictly prohibited
  Proprietary and confidential
*/
#ifndef HIRO_DRAW_SKELETON_RENDERER_H
#define HIRO_DRAW_SKELETON_RENDERER_H
#include <GLW/UniformBuffer.h>
#include <COGS/Skeleton.h>

#include <HIRO_DRAW/ElementRenderer.h>
#include <HIRO_DRAW/ShaderApi.h>



namespace cogs
{
  struct Pose;
}

namespace hiro::draw
{

  //! Structure specifying how the skeleton should be rendered.
  struct HIRO_DRAW_API SkeletonStyle : public hiro::draw::Style
  {
    //! Mode used to render skeleton.
    enum class RenderMode
    {
      octahedral, //!< Renders bone as octahedron and joint as icosahedron.
      octahedral_wire, //!< Renders bone as wired octahedron and joint as wired icosahedron.
      stick //!< Renders bone as line and joint as point.
    };
    //! Material used to render bones as well as joints of the skeleton.
    hiro::shader::Material bonejoint_material{ hiro::shader::Material(cogs::color::GRAY70) };
    //! Defines whether the basis vectors of each individual bone should be displayed.
    bool display_basis{ false };
    //! When enabled, also joints will be rendered.
    bool display_joints{ true };
    //! Specifies the mode used to render the skeleton.
    hiro::draw::SkeletonStyle::RenderMode render_mode{ hiro::draw::SkeletonStyle::RenderMode::octahedral };
    //! Import state from stream.
    bool ReadFromStream(std::istream &str) override;
    //! Export state to stream.
    void WriteToStream(std::ostream &str) override;
  };



  //! Skeleton visualization with possibility to change poses.
  class HIRO_DRAW_API SkeletonRenderer : public hiro::draw::ElementRenderer
  {
  public:
    //! Number of bones in the skeleton.
    const uint32_t BONE_COUNT;

    //! Creates a renderer with the specified skeleton.
    SkeletonRenderer(const cogs::Skeleton &skeleton);

    SkeletonRenderer(const hiro::draw::SkeletonRenderer &source) = delete;
    SkeletonRenderer &operator=(const hiro::draw::SkeletonRenderer &source) = delete;
    SkeletonRenderer(hiro::draw::SkeletonRenderer &&) noexcept = delete;
    SkeletonRenderer &operator=(hiro::draw::SkeletonRenderer &&) noexcept = delete;
    virtual ~SkeletonRenderer();

    //! Changes the pose in which the skeleton will be rendered.
    void SetPose(const cogs::SkeletonPose &skelpose);

  protected:
    //! Test whether specified style is compatible with object.
    bool IsCompatibileWithStyle(const hiro::draw::Style *style) override;
    //! Renders the skeleton in the line mode.
    void OnRenderSimple() override;
    //! Renders the skeleton in the polygonal mode.
    virtual void OnRenderFaces() override;

  private:
    //! Copy of the skeleton object.
    cogs::Skeleton skeleton_;
    //! Uniform buffer for transformations to the joint positions.
    glw::UniformBuffer<glm::mat4> joint_transform_buffer_;
    //! Uniform buffer for mapping to the bone transformations.
    glw::UniformBuffer<glm::mat4> bone_transform_buffer_;
    //! Uniform buffer for mapping to the bone basis transformations.
    glw::UniformBuffer<glm::mat4> basis_transform_buffer_;
    //! Array buffer of joint positions.
    glw::PArrayObject joint_point_buffer_;
    //! Array buffer of bone lines.
    glw::ArrayObject bone_line_buffer_;
    //! Recalculates all buffers.
    void ResetTransfromBuffers();
  };



  //! Shared pointer to an object of the type SkeletonStyle.
  using PSkeletonStyle = std::shared_ptr<hiro::draw::SkeletonStyle>;
  //! Shared pointer to an object of the type SkeletonRenderer.
  using PSkeletonRenderer = std::shared_ptr<hiro::draw::SkeletonRenderer>;
}

#endif /* !HIRO_DRAW_SKELETON_RENDERER_H */