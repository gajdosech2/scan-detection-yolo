/*
  Copyright (C) Skeletex Research, s.r.o. - All Rights Reserved
  Unauthorized copying of this file, via any medium is strictly prohibited
  Proprietary and confidential
*/
#ifndef COGS_DATA_BLOCK_IMPORTER_H
#define COGS_DATA_BLOCK_IMPORTER_H
#include <unordered_map>
#include <vector>
#include <memory>

#include <COGS/io/DataBlockManager.h>



namespace cogs // forward declarations
{
  class PointCloud;
  class Scan;
  struct Mesh;
}



namespace cogs
{
  namespace io
  {
    /*!
      \brief Enables reading of cogs structures into files.

      When file is open, only header is fetched, containing information
      about data available in file and it counts. When user gets specific object,
      it is imported directly from file. When file is closed, no data can be obtained.

      By default, exporter supports only predefined data blocks, but can be altered
      to support also custom data blocks, when user-defined DataBlockManager
      is provided during class construction.

      For more information about cogs file io system, see page \ref cogs-file-format.
    */
    class COGS_API DataBlockImporter
    {
    public:

      //! Creates importer with default DataBlockManager object.
      explicit DataBlockImporter();

      //! Creates importer with custom DataBlockManager object.
      DataBlockImporter(const std::shared_ptr<DataBlockManager> &datablock_manager);

      DataBlockImporter(const DataBlockImporter &) = delete;
      DataBlockImporter &operator=(const DataBlockImporter &) = delete;
      DataBlockImporter(const DataBlockImporter &&) = delete;
      DataBlockImporter &operator=(const DataBlockImporter &&) = delete;

      //! Opens file for reading and fetches file header information.
      bool OpenFile(const std::string &filename);

      //! Closes currently opened file, disabling getters.
      void CloseFile();

      //! Checks if a file is currently open.
      [[nodiscard]] bool IsFileOpen() const;

      //! Returns number of available all point cloud objects.
      [[nodiscard]] size_t GetPointCloudCount() const;

      //! Loads object with specified index from file. Returns success.
      bool ReadPointCloud(cogs::PointCloud &out_cloud, DataBlockIndex id = 0);

      //! Returns number of available point cloud objects with scan information.
      [[nodiscard]] size_t GetScanCount() const;

      //! Loads object with specified index from file. Returns success.
      bool ReadScan(cogs::Scan &out_scan, DataBlockIndex id = 0);

      //! Returns number of available mesh objects.
      [[nodiscard]] size_t GetMeshCount() const;

      //! Loads object with specified index from file. Returns success.
      bool ReadMesh(cogs::Mesh &out_mesh, DataBlockIndex id = 0);

    private:

      struct DataBlockInfo
      {
        //! Exporter version of data block in the file.
        uint8_t version;
        //! Position of data block in the file.
        std::streampos position;
        //! Pointer to data block object.
        std::shared_ptr<DataBlock> block;
        //! Casts data block to specified type.
        template <typename T>
        std::shared_ptr<T> CastBlock() const
        {
          return std::static_pointer_cast<T>(block);
        }
      };

      std::shared_ptr<DataBlockManager> datablock_manager_;
      std::ifstream file_;
      uint8_t file_version_;
      std::unordered_map<DataBlockType, std::vector<DataBlockInfo>> navigation_;

      //! Returns number of available data blocks of specified type.
      [[nodiscard]] size_t GetDatablockCount(const DataBlockType &type) const;

      //! Returns data block of specified type and index. Returns null when no such block exists.
      std::optional<DataBlockInfo> GoToDatablock(const DataBlockType &type, DataBlockIndex id = 0);

      //! Imports header information. Returns true if header is correct and version supported.
      bool ImportHeader(std::istream &in_s);

      //! Imports file navigation and stores it.
      bool ImportNavigation(std::istream &in_s);
    };

  }
}

#endif /* !COGS_DATA_BLOCK_IMPORTER_H */