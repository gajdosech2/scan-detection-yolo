#ifndef COGS_DATA_BLOCK_H
#define COGS_DATA_BLOCK_H
#include <fstream>
#include <memory>
#include <limits>

namespace cogs
{
  //! Definitions for cogs file format.
  namespace io
  {
    //! Defines position index of the data block in a file.
    using DataBlockIndex = size_t;

    const static DataBlockIndex INVALID_DATABLOCK_INDEX {std::numeric_limits<size_t>::max()};

    /*!
      \brief
        Identifies data block instances.
        Each class derived from cogs::io::DataBlockType should have unique type identifier.
    */
    using DataBlockType = std::string;

    //! Definition of required interface for derived data blocks.
    class DataBlock
    {
    public:

      const DataBlockIndex INDEX;

      explicit DataBlock(DataBlockIndex index) : INDEX(index) {};

      //! Returns unique identifier of class. Usually class name.
      [[nodiscard]] virtual DataBlockType GetType() const = 0;

      //! Version of export function.
      [[nodiscard]] virtual uint8_t GetExportVersion() const = 0;

      //! Checks if specified version is supported by import function.
      [[nodiscard]] virtual bool IsImportVersionSupported(uint8_t version) const = 0;

      //! Executes import form specified stream.
      virtual bool Import(std::istream &in_s, uint8_t version) = 0;

      //! Executes export to specified stream.
      virtual bool Export(std::ostream &out_s) = 0;
    };

    //! Factory for data block type.
    struct DataBlockFactory
    {
    public:
      //! Creates new instance of data block type.
      virtual std::unique_ptr<DataBlock> Create(DataBlockIndex index) const = 0;
    };

  }
}
#endif /* !COGS_DATA_BLOCK_H */