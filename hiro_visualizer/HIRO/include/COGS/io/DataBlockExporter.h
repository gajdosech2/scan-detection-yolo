/*
  Copyright (C) Skeletex Research, s.r.o. - All Rights Reserved
  Unauthorized copying of this file, via any medium is strictly prohibited
  Proprietary and confidential
*/
#ifndef COGS_DATA_BLOCK_EXPORTER_H
#define COGS_DATA_BLOCK_EXPORTER_H
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
      \brief Enables writing or cogs structures into files.

      Objects and data blocks for export are stored in the export list,
      and have to be valid until file is saved. Each object can be represented by one
      or multiple data blocks.

      By default, exporter supports only predefined data blocks, but can be altered
      to support also custom data blocks, when user-defined DataBlockManager
      is provided during class construction.

      For more information about cogs file io system, see page \ref cogs-file-format.
    */
    class COGS_API DataBlockExporter
    {
    public:

      //! Current exporter version.
      static uint8_t VERSION;

      //! Creates exporter with default DataBlockManager object.
      explicit DataBlockExporter();

      //! Creates exporter with custom DataBlockManager object.
      DataBlockExporter(const std::shared_ptr<DataBlockManager> &datablock_manager);

      virtual ~DataBlockExporter();
      DataBlockExporter(const DataBlockExporter &) = delete;
      DataBlockExporter &operator=(const DataBlockExporter &) = delete;
      DataBlockExporter(const DataBlockExporter &&) = delete;
      DataBlockExporter &operator=(const DataBlockExporter &&) = delete;

      /*!
        \brief Opens file into which the data blocks can be written.
        \param filename Name of the file. When extension is not provided, sets to "cogs".
        \param overwrite_existing Set to true is you wish to rewrite the file that already exists.
        \returns True, if the file was successfully opened and can be used for writing.
      */
      [[nodiscard]] bool OpenFile(const std::string &filename, bool overwrite_existing = false);

      //! Finishes and closes currently opened file, disabling writers.
      void CloseFile();

      /*!
        \brief Adds the object to the export list.
        \param object_ref Reference to object. Must be valid until saved.
        \return Index of data block for added object type.
      */
      [[nodiscard]] DataBlockIndex WritePointCloud(const cogs::PointCloud &cloud);

      /*!
        \brief Adds the object to the export list.
        \param object_ref Reference to object. Must be valid until saved.
        \return Index of data block for added object type.
      */
      [[nodiscard]] DataBlockIndex WriteScan(const cogs::Scan &scan);

      /*!
        \brief Adds the object to the export list.
        \param object_ref Reference to object. Must be valid until saved.
        \return Index of data block for added object type.
      */
      [[nodiscard]] DataBlockIndex WriteMesh(const cogs::Mesh &mesh);

    private:

      struct DataBlockInfo
      {
        //! Type of data block that was exported.
        DataBlockType type;
        //! Export version of data block in the file.
        uint8_t version;
        //! Position of data block in the file.
        uint64_t position;
      };

      std::ofstream file_;
      std::streampos nav_reference_position_;
      std::vector<DataBlockInfo> navigation_;
      std::shared_ptr<DataBlockManager> datablock_manager_;
      std::unordered_map<DataBlockType, DataBlockIndex> index_counter_;

      /*!
        \brief Creates and adds custom data block to the export list.
        \param type Type identifier of data block to create.
        \return Pointer to data block and its file index.
      */
      [[nodiscard]] std::unique_ptr<cogs::io::DataBlock> WriteCustom(const DataBlockType &type);

      /*!
        \brief Creates and adds custom data block to the export list.
        \param type Type identifier of data block to create.
        \return Pointer to data block, static casted to the template type T, and its file index.
      */
      template <typename T>
      std::unique_ptr<T> WriteCustom(const DataBlockType &type)
      {
        auto dtb_ptr = WriteCustom(type);
        return std::unique_ptr<T> { static_cast<T *>(dtb_ptr.release()) };
      }

      //! Exports header information.
      void ExportHeader();

      //! Exports file navigation.
      void ExportNavigation();

      //! Exports defines data block and stores its info in navigation.
      [[nodiscard]] bool ExportDatablock(DataBlock &dtb);
    };

  }
}

#endif /* !COGS_DATA_BLOCK_EXPORTER_H */