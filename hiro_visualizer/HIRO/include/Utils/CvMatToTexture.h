#include <glm/gtc/type_ptr.hpp>
#include <opencv2/opencv.hpp>
#include <GLW/Texture.h>
#include <Utils/Ulog.h>

namespace utils
{

  const std::unordered_map<int, std::string> CV_MAT_TYPE_TO_STRING =
  {
    {CV_8UC1, "CV_8UC1"},
    {CV_8SC1, "CV_8SC1"},
    {CV_16UC1, "CV_16UC1"},
    {CV_16SC1, "CV_16SC1"},
    {CV_32SC1, "CV_32SC1"},
    {CV_32FC1, "CV_32FC1"},
    {CV_64FC1, "CV_64FC1"},
    {CV_8UC2, "CV_8UC2"},
    {CV_8SC2, "CV_8SC2"},
    {CV_16UC2, "CV_16UC2"},
    {CV_16SC2, "CV_16SC2"},
    {CV_32SC2, "CV_32SC2"},
    {CV_32FC2, "CV_32FC2"},
    {CV_64FC2, "CV_64FC2"},
    {CV_8UC3, "CV_8UC3"},
    {CV_8SC3, "CV_8SC3"},
    {CV_16UC3, "CV_16UC3"},
    {CV_16SC3, "CV_16SC3"},
    {CV_32SC3, "CV_32SC3"},
    {CV_32FC3, "CV_32FC3"},
    {CV_64FC3, "CV_64FC3"},
    {CV_8UC4, "CV_8UC4"},
    {CV_8SC4, "CV_8SC4"},
    {CV_16UC4, "CV_16UC4"},
    {CV_16SC4, "CV_16SC4"},
    {CV_32SC4, "CV_32SC4"},
    {CV_32FC4, "CV_32FC4"},
    {CV_64FC4, "CV_64FC4"},
  };

  gl::GLenum CvMatTypeToGlType(const int mat_type)
  {
    if (!std_ext::Contains(mat_type, CV_MAT_TYPE_TO_STRING))
    {
      return gl::GLenum(0);
    }
    const auto &mat_type_str = CV_MAT_TYPE_TO_STRING.at(mat_type);
    if (std_ext::Contains("8U", mat_type_str))
    {
      return gl::GL_UNSIGNED_BYTE;
    }
    if (std_ext::Contains("8S", mat_type_str))
    {
      return gl::GL_BYTE;
    }
    if (std_ext::Contains("16U", mat_type_str))
    {
      return gl::GL_UNSIGNED_SHORT;
    }
    if (std_ext::Contains("16S", mat_type_str))
    {
      return gl::GL_SHORT;
    }
    if (std_ext::Contains("32S", mat_type_str))
    {
      return gl::GL_INT;
    }
    if (std_ext::Contains("32F", mat_type_str))
    {
      return gl::GL_FLOAT;
    }
    return gl::GLenum(0);
  }

  unsigned int GetNumOfChannels(const int mat_type)
  {
    if (!std_ext::Contains(mat_type, CV_MAT_TYPE_TO_STRING))
    {
      return 0;
    }
    const auto &mat_type_str = CV_MAT_TYPE_TO_STRING.at(mat_type);
    if (std_ext::Contains("C1", mat_type_str))
    {
      return 1;
    }
    if (std_ext::Contains("C2", mat_type_str))
    {
      return 2;
    }
    if (std_ext::Contains("C3", mat_type_str))
    {
      return 3;
    }
    if (std_ext::Contains("C4", mat_type_str))
    {
      return 4;
    }
    return 0;
  }

  glw::PTexture2D MatToTexture(const cv::Mat &image, bool flip_vertically)
  {
    cv::Mat img = image.clone();
    if (flip_vertically)
    {
      cv::flip(img, img, 0);
    }

    const int mat_type = image.type();

    gl::GLenum input_format;
    gl::GLenum internal_format;
    if (img.channels() == 1)
    {
      input_format = gl::GL_LUMINANCE;
      switch (mat_type)
      {
      case CV_8UC1:
        internal_format = gl::GL_R8;
        break;
      case CV_8SC1:
        internal_format = gl::GL_R8I;
        break;
      case CV_16UC1:
        internal_format = gl::GL_R16UI;
        break;
      case CV_16SC1:
        internal_format = gl::GL_R16I;
        break;
      case CV_32SC1:
        internal_format = gl::GL_R32I;
        break;
      case CV_32FC1:
        internal_format = gl::GL_R32F;
        break;
      default:
        internal_format = gl::GL_R8;
        break;
      }

    }
    else if (img.channels() == 3)
    {
      input_format = gl::GL_BGR;
      switch (mat_type)
      {
      case CV_8UC3:
        internal_format = gl::GL_RGB8;
        break;
      case CV_8SC3:
        internal_format = gl::GL_RGB8I;
        break;
      case CV_16UC3:
        internal_format = gl::GL_RGB16UI;
        break;
      case CV_16SC3:
        internal_format = gl::GL_RGB16I;
        break;
      case CV_32SC3:
        internal_format = gl::GL_RGB32I;
        break;
      case CV_32FC3:
        internal_format = gl::GL_RGB32F;
        break;
      default:
        internal_format = gl::GL_RGB8;
        break;
      }
    }
    else if (img.channels() == 4)
    {
      input_format = gl::GL_BGRA;
      switch (mat_type)
      {
      case CV_8UC4:
        internal_format = gl::GL_RGBA8;
        break;
      case CV_8SC4:
        internal_format = gl::GL_RGBA8I;
        break;
      case CV_16UC4:
        internal_format = gl::GL_RGBA16UI;
        break;
      case CV_16SC4:
        internal_format = gl::GL_RGBA16I;
        break;
      case CV_32SC4:
        internal_format = gl::GL_RGBA32I;
        break;
      case CV_32FC4:
        internal_format = gl::GL_RGBA32F;
        break;
      default:
        internal_format = gl::GL_RGBA8;
        break;
      }
    }
    else
    {
      ulog::Fail("Unrecognized OpenCV image format. Invalid number of dimensions (" + std::to_string(img.channels()) + ").", "utils::MatToTexture");
      return nullptr;
    }

    glw::PTexture2D texture = glw::Texture2D::Create(img.cols, img.rows, internal_format);
    texture->Bind();

    int *param = new int[1];
    gl::glGetIntegerv(gl::GL_UNPACK_ALIGNMENT, param);

    gl::glPixelStorei(gl::GL_UNPACK_ALIGNMENT, 1);

    gl::GLenum gl_type = CvMatTypeToGlType(mat_type);

    if (gl_type == 0)
    {
      ulog::Fail("Unsupported cv::Mat data type.", "utils::MatToTexture");
      return texture;
    }

    texture->SetData(input_format, gl_type, img.ptr());

    gl::glPixelStorei(gl::GL_UNPACK_ALIGNMENT, *param);

    texture->Unbind();
    return texture;
  }

  cv::Mat TextureToMat(const glw::PTexture2D &texture, bool flip_vertically /*= false*/, const int mat_type /*= CV_8UC3*/)
  {
    if (texture == nullptr)
    {
      return cv::Mat();
    }

    texture->Bind();
    int gl_texture_width, gl_texture_height;
    const gl::GLenum gl_type = CvMatTypeToGlType(mat_type);
    const unsigned int num_of_channels = GetNumOfChannels(mat_type);

    if (num_of_channels == 0 || num_of_channels == 2 || num_of_channels > 4)
    {
      ulog::Fail("Unrecognized OpenCV image format. Invalid number of dimensions.", "utils::TextureToMat");
      return cv::Mat();
    }

    gl::glGetTexLevelParameteriv(gl::GL_TEXTURE_2D, 0, gl::GL_TEXTURE_WIDTH, &gl_texture_width);
    gl::glGetTexLevelParameteriv(gl::GL_TEXTURE_2D, 0, gl::GL_TEXTURE_HEIGHT, &gl_texture_height);

    auto gl_texture_floats = (float *)malloc(sizeof(float) * gl_texture_width * gl_texture_height * num_of_channels);

    if (num_of_channels == 1)
    {
      gl::glGetTexImage(gl::GL_TEXTURE_2D, 0, gl::GL_R, gl_type, gl_texture_floats);
    }
    else if (num_of_channels == 3)
    {
      gl::glGetTexImage(gl::GL_TEXTURE_2D, 0, gl::GL_BGR, gl_type, gl_texture_floats);
    }
    else
    {
      gl::glGetTexImage(gl::GL_TEXTURE_2D, 0, gl::GL_BGRA, gl_type, gl_texture_floats);
    }

    texture->Unbind();

    cv::Mat result = cv::Mat(gl_texture_height, gl_texture_width, mat_type, gl_texture_floats);
    result = result.clone();

    delete gl_texture_floats;

    if (flip_vertically)
    {
      cv::Mat flipped_mat;
      cv::flip(result, flipped_mat, 0);
      return flipped_mat;
    }

    return result;
  }

}