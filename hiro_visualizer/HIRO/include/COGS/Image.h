#ifndef COGS_IMAGE_H
#define COGS_IMAGE_H

#include <string>
#include <COGS/Color.h>
#include <COGS/Grid.h>

namespace cogs
{
  class COGS_API Image
  {
  public:
    Image() = default;
    explicit Image(const std::string &file_path);
    explicit Image(uint16_t width, uint16_t height);

    uint16_t GetWidth() const;
    uint16_t GetHeight() const;

    void LoadFromFile(const std::string &file_path);
    void SaveToFile(const std::string &file_path);

    const cogs::Color4b GetColorAt(const glm::vec2 &uv) const;

    const cogs::Color4b GetPixel(int32_t x, int32_t y) const;

    void SetPixel(int32_t x, int32_t y, const cogs::Color3b &color);

  private:
    std::vector<cogs::Color4b> pixels_;
    int32_t width_;
    int32_t height_;
    int32_t bpp_;
  };
}

#endif /* !COGS_IMAGE_H */