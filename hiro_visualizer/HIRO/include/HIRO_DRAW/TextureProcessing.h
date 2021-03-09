/*
  Copyright (C) Skeletex Research, s.r.o. - All Rights Reserved
  Unauthorized copying of this file, via any medium is strictly prohibited
  Proprietary and confidential
*/
#ifndef HIRO_DRAW_TEXTURE_PROCESSING_H
#define HIRO_DRAW_TEXTURE_PROCESSING_H
#include <GLW/Texture.h>
#include <GLW/FrameBuffer.h>



namespace glw
{
  glw::PTexture2D SumDiffTextures(const glw::PTexture2D &texture1, const glw::PTexture2D &texture2, const glw::FrameBuffer::Settings &framebuffer_settings, const bool summation);
  glw::PTexture2D SumTextures(const glw::PTexture2D &texture1, const glw::PTexture2D &texture2, const glw::FrameBuffer::Settings &framebuffer_settings);
  glw::PTexture2D DiffTextures(const glw::PTexture2D &texture1, const glw::PTexture2D &texture2, const glw::FrameBuffer::Settings &framebuffer_settings);
}
#endif /* !HIRO_DRAW_TEXTURE_PROCESSING_H */