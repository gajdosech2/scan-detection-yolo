/*
  Copyright (C) Skeletex Research, s.r.o. - All Rights Reserved
  Unauthorized copying of this file, via any medium is strictly prohibited
  Proprietary and confidential
*/
#ifndef COGS_C_SCAN_H
#define COGS_C_SCAN_H
#include "API.h"
#include <COGS/C_PointCloud.h>
#include <COGS/ScanCameraParams.h>

namespace cogs
{
  /*!
    \brief Adapter for cogs::Scan structure.
  */
  class COGS_API C_Scan : public C_PointCloud
  {
  public:
    const static glm::vec3 CAMERA_SPACE_FORWARD;
    const static glm::vec3 CAMERA_SPACE_UP;
    const static glm::vec3 CAMERA_SPACE_RIGHT;

    //! Creates a scan with no points.
    C_Scan();
    //! Destroys scan.
    virtual ~C_Scan();

    //! Make a deep copy of the source C_Scan
    C_Scan(const C_Scan &source);
    //! Make a deep copy of the source C_Scan.
    C_Scan &operator=(const C_Scan &source);
    //! Move-construct C_Scan.
    C_Scan(C_Scan &&) noexcept = default;
    //! Move-construct C_Scan.
    C_Scan &operator=(C_Scan &&) noexcept = default;

    //! Imports scan from a file.
    virtual bool Import(const char *filename) override;
    //! Exports scan to a file.
    virtual bool Export(const char *filename) const override;

    /*!
      \brief
      Changes grid resolution new grid points are empty and old points may be erased.
      \warning
      Camera parameters remain unchanged.
    */
    void SetResolution(const glm::uvec2 &new_resolution);
    //! Returns current grid resolution.
    glm::uvec2 GetResolution() const;

    //! Returns current grid width.
    inline uint32_t GetWidth() const { return GetResolution()[0]; }
    //! Returns current grid height.
    inline uint32_t GetHeight() const { return GetResolution()[1]; }

    //! Sets camera parameters to the new value.
    void SetCameraParams(const ScanCameraParams &new_params);
    //! Returns currently set camera parameters.
    const ScanCameraParams &GetCameraParams() const;
    //! Sets camera position to the new value.
    void SetCameraPosition(const glm::vec3 &new_position);
    //! Returns currently set camera position.
    const glm::vec3 &GetCameraPosition() const;
    //! Sets camera basis to the new value.
    void SetCameraBasis(const glm::mat3 &new_basis);
    //! Returns currently set camera basis.
    glm::mat3 GetCameraBasis() const;

    //! Returns points coordinates.
    const glm::uvec2 *GetCoords() const;

    //! Checks whether the coordinates are valid and occupied by a point.
    bool IsPointAt(const glm::uvec2 &coord) const;
    //! Checks whether the coordinates are valid and occupied by a point.
    bool IsPointAt(const uint32_t x_coord, const uint32_t y_coord) const;

    //! Adds new point at grid coordinate. Returns point index.
    uint32_t AddPointAt(const glm::uvec2 &coord);
    //! Adds new point at grid coordinate. Returns point index.
    uint32_t AddPointAt(const uint32_t x_coord, const uint32_t y_coord);

    //! Adds a vector of new points at grid coordinates. Returns starting point index.
    uint32_t AddPointsAt(const glm::uvec2 *new_coords, uint32_t array_size);

    //! Returns point index at grid coordinate. May return Scan::INVALID_INDEX if there is no point.
    uint32_t GetPointAt(const glm::uvec2 &coord) const;
    //! Returns point index at grid coordinate. May return Scan::INVALID_INDEX if there is no point.
    uint32_t GetPointAt(const uint32_t x_coord, const uint32_t y_coord) const;

    //! Get coordinate
    static bool GetCameraUV(const glm::vec3 &point, const ScanCameraParams &cam_params, glm::vec2 &result);

    //! Transforms point positions, normals and updates camera
    virtual void Transform(const glm::mat4 &transform) override;

  protected:
    //! Returns reference to the inner cogs::Scan.
    class Scan &GetScan();
    //! Returns const reference to the inner cogs::Scan.
    const Scan &GetScan() const;
  };
}




#endif /* !COGS_C_SCAN_H */