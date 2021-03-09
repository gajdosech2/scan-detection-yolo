/*
  Copyright (C) Skeletex Research, s.r.o. - All Rights Reserved
  Unauthorized copying of this file, via any medium is strictly prohibited
  Proprietary and confidential
*/
#ifndef GLW_SHADER_BUILD_H
#define GLW_SHADER_BUILD_H
#include <GLW/ShaderProgram.h>

namespace glw
{

  //! Returns directory path where function BuildShader looks for shader files. Can be changed by calling SetShaderBuildDirectory.
  GLW_API std::string GetShaderBuildDirectory();

  //! Changes directory path where function BuildShader looks for shader files.
  GLW_API void SetShaderBuildDirectory(const std::string &directory);

  /*!
    \brief
      Builds shader file using extended build system, which supports file including, error checks, etc.
    \param filename
      Name of shader file, which is looked for in directory set by SetShaderBuildDirectory.
    \param replace_map
      Searches for all occurrences of specified replacement pairs and replaces them.
  */
  GLW_API glw::PShader BuildShader(std::string filename, const glw::Shader::ReplaceMap replace_map);

}
#endif /* !GLW_SHADER_BUILD_H */