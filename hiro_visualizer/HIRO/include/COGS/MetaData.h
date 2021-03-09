#ifndef COGS_META_DATA_H
#define COGS_META_DATA_H

#include <optional>
#include <memory>
#include <string>
#include <vector>
#include <glm/vec3.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <Utils/GeometryStructures.h>

#include <COGS/Scan.h>


namespace cogs
{
  class MetaData
  {

  public:
    enum class Units : uint8_t
    {
      m = 0,
      mm = 1
    };



    struct Transformation
    {
      Transformation() {}
      ~Transformation() = default;

      glm::vec3 translation;
      glm::quat rotation;
      float scaling = 1.0f;
    };



    struct CameraParams
    {
      CameraParams() {}
      ~CameraParams() = default;

      glm::uvec2 resolution;
      glm::vec3 position;
      glm::vec3 forward;
      glm::vec3 up;
      glm::vec3 right;
      float fx = 0.0f, fy = 0.0f,
            cx = 0.0f, cy = 0.0f;
      float k1 = 0.0f, k2 = 0.0f, k3 = 0.0f,
            p1 = 0.0f, p2 = 0.0f;
    };

    struct CameraSpace
    {
      glm::vec3 forward;
      glm::vec3 up;
      glm::vec3 right;
    };

    MetaData()
      : units(Units::m)
      , transformation()
      , camera_params(std::nullopt)
    {
      camera_space.forward = cogs::Scan::CAMERA_SPACE_FORWARD;
      camera_space.up = cogs::Scan::CAMERA_SPACE_UP;
      camera_space.right = cogs::Scan::CAMERA_SPACE_RIGHT;
    }

    ~MetaData() = default;

    std::shared_ptr<glm::mat4> GetTransformationMatrix() const
    {
      return std::make_shared<glm::mat4>(
          glm::translate(glm::mat4(1.0f), transformation.translation)
          * glm::scale(glm::mat4(1.0f), glm::vec3(transformation.scaling))
          * glm::mat4_cast(transformation.rotation));
    }

    Units units;
    CameraSpace camera_space;
    Transformation transformation;
    std::optional<CameraParams> camera_params;
  };
}

#endif /* !COGS_META_DATA_H */