/*
  Copyright (C) Skeletex Research, s.r.o. - All Rights Reserved
  Unauthorized copying of this file, via any medium is strictly prohibited
  Proprietary and confidential
*/
#ifndef GLW_TEXTURE_H
#define GLW_TEXTURE_H
#include <string>
#include <map>
#include <vector>
#include <memory>

#include <glbinding/gl/gl.h>
#include <glm/glm.hpp>

#include <GLW/API.h>

namespace glw
{

  /*
    \brief
      Specifies how to evaluate color of a texture, when coordinate
      is outside of usual range <0,1>.
  */
  enum class Wrapping
  {
    //! repeats image as tiles
    repeat = uint32_t(gl::GLenum::GL_REPEAT),
    //! repeats image but flips closest tiles
    mirror_repeat = uint32_t(gl::GLenum::GL_MIRRORED_REPEAT),
    //! colors around image are equal to the image edges
    clamp = uint32_t(gl::GLenum::GL_CLAMP_TO_EDGE),
    //! colors around have color specified using GL_TEXTURE_BORDER_COLOR
    border_color = uint32_t(gl::GLenum::GL_CLAMP_TO_BORDER)
  };


  /*!
    \brief
      Texture filtering types. Define how colors are pulled from texture image
      when picking from between multiple texel points.
  */
  enum class Filtering
  {
    //! takes nearest texel to the coordinate
    nearest = uint32_t(gl::GLenum::GL_NEAREST),
    //! linearly interpolates 4 nearest texels
    linear = uint32_t(gl::GLenum::GL_LINEAR),
    //! takes nearest from closest mipmap level
    closest_mip_nearest = uint32_t(gl::GLenum::GL_NEAREST_MIPMAP_NEAREST),
    //! takes linear from closest mipmap level
    closest_mip_linear = uint32_t(gl::GLenum::GL_LINEAR_MIPMAP_NEAREST),
    //! takes nearest from the 2 closest mipmaps and interpolates
    inter_mip_nearest = uint32_t(gl::GLenum::GL_NEAREST_MIPMAP_LINEAR),
    //! takes linear from the 2 closest mipmaps and interpolates
    inter_mip_linear = uint32_t(gl::GLenum::GL_LINEAR_MIPMAP_LINEAR)
  };



  enum class ColorType
  {
    //! range < 0.0, 1.0> internally represented as 8 bit unsigned integral number
    uint8_norm,
    //! range <-1.0, 1.0> internally represented as 8 bit integral number
    int8_norm,
    //! range < 0.0, 1.0> internally represented as 16 bit unsigned integral number
    uint16_norm,
    //! range <-1.0, 1.0> internally represented as 16 bit integral number
    int16_norm,
    //! true 8 bit unsigned integral number
    uint8,
    //! true 8 bit integral number
    int8,
    //! true 16 bit unsigned integral number
    uint16,
    //! true 16 bit integral number
    int16,
    //! true 32 bit unsigned integral number
    uint32,
    //! true 32 bit integral number
    int32,
    //! 16 bit floating point number
    float16,
    //! 32 bit floating point number
    float32
  };

  //! Creates OpenGL color format from desired data type per channel, and desired number of channels.
  GLW_API gl::GLenum ColorFormat(const ColorType color_data_type, const uint8_t channels);



  enum class DepthDataFormat
  {
    //! range < 0.0, 1.0> internally represented as 16 bit unsigned integral number
    uint16_norm = uint32_t(gl::GLenum::GL_DEPTH_COMPONENT16),
    //! range < 0.0, 1.0> internally represented as 24 bit unsigned integral number
    uint24_norm = uint32_t(gl::GLenum::GL_DEPTH_COMPONENT24),
    //! 32 bit floating point number
    float32 = uint32_t(gl::GLenum::GL_DEPTH_COMPONENT32F)
  };



  using PTexture = std::shared_ptr<class Texture>;



  //! Basic texture type.
  class GLW_API Texture
  {
  public:
    explicit Texture();
    virtual ~Texture();
    void Initialize(const gl::GLenum internal_format);

    void Enable();
    void Disable();
    void Unbind();

    void Bind();
    void Bind(const uint8_t binding_unit);

    gl::GLuint GetID();

    gl::GLenum GetInternalFormat();

    void SetFiltering(const Filtering mag_min);
    virtual void SetFiltering(const Filtering mag, const Filtering min);

    void SetWrapping(const Wrapping wrap_st);
    virtual void SetWrapping(const Wrapping wrap_s, const Wrapping wrap_t);

    virtual void SetParameteri(const gl::GLenum pname, const gl::GLint param);
    void SetParameterfv(const gl::GLenum pname, const gl::GLfloat *param);

  protected:
    virtual gl::GLenum GetTarget() = 0;
    virtual void ReserveMemory() = 0;

  private:
    void GenerateId();
    gl::GLenum internal_format_ = gl::GLenum::GL_RGBA8;
    gl::GLuint texture_id_ = 0;
  };



  using PTexture2D = std::shared_ptr<class Texture2D>;



//! Two dimensional texture. Used mostly to store color images or results of internal rendering.
  class GLW_API Texture2D : public Texture
  {
  public:

    static PTexture2D Create(
      const uint32_t width,
      const uint32_t height,
      const gl::GLenum internal_format = gl::GLenum::GL_RGBA8);
    static PTexture2D CreateLayered(
      const uint32_t width,
      const uint32_t height,
      const uint32_t layer_count,
      const gl::GLenum internal_format = gl::GLenum::GL_RGBA8);
    static PTexture2D CreateFromFile(
      const std::string &image_file_name,
      const bool load_as_float = false);

  public:
    //! Creates a single 2D texture.
    Texture2D(
      const uint32_t width,
      const uint32_t height,
      const gl::GLenum internal_format = gl::GLenum::GL_RGBA8);
    //! Creates array of 2D textures, represented as layers.
    Texture2D(
      const uint32_t width,
      const uint32_t height,
      const uint32_t layer_count,
      const gl::GLenum internal_format);

    virtual ~Texture2D() override;

    uint32_t GetWidth();
    uint32_t GetHeight();
    glm::uvec2 GetResolution();
    uint32_t GetLayerCount();

    void SetData(
      const gl::GLenum data_format,
      const gl::GLenum data_type,
      const void *data_ptr);
    void SetDataLayer(
      const uint32_t layer,
      const gl::GLenum data_format,
      const gl::GLenum data_type,
      const void *data_ptr);

    bool SaveToFile(const std::string &image_file_name);

  protected:

    gl::GLenum GetTarget() override;
    void ReserveMemory() override;
  private:
    const gl::GLenum target_;
    uint32_t width_ = 0, height_ = 0;
    uint32_t layers_ = 1;
  };



  using PTexture2dMultisample = std::shared_ptr<class Texture2dMultisample>;



  /*!
    \brief Similar to Texture2D, uses multi-sampling for anti-aliasing effects.

    .. hint::
        When used in shader it must be decalred as `sampler2DMS` and accessed via `texelFetch()`.
  */
  class GLW_API Texture2dMultisample : public Texture
  {
  public:
    Texture2dMultisample(
      const uint32_t width,
      const uint32_t height,
      const gl::GLenum internal_format,
      const uint8_t sample_count);
    uint8_t GetSampleCount();
    uint32_t GetWidth();
    uint32_t GetHeight();
    void SetFiltering(const Filtering mag, const Filtering min) override;
    void SetWrapping(const Wrapping wrap_s, const Wrapping wrap_t) override;
    void SetParameteri(const gl::GLenum pname, const gl::GLint param) override;
  protected:
    gl::GLenum GetTarget() override;
    void ReserveMemory() override;
  private:
    const gl::GLenum target_ = gl::GLenum::GL_TEXTURE_2D_MULTISAMPLE;
    uint32_t width_ = 0, height_ = 0;
    uint8_t sample_count_ = 0;
  };


}

#endif /* !GLW_TEXTURE_H */