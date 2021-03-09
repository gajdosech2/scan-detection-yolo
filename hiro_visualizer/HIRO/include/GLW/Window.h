/*
  Copyright (C) Skeletex Research, s.r.o. - All Rights Reserved
  Unauthorized copying of this file, via any medium is strictly prohibited
  Proprietary and confidential
*/
#ifndef GLW_WINDOW_H
#define GLW_WINDOW_H
#include <string>
#include <set>
#include <array>
#include <unordered_map>
#include <memory>

#include <glm/glm.hpp>

#include <GLW/WindowEventObserver.h>

struct GLFWwindow;

namespace glw
{

  //! Implements GLFW functions in object style programming.
  class GLW_API Window : public WindowEventObserver
  {
  public:

    static constexpr uint8_t max_observer_priority = 15u;

    //! Parameters used to initialize Window.
    struct InitParameters
    {
      //! Initial resolution of the window frame buffer.
      glm::uvec2 resolution = glm::uvec2(640, 480);
      //! Minimum resolution of the window frame buffer.
      glm::uvec2 min_resolution = glm::uvec2(0);
      //! Maximum resolution of the window frame buffer.
      glm::uvec2 max_resolution = glm::uvec2(0);
      //! Whether the window should be maximized on creation. Overrides resolution.
      bool maximized = false;
      //! Window title shown in frame top.
      std::string caption = "GLW Window";
      //! Desired number of samples to use for multisampling; Zero disables multisampling; Negative lets the driver decide; Default is 8
      int8_t aa_samples = 8;
      //! Whether the windowed window will be initially visible.
      bool visible = true;
      //! Try to detect if window exist in another context during initialization and share its context with it; default is true.
      bool try_share_contexts = true;
      //! Whether the windowed window will be resizable by the use; default is true.
      bool resizable = true;
      //! Specifies position of created window; default is 100.
      glm::ivec2 position = glm::ivec2(100);
      //! Whether the window will be windowed or fullscreen
      bool fullscreen = false;
      //! Whether the cursor will be hidden
      bool hidden_cursor = false;
    };

    explicit Window();
    explicit Window(const InitParameters &params);
    ~Window();
    /*!
      Registers observer for window callback events.
      Priority parameter sets ordering update - the lower number = the sooner notified
    */
    void ObserverRegister(WindowEventObserver *object, const uint8_t priority = glw::Window::max_observer_priority);
    //! Unregisters observer for window callback events.
    void ObserverRemove(WindowEventObserver *object);

    [[nodiscard]] bool IsVisible() const;
    [[nodiscard]] bool IsMaximized() const;
    [[nodiscard]] bool IsIconified() const;
    [[nodiscard]] bool IsFullscreen();

    [[nodiscard]] bool IsInitialized();
    [[nodiscard]] bool ShouldClose();
    void SetShouldClose();

    [[nodiscard]] bool IsContextShared();

    //! Returns pointer to raw GLFW window.
    [[nodiscard]] GLFWwindow *GetWindowPtr();

    //! Returns position of mouse, relative to the window position.
    [[nodiscard]] glm::vec2 GetMousePosition() const;
    //! Returns screen position of window client area.
    [[nodiscard]] glm::ivec2 GetPosition() const;
    //! Returns resolution of window rendering buffer.
    [[nodiscard]] glm::uvec2 GetResolution() const;
    //! Returns width of window rendering buffer.
    [[nodiscard]] uint32_t GetWidth() const;
    //! Returns height of window rendering buffer.
    [[nodiscard]] uint32_t GetHeight() const;
    /*!
      \brief The content scale is the ratio between the current DPI
      and the platform's default DPI.

      The content scale may depend on both the monitor resolution and pixel
      density and on user settings. It may be very different from the raw DPI
      calculated from the physical size and current resolution.

      On systems where each monitors can have its own content scale,
      the window content scale will depend on which monitor the system
      considers the window to be on.
    */
    [[nodiscard]] glm::vec2 GetContentScaling() const;

    //! Window resolution modulated by a content scaling factor.
    [[nodiscard]] glm::uvec2 GetUnscaledResolution() const;

    void SetWindowedMode(int width, int height, int posx = 0, int posy = 0);
    void SetFullscreenMode();

    void PollEvents();
    void SwapBuffers();

    void SetContextConditional();
    void UnsetContextConditional();

  protected:
    /*!
      Window initialization procedure.
      When creating derived class, this method needs to be called at some point in window creation!
    */
    bool Initialize(const InitParameters &init);

  private:
    std::array < std::set<WindowEventObserver *>, glw::Window::max_observer_priority + 1 > obs_priority_lists_;
    std::unordered_map<WindowEventObserver *, std::set<WindowEventObserver *>*> obs_iterator_for_ptr_;

    GLFWwindow *window_ = nullptr;
    GLFWwindow *shared_window_ = nullptr;

    glm::uvec2 resolution_;
    glm::ivec2 position_;
    glm::vec2 mouse_position_;

    bool is_initialized_ = false;

    bool is_fullscreen_ = false;

    void InitializeMembers(const InitParameters &init);
    void RegisterCallbacks();

    static void CursorPosCallback(GLFWwindow *window, double xpos, double ypos);
    static void MouseButtonCallback(GLFWwindow *window, int button, int action, int mods);
    static void ScrollCallback(GLFWwindow *window, double xoffset, double yoffset);
    static void CharCallback(GLFWwindow *window, unsigned int codepoint);
    static void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
    static void TouchCallback(GLFWwindow *window, unsigned int num_of_contacts, unsigned int *id, double *xpos, double *ypos, double *cwidth, double *cheight);
    static void TouchGestBeginCallback(GLFWwindow *window);
    static void TouchGestEndCallback(GLFWwindow *window);
    static void TouchGestZoomCallback(GLFWwindow *window, double distance, double xpos, double ypos);
    static void TouchGestPanCallback(GLFWwindow *window, double distance, double xpos, double ypos);
    static void FramebufferResizeCallback(GLFWwindow *window, int xpos, int ypos);
    static void WindowMoveCallback(GLFWwindow *window, int xpos, int ypos);
    static void WindowRefreshCallback(GLFWwindow *window);
    static void WindowResizeCallback(GLFWwindow *window, int xpos, int ypos);
    static void WindowFocusCallback(GLFWwindow *window, int is_focused);
    static void WindowCloseCallback(GLFWwindow *window);
    static void WindowIconifyCallback(GLFWwindow *window, int is_iconified);
    static void FilesDropCallback(GLFWwindow *window, int32_t file_count, const char **files);
    static void WindowContentScaleCallback(GLFWwindow *window, float xscale, float yscale);
  };

  class GLW_API HiddenWindow : public WindowEventObserver
  {
  public:
    HiddenWindow();
    void SwapBuffers();
  protected:
    std::unique_ptr<Window> window_;
  };

}
#endif /* !GLW_WINDOW_H */