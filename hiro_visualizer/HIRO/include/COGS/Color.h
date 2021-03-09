#ifndef COGS_COLOR_H
#define COGS_COLOR_H
#include <vector>
#include <functional>

#include <glm/common.hpp>

#include <COGS/API.h>


namespace cogs
{
  struct Color3b;
  struct Color4b;
  struct Color3f;
  struct Color4f;
  struct Color3hex;
  struct Color4hex;

  //! Holds three color channels in uint8 format in range 0-255.
  struct COGS_API Color3b
  {
    uint8_t r = 0, g = 0, b = 0;
    Color3b() = default;
    Color3b(uint8_t red, uint8_t green, uint8_t blue);
    Color3b(const Color4b &col);
    Color3b(const Color3f &col);
    Color3b(const Color4f &col);
    Color3b(const Color3hex &col);
    Color3b(const Color4hex &col);
    Color3b operator+(const Color3b &col) const;
    Color3b &operator+=(const Color3b &col);
    uint8_t *GetPtr();
    const uint8_t *GetPtr() const;
    Color3b Mix(const Color3b &col, float weight) const;
  };

  //! Holds four color channels in uint8 format in range 0-255.
  struct COGS_API Color4b
  {
    uint8_t r = 0, g = 0, b = 0, a = 255;
    Color4b() = default;
    Color4b(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha);
    Color4b(const Color3b &col);
    Color4b(const Color3f &col);
    Color4b(const Color4f &col);
    Color4b(const Color3hex &col);
    Color4b(const Color4hex &col);
    Color4b operator+(const Color4b &col) const;
    Color4b &operator+=(const Color4b &col);
    uint8_t *GetPtr();
    const uint8_t *GetPtr() const;
    Color4b Mix(const Color4b &col, float weight) const;
  };

  //! Holds three color channels in float format in range 0-1.
  struct COGS_API Color3f
  {
    float r = 0.0f, g = 0.0f, b = 0.0f;
    Color3f() = default;
    Color3f(float red, float green, float blue);
    Color3f(const Color3b &col);
    Color3f(const Color4b &col);
    Color3f(const Color4f &col);
    Color3f(const Color3hex &col);
    Color3f(const Color4hex &col);
    float *GetPtr();
    const float *GetPtr() const;
    Color3f operator+(const Color3f &col) const;
    Color3f &operator+=(const Color3f &col);
    Color3f &operator*=(float multiplier);
    cogs::Color3f Mix(const Color3f &col, float weight) const;
  };

  //! Holds four color channels in float format in range 0-1.
  struct COGS_API Color4f
  {
    float r = 0.0f, g = 0.0f, b = 0.0f, a = 1.0f;
    Color4f() = default;
    Color4f(float red, float green, float blue, float alpha);
    Color4f(const Color3b &col);
    Color4f(const Color4b &col);
    Color4f(const Color3f &col);
    Color4f(const Color3f &col, float alpha);
    Color4f(const Color3hex &col);
    Color4f(const Color4hex &col);
    float *GetPtr();
    const float *GetPtr() const;
    Color4f operator+(const Color4f &col) const;
    Color4f &operator+=(const Color4f &col);
    Color4f &operator*=(float multiplier);
    Color4f Mix(const Color4f &col, float weight) const;
  };

  //! Holds three color channels in hexadecimal string representation.
  struct COGS_API Color3hex
  {
    Color3hex() = default;
    Color3hex(const char *hex_color);
    Color3hex &operator=(const char *hex_color);
    Color3hex(const Color3hex &col);
    Color3hex &operator =(const Color3hex &col);
    explicit Color3hex(const Color3b &col);
    explicit Color3hex(const Color3f &col);
    explicit Color3hex(const Color4b &col);
    explicit Color3hex(const Color4f &col);
    explicit Color3hex(const Color4hex &col);
    const char *GetPtr() const;

  private:
    char hex[7] = "000000";
  };

  //! Holds four color channels in hexadecimal string representation.
  struct COGS_API Color4hex
  {
    Color4hex() = default;
    Color4hex(const char *hex_color);
    Color4hex &operator=(const char *hex_color);
    Color4hex(const Color4hex &col);
    Color4hex &operator =(const Color4hex &col);
    explicit Color4hex(const Color3b &col);
    explicit Color4hex(const Color3f &col);
    explicit Color4hex(const Color4b &col);
    explicit Color4hex(const Color4f &col);
    explicit Color4hex(const Color3hex &col);
    const char *GetPtr() const;
  private:
    char hex[9] = "000000FF";
  };

  COGS_API bool operator ==(const Color3b &a, const Color3b &b);
  COGS_API bool operator ==(const Color4b &a, const Color4b &b);
  COGS_API bool operator ==(const Color3f &a, const Color3f &b);
  COGS_API bool operator ==(const Color4f &a, const Color4f &b);
  COGS_API bool operator ==(const Color3hex &a, const Color3hex &b);
  COGS_API bool operator ==(const Color4hex &a, const Color4hex &b);

  COGS_API bool operator !=(const Color3b &a, const Color3b &b);
  COGS_API bool operator !=(const Color4b &a, const Color4b &b);
  COGS_API bool operator !=(const Color3f &a, const Color3f &b);
  COGS_API bool operator !=(const Color4f &a, const Color4f &b);
  COGS_API bool operator !=(const Color3hex &a, const Color3hex &b);
  COGS_API bool operator !=(const Color4hex &a, const Color4hex &b);

  COGS_API Color3f operator* (const float factor, const Color3f &col);
  COGS_API Color3f operator* (const Color3f &col, const float factor);
  COGS_API Color4f operator* (const float factor, const Color4f &col);
  COGS_API Color4f operator* (const Color4f &col, const float factor);

  COGS_API Color3f Interpolate(const Color3f &col1, const Color3f &col2, float weight);

  //! Color mapping options.
  enum class ColorMap
  {
    //! blue > cyan > green > yellow > red > purple
    rainbow = 0,
    //! bluish tones > green > redish tones
    thermal = 1,
    //! blue > magenta > red
    blue_red = 2,
    //! red > yellow > green
    red_green = 3,
    //! pseudo-random values
    scattered = 4,
    //! black > white
    grayscale = 5,
    //! many colors
    colorful = 6,
    //! many bright colors
    colorful_bright = 7
  };

  //! Returns string representation of ColorMap enum value.
  COGS_API std::string ColorMapToString(ColorMap map);

  //! Converts float value in range <0.0, 1.0> to color, depending on selected mapping function.
  COGS_API cogs::Color3f MapValueToColor(float value, ColorMap mapping_func);

  //! Converts float values in range <0.0, 1.0> to colors, depending on selected mapping function.
  COGS_API std::vector<cogs::Color3f> MapValuesToColors(const std::vector<float> &values, ColorMap mapping_func);

  //! For each float from vector applies processing function and converts value to color afterwards, depending on selected mapping function.
  COGS_API std::vector<cogs::Color3f> MapValuesToColors(const std::vector<float> &values, std::function<float(float)> process_func, ColorMap mapping_func);



  //! Definitions of color constants.
  namespace color
  {
    const Color3f WHITE = Color3b(255, 255, 255);
    const Color3f GRAY = Color3b(128, 128, 128);
    const Color3f BLACK = Color3b(0, 0, 0);

    //! 90% lightness -lightest of grays
    const Color3f GRAY90 = Color3b(230, 230, 230);
    //! 80% lightness
    const Color3f GRAY80 = Color3b(204, 204, 204);
    //! 70% lightness
    const Color3f GRAY70 = Color3b(179, 179, 179);
    //! 60% lightness
    const Color3f GRAY60 = Color3b(153, 153, 153);
    //! 50% lightness
    const Color3f GRAY50 = Color3b(128, 128, 128);
    //! 40% lightness
    const Color3f GRAY40 = Color3b(102, 102, 102);
    //! 30% lightness
    const Color3f GRAY30 = Color3b(77, 77, 77);
    //! 20% lightness
    const Color3f GRAY20 = Color3b(51, 51, 51);
    //! 10% lightness - darkest of grays
    const Color3f GRAY10 = Color3b(26, 26, 26);

    //! pure red - 255 0 0
    const Color3f RED = Color3b(255, 0, 0);
    //! pure green - 0 255 0
    const Color3f GREEN = Color3b(0, 255, 0);
    //! pure blue - 0 0 255
    const Color3f BLUE = Color3b(0, 0, 255);

    //! nicer pure red
    const Color3f CRIMSON = Color3b(214, 44, 54);
    const Color3f ORANGE = Color3b(242, 172, 41);
    const Color3f YELLOW = Color3b(252, 223, 78);
    //! darker green
    const Color3f FOREST = Color3b(31, 140, 69);
    //! bright green
    const Color3f LIME = Color3b(83, 252, 20);
    //! blueish green
    const Color3f EMERALD = Color3b(80, 220, 100);
    //! greenish blue
    const Color3f CYAN = Color3b(0, 245, 255);
    //! nicer pure blue
    const Color3f SKY = Color3b(5, 157, 255);
    //! dark blue
    const Color3f NAVY = Color3b(4, 59, 106);
    const Color3f PURPLE = Color3b(148, 14, 112);
    //! pinkish red
    const Color3f MAGENTA = Color3b(211, 19, 90);
    const Color3f SALMON = Color3b(250, 128, 114);
    const Color3f PINK = Color3b(242, 131, 166);
    const Color3f GOLD = Color3b(255, 215, 0);
    const Color3f CREAM_WHITE = Color3b(255, 252, 209);

    //! Skeletex dark blue
    const Color3f STX_NAVY = Color3b(34, 83, 120);
    //! Skeletex darker green
    const Color3f STX_GREEN = Color3b(23, 150, 164);
    //! Skeletex light green
    const Color3f STX_LIME = Color3b(85, 203, 199);
    //! Skeletex bright yellow
    const Color3f STX_VANILLA = Color3b(243, 255, 226);
    //! Skeletex orange
    const Color3f STX_ORANGE = Color3b(255, 150, 73);
  }
}

#endif /* !COGS_COLOR_H */