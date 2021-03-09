/*
  Copyright (C) Skeletex Research, s.r.o. - All Rights Reserved
  Unauthorized copying of this file, via any medium is strictly prohibited
  Proprietary and confidential
*/
#ifndef COGS_POINT_CLOUD_H
#define COGS_POINT_CLOUD_H
#include <vector>
#include <set>
#include <unordered_map>
#include <optional>
#include <variant>

#include <glm/glm.hpp>
#include <Utils/GeometryStructures.h>
#include <Utils/SpaceAndUnits.h>

#include <COGS/DataType.h>
#include <COGS/PointCloudProperty.h>


namespace cogs
{
  /*!
    \brief
      Management class for a set of data points in a 3D space.

    Class stores point data separated in data buffers. Every data record is called a property,
    and by default, only a single property exists - PointCloud::POSITIONS.
    User can specify custom properties which will be assigned to all points in the cloud.
  */
  class COGS_API PointCloud
  {
  public:
    //! A predicate over points and normals. A function that returns true or false.
    using PointNormalPredicate = std::function<bool(const glm::vec3 &, const glm::vec3 &)>;

    //! Common identifier for point positions.
    static const cogs::PointCloudProperty::Key POSITIONS;
    //! Common identifier for point normals.
    static const cogs::PointCloudProperty::Key NORMALS;
    //! Common identifier for point colors.
    static const cogs::PointCloudProperty::Key COLORS;
    //! Common identifier for point texture coordinates.
    static const cogs::PointCloudProperty::Key UVS;
    //! Common identifier for point intensities.
    static const cogs::PointCloudProperty::Key INTENSITIES;

    //! Creates a cloud with no points.
    PointCloud();
    //! Destroys cloud and frees all property data.
    virtual ~PointCloud();

    //! Make a deep copy of the source PointCloud.
    PointCloud(const PointCloud &source);
    //! Make a deep copy of the source PointCloud.
    PointCloud &operator=(const PointCloud &source);
    //! Move-construct PointCloud.
    PointCloud(PointCloud &&) noexcept = default;
    //! Move-construct PointCloud.
    PointCloud &operator=(PointCloud &&) noexcept = default;

    //! Imports point cloud from a file.
    virtual bool Import(const std::string &filename);
    //! Exports point clouds to a file.
    virtual bool Export(const std::string &filename) const;

    //! Resizes point count to the new value without initialization of data of newly created points.
    virtual bool Resize(uint32_t new_size);
    //! Returns number of points currently stored in the cloud.
    [[nodiscard]] virtual uint32_t GetSize() const;
    //! Changes capacity of cloud. This method is not adding any points.
    virtual void Reserve(uint32_t new_capacity);
    //! Returns how much points can be added with currently reserved memory.
    [[nodiscard]] uint32_t GetCapacity() const;
    //! Frees spare memory so that new capacity exactly matches size.
    virtual void ShrinkToFit();
    //! Removes all points from cloud.
    virtual void Clear();

    /*!
      \brief
        Removes points with specific indices from cloud.

        Every chunk of points that should be erased, is replaced with the points from the back
        of cloud. This ensures minimal copy operations.
      \note
        Method changes point ordering.
        Memory for erased points is not released, you should call ShrinkToFit afterwards,
        to free excess memory.
      \param indices_to_erase
        Indices of points to erase.
      \param replacement_map
        Optional output parameter - vector representing the mapping old_index->new_index.
    */
    virtual bool Erase(std::vector<uint32_t> indices_to_erase, std::vector<int> *replacement_map = nullptr);

    /*!
      \brief
        Removes all points from cloud that satisfy a specified condition.

        Every chunk of points that should be erased, is replaced with the points from the back
        of cloud. This ensures minimal copy operations.
      \note
        Method changes point ordering.
        Memory for erased points is not released, you should call ShrinkToFit afterwards,
        to free excess memory.
      \param Predicate
        The erase condition. A point is removed from the point cloud if it returns true.
      \param replacement_map
        Optional output parameter - vector representing the mapping old_index->new_index.
    */
    virtual bool Erase(const PointNormalPredicate &Predicate, std::vector<int> *replacement_map = nullptr);

    /*!
      \brief
        Increments size of this by the size of pc and copies property data available in both.
      \note
        Properties not available in this will not be copied.
        To add also properties not currently available in this,
        use PointCloud::ClonePropertiesOf before calling this function.
    */
    virtual bool Append(const PointCloud &pc);

    /*!
      \brief
        Returns pointer to position data.
      \note
        Equivalent to PointCloud::GetData<glm::vec3>(PointCloud::POSITIONS);
    */
    [[nodiscard]] glm::vec3 *GetPositions();

    /*!
      \brief
        Returns pointer to position data.
      \note
        Equivalent to PointCloud::GetData<glm::vec3>(PointCloud::POSITIONS);
    */
    [[nodiscard]] const glm::vec3 *GetPositions() const;

    /*!
      \brief
        Checks whether normal property exists.
      \note
        Equivalent to PointCloud::HasProperty(PointCloud::NORMALS);
    */
    [[nodiscard]] bool HasNormals() const;

    /*!
      \brief
        When normal property exists, returns the pointer to data, nullptr otherwise.
      \note
        Equivalent to PointCloud::GetData<glm::vec3>(PointCloud::NORMALS);
    */
    [[nodiscard]] glm::vec3 *GetNormals();

    /*!
      \brief
        When normal property exists, returns the pointer to data, nullptr otherwise.
      \note
        Equivalent to PointCloud::GetData<glm::vec3>(PointCloud::NORMALS);
    */
    [[nodiscard]] const glm::vec3 *GetNormals() const;

    /*!
      \brief
        Creates PointCloud::NORMALS property buffer if it was not added already.
      \note
        Do not add this property using PointCloud:AddProperty method.
    */
    const PointCloudProperty &AddNormals();

    /*!
      \brief
        Checks whether color property exists.
      \note
        Equivalent to PointCloud::HasProperty(PointCloud::COLORS);
    */
    [[nodiscard]] bool HasColors() const;

    /*!
      \brief
        When color property exists, returns the pointer to data, nullptr otherwise.
      \note
        Equivalent to PointCloud::GetData<COGS::Color3f>(PointCloud::COLORS);
    */
    [[nodiscard]] struct Color3f *GetColors();

    /*!
      \brief
      When color property exists, returns the pointer to data, nullptr otherwise.
      \note
      Equivalent to PointCloud::GetData<COGS::Color3f>(PointCloud::COLORS);
    */
    [[nodiscard]] const struct Color3f *GetColors() const;

    /*!
      \brief
        Creates PointCloud::COLORS property buffer if it was not added already.
      \note
        Do not add this property using PointCloud:AddProperty method.
    */
    const PointCloudProperty &AddColors ();

    /*!
      \brief
        Checks whether intensity property exists.
      \note
        Equivalent to PointCloud::HasProperty(PointCloud::INTENSITIES);
    */
    [[nodiscard]] bool HasIntensities() const;

    /*!
      \brief
        When intensity property exists, returns the pointer to data, nullptr otherwise.
      \note
        Equivalent to PointCloud::GetData<float>(PointCloud::INTENSITIES);
    */
    [[nodiscard]] float *GetIntensities();

    /*!
      \brief
        When intensity property exists, returns the pointer to data, nullptr otherwise.
      \note
        Equivalent to PointCloud::GetData<float>(PointCloud::INTENSITIES);
    */
    [[nodiscard]] const float *GetIntensities() const;

    /*!
      \brief
        Creates PointCloud::INTENSITIES property buffer if it was not added already.
      \note
        Do not add this property using PointCloud:AddProperty method.
    */
    const PointCloudProperty &AddIntensities();

    //! Returns all available properties.
    [[nodiscard]] const std::vector<PointCloudProperty> &GetProperties() const;

    /*!
      \brief
        Creates new property buffer.
      \param key
         Property identifier. If it already exists, does nothing and returns existing property.
      \param type
        Specific type of data in buffer.
      \return
        Newly created property.
    */
    const PointCloudProperty &AddProperty(const PointCloudProperty::Key &key, DataType type);

    /*!
      \brief
        Creates new property buffer.
      \param key
         Property identifier. If it already exists, does nothing and returns existing property.
      \param bytes_per_point
        Number of bytes reserved for each point.
      \return
        Newly created property.
    */
    const PointCloudProperty &AddProperty(const PointCloudProperty::Key &key, size_t bytes_per_point);
    //! Remove a single property by key..
    void RemoveProperty(const PointCloudProperty::Key &key);
    //! Adds all properties, which are not already present in this.
    void ClonePropertiesOf(const PointCloud &pc);
    //! Checks whether a specific property exists.
    [[nodiscard]] bool HasProperty(const PointCloudProperty::Key &key) const;
    //! Returns property with specified key if it exists, std::nullopt otherwise.
    [[nodiscard]] std::optional<PointCloudProperty> GetProperty(const PointCloudProperty::Key &key);
    //! Returns property with specified key if it exists, std::nullopt otherwise.
    [[nodiscard]] std::optional<const PointCloudProperty> GetProperty(const PointCloudProperty::Key &key) const;

    //! When property exists, returns the pointer to data, nullptr otherwise.
    [[nodiscard]] virtual void *GetVoidData(const PointCloudProperty::Key &key);
    //! When property exists, returns the pointer to data, nullptr otherwise.
    [[nodiscard]] const void *GetVoidData(const PointCloudProperty::Key &key) const;

    //! When property exists, returns the pointer to data of a template type, nullptr otherwise.
    template <typename T> [[nodiscard]] T *GetData(const PointCloudProperty::Key &key);
    //! When property exists, returns the pointer to data of a template type, nullptr otherwise.
    template <typename T> [[nodiscard]] const T *GetData(const PointCloudProperty::Key &key) const;

    /*!
      \brief Transforms point positions and normals.
      \param transformation   Transformation matrix applied on every point and camera parameter.
      \param resulting_space  Resulting point cloud space after the transformation is applied.
    */
    virtual void Transform(
      const glm::mat4 &transformation,
      const std::optional<utils::SpaceDefinition> &resulting_space = std::nullopt);

    //! Returns true, if there is a space defined for this structure.
    bool HasSpace() const;
    //! Returns current space definition, if there is one.
    const std::optional<utils::SpaceDefinition> &GetSpace() const;
    //! Returns string representation of current space definition. Returns "N/A" otherwise.
    std::string GetSpaceId() const;
    //! Assigns a new space definition to the structure, overwriting the previous one.
    void SetSpace(const std::optional<utils::SpaceDefinition> &new_space);
    //! Transforms the structure to the new space. Fails, if the current space is not defined.
    bool TransformToSpace(const utils::SpaceDefinition &new_space);

  protected:

    //! A command for copying points.
    struct CopyCommand
    {
      uint32_t source; //!< Index of the first point that should be copied.
      uint32_t target; //!< Index of the first point that should be replaced.
      uint32_t length; //!< Number of sequential points to copy.
    };

    //! Make a deep copy of the source PointCloud.
    void MakeCloneOf(const PointCloud &source);
    //! Copies chunks of points according to copy commands.
    virtual void ExecuteCopyCommands(const std::vector<CopyCommand> &copy_info);
    //! Decreases cloud size by the specified number of points.
    virtual void TruncateSize(size_t delta_size);

  private:

    //! Group of points in a sequence.
    struct Chunk
    {
      uint32_t first; //!< First point belonging to the chunk.
      uint32_t last;  //!< Last point belonging to the chunk.
      Chunk(uint32_t first, uint32_t last);
      //! Test whether first <= last.
      [[nodiscard]] bool IsValid() const;
      //! Returns number of points contained in the chunk.
      [[nodiscard]] uint32_t GetSize() const;
    };

    uint32_t capacity_;
    uint32_t size_;
    std::vector<PointCloudProperty> properties_;
    std::unordered_map<PointCloudProperty::Key, size_t> property_map_;
    std::optional<utils::SpaceDefinition> space_definition_;

    //! Creates new property record without initialization.
    PointCloudProperty &AddProperty(
      const PointCloudProperty::Key &key,
      const std::variant<DataType, size_t> type_or_size);
    //! Converts indices to chunks. Sequential indices form a single chunk in the output.
    [[nodiscard]] std::vector<Chunk> IndicesToChunks(const std::vector<uint32_t> &indices) const;
    //! Creates copy commands to erase specified chunks.
    [[nodiscard]] std::vector<CopyCommand> CreateEraseCopyCommands(std::vector<Chunk> chunks_to_erases) const;
  };



  template <typename T>
  const T *cogs::PointCloud::GetData(const PointCloudProperty::Key &key) const
  {
    return reinterpret_cast<const T *>(GetVoidData(key));
  }

  template <typename T>
  T *cogs::PointCloud::GetData(const PointCloudProperty::Key &key)
  {
    return reinterpret_cast<T *>(GetVoidData(key));
  }

  [[nodiscard]] COGS_API geom::Aabb3 GetPointCloudAabb(const PointCloud &cloud);
  COGS_API void ErasePointsOutsideAabb(const geom::Aabb3 &aabb, PointCloud &cloud);

}


#endif /* !COGS_POINT_CLOUD_H */