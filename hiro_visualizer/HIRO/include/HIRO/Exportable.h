#ifndef HIRO_EXPORTABLE_H
#define HIRO_EXPORTABLE_H
#include <iostream>

namespace hiro
{

  //! Object whose state can be written to and read from stream.
  class Exportable
  {
  public:

    /*!
      \brief Helper function for reading version number from input stream.
      \param str Stream to read version number from.
      \param expected_version Version number to compare stream version number to.
      \returns Whether the version in file is equal to the expected_version.
    */
    [[nodiscard]] static bool ReadVersion(
      std::istream &str,
      uint32_t expected_version
    );

    /*!
      \brief Helper function for writing version number to output stream.
      \param str Stream to write version number to.
      \param version Version number to write to stream.
    */
    static void WriteVersion(
      std::ostream &str,
      uint32_t version
    );

    //! Override this method to specify custom data to be loaded.
    virtual bool ReadFromStream(std::istream &str);
    //! Override this method to specify custom data to be stored.
    virtual void WriteToStream(std::ostream &str) const;

    hiro::Exportable &operator >>(std::istream &str);
    hiro::Exportable &operator <<(std::ostream &str);
  };

}
#endif /* !HIRO_EXPORTABLE_H */