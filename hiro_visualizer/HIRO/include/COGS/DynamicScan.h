#ifndef COGS_DYNAMIC_SCAN_H
#define COGS_DYNAMIC_SCAN_H
#include <glm/detail/type_mat4x4.hpp>
#include <COGS/Scan.h>

namespace cogs
{
  //! Scan able to change and remember its current transformation.
  class COGS_API DynamicScan : public cogs::Scan
  {
  public:

    //! Creates a new scan with zero resolution and no points.
    DynamicScan() = default;
    //! Destroys cloud, frees all property data and destroys grid.
    ~DynamicScan() override = default;

    //! Make a deep copy of the source Scan.
    DynamicScan(const DynamicScan &source);
    //! Make a deep copy of the source Scan.
    DynamicScan &operator=(const DynamicScan &source);
    //! Move-construct Scan.
    DynamicScan(DynamicScan &&) = default;
    //! Move-construct Scan.
    DynamicScan &operator=(DynamicScan &&) = default;

    /*!
      \brief Transforms point positions and normals and camera parameters.
      \param transformation   Transformation matrix applied on every point and camera parameter.
      \param resulting_space  Resulting point cloud space after the transformation is applied.
    */
    virtual void Transform(
      const glm::mat4 &transformation,
      const std::optional<utils::SpaceDefinition> &resulting_space = std::nullopt) override;

    //! Returns cumulative transformation applied to scan from creation.
    const glm::mat4 &GetCurrentTransform() const;

    //! Resets scan to its previous state and current transformation to identity.
    void ResetTransform();

  private:
    glm::mat4 transformation_{ glm::mat4(1.0f) };
  };
}

#endif /* !COGS_DYNAMIC_SCAN_H */