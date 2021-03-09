/*
  Copyright (C) Skeletex Research, s.r.o. - All Rights Reserved
  Unauthorized copying of this file, via any medium is strictly prohibited
  Proprietary and confidential
*/
#ifndef GLW_SHADER_PROGRAM_H
#define GLW_SHADER_PROGRAM_H
#include <memory>
#include <vector>
#include <map>
#include <glbinding/gl/gl.h>
#include <GLW/API.h>



namespace glw
{

  //! Indicates the type of shader.
  enum class ShaderType
  {
    vertex		= (unsigned int)gl::GLenum::GL_VERTEX_SHADER,
    tess_ctrl	= (unsigned int)gl::GLenum::GL_TESS_CONTROL_SHADER,
    tess_eval	= (unsigned int)gl::GLenum::GL_TESS_EVALUATION_SHADER,
    geometry	= (unsigned int)gl::GLenum::GL_GEOMETRY_SHADER,
    fragment	= (unsigned int)gl::GLenum::GL_FRAGMENT_SHADER,
    compute		= (unsigned int)gl::GLenum::GL_COMPUTE_SHADER,
    none		= (unsigned int)gl::GLenum::GL_NONE
  };

  //! Creates ShaderType from extension of specified shader file name.
  GLW_API glw::ShaderType GetShaderTypeFromFileName(const std::string &filename);



  using PShader = std::shared_ptr<class Shader>;

  //! Maintains the source code strings that defines a shader.
  class GLW_API Shader
  {
  public:

    using ReplaceMap = std::map<std::string, std::string>;

    //! Crate a shader object and return reference.
    static PShader Create(const ShaderType shader_type);

    //! Create and compile a shader object and show compilation errors.
    static PShader CreateFromFile(const ShaderType shader_type, const std::string &file_name, const ReplaceMap &replace_map = ReplaceMap());

    //! Create and compile a shader object and show compilation errors.
    static PShader CreateFromStr(const ShaderType shader_type, const std::string &shader_code, const ReplaceMap &replace_map = ReplaceMap());

    //! Create new shader object of specified type.
    Shader(const ShaderType shader_type);

    //! Create new shader object of specified type.
    Shader(const gl::GLenum shader_type);

    //! Destroy shader object and release OpenGL resources.
    ~Shader();

    //! Load shader source from string.
    bool LoadFromStr(const std::string &shader_code, const ReplaceMap &replace_map = ReplaceMap());

    //! Load shader source from text file.
    bool LoadFromFile(const std::string &file_name, const ReplaceMap &replace_map = ReplaceMap());

    //! Compiles shader and returns whether was compilation successful.
    bool Compile();

    //! Checks, if last compilation was successful.
    bool IsCompiled() const;

    //! Returns OpenGL reference id.
    gl::GLuint GetID() const;

    //! Get type of this.
    ShaderType GetType() const;

    //! Get log of last compilation with errors and warnings. If no errors, function returns empty string.
    std::string GetCompilationLog() const;

  private:
    ShaderType type_;
    gl::GLuint shader_id_ = 0;
    bool was_compiled_successfully_ = false;
  };



  using PProgram = std::shared_ptr <class Program>;

  //! Holds several compiled shaders which are used as a whole.
  class GLW_API Program
  {
  public:
    //! Crates a program object and returns reference.
    static PProgram Create();

    //! Creates shader program.
    explicit Program();

    //! Destroy program object and remove OpenGL references.
    ~Program();

    //! Attaches a compiled shader to the program.
    bool AttachShader(const PShader &shader_ptr);

    //! Links all attached Shader files and returns whether linking finished successfully.
    bool Link();

    //! Checks, whether last linking has finished successful.
    bool IsLinked() const;

    //! Returns OpenGL reference index.
    gl::GLuint GetID() const;

    //! Returns log of last linking. When no errors nor warnings occurred, returned string is empty.
    std::string GetLinkLog() const;

    //! Use this program as OpenGL current.
    void Use() const;

    //! Returns location of uniform variable with specified name.
    gl::GLint GetUniformLocation(const std::string &name) const;

    //! Returns location of uniform block with specified name.
    gl::GLint GetUniformBlockLocation(const std::string &name) const;

  private:
    gl::GLuint program_id_ = 0;
    bool is_linked_successfuly = false;
    std::map<ShaderType, PShader> attached_shaders_;
  };

}

#endif /* !GLW_SHADER_PROGRAM_H */