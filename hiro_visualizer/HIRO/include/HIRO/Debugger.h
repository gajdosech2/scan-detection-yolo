/*
  Copyright (C) Skeletex Research, s.r.o. - All Rights Reserved
  Unauthorized copying of this file, via any medium is strictly prohibited
  Proprietary and confidential
*/
#ifndef HIRO_DEBUGGER_H
#define HIRO_DEBUGGER_H
#include <HIRO/Resource.h>
#include <Utils/GeometryStructures.h>



namespace hiro
{

  //! API for rendering primitive debug objects.
  class HIRO_API Debugger : public hiro::Resource
  {
    friend class DebuggerGadget;
  public:

    //! Default constructor, object is automatically created by the HIRO Engine and should not be created manually.
    explicit Debugger(const std::string &name);

    //! Default destructor, properly removes the Impl pointer.
    ~Debugger();

    /*!
      \brief
        Draws a sphere for the lifetime seconds.
      \param sphere
        Sphere to be drawn.
      \param color
        Color to be used for the polygon wires.
      \param lifetime
        Lifetime in seconds, sphere will be removed after it expires. Value of 0 means visibility for one frame only.
    */
    void DrawSphere(const geom::Sphere &sphere, const cogs::Color3f &color = cogs::color::LIME, float lifetime = 0.0f);

    /*!
      \brief
        Draws a box for the lifetime seconds.
      \param box
        AABB box to be drawn.
      \param color
        Color to be used for the polygon wires.
      \param lifetime
        Lifetime in seconds, box will be removed after it expires. Value of 0 means visibility for one frame only.
    */
    void DrawBox(const geom::Aabb3 &box, const cogs::Color3f &color = cogs::color::LIME, float lifetime = 0.0f);

    /*!
      \brief
        Draws given line segments for the lifetime seconds.
      \param segments
        Vector of line segments to be drawn.
      \param color
        Color to be used for the lines.
      \param lifetime
        Lifetime in seconds, lines will be removed after it expires. Value of 0 means visibility for one frame only.
    */
    void DrawLines(const std::vector<geom::LineSegment3> &segments, const cogs::Color3f &color = cogs::color::LIME, float lifetime = 0.0f);

    /*!
      \brief
        Prints a debug text to the screen.
        Text will disappear when the time passes or when it is replaced by other print call.
      \param text
        Text to be printed.
      \param lifetime
        Lifetime in seconds, text will be removed after it expires. Value of 0 means visibility for one frame only.
    */
    void LogMessage(const std::string &text, float lifetime = 3.0f);

  private:
    struct Impl;
    hiro::Debugger::Impl *m = nullptr;

    //! Automatically called by the HIRO engine to create a Gadget object.
    hiro::PGadget CreateGadget() override;

    /*!
      \brief
        Decreases the lifetime counters of debug objects and deletes the expired ones.
      \note
        This method is automatically called by HIRO Engine.
      \param delta_time
        Specifies the number of seconds since the last update.
    */
    void Update(const float delta_time) override;

    using hiro::Resource::ResetGadgets;
  };

}
#endif /* !HIRO_DEBUGGER_H */