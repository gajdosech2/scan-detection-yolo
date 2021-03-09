/*
  Copyright (C) Skeletex Research, s.r.o. - All Rights Reserved
  Unauthorized copying of this file, via any medium is strictly prohibited
  Proprietary and confidential
*/
#ifndef COGS_C_POINT_CLOUD_H
#define COGS_C_POINT_CLOUD_H
#include <glm/glm.hpp>
#include <COGS/DataType.h>
#include <COGS/API.h>

namespace cogs
{
  // forward declaration of PointCloud class
  class PointCloud;

  //forward declaration of cogs::PointCloudProperty structure
  struct PointCloudProperty;
}

namespace cogs
{

  /*!
    \brief Adapter for cogs::PointCloud structure.
  */
  class COGS_API C_PointCloud
  {
  public:

    //! Creates a cloud with no points.
    C_PointCloud();
    //! Destroys cloud and frees all property data.
    virtual ~C_PointCloud();

    //! Make a deep copy of the source C_PointCloud.
    C_PointCloud(const C_PointCloud &source);
    //! Make a deep copy of the source C_PointCloud.
    C_PointCloud &operator=(const C_PointCloud &source);
    //! Move-construct C_PointCloud.
    C_PointCloud(C_PointCloud &&) noexcept = default;
    //! Move-construct C_PointCloud.
    C_PointCloud &operator=(C_PointCloud &&) noexcept = default;

    //! Imports point cloud from a file.
    virtual bool Import(const char *filename);
    //! Exports point clouds to a file.
    virtual bool Export(const char *filename) const;

    //! Resizes point count to the new value without initialization of data of newly created points.
    virtual void Resize(uint32_t new_size);
    //! Returns number of points currently stored in the cloud.
    virtual uint32_t GetSize() const;
    //! Changes capacity of cloud. This method is not adding any points.
    virtual void Reserve(uint32_t new_capacity);
    //! Returns how much points can be added with currently reserved memory.
    uint32_t GetCapacity() const;
    //! Frees spare memory so that new capacity exactly matches size.
    virtual void ShrinkToFit();
    //! Removes all points from cloud.
    void Clear();
    /*!
      \brief
        Removes points with specific ids from cloud.
      \param ids_to_erase
        Array of indices which should be erased.
      \param
        Number of indices provided in ids_to_erase array.
      \warning
        Method may change order of points.
    */
    virtual void Erase(const uint32_t *ids_to_erase, size_t count);
    /*!
      \brief
        Increments size of this by the size of pc and copies property data available in both.
      \note
        Properties not available in this will not be copied.
        To add also properties not currently available in this,
        use C_PointCloud::ClonePropertiesOf before calling this function.
    */
    virtual void Append(const C_PointCloud &pc);

    /*!
      \brief
        Returns pointer to position data.
      \note
        Equivalent to PointCloud::GetData<glm::vec3>(PointCloud::POSITIONS);
    */
    glm::vec3 *GetPositions();
    /*!
      \brief
        Returns pointer to position data.
      \note
        Equivalent to PointCloud::GetData<glm::vec3>(PointCloud::POSITIONS);
    */
    const glm::vec3 *GetPositions() const;

    /*!
      \brief
        Checks whether normal property exists.
      \note
        Equivalent to PointCloud::HasProperty(PointCloud::NORMALS);
    */
    bool HasNormals() const;
    /*!
      \brief
        When normal property exists, returns the pointer to data, nullptr otherwise.
      \note
        Equivalent to PointCloud::GetData<glm::vec3>(PointCloud::NORMALS);
    */
    glm::vec3 *GetNormals();
    /*!
      \brief
        When normal property exists, returns the pointer to data, nullptr otherwise.
      \note
        Equivalent to PointCloud::GetData<glm::vec3>(PointCloud::NORMALS);
    */
    const glm::vec3 *GetNormals() const;
    /*!
      \brief
        Creates PointCloud::NORMALS property buffer if it was is not added already.
      \note
        Do not add this property using PointCloud:AddProperty method.
    */
    void AddNormals();
    /*!
      \brief
      When intensity property exists, returns the pointer to data, nullptr otherwise.
      \note
      Equivalent to PointCloud::GetData<glm::vec3>(PointCloud::INTENSITIES);
    */

    float *GetIntensities();
    /*!
      \brief
      When intensity property exists, returns the pointer to data, nullptr otherwise.
      \note
      Equivalent to PointCloud::GetData<glm::vec3>(PointCloud::INTENSITIES);
    */
    const float *GetIntensities() const;
    /*!
      \brief
        Creates PointCloud::INTENSITIES property buffer if it was is not added already.
      \note
        Equivalent to PointCloud::AddProperty(PointCloud::INTENSITIES, DataType::FVEC3)
    */
    void AddIntensities();

    //! Returns count of all available properties.
    size_t GetPropertyCount() const;
    //! Returns an array of all available properties.
    const cogs::PointCloudProperty *GetProperties() const;

    /*!
      \brief
      Creates new property buffer.
      \param key
      Property identifier. If it already exists, does nothing and returns existing property.
      \param type
      Specific type of data in buffer.
    */
    const cogs::PointCloudProperty AddProperty(const char *key, DataType type);
    /*!
      \brief
        Creates new property buffer.
      \param key
         Property identifier. If it already exists, does nothing and returns existing property.
      \param bytes_per_point
        Number of bytes reserved for each point.
    */
    const cogs::PointCloudProperty AddProperty(const char *key, size_t bytes_per_point);
    //! Remove a single property by key..
    void RemoveProperty(const char *key);
    //! Checks whether a specific property exists.
    bool HasProperty(const char *key) const;
    //! Returns property with specified key if it exists, nullptr otherwise.
    PointCloudProperty GetProperty(const char *key);
    //! Returns property with specified key if it exists, nullptr otherwise.
    const PointCloudProperty GetProperty(const char *key) const;

    //! Transforms point positions and normals
    virtual void Transform(const glm::mat4 &transform);

  protected:
    //! Creates a wrapper for given cogs::PointCloud.
    C_PointCloud(cogs::PointCloud *target);

    //! Returns reference to the inner cogs::Pointcloud.
    PointCloud &GetPointCloud();
    //! Returns const reference to the inner cogs::Pointcloud.
    const PointCloud &GetPointCloud() const;

    //! Make a deep copy of the source C_PointCloud.
    void MakeCloneOf(const C_PointCloud &source);

  private:
    struct Impl;
    Impl *m = nullptr;
  };

}


#endif /* !COGS_C_POINT_CLOUD_H */