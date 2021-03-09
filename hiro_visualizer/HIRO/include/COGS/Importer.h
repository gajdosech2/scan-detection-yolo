/*
  Copyright (C) Skeletex Research, s.r.o. - All Rights Reserved
  Unauthorized copying of this file, via any medium is strictly prohibited
  Proprietary and confidential
*/
#ifndef COGS_IMPORTER_H
#define COGS_IMPORTER_H
#include <vector>
#include <string>
#include <memory>
#include <COGS/API.h>



namespace cogs // forward declarations
{
  class Armature;
  class Skeleton;
  struct SkeletonAction;
  struct Mesh;
  class PointCloud;
  class Scan;
}



namespace cogs
{
  // #TODO Update tested file formats.
  /*!
    \brief Universal file importer for COGS structures.

    Supports all COGS file extensions which can be found in \ref cogs-file-format-extensions.

    Internally uses Assimp library which supports common data formats found in
    http://assimp.sourceforge.net/main_features_formats.html. However,
    compatibility is not guaranteed for all file formats.

    Assimp import was tested on the following file formats:
    - Wavefront (.obj)
    - Autodesk Filmbox (.fbx)
    - COLLADA (.dae)
    - Biovision Hierarchy (.bvh)
  */
  class COGS_API Importer
  {
  public:

    explicit Importer();
    explicit Importer(const std::string &filename);
    Importer(const Importer &other) = delete;
    Importer(const Importer &&other) = delete;
    Importer &operator=(const Importer &other) = delete;
    Importer &operator=(const Importer &&other) = delete;
    ~Importer();

    //! Loads the file. When the file is COGS file, it remains open. Returns success.
    bool LoadFile(const std::string &filename);
    //! When loaded file was in COGS file format, closes it. Otherwise, does nothing.
    void CloseFile();

    //! Returns number of point clouds contained in a loaded file.
    [[nodiscard]] size_t GetPointCloudCount() const;
    /*!
      \brief Requests point cloud structure from the loaded file.
      \param out_cloud Object, to which should data be loaded.
      \param id Index of object in the file when there are more of the same type.
      \returns Whether load finished successfully, and output is valid.
    */
    bool GetPointCloud(cogs::PointCloud &out_cloud, size_t id = 0) const;

    //! Returns number of scans contained in a loaded file.
    [[nodiscard]] size_t GetScanCount() const;
    /*!
      \brief Requests scan structure from the loaded file.
      \param out_scan Object, to which should data be loaded.
      \param id Index of object in the file when there are more of the same type.
      \returns Whether load finished successfully, and output is valid.
    */
    bool GetScan(cogs::Scan &out_scan, size_t id = 0) const;

    //! Returns number of meshes contained in a loaded file.
    [[nodiscard]] size_t GetMeshCount() const;
    /*!
      \brief Requests mesh structure from the loaded file.
      \param out_meshmodel Object, to which should data be loaded.
      \param id Index of object in the file when there are more of the same type.
      \returns Whether load finished successfully, and output is valid.
    */
    bool GetMesh(cogs::Mesh &out_meshmodel, size_t id = 0) const;
    //! Returns all meshes from the loaded file.
    std::vector<cogs::Mesh> GetAllMeshes() const;

    //! Returns names of all loaded meshes. Not supported by cogs files.
    [[nodiscard]] std::vector<std::string> GetMeshNames() const;
    /*!
      \brief Finds and requests mesh structure from the loaded file.
      \param out_meshmodel Object, to which should data be loaded.
      \param name Name identifier of an object.
      \returns Whether load finished successfully, and output is valid.
    */
    bool GetMeshByName(const std::string &name, cogs::Mesh &out_meshmodel) const;

    //! Returns number of skeletons contained in a loaded file.
    [[nodiscard]] uint32_t GetSkeletonCount() const;
    /*!
       \brief Requests skeleton structure from the loaded file.
       \param out_skeleton Object, to which should data be loaded.
       \param id Index of object in the file when there are more of the same type.
       \returns Whether load finished successfully, and output is valid.
    */
    bool GetSkeleton(cogs::Skeleton &out_skeleton, size_t id = 0) const;

    //! Returns names of all loaded skeletons. Not supported by cogs files.
    [[nodiscard]] std::vector<std::string> GetSkeletonNames() const;
    /*!
       \brief Finds and requests mesh structure from the loaded file.
       \param out_skeleton Object, to which should data be loaded.
       \param name Name identifier of an object to find.
       \returns Whether load finished successfully, and output is valid.
    */
    bool GetSkeletonByName(const std::string &name, cogs::Skeleton &out_skeleton) const;

    /*!
       \brief Requests armature structure from the loaded file.
       \param out_armature Object, to which should data be loaded.
       \param id Index of object in the file when there are more of the same type.
       \returns Whether load finished successfully, and output is valid.
    */
    bool GetArmature(cogs::Armature &out_armature) const;

    /*!
       \brief Requests all skeleton actions from the loaded file.
       \param out_actions Array in which output should be stored.
       \returns Whether load finished successfully, and output is valid.
    */
    bool GetAllSkeletonActions(std::vector<cogs::SkeletonAction> &out_actions) const;
    /*!
       \brief Requests all skeleton actions from the loaded file, compatible with specific skeleton.
       \param skeleton_name Name of skeleton object, actions should be compatible with.
       \param out_actions Array in which output should be stored.
       \returns Whether load finished successfully, and output is valid.
    */
    bool GetAllSkeletonActions(const std::string &skeleton_name, std::vector<cogs::SkeletonAction> &out_actions) const;
    /*!
       \brief Requests a skeleton action from the loaded file, compatible with specific skeleton.
       \param skeleton_name Name of skeleton object, actions should be compatible with.
       \param action_name Name of the requested action.
       \param out_actions Object, to which should data be loaded.
       \returns Whether load finished successfully, and output is valid.
    */
    bool GetSkeletonActionByName(const std::string &skeleton_name, const std::string &action_name, cogs::SkeletonAction &out_action) const;

  private:
    struct Impl;
    Impl *m = nullptr;
  };

}
#endif /* !COGS_IMPORTER_H */