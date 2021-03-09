/*
  Copyright (C) Skeletex Research, s.r.o. - All Rights Reserved
  Unauthorized copying of this file, via any medium is strictly prohibited
  Proprietary and confidential
*/
#ifndef HIRO_DRAW_VISUAL_CAMERA_CONTROLLER_H
#define HIRO_DRAW_VISUAL_CAMERA_CONTROLLER_H
#include <GLW/WindowEventObserver.h>
#include <HIRO_DRAW/Scene.h>



namespace hiro::draw
{

  //! Defines camera manipulation behavior.
  enum class CameraMode
  {
    move_free   = 0,  //!< Cinematic mode. Camera can be moved freely.
    orbit_free  = 1,  //!< Camera orbits defined 3D point.
    orbit_x     = 2,  //!< ORBIT_FREE, with up vector fixed to positive X.
    orbit_x_inv = 3,  //!< ORBIT_FREE, with up vector fixed to negative X.
    orbit_y     = 4,  //!< ORBIT_FREE, with up vector fixed to positive Y.
    orbit_y_inv = 5,  //!< ORBIT_FREE, with up vector fixed to negative Y.
    orbit_z     = 6,  //!< ORBIT_FREE, with up vector fixed to positive Z.
    orbit_z_inv = 7   //!< ORBIT_FREE, with up vector fixed to negative Z.
  };

  /*!
      \brief Provides an automatic interface to camera manipulation by runtime user interaction.

      For each Scene added to CameraController, an interaction is enabled.
      Cameras can be grouped in order to control multiple using a single action.

      A method Update needs to be called every frame in order to function properly.
  */
  class HIRO_DRAW_API VisualCameraController : public glw::WindowEventObserver
  {
  public:
    /*!
      \brief Callback function which is called each time a scene camera changes it's state.

      First parameter defines an index of the scene for which the change happened.
    */
    using OnCameraChangeCallback = std::function<void(uint32_t)>;

    //! Creates object with no scene to manipulate with.
    VisualCameraController();

    ~VisualCameraController();

    //! Set scenes, whose internal cameras are to be controlled by mouse.
    void SetScenes(const std::vector<hiro::draw::PScene> &scenes);

    //! Add scene to the list of scenes, whose internal cameras are to be controlled by mouse.
    void AddScene(const hiro::draw::PScene &scene);

    //! Update all controlled cameras once a render cycle. Obligatory for smoothened and animated cameras.
    void Update(double delta_time);

    //! Changes behavioral mode for a camera of specified scene.
    void SetCameraMode(uint32_t scene_id, hiro::draw::CameraMode mode);

    //! Returns behavioral mode for a camera of specified scene.
    hiro::draw::CameraMode GetCameraMode(uint32_t scene_id) const;

    /*!
      \brief
        Sets up point of interest for camera, which will automatically look at the point.

        If camera mode is set to one of orbital modes, camera will orbit the point.
    */
    void SetCameraPoi(uint32_t scene_id, const glm::vec3 &poi);

    //! Returns point of interest for camera.
    glm::vec3 GetCameraPoi(uint32_t scene_id) const;

    //! Sets up group of scene ids, whose cameras are grouped and behave simultaneously.
    void SetCameraGroup(const std::set<uint32_t> &scene_ids);

    //! Returns group of scene ids, whose cameras are grouped and behave simultaneously.
    const std::set<uint32_t> &GetCameraGroup() const;

    /*!
      \brief All cameras in group with source scene are updated by a camera of source scene.

      This method needs to be called when camera of source scene is changed manually, in order to work correctly.
    */
    void UpdateGroupedCameras(const uint32_t source_scene_id) const;

    //! Sets up optional callback function, which will be called each time a scene camera changes it's state.
    void SubscribeEventCameraChanged(const hiro::draw::VisualCameraController::OnCameraChangeCallback &func);

    void SetCameraSensitivity(float sens);

    float GetCameraSensitivity();

  protected:
    virtual void OnMouseMove(double xpos, double ypos) override;
    virtual void OnMouseDown(int button, int mods) override;
    virtual void OnMouseUp(int button, int mods) override;

    virtual void NotifyOnCameraChange(uint32_t scene_id);

    virtual void OnMouseWheel(double xoffset, double yoffset) override;
    virtual void OnKeyDown(int key, int mods, bool is_repeat) override;
    virtual void OnKeyUp(int key, int mods) override;

  private:
    struct Impl;
    std::unique_ptr<hiro::draw::VisualCameraController::Impl> m;

    // Returns index of scene over whose viewport is mouse cursor. Returns -1 if cursor is not over any scene viewport.
    int32_t GetSceneUnderMousePos();
  };

}

#endif /* !HIRO_DRAW_VISUAL_CAMERA_CONTROLLER_H */