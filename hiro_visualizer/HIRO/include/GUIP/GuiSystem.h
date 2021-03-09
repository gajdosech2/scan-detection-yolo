#ifndef GUIP_GUI_SYSTEM_H
#define GUIP_GUI_SYSTEM_H
#ifdef __linux__
#  undef True
#  undef False
#  undef None
#endif

#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/OpenGL/GL3Renderer.h>

#include <GLW/Window.h>
#include <GLW/ShaderProgramList.h>
#include <GLW/FrameBuffer.h>
#include <GUIP/API.h>

namespace guip
{

  /*!
    \brief
      Manages context, rendering and live span for all created widgets.

    The class automatically creates and destroys gui context as it exists.
  */
  class GUIP_API GuiSystem : public glw::WindowEventObserver
  {
  public:
    GuiSystem();
    ~GuiSystem();
    //! Creates context. Without invoking this function, gui will not work.
    bool Initialize(const std::string &resource_dir, std::shared_ptr<glw::Window> window);

    // Updates GUI state.
    void Update(float time_delta);
    //! Renders GUI into currently bound gl frame buffer.
    void Draw();
    //! Whether GUI should be rendered.
    bool IsDirty();
    //! Returns  context of CEGUI system.
    CEGUI::GUIContext *GetContext();
    //! Returns the root window widget.
    CEGUI::Window *GetRoot();

  protected:
    virtual void OnMouseDown(int button, int mods) override;
    virtual void OnMouseUp(int button, int mods) override;
    virtual void OnMouseWheel(double xoffset, double yoffset) override;
    virtual void OnMouseMove(double xpos, double ypos) override;
    virtual void OnCharacter(char codepoint) override;
    virtual void OnKeyDown(int key, int mods, bool is_repeat) override;
    virtual void OnKeyUp(int key, int mods) override;
    virtual void OnWindowResize(int width, int height) override;
    virtual void OnContentScale(float xscale, float yscale) override;

  private:

    class LoggerProxy : public CEGUI::Logger
    {
    public:
      LoggerProxy();
      void logEvent(const CEGUI::String &message, CEGUI::LoggingLevel level = CEGUI::LoggingLevel::Standard) override;
      void setLogFilename(const CEGUI::String &filename, bool append = false) override;
    };

    float gui_scale_ {1.0f};
    glm::uvec2 window_resoultion_;
    glw::ProgramList programs_;
    glw::PFrameBuffer framebuffer_;
    CEGUI::Renderer *renderer_ {nullptr};
    CEGUI::GUIContext *context_ {nullptr};
    CEGUI::Window *root_widget_;
    std::shared_ptr<glw::Window> window_;

    bool InitializeCegui(const std::string &resource_dir);
    void InitializeLogging();
    void UpdateFramebuffer();
  };

}
#endif /* !GUIP_GUI_SYSTEM_H */