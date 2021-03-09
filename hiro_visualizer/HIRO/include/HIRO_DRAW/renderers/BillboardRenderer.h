/*
  Copyright (C) Skeletex Research, s.r.o. - All Rights Reserved
  Unauthorized copying of this file, via any medium is strictly prohibited
  Proprietary and confidential
*/
#ifndef HIRO_DRAW_BILLBOARD_RENDERER_H
#define HIRO_DRAW_BILLBOARD_RENDERER_H
#include <GLW/Texture.h>
#include <HIRO_DRAW/ElementRenderer.h>



namespace hiro::draw
{

  //! Stylization of the rendered billboard.
  struct HIRO_DRAW_API BillboardStyle : public hiro::draw::Style
  {
    //! Denotes, whether to use nearest or linear filtering when rendering image.
    bool use_nearest_filtering{ false };
    //! Imports state from stream.
    virtual bool ReadFromStream(std::istream &str) override;
    //! Exports state to stream.
    virtual void WriteToStream(std::ostream &str) override;
  };


  //! Renderer used for rendering images in 3D space.
  class HIRO_DRAW_API BillboardRenderer : public hiro::draw::ElementRenderer
  {
  public:
    //! Creates a renderer with an empty image.
    BillboardRenderer() = default;
    //! Creates a renderer with an image loaded from a file.
    BillboardRenderer(const std::string &texture_filename);
    //! Creates a renderer with an image stored in a provided texture.
    BillboardRenderer(const glw::PTexture2D &texture);

    BillboardRenderer(const hiro::draw::BillboardRenderer &source) = delete;
    BillboardRenderer &operator=(const hiro::draw::BillboardRenderer &source) = delete;
    BillboardRenderer(hiro::draw::BillboardRenderer &&) noexcept = delete;
    BillboardRenderer &operator=(hiro::draw::BillboardRenderer &&) noexcept = delete;
    virtual ~BillboardRenderer() = default;

    //! Replaces currently set image with a new one.
    void SetTexture(const glw::PTexture2D &texture);
    //! Returns currently set texture.
    glw::PTexture2D GetTexture() const;

    //! Test whether specified style is compatible with the object.
    bool IsCompatibileWithStyle(const hiro::draw::Style *style) override;

  protected:
    //! Defines behavior on face rendering.
    virtual void OnRenderFaces() override;

  private:
    //! Currently used texture object.
    glw::PTexture2D texture_ = nullptr;
  };



  //! Shared pointer to an object of the type BillboardStyle.
  using PBillboardStyle = std::shared_ptr<BillboardStyle>;
  //! Shared pointer to an object of the type BillboardRenderer.
  using PBillboardRenderer = std::shared_ptr<BillboardRenderer>;

}

#endif /* !HIRO_DRAW_BILLBOARD_RENDERER_H */