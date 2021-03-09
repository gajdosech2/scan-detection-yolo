#ifndef GLW_WINDOW_EVENT_OBSERVER_H
#define GLW_WINDOW_EVENT_OBSERVER_H
#include <functional>
#include <vector>

#include <glm/glm.hpp>

#include <GLW/API.h>

namespace glw
{

  //! Any class derived from WindowEventObserver can receive Window events.
  class GLW_API WindowEventObserver
  {
    friend class Window;
  protected:
    virtual void OnMouseMove(double xpos, double ypos);
    virtual void OnMouseDown(int button, int mods);
    virtual void OnMouseUp(int button, int mods);
    virtual void OnMouseWheel(double xoffset, double yoffset);
    virtual void OnCharacter(char codepoint);
    virtual void OnKeyDown(int key, int mods, bool is_repeat);
    virtual void OnKeyUp(int key, int mods);
    virtual void OnTouch(unsigned int num_of_contacts, unsigned int *id, double *xpos, double *ypos, double *cwidth, double *cheight);
    virtual void OnTouchGestBegin();
    virtual void OnTouchGestEnd();
    virtual void OnTouchGestZoom(double distance, double xpos, double ypos);
    virtual void OnTouchGestPan(double distance, double xpos, double ypos);
    virtual void OnWindowMove(int xpos, int ypos);
    virtual void OnWindowRefresh();
    virtual void OnWindowResize(int width, int height);
    virtual void OnContentScale(float xscale, float yscale);
    virtual void OnFramebufferResize(int width, int height);
    virtual void OnWindowIconify(int is_iconified);
    virtual void OnWindowFocus(int is_focused);
    virtual void OnWindowClose();
    virtual void OnFilesDropped(const std::vector<std::string> &files);
  };

}


#endif /* !GLW_WINDOW_EVENT_OBSERVER_H */