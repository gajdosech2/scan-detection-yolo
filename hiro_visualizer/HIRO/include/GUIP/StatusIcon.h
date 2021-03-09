#ifndef GUIP_STATUS_ICON_H
#define GUIP_STATUS_ICON_H
#include <CEGUI/Window.h>
#include <GUIP/API.h>

namespace guip
{

  //! Image class that represents status of a process.
  class GUIP_API StatusIcon : public CEGUI::Window
  {
  public:

    enum class Status
    {
      //! Rendering no image.
      none,
      //! Rendering spinning circle.
      waiting,
      //! Rendering green check mark.
      success,
      //! Rendering red cross.
      failure
    };

    //! Unique gui system identifier.
    static CEGUI::String WidgetTypeName;

    StatusIcon(const CEGUI::String &type, const CEGUI::String &name);

    //! Changes status to the defined one.
    void SetStatus(StatusIcon::Status status);
    //! Returns current status.
    StatusIcon::Status GetStatus() const;
    //! Updates widget. This function is called automatically by a gui system.
    virtual void update(float elapsed) override;
  private:
    Status status_ = Status::none;
    float time_since_last_render_ = 0.0f;
    void RotateSelf(float elapsed);
  };

}
#endif /* !GUIP_STATUS_ICON_H */