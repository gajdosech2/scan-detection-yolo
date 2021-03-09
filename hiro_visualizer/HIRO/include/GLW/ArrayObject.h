/*
  Copyright (C) Skeletex Research, s.r.o. - All Rights Reserved
  Unauthorized copying of this file, via any medium is strictly prohibited
  Proprietary and confidential
*/
#ifndef GLW_ARRAY_OBJECT_H
#define GLW_ARRAY_OBJECT_H
#include <memory>
#include <vector>
#include <string>

#include <glbinding/gl/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <GLW/API.h>

namespace glw
{

  /*!
    \brief
      Hint to the GL implementation as to how a buffer object's data store will be accessed.

    The frequency of access may be one of these:
    STREAM - The data store contents will be modified once and used at most a few times.
    STATIC - The data store contents will be modified once and used many times.
    DYNAMIC - The data store contents will be modified repeatedly and used many times.

    The nature of access may be one of these:
    DRAW - The data store contents are modified by the application, and used as the source for GL drawing and image specification commands.
    READ - The data store contents are modified by reading data from the GL, and used to return that data when queried by the application.
    COPY - The data store contents are modified by reading data from the GL, and used as the source for GL drawing and image specification commands.

  */
  enum class DataUsage : uint32_t
  {
    stream_draw = uint32_t(gl::GLenum::GL_STREAM_DRAW),
    stream_read = uint32_t(gl::GLenum::GL_STREAM_READ),
    stream_copy = uint32_t(gl::GLenum::GL_STREAM_COPY),
    static_draw = uint32_t(gl::GLenum::GL_STATIC_DRAW),
    static_read = uint32_t(gl::GLenum::GL_STATIC_READ),
    static_copy = uint32_t(gl::GLenum::GL_STATIC_COPY),
    dynamic_draw = uint32_t(gl::GLenum::GL_DYNAMIC_DRAW),
    dynamic_read = uint32_t(gl::GLenum::GL_DYNAMIC_READ),
    dynamic_copy = uint32_t(gl::GLenum::GL_DYNAMIC_COPY)
  };



  //! Specifies what kind of primitives are rendered.
  enum class DrawMode : uint32_t
  {
    points = uint32_t(gl::GLenum::GL_POINTS),
    lines = uint32_t(gl::GLenum::GL_LINES),
    line_strip = uint32_t(gl::GLenum::GL_LINE_STRIP),
    line_loop = uint32_t(gl::GLenum::GL_LINE_LOOP),
    triangles = uint32_t(gl::GLenum::GL_TRIANGLES),
    triangle_strip = uint32_t(gl::GLenum::GL_TRIANGLE_STRIP),
    triangle_fan = uint32_t(gl::GLenum::GL_TRIANGLE_FAN),
    patches = uint32_t(gl::GLenum::GL_PATCHES)
  };


  //! Array attribute. Defines how specific data are stored in combined buffer. For example how are vertex colors stored in array of vertex data.
  struct Attrib
  {
    gl::GLenum type;        // Type of attribute defined by OpenGL specifier.
    uint32_t per_vert;  // Number of values for a single vertex.
    uint64_t offset;    // Byte offset of first value, from buffer start.
    uint32_t stride;    // Byte space between starts of two consecutive attribute values.
    Attrib(gl::GLenum gl_type, uint32_t data_per_vert, uint32_t byte_offset, uint32_t byte_stride)
      : type(gl_type), per_vert(data_per_vert), offset(byte_offset), stride(byte_stride) {};
  };

  template <gl::GLenum T, uint32_t N>
  struct TAttrib : public Attrib
  {
    TAttrib() : Attrib(T, N, 0u, 0u) {};
    TAttrib(uint32_t byte_offset, uint32_t byte_stride)
      : Attrib(T, N, byte_offset, byte_stride) {};
  };

  using Attrib1f = TAttrib<gl::GLenum::GL_FLOAT, 1>;
  using Attrib2f = TAttrib<gl::GLenum::GL_FLOAT, 2>;
  using Attrib3f = TAttrib<gl::GLenum::GL_FLOAT, 3>;
  using Attrib4f = TAttrib<gl::GLenum::GL_FLOAT, 4>;
  using Attrib1i = TAttrib<gl::GLenum::GL_INT, 1>;
  using Attrib2i = TAttrib<gl::GLenum::GL_INT, 2>;
  using Attrib3i = TAttrib<gl::GLenum::GL_INT, 3>;
  using Attrib4i = TAttrib<gl::GLenum::GL_INT, 4>;



  using PArrayObject = std::shared_ptr<class ArrayObject>;

  //! Class to store data arrays. Arrays can be later accessed by shaders when draw is requested.
  class GLW_API ArrayObject
  {
  public:
    using BufferName = size_t;        //!< Identifier of vertex buffer.
    using ElementBufferName = size_t; //!< Identifier of element buffer.

    //! Element buffer or vertex buffer name which do not represent valid buffer.
    static const BufferName INVALID_NAME { UINT32_MAX };


    //! Crate a shared pointer with new instance of ArrayObject class.
    static PArrayObject Create(const size_t vertex_count);

    //! Creates new object. Defined vertex count is expected for a setters of this instance.
    explicit ArrayObject(size_t vertex_count);

    //! Destructs array object and frees all allocated OpenGL buffers.
    ~ArrayObject();

    //! Returns number of vertices expected by this instance.
    uint64_t GetVertexCount() const;

    //! Binds this ArrayObject. Needs to be called before any changes and drawings are performed with this object.
    void Bind() const;

    //! Unbinds this ArrayObject.
    void Unbind() const;

    //! Returns, whether this ArrayObject is currently bound.
    bool IsBound() const;

    //! Creates new buffer in graphic memory, and fills it with data. Parameter per_vert_size defines data memory size (in bytes) for each vertex.
    BufferName AddBuffer(const void *data, size_t per_vert_size, DataUsage usage = DataUsage::dynamic_draw);

    //! Replaces data in existing buffer.
    void SetBuffer(BufferName vert_buffer, const void *data, size_t per_vert_size);

    //! Checks whether specified buffer name belongs to valid buffer.
    bool IsBufferValid(BufferName vert_buffer) const;

    //! Creates shader binding for specified buffer. Attribute parameter defines how are data structured inside buffer.
    void SetBinding(const Attrib &att, uint32_t shader_location, BufferName buffer);

    //! Return the name of buffer that is bound to shader location. If no such buffer exists, returns INVALID_NAME.
    BufferName GetBinding(uint32_t shader_location) const;

    //! Check if there is binding for a shader location;
    bool ExistsBinding(uint32_t shader_location) const;

    //! Creates new buffer and sets shader binding. This function replaces call of SetBuffer and SetBinding with Attrib1f parameter.
    BufferName AddBufferBinding1f(uint32_t shader_location, const void *data);

    //! Creates new buffer and sets shader binding. This function replaces call of SetBuffer and SetBinding with Attrib2f parameter.
    BufferName AddBufferBinding2f(uint32_t shader_location, const void *data);

    //! Creates new buffer and sets shader binding. This function replaces call of SetBuffer and SetBinding with Attrib3f parameter.
    BufferName AddBufferBinding3f(uint32_t shader_location, const void *data);

    //! Creates new buffer and sets shader binding. This function replaces call of SetBuffer and SetBinding with Attrib4f parameter.
    BufferName AddBufferBinding4f(uint32_t shader_location, const void *data);

    //! Creates new buffer and sets shader binding. This function replaces call of SetBuffer and SetBinding with Attrib1i parameter.
    BufferName AddBufferBinding1i(uint32_t shader_location, const void *data);

    //! Creates new buffer and sets shader binding. This function replaces call of SetBuffer and SetBinding with Attrib2i parameter.
    BufferName AddBufferBinding2i(uint32_t shader_location, const void *data);

    //! Creates new buffer and sets shader binding. This function replaces call of SetBuffer and SetBinding with Attrib3i parameter.
    BufferName AddBufferBinding3i(uint32_t shader_location, const void *data);

    //! Creates new buffer and sets shader binding. This function replaces call of SetBuffer and SetBinding with Attrib4i parameter.
    BufferName AddBufferBinding4i(uint32_t shader_location, const void *data);

    //! Creates new element buffer which defines how primitives are structured.
    ElementBufferName AddElementBuffer(const uint32_t *data, size_t count);

    //! Set default drawing mode used when calling pure Draw or DrawInstanced functions. Default value is DrawMode::points.
    void SetDrawMode(DrawMode mode);

    //! Draws vertices or first defined elements. Default draw mode set by function SetDrawMode.
    void Draw() const;

    //! Draws vertices or first defined elements multiple times. Default draw mode set by function SetDrawMode.
    void DrawInstanced(uint32_t instance_count) const;

    //! Draws vertices from buffer arrays.
    void DrawVertices(DrawMode mode) const;

    //! Draws vertices from buffer arrays, the number of vertices drawn is num_vertices or vao vertex count, whichever is smaller.
    void DrawVertices(size_t num_vertices, DrawMode mode) const;

    //! Draws vertices from buffer arrays multiple times.
    void DrawVerticesInstanced(uint32_t instance_count, DrawMode mode) const;

    //! Draws elements specified element buffer.
    void DrawElements(ElementBufferName el_buff, DrawMode mode) const;

    //! Draws elements specified element buffer multiple times.
    void DrawElementsInstanced(uint32_t instance_count, ElementBufferName el_buff, DrawMode mode) const;

  protected:
    struct ElementBuffer
    {
      uint32_t name;
      size_t primitive_count;
    };
    uint32_t vao_ = 0;
    size_t vertex_count_ = 0;
    DrawMode default_mode_ = DrawMode::points;
    std::vector<uint32_t> buffer_names_;
    std::unordered_map<uint32_t, BufferName> bindings_;
    std::vector<ElementBuffer> elements_;
  };

}

#endif /* !GLW_ARRAY_OBJECT_H */