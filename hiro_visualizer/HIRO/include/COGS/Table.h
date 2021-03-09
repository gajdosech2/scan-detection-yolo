#ifndef COGS_TABLE_H
#define COGS_TABLE_H
#include <COGS/Grid.h>

namespace cogs
{
  class COGS_API Table : public cogs::Grid<std::string>
  {
  public:
    Table(size_t columns, size_t rows);
    Table(size_t rows, const std::vector<std::string> &labels);
    void SetRow(size_t row_id, const std::vector<std::string> &cells);
    std::string ToString() const;

  private:
    bool has_labels{ false };
    std::string GetSeparator(const std::vector<size_t> &cell_widths) const;
    std::string GetRow(size_t row_id, const std::vector<size_t> &cell_widths) const;
  };
}
#endif /* !COGS_TABLE_H */