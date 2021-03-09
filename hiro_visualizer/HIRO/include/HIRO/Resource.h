/*
  Copyright (C) Skeletex Research, s.r.o. - All Rights Reserved
  Unauthorized copying of this file, via any medium is strictly prohibited
  Proprietary and confidential
*/
#ifndef HIRO_RESOURCE_H
#define HIRO_RESOURCE_H
#include <HIRO/Gadget.h>



namespace hiro
{
  /*!
      \brief Data storage and application interface for every module.

      Each custom module implementation should override Resource and create a custom class.
      The custom class should specify type of Gadget object to create. The custom Resource
      objects are is created by user application, and registered in HIRO as shared pointer
      via hiro::AddResource function.
  */
  class HIRO_API Resource
  {
  public:
    const hiro::ResourceId ID; //!< Unique identifier of this object.

    //! Constructor that assign specified ResourceId.
    explicit Resource(const hiro::ResourceId &id);

    //! Constructor that creates ResourceId from the specified name and category parameters.
    Resource(const std::string &name, const std::string &category);

    //! Override this method to create custom Gadget type objects.
    virtual hiro::PGadget CreateGadget() = 0;

    //! Forces all existing Gadget objects created by this to be destroyed and created again.
    void ResetGadgets();

    /*!
      \brief
        Update method is called by the HIRO engine automatically every frame.
      \param delta_time
        Specifies the number of seconds since the last Update call.
    */
    virtual void Update(float delta_time);

  protected:
    //! Tells the system to render on next update. Effect only when "optimized rendering" enabled.
    void DrawOnNextUpdate() const;

  };

  //! Shared pointer to Resource.
  using PResource = std::shared_ptr<hiro::Resource>;

}
#endif /* !HIRO_RESOURCE_H */