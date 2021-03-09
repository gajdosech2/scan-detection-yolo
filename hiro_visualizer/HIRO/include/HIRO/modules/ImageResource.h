/*
  Copyright (C) Skeletex Research, s.r.o. - All Rights Reserved
  Unauthorized copying of this file, via any medium is strictly prohibited
  Proprietary and confidential
*/
#ifndef HIRO_IMAGE_RESOURCE_H
#define HIRO_IMAGE_RESOURCE_H
#include <string>

#include <GLW/Texture.h>

#include <HIRO_DRAW/renderers/ImageRenderer.h>
#include <HIRO/Resource.h>



namespace hiro::modules
{

  class HIRO_API ImageResource : public Resource
  {
  public:
    ImageResource(const std::string &name, const glw::PTexture2D &tex);
    virtual PGadget CreateGadget() override;
    void SetImage(const glw::PTexture2D &image_texture);
    void LoadImageFile(const std::string &image_file);
    hiro::draw::PImageRenderer GetObjectPtr() const;
  private:
    hiro::draw::PImageRenderer image_;
  };

  using PImageResource = std::shared_ptr<ImageResource>;

  HIRO_API PImageResource AddImage(const std::string &name, const std::string &file_path);
  HIRO_API PImageResource AddImage(const std::string &name, const glw::PTexture2D &texture);

}

#endif /* !HIRO_IMAGE_RESOURCE_H */