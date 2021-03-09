/*
  Copyright (C) Skeletex Research, s.r.o. - All Rights Reserved
  Unauthorized copying of this file, via any medium is strictly prohibited
  Proprietary and confidential
*/
#ifndef HIRO_CAMERA_H
#define HIRO_CAMERA_H
#include <COGS/Frustum.h>
#include <HIRO_DRAW/Scene.h>
#include <HIRO/API.h>



namespace hiro
{

  /*!
    \brief Denotes view on a scene.

    Camera pose is denoted by two points: camera position and "target" point. While both points can
    be set individually, the forward direction of the camera is always oriented towards the target.

    The camera can rotate in two modes. Free rotation and fixed rotation, denoted by property
    "fixed rotation enabled". When the camera uses fixed rotation, up direction is always aligned
    with fixed rotation axis, that can be also set manually.
  */
  class HIRO_API Camera
  {
  public:

    //! Holds information about camera pose.
    struct HIRO_API Pose
    {
      glm::vec3 target;   //!< Point at which camera looks at.
      glm::vec3 position; //!< Position of a camera.
      glm::vec3 up;       //!< Camera up direction.
      //! Calculates view matrix of current pose.
      glm::mat4 GetViewMatrix() const;
    };

    explicit Camera(hiro::draw::Scene *scene);
    Camera(const hiro::Camera &cp);
    Camera &operator =(const hiro::Camera &cp);
    ~Camera();

    //! Returns the position of the camera.
    glm::vec3 GetPosition() const;

    //! Set position of the camera. The view direction is corrected automatically.
    void SetPosition(const glm::vec3 &camera_position);

    //! Returns point of interest.
    glm::vec3 GetTarget() const;

    //! Changes point of interest. The view direction is corrected automatically.
    void SetTarget(const glm::vec3 &poi);

    //! Returns forward direction.
    glm::vec3 GetForward() const;

    //! Returns right direction.
    glm::vec3 GetRight() const;

    //! Returns up direction.
    glm::vec3 GetUp() const;

    //! Aligns up direction of camera to match the specified vector.
    void AlignUp(const glm::vec3 &up);

    /*!
      \brief
        Modulates distance of camera position to target.
      \param factor
        A factor by which the distance is multiplied.
    */
    void Zoom(float factor);

    //! Checks whether fixed rotation mode is enabled.
    bool IsFixedRotationEnabled() const;

    /*!
      \brief
        Set whether to enable fixed rotation mode. By default disabled.
      \note
        Axis of fixed rotation can be specified using SetFixedRotationAxis function.
    */
    void SetFixedRotationEnabled(bool state);

    //! Returns axis of fixed rotation.
    const glm::vec3 &GetFixedRotationAxis() const;

    /*!
      \brief Sets fixed rotation axis to specified. By default Y axis.

      Used only when fixed rotation enabled using SetFixedRotationEnabled function.
    */
    void SetFixedRotationAxis(const glm::vec3 &axis);

    //! Rotates the camera using mouse movement over screen.
    void ScreenRotate(const glm::vec2 &last_mouse_pos, const glm::vec2 &mouse_pos);

    //! Rotates around view direction, counter-clockwise using mouse movement over screen.
    void ScreenRoll(const glm::vec2 &last_mouse_pos, const glm::vec2 &mouse_pos);

    //! Moves camera left and up relatively using mouse movement over screen.
    void ScreenMove(const glm::vec2 &last_mouse_pos, const glm::vec2 &mouse_pos);

    //! Moves forward using mouse movement over screen.
    void ScreenDolly(const glm::vec2 &last_mouse_pos, const glm::vec2 &mouse_pos);

    //! Sets up callback function, called every time a scene camera changes it's state.
    void SubscribeChange(const std::function<void(void)> &callback);

    //! Sets up camera pose to exactly match the source camera.
    void CopyView(const hiro::Camera &source_camera);

    //! Loads camera pose from stream.
    void ReadFromStream(std::istream &str);

    //! Saves camera pose to stream.
    void WriteToStream(std::ostream &str);

    //! Resets camera pose to an initial state.
    void Reset();

    //! Returns current camera pose.
    hiro::Camera::Pose GetPose();

    //! Sets camera pose.
    void SetPose(const hiro::Camera::Pose &pose);

    //! Computes the camera's view frustum.
    cogs::Frustum ComputeViewFrustum() const;

    //! Returns current view matrix.
    const glm_ext::TransMat4 &GetViewMatrix() const;

  private:
    void CorrectUpVectorIfRequired();
    glm::vec3 MoveInProjectionSpace(
      const glm::vec3 &point,
      const glm::vec2 &proj_move_origin,
      const glm::vec2 &proj_move_end
    );

    struct Impl;
    std::unique_ptr<Impl> m;
  };

  /*!
    \brief Interpolates two camera poses using linear interpolation.
    \param p0 Start pose.
    \param p1 End pose.
    \param t Interpolation factor in range <0,1>, where 0 returns p0 and 1 returns p1.
    \return Interpolated pose.
  */
  hiro::Camera::Pose Interpolate(
    const hiro::Camera::Pose &p0,
    const hiro::Camera::Pose &p1,
    float t
  );

  /*!
    \brief Interpolates camera poses using cubic spline interpolation.
    \param p0 Pose before start pose.
    \param p1 Start pose.
    \param p2 End pose.
    \param p3 Pose after end pose.
    \param t Interpolation factor in range <0,1>.
    \return Interpolated pose.
  */
  hiro::Camera::Pose InterpolateCubic(
    const hiro::Camera::Pose &p0,
    const hiro::Camera::Pose &p1,
    const hiro::Camera::Pose &p2,
    const hiro::Camera::Pose &p3,
    float t
  );

}

#endif /* !HIRO_CAMERA_H */