/*
  Copyright (C) Skeletex Research, s.r.o. - All Rights Reserved
  Unauthorized copying of this file, via any medium is strictly prohibited
  Proprietary and confidential
*/
#ifndef HIRO_INPUT_H
#define HIRO_INPUT_H



namespace hiro
{

  //! Key names.
  enum class Key
  {
    unknown = -1,
    space = 32,
    apostrophe = 39,  /* ' */
    comma = 44,  /* , */
    minus = 45,  /* - */
    period = 46,  /* . */
    slash = 47,  /* / */
    k0 = 48,
    k1 = 49,
    k2 = 50,
    k3 = 51,
    k4 = 52,
    k5 = 53,
    k6 = 54,
    k7 = 55,
    k8 = 56,
    k9 = 57,
    semicolon = 59,  /* ; */
    equal = 61,  /* = */
    a = 65,
    b = 66,
    c = 67,
    d = 68,
    e = 69,
    f = 70,
    g = 71,
    h = 72,
    i = 73,
    j = 74,
    k = 75,
    l = 76,
    m = 77,
    n = 78,
    o = 79,
    p = 80,
    q = 81,
    r = 82,
    s = 83,
    t = 84,
    u = 85,
    v = 86,
    w = 87,
    x = 88,
    y = 89,
    z = 90,
    left_bracket = 91,  /* [ */
    backslash = 92,  /* \ */
    right_bracket = 93,  /* ] */
    grave_accent = 96,  /* ` */
    world_1 = 161, /* non-us #1 */
    world_2 = 162, /* non-us #2 */
    escape = 256,
    enter = 257,
    tab = 258,
    backspace = 259,
    insert = 260,
    del = 261,
    right = 262,
    left = 263,
    down = 264,
    up = 265,
    page_up = 266,
    page_down = 267,
    home = 268,
    end = 269,
    caps_lock = 280,
    scroll_lock = 281,
    num_lock = 282,
    print_screen = 283,
    pause = 284,
    f1 = 290,
    f2 = 291,
    f3 = 292,
    f4 = 293,
    f5 = 294,
    f6 = 295,
    f7 = 296,
    f8 = 297,
    f9 = 298,
    f10 = 299,
    f11 = 300,
    f12 = 301,
    f13 = 302,
    f14 = 303,
    f15 = 304,
    f16 = 305,
    f17 = 306,
    f18 = 307,
    f19 = 308,
    f20 = 309,
    f21 = 310,
    f22 = 311,
    f23 = 312,
    f24 = 313,
    f25 = 314,
    num_0 = 320,
    num_1 = 321,
    num_2 = 322,
    num_3 = 323,
    num_4 = 324,
    num_5 = 325,
    num_6 = 326,
    num_7 = 327,
    num_8 = 328,
    num_9 = 329,
    num_decimal = 330,
    num_divide = 331,
    num_multiply = 332,
    num_subtract = 333,
    num_add = 334,
    num_enter = 335,
    num_equal = 336,
    left_shift = 340,
    left_control = 341,
    left_alt = 342,
    left_super = 343,
    right_shift = 344,
    right_control = 345,
    right_alt = 346,
    right_super = 347,
    menu = 348
  };

  //! Mouse button names.
  enum class MouseButton
  {
    left = 0,
    right = 1,
    middle = 2
  };

  //! Modifier key names.
  enum class Mod : uint8_t
  {
    shift = 0x0001,
    control = 0x0002,
    alt = 0x0004,
    super = 0x0008,
    caps_lock = 0x0010,
    num_lock = 0x0020
  };

  //! Holds information about pressed modifier keys.
  class ModKeys
  {
  public:
    //! Creates structure with bit map of pressed modifier keys.
    ModKeys(uint8_t state) : state_(state) {};

    //! Checks whether specified modifier key is pressed.
    bool IsPressed(hiro::Mod modifier_key) const
    {
      return state_ & static_cast<uint8_t>(modifier_key);
    }

  private:
    uint8_t state_{ 0u };
  };

}
#endif /* !HIRO_INPUT_H */