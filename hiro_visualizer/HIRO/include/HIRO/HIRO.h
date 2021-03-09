/*
  Copyright (C) Skeletex Research, s.r.o. - All Rights Reserved
  Unauthorized copying of this file, via any medium is strictly prohibited
  Proprietary and confidential
*/
#ifndef HIRO_HIRO_H
#define HIRO_HIRO_H
#include <memory>
#include <Utils/Version.h>
#include <HIRO/Resource.h>
#include <HIRO/Debugger.h>

#ifdef _WIN32
#include <windows.h>
#endif


namespace hiro
{

  /*!
    \brief Information about currently active Resource objects.

    Active Resource objects are the ones that were used to
    create at least one Gadget and it still exists.
  */
  struct ActiveResourceInfo
  {
    //! Pointer to an active data resource.
    std::shared_ptr<hiro::Resource> resource;
    //! Index of viewarea where the resource is active.
    uint32_t viewarea;
    //! Defines whether the resource is selected. If false, the resource is pinned.
    bool is_selected;
  };

  using FileDropCallback = std::function<void(const std::vector<std::string> &)>;
  using KeyCallback = std::function<void(const hiro::Key &, const hiro::ModKeys &)>;

  //! Returns current library version.
  HIRO_API utils::Version GetVersion();

  /*!
    \brief
      Sets directory where hiro stores temporal cache data.
    \warning
      Needs to be called before initialization using hiro::Initialize().
  */
  HIRO_API void SetIntermediateDirectory(const std::string &dir);

  /*!
    \brief
      Sets directory where are sub-folders "resources" and "shaders" present.
    \warning
      Needs to be called before initialization using hiro::Initialize().
  */
  HIRO_API void SetAssetDirectory(const std::string &dir);

  //! Initializes the library. From this moment the library can be fully used.
  HIRO_API bool Initialize();

  /*!
    \brief
      Initializes the library with custom look visuals of application on startup.
    \note
      Not available in educational version of HIRO library.
  */
  HIRO_API bool Initialize(const std::string &custom_look);

  //! Terminates the library. Call to release all HIRO related data.
  HIRO_API void Terminate();

  //! Check whether hiro window has not been closed.
  HIRO_API bool IsOpen();

  /*!
    \brief
      Updates window and redraws if required.

    Ensure that this function is called regularly in your application.
    If not, it may cause window freezing and lag.
  */
  HIRO_API void Update();

  //! Add specified resource to the list of available resources.
  HIRO_API void AddResource(const hiro::PResource &resource);

  //! Remove all resources from the list of available resources.
  HIRO_API void RemoveAllResources();

  //! Remove all resources whose name includes prefix from the list of available resources
  void RemoveResourcesWithPrefix(const std::string &prefix);

  /*!
    \brief Returns information about all resources currently active in context.

    Active Resource objects are the ones that were used to
    create at least one Gadget ant it still exists.
  */
  HIRO_API std::vector<hiro::ActiveResourceInfo> GetActiveResources();

  /*!
    \brief Returns handle to visual debugger.

    The visual debugger provides visualization of debug objects, useful fo visual feedback.
    When the library is not initialized yet, this function throws std::runtime_error.
  */
  HIRO_API hiro::Debugger &Debug();

  //! Sets a unique function called when files are dropped onto an active HIRO window.
  HIRO_API void SetFileDropCallback(const FileDropCallback &);

  //! Sets a unique function called when a key is pressed in an active HIRO window.
  HIRO_API void SetKeyDownCallback(const KeyCallback &);

  //! Sets a unique function called when a key is released in an active HIRO window.
  HIRO_API void SetKeyUpCallback(const KeyCallback &);

  //! Returns axes visibility state in the viewarea with the given id.
  HIRO_API bool IsAxesVisible(uint8_t viewarea_id);

  //! Sets axes visibility in the viewarea with the given id.
  HIRO_API void SetAxesVisible(uint8_t viewarea_id, bool visible);

#ifdef _WIN32
  /*!
    \brief
      Returns WIN API pointer to owned window.
    \note
      Not available in educational version of HIRO library.
  */
  HIRO_API HWND GetWindowHandle();
#endif
}

#endif /* !HIRO_HIRO_H */