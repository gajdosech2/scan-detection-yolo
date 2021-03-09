/*
  Copyright (C) Skeletex Research, s.r.o. - All Rights Reserved
  Unauthorized copying of this file, via any medium is strictly prohibited
  Proprietary and confidential
*/
#ifndef HIRO_GADGET_H
#define HIRO_GADGET_H
#include <HIRO_DRAW/Scene.h>
#include <HIRO_DRAW/TextRenderer.h>
#include <HIRO/Input.h>
#include <HIRO/Camera.h>
#include <HIRO/gui/GuiGenerator.h>



namespace hiro { class Resource; class Viewarea; }



namespace hiro
{

  //! Informational status of an event function.
  enum class EventStatus
  {
    unprocessed,  //!< Event was not processed by other object yet.
    processed,    //!< Event was already processed by other object.
  };



  /*!
    \brief Visual part of module. Provides options for visualization, that do not interfere with data stored in Resource.

    To unlock its powers, derive your custom Gadget and override functionality that you require.
  */
  class HIRO_API Gadget
  {
  public:
    const hiro::ResourceId RESOURCE_ID;
    explicit Gadget(const hiro::Resource *res);
    virtual ~Gadget();

    //! Function invoked right after object creation to set up all properties.
    virtual void Initialize();

    //! Function invoked right before object destruction.
    virtual void Terminate();

    //! Function invoked right after object initialization to define gui.
    virtual void GenerateGui(hiro::GuiGenerator &gui);

    //! Function invoked each time HIRO context is updated.
    virtual void Update(const float time_delta);

    /*!
      \brief  Function invoked when user requests to focus camera at this gadget.
      \param focus_point Point at which the camera should look at.
      \param cam_position Position of the camera.
      \returns When the camera can be set correctly, the method should return true.
    */
    virtual bool FocusCamera(
      glm::vec3 &focus_point,
      glm::vec3 &cam_position
    ) const;

    /*!
      \brief The function invoked after the key press event, triggered by a user.
      \param key Identifier of key that was pressed.
      \param mods Set of modifier keys being held at the time of key press.
      \param status Whether the event was already processed by other object.
      \returns When the event was handled, the function should return EventStatus::processed.
    */
    virtual hiro::EventStatus KeyPressed(
      hiro::Key key,
      const hiro::ModKeys &mods,
      hiro::EventStatus status
    );

    /*!
      \brief The function invoked after the key release event, triggered by a user.
      \param key Identifier of key that was released.
      \param mods Set of modifier keys being held at the time of key release.
      \param status Whether the event was already processed by other object.
      \returns When the event was handled, the function should return EventStatus::processed.
    */
    virtual hiro::EventStatus KeyReleased(
      hiro::Key key,
      const hiro::ModKeys &mods,
      hiro::EventStatus status
    );

    /*!
      \brief The function invoked after the mouse button press event, triggered by a user.
      \param button Identifier of button that was pressed.
      \param mods Set of modifier keys being held at the time of button press.
      \param status Whether the event was already processed by other object.
      \returns When the event was handled, the function should return EventStatus::processed.
    */
    virtual hiro::EventStatus MouseButtonPressed(
      hiro::MouseButton button,
      const hiro::ModKeys &mods,
      hiro::EventStatus status
    );

    /*!
      \brief The function invoked after the mouse button release event, triggered by a user.
      \param button Identifier of button that was released.
      \param mods Set of modifier keys being held at the time of button release.
      \param status Whether the event was already processed by other object.
      \returns When the event was handled, the function should return EventStatus::processed.
    */
    virtual hiro::EventStatus MouseButtonReleased(
      hiro::MouseButton button,
      const hiro::ModKeys &mods,
      hiro::EventStatus status
    );

    /*!
      \brief The function invoked after the mouse wheel was interacted with, triggered by a user.
      \param offset Orientation and intensity of a wheel change.
      \param status Whether the event was already processed by other object.
      \returns When the event was handled, the function should return EventStatus::processed.
    */
    virtual hiro::EventStatus MouseWheel(
      float offset,
      hiro::EventStatus status
    );

    /*!
      \brief The function invoked after the mouse is moved, triggered by a user.
      \param x Horizontal position of a mouse cursor.
      \param y Vertical position of a mouse cursor.
      \param status Whether the event was already processed by other object.
      \returns When the event was handled, the function should return EventStatus::processed.
    */
    virtual hiro::EventStatus MouseMoved(
      float x,
      float y,
      hiro::EventStatus status
    );

    /*!
      \brief The function invoked after the view resolution changes.
      \param width Horizontal pixel resolution of a view.
      \param height Vertical pixel resolution of a view.
      \param status Whether the event was already processed by other object.
      \returns When the event was handled, the function should return EventStatus::processed.
    */
    virtual hiro::EventStatus ViewResized(
      uint32_t width,
      uint32_t height,
      hiro::EventStatus status
    );

    /*!
      \brief Function called before rendering, to define what texts should be printed on screen.
      \param t_renderer Text printer used to define texts to be printed.
    */
    virtual void RenderTexts( hiro::draw::TextRenderer &t_renderer );

    //! Return handle to the camera used to render this.
    hiro::Camera *GetCamera() const;

    /*!
      \brief Insert specified renderer to the list of currently used renderers.
      \param renderer Renderer to add to the rendering system.
      \param style Style used for rendering.
      \param layer Rendering layer used for rendering.
      \return Identifier of currently added renderer.
    */
    virtual int32_t AddRenderer(
      const hiro::draw::PRenderer &renderer,
      const hiro::draw::PStyle &style,
      uint8_t layer = 0u
    ) const;

    /*!
      \brief Remove specified renderer from the list of currently used renderers.
      \param renderer_id Identifier of renderer to be removed.
    */
    virtual void RemoveRenderer(int32_t renderer_id) const;

    //! Returns projection parameters for view where object exists.
    hiro::draw::ProjectionParams GetProjectionParams() const;

    //! Returns pointer to Resource object that was used to create this object.
    template <typename UnitType = Resource>
    const UnitType * GetResource() const { return static_cast<const UnitType *>(resource_); }

#ifdef HIRO_ENABLE_CEGUI
    //! Adds a custom GUI element to the viewport of viewarea. Not available in educational builds.
    [[maybe_unused]] void AddCeguiElement(CEGUI::Element *element);
#endif

    //! Assign Viewarea to this. Not to be called by a user.
    void SetViewarea(hiro::Viewarea *viewarea);

    /*!
      \brief Forces this to save its state.
      \note
        State is saved automatically when changes are made to gui.
        May negatively affect performance when used a lot.
      \returns Whether saving was successful.
    */
    bool SaveState() const;

    //! Set near and far values of the viewarea
    void SetNearFar(float near, float far) const;

  protected:

    //! Loads file stored from previous session. This method calls also ReadFromStream.
    void LoadState();

    /*!
      \brief Helper function for reading version number from input stream.
      \param str Stream to read version number from.
      \param expected_version Version number to compare stream version number to.
      \returns Whether the number red is equal to the expected_version.
    */
    static bool ReadStateVersion(
      std::istream &str,
      uint32_t expected_version
    );

    /*!
      \brief Helper function for writing version number to output stream.
      \param str Stream to write version number to.
      \param version Version number to write to stream.
    */
    static void WriteStateVersion(
      std::ostream &str,
      uint32_t version
    );

    /*!
      \brief Override this method to read custom state from auto save stream.

      This method is not designed to be called by user directly,
      it is called automatically by the system.
      \note Must be consistent with WriteToStream counterpart method.
    */
    virtual bool ReadFromStream(std::istream &str);

    /*!
      \brief Override this method to write custom state to auto save stream.

      This method is not designed to be called by user directly,
      it is called automatically by the system.
      \note Must be consistent with ReadFromStream counterpart method.
    */
    virtual void WriteToStream(std::ostream &str) const;

    //! Forces system to render on next update frame. Has effect when "optimized rendering" is enabled.
    void DrawOnNextUpdate() const;

  private:
    const hiro::Resource *resource_;
    bool was_initialized_ = false;
    hiro::Viewarea *viewarea_;
    bool is_save_enabled_ = false;
    bool TestInitialization(const std::string &callee_name) const;
    std::string GetStateFileName() const;
  };

  //! Shared pointer to Gadget.
  using PGadget = std::shared_ptr<hiro::Gadget>;

}
#endif /* !HIRO_GADGET_H */