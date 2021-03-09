/*
  Copyright (C) Skeletex Research, s.r.o. - All Rights Reserved
  Unauthorized copying of this file, via any medium is strictly prohibited
  Proprietary and confidential
*/
#ifndef HIRO_GUI_TYPES_H
#define HIRO_GUI_TYPES_H
#include <vector>
#include <optional>
#include <memory>
#include <functional>

#ifdef HIRO_ENABLE_CEGUI
#  ifdef __GNUC__
#    undef True
#    undef False
#    undef None
#  endif
#  include <CEGUI/CEGUI.h>
#  include <GUIP/Combobox.h>
#endif

#include <COGS/Color.h>
#include <HIRO/API.h>



namespace guip { class ArrayPanel; }



namespace hiro
{

  //! Type of function used to evaluate boolean conditions.
  enum class BoolFunc
  {
    equals_true, //!< Compares value to true.
    equals_false //!< Compares value to false.
  };

  namespace gui
  {

    //! A general element containing basic interface methods.
    class HIRO_API Element
    {
    public:
      /*!
        \brief Test the visibility conditions.

        If there were no conditions provided, returns true.
      */
      bool TestCondition() const
      {
        return (condition_ == nullptr) || condition_();
      }

      //! Returns a unique identifier of current element.
      uint32_t GetId() const
      {
        return id_;
      }

#ifdef HIRO_ENABLE_CEGUI
      Element(CEGUI::Window *win) : id_(win->getID())
      {
      }
#endif
    protected:
      void SetConditionFuncImpl(std::function<bool(void)> condition_func)
      {
        condition_ = condition_func;
      }
    private:
      const uint32_t id_ = 0u;
      std::function<bool(void)> condition_ = nullptr;
    };



    //! A general element containing basic interface methods.
    template <typename C>
    class HIRO_API TElement : public hiro::gui::Element
    {
    public:
      /*!
        \brief Set a visibility condition to this element.

        The element will be visible only when specified condition function
        returns true. The condition function is called automatically
        on a GUI refresh.
      */
      C *SetConditionFunc(std::function<bool(void)> condition_func)
      {
        SetConditionFuncImpl(condition_func);
        return  reinterpret_cast<C *>(this);
      }

      /*!
        \brief Set a visibility condition to this element.

        The element will be visible only when specified boolean variable
        passes the test. The condition variable is checked automatically
        on a GUI refresh.

        \param var
          Pointer to a boolean variable that will be tested.
        \param func
          A function used to test the variable against. If the variable
          passes the function, the condition is satisfied.
      */
      C *SetConditionBool(bool *var, hiro::BoolFunc func = hiro::BoolFunc::equals_true)
      {
        SetConditionFuncImpl([var, func]()
        {
          return *var == (func == hiro::BoolFunc::equals_true);
        });
        return  reinterpret_cast<C *>(this);
      }

      /*!
        \brief Add a callback function to the subscriber list.

        Every function in the subscriber list is called every time an element
        state changes.
      */
      C *Subscribe(std::function<void(const C *)> callback_func)
      {
        callbacks_.emplace_back(callback_func);
        return  reinterpret_cast<C *>(this);
      }

#ifdef HIRO_ENABLE_CEGUI
      TElement(CEGUI::Window *win) : hiro::gui::Element::Element(win)
      {
      }
#endif
    protected:
      virtual void NotifyChange() const
      {
        for (const auto &on_change : callbacks_)
        {
          if (on_change)
          {
            on_change(reinterpret_cast<const C *>(this));
          }
        }
      }
    private:
      std::vector<std::function<void(const C *)>> callbacks_;
    };



    //! An element which can be interpreted as a variable of a specific type.
    template <typename T, typename C>
    class HIRO_API LinkedElement : public hiro::gui::TElement<C>
    {
    public:
      /*!
        \brief Change the current value
        and notify subscribers if it differs from the previous value.
      */
      virtual C *Set(const T new_value) = 0;
      //! Get current value.
      virtual T Get() const = 0;
      /*!
        \brief Set a variable updated according the element state.

        \warning
          - Changes introduced to a link will not affect the element.
          - Only a single link can be active at a time.
      */
      C *SetLink(T *pointer)
      {
        link_ptr_ = pointer;
        if (link_ptr_ != nullptr)
        {
          Set(*link_ptr_);
        }
        return reinterpret_cast<C *>(this);
      }
#ifdef HIRO_ENABLE_CEGUI
      LinkedElement(CEGUI::Window *win) : hiro::gui::TElement<C>(win) {};
#endif
    protected:
      void NotifyChange() const override
      {
        if (link_ptr_ != nullptr)
        {
          *link_ptr_ = Get();
        }
        hiro::gui::TElement<C>::NotifyChange();
      };
    private:
      T *link_ptr_ = nullptr;
    };


    //! A panel that contains other elements within.
    class Panel : public hiro::gui::TElement<hiro::gui::Panel>
    {
    public:
#ifdef HIRO_ENABLE_CEGUI
      Panel(CEGUI::Window *win);
#endif
    };



    /*!
      \brief Clickable button element.

      Subscribe the element to receive click events.
    */
    class HIRO_API Button : public hiro::gui::TElement<hiro::gui::Button>
    {
    public:
      //! Set a text that will be shown on the button.
      hiro::gui::Button *SetCaption(const std::string &caption);
      //! Returns text that is currently shown on the button.
      std::string GetCaption() const;
#ifdef HIRO_ENABLE_CEGUI
      Button(CEGUI::PushButton *cegui_btn);
    private:
      CEGUI::PushButton *cegui_win;
      bool OnPressed(const CEGUI::EventArgs &e);
#endif
    };



    //! Non-editable text element.
    class HIRO_API Label : public hiro::gui::TElement<hiro::gui::Label>
    {
    public:
      //! Set the text of the label.
      hiro::gui::Label *Set(const std::string &text);
      //! Get the text of the label.
      std::string Get() const;
#ifdef HIRO_ENABLE_CEGUI
      Label(CEGUI::Window *cegui_checkbox);
    private:
      CEGUI::Window *cegui_win;
#endif
    };



    //! Selectable checkbox that can be linked to a boolean variable.
    class HIRO_API Checkbox : public hiro::gui::LinkedElement<bool, hiro::gui::Checkbox>
    {
    public:
      //! Set the state of the checkbox. Default false
      hiro::gui::Checkbox *Set(bool state) override;
      //! Get current state of the checkbox.
      bool Get() const override;
#ifdef HIRO_ENABLE_CEGUI
      Checkbox(CEGUI::ToggleButton *cegui_checkbox);
    private:
      CEGUI::ToggleButton *cegui_win;
      bool OnStateChange(const CEGUI::EventArgs &e);
#endif
    };



    /*!
      \brief Editbox that can contain only numeric integer values.
    */
    class HIRO_API NumericInt : public hiro::gui::LinkedElement<int32_t, hiro::gui::NumericInt>
    {
    public:
      //! Set value to numeric. Values outside of min max range are clipped. Default 0
      hiro::gui::NumericInt *Set(int32_t value) override;
      //! Define the minimal value that can be set. Default -32768
      hiro::gui::NumericInt *SetMin(int32_t min_val);
      //! Define the maximal value that can be set. Default 32767
      hiro::gui::NumericInt *SetMax(int32_t max_val);
      /*!
        \brief Define the minimal and the maximal values that can be set.

        Default for minimal is -32768 and for maximal is 32767.
      */
      hiro::gui::NumericInt *SetMinMax(int32_t min, int32_t max);
      //! Set step by which the value changes when clicked on the up and down. Default 1
      hiro::gui::NumericInt *SetStep(int32_t val_step);

      //! Returns current value of numeric.
      int32_t Get() const override;
      //! Get the minimal value that can be set.
      int32_t GetMin() const;
      //! Get the maximal value that can be set.
      int32_t GetMax() const;
      //! Get step by which the value changes when clicked on the up and down.
      int32_t GetStep() const;
#ifdef HIRO_ENABLE_CEGUI
      NumericInt(CEGUI::Spinner *cegui_spinner);
    private:
      CEGUI::Spinner *spinner_win_;
      bool OnValueChange(const CEGUI::EventArgs &e);
#endif
    };



    /*!
      \brief  Edit box which can contain only numeric float values.
    */
    class HIRO_API NumericFloat: public hiro::gui::LinkedElement<float, hiro::gui::NumericFloat>
    {
    public:
      //! Set value to numeric. Values outside of min max range are clipped. Default 0
      hiro::gui::NumericFloat *Set(float value) override;
      //! Define the minimal value that can be set. Default -32768
      hiro::gui::NumericFloat *SetMin(float min_val);
      //! Define the maximal value that can be set. Default 32767
      hiro::gui::NumericFloat *SetMax(float max_val);
      /*!
        \brief Define the minimal and the maximal values that can be set.

        Default for minimal is -32768 and for maximal is 32767.
      */
      hiro::gui::NumericFloat *SetMinMax(float min, float max);
      //! Set step by which the value changes when clicked on the up and down. Default 0.1
      hiro::gui::NumericFloat *SetStep(float val_step);
      //! Returns current value of numeric.
      float Get() const override;
      //! Get the minimal value that can be set.
      float GetMin() const;
      //! Get the maximal value that can be set.
      float GetMax() const;
      //! Get step by which the value changes when clicked on the up and down.
      float GetStep() const;
#ifdef HIRO_ENABLE_CEGUI
      NumericFloat(CEGUI::Spinner *cegui_spinner);
    private:
      CEGUI::Spinner *spinner_win_;
      bool OnValueChange(const CEGUI::EventArgs &e);
#endif
    };



    /*!
      \brief  Slider that can be directly interpreted by float value.
    */
    class HIRO_API SlidingFloat : public hiro::gui::LinkedElement<float, hiro::gui::SlidingFloat>
    {
    public:
      //! Set value to slider handle. Values outside of min max range are clipped. Default 0
      hiro::gui::SlidingFloat *Set(float value) override;
      //! Define the minimal value that can be set. Default 0
      hiro::gui::SlidingFloat *SetMin(float min_val);
      //! Define the maximal value that can be set. Default 1
      hiro::gui::SlidingFloat *SetMax(float max_val);
      /*!
        \brief Define the minimal and the maximal values that can be set.

        Default for minimal is 0 and for maximal is 1.
      */
      hiro::gui::SlidingFloat *SetMinMax(float min, float max);
      //! Set step by which the slider moves when clicked out of handle bounds. Default 0.1
      hiro::gui::SlidingFloat *SetStep(float val_step);
      //! Returns current value defined by slider handle.
      float Get() const override;
      //! Get the minimal value that can be set.
      float GetMin() const;
      //! Get the maximal value that can be set.
      float GetMax() const;
      //! Returns step by which the slider moves when clicked out of handle bounds.
      float GetStep() const;
#ifdef HIRO_ENABLE_CEGUI
      SlidingFloat(CEGUI::Slider *cegui_slider);
    private:
      float min_value_ = 0.0f;
      CEGUI::Slider *cegui_win_;
      bool OnValueChange(const CEGUI::EventArgs &e);
#endif
    };



    /*!
      \brief  Slider which can be directly represented by integer variable.

      Set min max values to define range. Default range is <0,10>.
    */
    class HIRO_API SlidingInt : public hiro::gui::LinkedElement<int32_t, hiro::gui::SlidingInt>
    {
    public:
      //! Set value to slider handle. Values outside of min max range are clipped. Default 0
      hiro::gui::SlidingInt *Set(int32_t value) override;
      //! Define the minimal value that can be set. Default 0
      hiro::gui::SlidingInt *SetMin(int32_t min_val);
      //! Define the maximal value that can be set. Default 10
      hiro::gui::SlidingInt *SetMax(int32_t max_val);
      /*!
        \brief Define the minimal and the maximal values that can be set.

        Default for minimal is 0 and for maximal is 10.
      */
      hiro::gui::SlidingInt *SetMinMax(int32_t min, int32_t max);
      //! Set step by which the slider moves when clicked out of handle bounds. Default 1
      hiro::gui::SlidingInt *SetStep(int32_t val_step);
      //! Returns current value defined by slider handle.
      int32_t Get() const override;
      //! Get the minimal value that can be set.
      int32_t GetMin() const;
      //! Get the maximal value that can be set.
      int32_t GetMax() const;
      //! Returns step by which the slider moves when clicked out of handle bounds.
      int32_t GetStep() const;
#ifdef HIRO_ENABLE_CEGUI
      SlidingInt(CEGUI::Slider *cegui_slider);
    private:
      int32_t min_value_ = 0;
      int32_t max_value_ = 10;
      CEGUI::Slider *cegui_win_;
      bool OnValueChange(const CEGUI::EventArgs &e);
      bool OnThumbReleased(const CEGUI::EventArgs &e);
      bool OnThumbChanged(const CEGUI::EventArgs &e);
#endif
      float GetAsFloat() const;
    };



    /*!
      \brief List of items, where one of the items is selected.

      Each item has a value defined, that can be used to identify it.
    */
    class HIRO_API Droplist : public hiro::gui::LinkedElement<int32_t, hiro::gui::Droplist>
    {
    public:
      /*!
        \brief Selects an item that has a defined value.

        When there are multiple items with the same value, selects the first one in the list.
      */
      hiro::gui::Droplist *Set(const int32_t value) override;
      //! Returns the value of currently selected item.
      int32_t Get() const override;
      //! Returns the text of currently selected item.
      std::string GetText() const;
      //! Adds a single item to the list and assigns it a specified value.
      hiro::gui::Droplist *AddItem(const std::string &name, int32_t value);
      //! Adds a single item to the list. Position in the list determines the value.
      hiro::gui::Droplist *AddItemIndexed(const std::string &name);
      //! Adds multiple items by pair <name,value>.
      hiro::gui::Droplist *AddItems(const std::vector<std::pair<std::string, int32_t>> &items);
      //! Adds multiple items by name. Position in the list determines value of item.
      hiro::gui::Droplist *AddItemsIndexed(const std::vector<std::string> &items);
#ifdef HIRO_ENABLE_CEGUI
      Droplist(guip::Combobox *cegui_listbox);
    private:
      guip::Combobox *cegui_win_;
      bool OnSelectionChange(const CEGUI::EventArgs &e);
#endif
    };



    /*!
      \brief List of checkbox elements that can be managed in a group.
    */
    class HIRO_API CheckboxList : public hiro::gui::TElement<hiro::gui::CheckboxList>
    {
    public:
      /*!
        \brief
          Add checkbox element to the list.
        \param title
          Checkbox element title.
        \param state
          Initial state of checkbox.
        \param id
          User defined item identifier.
          When not specified, equal to the number of elements already in the list.
        \returns
          Identifier of an item. Equal to parameter id when specified.
      */
      size_t AddItem(
        const std::string &title,
        bool state = false,
        const std::optional<size_t> id = std::nullopt
      );
      /*!
        \brief
          Assigns custom color to the item.
        \param id
          Identifier of an item.
        \param color
          Color used to highlight an item. Default black
      */
      hiro::gui::CheckboxList *SetItemColor(size_t id, const cogs::Color3f &color);
      /*!
        \brief
          Subscribe callback function that will be invoked on item state change.

        When the state of any checkbox element in a list changes, the specified
        function will be invoked. The first parameter of a function holds an
        identifier of the checkbox whose state has been changed. The second
        parameter holds the new state of the checkbox.
      */
      hiro::gui::CheckboxList *SubscribeItems(const std::function<void(uint32_t, bool)> &func);
#ifdef HIRO_ENABLE_CEGUI
      CheckboxList(guip::ArrayPanel *array_panel);
    private:
      struct Item
      {
        CEGUI::Window *wrapper;
        CEGUI::ToggleButton *checkbox;
        CEGUI::Window *colorstripe;
      };
      std::vector<hiro::gui::CheckboxList::Item> items_;
      std::vector<std::function<void(uint32_t, bool)>> item_callbacks_;
      guip::ArrayPanel *array_panel_;
      bool OnItemToggle(const CEGUI::EventArgs &e);
      bool OnSelectAll(const CEGUI::EventArgs &e);
      bool OnUnselectAll(const CEGUI::EventArgs &e);
      void CreateNewItem(hiro::gui::CheckboxList::Item *item, size_t id);
#endif
    };

  }

}

#endif /* !HIRO_GUI_TYPES_H */