/*
  Copyright (C) Skeletex Research, s.r.o. - All Rights Reserved
  Unauthorized copying of this file, via any medium is strictly prohibited
  Proprietary and confidential
*/
#ifndef COGS_SCAN_H
#define COGS_SCAN_H
#include <COGS/PointCloud.h>
#include <COGS/Grid.h>
#include <COGS/ScanCameraParams.h>

namespace cogs
{

  /*!
    \brief
      Set of 3D data points which are additionally organized over 2D grid.

    Class extends PointCloud by holding point indices in 2D grid. Adding of new points
    must be done strictly through grid so that each point has a valid grid coordinate.
  */
  class COGS_API Scan : public PointCloud
  {
  public:
    const static glm::vec3 CAMERA_SPACE_FORWARD;
    const static glm::vec3 CAMERA_SPACE_UP;
    const static glm::vec3 CAMERA_SPACE_RIGHT;


    //! Index which is never assigned to any point. Indicates invalid points.
    static const uint32_t INVALID_INDEX;
    //! Type of point Coordinates.
    using Coords = glm::uvec2;

    //! Creates a new scan with zero resolution and no points.
    Scan();
    //! Destroys cloud, frees all property data and destroys grid.
    ~Scan() override = default;

    //! Make a deep copy of the source Scan.
    Scan(const Scan &source);
    //! Make a deep copy of the source Scan.
    Scan &operator=(const Scan &source);
    //! Move-construct Scan.
    Scan(Scan &&) = default;
    //! Move-construct Scan.
    Scan &operator=(Scan &&) = default;

    //! Imports scan from a file.
    virtual bool Import(const std::string &filename) override;
    //! Exports scan to a file.
    virtual bool Export(const std::string &filename) const override;

    //! Changes capacity of cloud. This method is not adding any points.
    virtual void Reserve(uint32_t new_capacity) override;
    //! Frees spare memory so that new capacity exactly matches size.
    virtual void ShrinkToFit() override;
    //! Removes all points from cloud.
    virtual void Clear() override;

    //! Calls PointCloud::ClonePropertiesOf and additionally copies resolution and camera parameters.
    virtual void ClonePropertiesOf(const cogs::Scan &scan);

    /*!
      \brief
        Changes grid resolution new grid points are empty and old points may be erased.
      \warning
        Camera parameters remain unchanged.
    */
    void SetResolution(const glm::uvec2 &new_resolution);
    //! Returns current grid resolution.
    [[nodiscard]] glm::uvec2 GetResolution() const;

    //! Returns current grid width.
    [[nodiscard]] inline uint32_t GetWidth() const { return GetResolution()[0]; }
    //! Returns current grid height.
    [[nodiscard]] inline uint32_t GetHeight() const { return GetResolution()[1]; }

    //! Sets camera parameters to the new value.
    void SetCameraParams(const ScanCameraParams &new_params);
    //! Returns currently set camera parameters.
    [[nodiscard]] const ScanCameraParams &GetCameraParams() const;
    //! Sets camera position to the new value.
    void SetCameraPosition(const glm::vec3 &new_position);
    //! Returns currently set camera position.
    [[nodiscard]] const glm::vec3 &GetCameraPosition() const;
    //! Sets camera basis to the new value.
    void SetCameraBasis(const glm::mat3 &new_basis, const utils::BasisDefinition &basis_def);
    //! Returns currently set camera basis in the specified basis definition.
    [[nodiscard]] glm::mat3 GetCameraBasis(const utils::BasisDefinition &basis_def) const;
    //! Returns camera forward direction.
    [[nodiscard]] glm::vec3 GetCameraForward() const;
    //! Returns camera up direction.
    [[nodiscard]] glm::vec3 GetCameraUp() const;

    //! Returns current camera basis definition.
    [[nodiscard]] utils::BasisDefinition GetCameraBasisDefinition() const;
    //! Changes camera basis definition and transforms internal camera basis to the new one.
    void ChangeCameraBasisDefinition(const utils::BasisDefinition &new_def);
    //! Returns string representation of current camera basis definition.
    std::string GetCameraBasisDefinitionId() const;


    //! Returns points coordinates.
    [[nodiscard]] const std::vector<Coords> &GetCoords() const;

    //! Checks whether the coordinates are valid and occupied by a point.
    [[nodiscard]] bool IsPointAt(const glm::uvec2 &coord) const;
    //! Checks whether the coordinates are valid and occupied by a point.
    [[nodiscard]] bool IsPointAt(const uint32_t x_coord, const uint32_t y_coord) const;

    //! Adds new point at grid coordinate. Returns point index.
    uint32_t AddPointAt(const glm::uvec2 &coord);
    //! Adds new point at grid coordinate. Returns point index.
    uint32_t AddPointAt(const uint32_t x_coord, const uint32_t y_coord);

    //! Adds a vector of new points at grid coordinates. Returns starting point index.
    uint32_t AddPointsAt(const std::vector<glm::uvec2> &new_coords);

    //! Returns point index at grid coordinate. May return Scan::INVALID_INDEX if there is no point.
    [[nodiscard]] uint32_t GetPointAt(const glm::uvec2 &coord) const;
    //! Returns point index at grid coordinate. May return Scan::INVALID_INDEX if there is no point.
    [[nodiscard]] uint32_t GetPointAt(const uint32_t x_coord, const uint32_t y_coord) const;

    //! Returns coordinate for given point.
    static bool GetCameraUV(const glm::vec3 &point, const ScanCameraParams &cam_params, glm::vec2 &result);

    /*!
      \brief Transforms point positions and normals and camera parameters.
      \param transformation   Transformation matrix applied on every point and camera parameter.
      \param resulting_space  Resulting point cloud space after the transformation is applied.
    */
    virtual void Transform(
      const glm::mat4 &transformation,
      const std::optional<utils::SpaceDefinition> &resulting_space = std::nullopt) override;

    //! Computes depth map from scan.
    [[nodiscard]] static std::vector<std::vector<float>> ComputeDepthMap(const cogs::Scan &scan);

    //! Computes depth map from scan and custom camera position.
    [[nodiscard]] static std::vector<std::vector<float>> ComputeDepthMap(
        const cogs::Scan &scan,
        const glm::vec3 &camera_position);

    //! Computes map of point indices from scan.
    [[nodiscard]] static std::vector<std::vector<uint32_t>> ComputeIndexMap(const cogs::Scan &scan);

  protected:

    //! Deep-clone source Scan.
    void MakeCloneOf(const Scan &source);
    //! Decreases cloud size by the specified number of points.
    virtual void TruncateSize(size_t delta_size) override;

  private:

    cogs::Grid<uint32_t> index_grid_;
    std::vector<Coords> coords_;

    glm::vec3 camera_position_{ 0.0f };
    glm::mat3 camera_basis_{ 1.0f };
    utils::BasisDefinition camera_basis_definition_{ utils::COGS_CAMERA_SPACE };
    ScanCameraParams camera_params_;

    virtual bool Resize(uint32_t new_size) override;
    virtual bool Append(const PointCloud &pc) override;
    //! Copies chunks of points according to copy commands.
    virtual void ExecuteCopyCommands(const std::vector<CopyCommand> &copy_cmd) override;

    void UpdateCameraViewMatrix();

    //! Checks whether the coordinates are valid and not occupied by a point.
    [[nodiscard]] bool IsNullPointAt(const glm::uvec2 &coord) const;
    //! Checks whether the coordinates are valid and not occupied by a point.
    [[nodiscard]] bool IsNullPointAt(const uint32_t x_coord, const uint32_t y_coord) const;
  };
}

#endif /* !COGS_SCAN_H */