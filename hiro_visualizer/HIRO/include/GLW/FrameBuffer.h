/*
  Copyright (C) Skeletex Research, s.r.o. - All Rights Reserved
  Unauthorized copying of this file, via any medium is strictly prohibited
  Proprietary and confidential
*/
#ifndef GLW_FRAME_BUFFER_H
#define GLW_FRAME_BUFFER_H
#include <glm/glm.hpp>
#include <glbinding/gl/gl.h>
#include <string>
#include <vector>
#include <GLW/Texture.h>

namespace glw
{

  using PFrameBuffer = std::shared_ptr<class FrameBuffer>;

  //! Class used to store buffers for internal rendering.
  class GLW_API FrameBuffer
  {
  public:

    //! Possible depth buffer types.
    enum class DepthBufferType
    {
      none = 0,     //!< No depth buffer.
      hidden = 1,   //!< Hidden depth buffer using render buffer.
      texture = 2   //!< Accessible depth buffer using texture object.
    };

    //! Settings defining frame buffer properties.
    struct Settings
    {
      //! Horizontal frame buffer resolution.
      uint32_t width{ 0 };
      //! Vertical frame buffer resolution.
      uint32_t height{ 0 };
      //! Whether frame buffer should use multi-sampled attachments.
      bool multisample_enabled{ false };
      //! Number of samples. Used only when multi-sample enabled.
      uint32_t multisample_samples{ 4 };
      //! Type of depth buffer.
      DepthBufferType depth_buffer_type{ DepthBufferType::hidden };
      //! Data format of depth buffer. Used when depth buffer type is not DepthBufferType::none.
      DepthDataFormat depth_format{ DepthDataFormat::uint24_norm };
      //! Color format for every color attachment. Vector size defines number of attachments.
      std::vector<gl::GLenum> color_format;
      Settings() = default;
    };

    /*!
      \brief
      Creates initialized FrameBuffer object. Returns nullptr when OpenGL version is not sufficient.
      \param settings
        Settings used for FrameBuffer initialization.
    */
    static PFrameBuffer Create(const FrameBuffer::Settings &settings);

    /*!
      \brief
      Creates object. Needs to be initialized before use.
    */
    FrameBuffer(const FrameBuffer::Settings &settings);

    //! Destroys object and allocated resources.
    ~FrameBuffer();

    bool IsGood() const;

    const FrameBuffer::Settings &GetSettings() const;

    //! Binds this FrameBuffer object.
    void Bind() const;

    //! Binds default FrameBuffer.
    void Unbind() const;

    //! Returns number of color attachments.
    size_t GetTextureCount() const;

    //! Returns color attachment texture object.
    PTexture GetTexture(size_t texture_id = 0) const;

    //! Returns 2D color attachment texture object. If initialized to use multiple samples, returns nullptr.
    PTexture2D GetTexture2D(size_t texture_id = 0) const;

    //! Return depth attachment texture object.
    PTexture GetDepthTexture() const;

    //! Return 2D depth attachment texture object.
    PTexture2D GetDepthTexture2D() const;

    //! Binds all attached textures to different texture units in order.
    void BindTextures() const;

    //! Returns resolution frame buffer. Samples are not included.
    glm::uvec2 GetResolution() const;

    //! Returns horizontal resolution of frame buffer. Samples are not included.
    uint32_t GetWidth() const;

    //! Returns vertical resolution of frame buffer. Samples are not included.
    uint32_t GetHeight() const;

    //! Returns OpenGL name of frame buffer.
    gl::GLuint GetId() const;

    //! Copies data from this FrameBuffer to the passed. Returns true if copy was successful.
    bool CopyTo(const PFrameBuffer &dest) const;

    //! Copies data from this FrameBuffer to the passed. Returns true if copy was successful.
    PFrameBuffer Clone() const;

    //! Test whether number of color attachments satisfies the system limit.
    static bool TestMaxColorAttachments(int32_t color_att_count);

    //! Test whether system OpenGL version is sufficient for FrameBuffer usage.
    static bool TestOpenGLVersion();

  private:
    FrameBuffer(const FrameBuffer &) = delete;

    Settings settings_;
    bool is_good_{ false };
    gl::GLuint fbo_id_{ 0 };
    gl::GLuint depth_renderbuffer_id_{ 0 };
    PTexture depth_texture_{ nullptr };
    std::vector<PTexture> color_textures_;

  };

}

#endif /* !GLW_FRAME_BUFFER_H */