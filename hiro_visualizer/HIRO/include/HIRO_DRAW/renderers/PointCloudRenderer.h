/*
  Copyright (C) Skeletex Research, s.r.o. - All Rights Reserved
  Unauthorized copying of this file, via any medium is strictly prohibited
  Proprietary and confidential
*/
#ifndef HIRO_DRAW_POINT_CLOUD_RENDERER_H
#define HIRO_DRAW_POINT_CLOUD_RENDERER_H
#include <GLW/UniformBuffer.h>
#include <HIRO_DRAW/ElementRenderer.h>
#include <HIRO_DRAW/ShaderApi.h>



namespace cogs
{
  class PointCloud;
}

namespace hiro::draw
{

  //! Stylization of the rendered point cloud.
  struct HIRO_DRAW_API PointCloudStyle : public hiro::draw::Style
  {
    //! Material setting for points.
    hiro::shader::Material material;
    //! When enabled, points with normal vector turned away from the camera are hidden.
    bool back_face_culling{ false };
    //! Size of point in screen pixels.
    float point_size{ 10.0f };
    //! Color source used to colorize points.
    hiro::draw::ColorSource color_source{ hiro::draw::ColorSource::material };

    //! When enabled, normal vector for every point is rendered.
    bool display_normals{ false };
    //! Color of normal vector tips. Used only when normals are displayed.
    cogs::Color3f normal_color{ cogs::color::BLACK };
    //! Length of normal vectors. Used only used when normals are displayed.
    float normal_length{ 0.1f };

    //! Imports state from stream.
    bool ReadFromStream(std::istream &str) override;
    //! Exports state to stream.
    void WriteToStream(std::ostream &str) override;
  };



  //! Renderer used for rendering point clouds.
  class HIRO_DRAW_API PointCloudRenderer : public hiro::draw::ElementRenderer
  {
  public:
    //! Creates a renderer without point cloud.
    PointCloudRenderer() = default;
    //! Creates a renderer with the specified point cloud.
    PointCloudRenderer(const cogs::PointCloud &pc);

    PointCloudRenderer(const hiro::draw::PointCloudRenderer &source) = delete;
    PointCloudRenderer &operator=(const hiro::draw::PointCloudRenderer &source) = delete;
    PointCloudRenderer(hiro::draw::PointCloudRenderer &&) noexcept = delete;
    PointCloudRenderer &operator=(hiro::draw::PointCloudRenderer &&) noexcept = delete;
    virtual ~PointCloudRenderer() = default;

    //! Replaces currently set point cloud with a new one.
    void Reset(const cogs::PointCloud &pc);
    //! Returns number of points in the rendered pointcloud.
    size_t GetPointCount() const;
    //! Set custom color for each point.
    void SetColors(const std::vector<cogs::Color3f> &colors);

    //! Test whether specified style is compatible with the object.
    virtual bool IsCompatibileWithStyle(const hiro::draw::Style *style) override;

  protected:
    //! Defines behavior on point rendering.
    virtual void OnRenderPoints() override;
    //! Defines behavior on normal rendering.
    virtual void OnRenderNormals() override;

  private:
    //! Array buffer used to store attributes of currently rendered point cloud.
    glw::PArrayObject vao_;
    //! Name of the buffer that contains custom point colors.
    glw::ArrayObject::BufferName color_buffer_{ glw::ArrayObject::INVALID_NAME };
  };



  //! Shared pointer to an object of the type PointCloudStyle.
  using PPointCloudStyle = std::shared_ptr<hiro::draw::PointCloudStyle>;
  //! Shared pointer to an object of the type PointCloudRenderer.
  using PPointCloudRenderer = std::shared_ptr<hiro::draw::PointCloudRenderer>;

}

#endif /* !HIRO_DRAW_POINT_CLOUD_RENDERER_H */