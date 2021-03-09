/*
  Copyright (C) Skeletex Research, s.r.o. - All Rights Reserved
  Unauthorized copying of this file, via any medium is strictly prohibited
  Proprietary and confidential
*/
#ifndef UTILS_STATISTICS_H
#define UTILS_STATISTICS_H
#include <glm/detail/func_common.hpp>
#include <string>
#include <vector>

//! General namespace for utilities.
namespace utils
{

  /*!
    \brief Calculates statistical evaluation on a data set.

    Example usage:
    \code{.cpp}
      utils::StatAnalyser<float> stat;

      for (size_t i=0; i<MAX_ITERATIONS; ++i)
      {
        float val = CalculateSomeValue();
        stat.Add(val);
      }

      std::cout << "Average value: " << stat.Average() << std::endl;
    \endcode
  */
  template<typename Type>
  class Statistics
  {
  public:

    //! Creates new instance with default capacity of the data set.
    Statistics()
    {
      data_.reserve(100);
    };

    //! Creates new instance with specific capacity of the data set.
    Statistics(size_t initial_capacity)
    {
      data_.reserve(initial_capacity);
    };

    //! Creates new instance with initialized data set.
    Statistics(const std::vector<Type> &data_vector)
    {
      data_.reserve(data_vector.size());
      for (const auto &value : data_vector)
      {
        RawAdd(value);
      }
    };

    //! Checks if there are no data records.
    bool IsEmpty() const
    {
      return data_.empty();
    }

    //! Removes all stored data.
    void Clear()
    {
      data_.clear();
      data_sum_ = Type(0);
      data_min_ = std::numeric_limits<Type>::max();
      data_max_ = std::numeric_limits<Type>::lowest();
    }

    //! Stores a data record in the data set.
    void Add(const Type value)
    {
      if (data_.capacity() == data_.size())
      {
        data_.reserve(2 * data_.capacity());
      }
      data_.push_back(value);
      data_sum_ += value;
      data_min_ = glm::min(value, data_min_);
      data_max_ = glm::max(value, data_max_);
    };

    //! Returns number of stored data records.
    size_t Count() const
    {
      return data_.size();
    };

    //! Returns a sum of all elements in the data set.
    Type Sum() const
    {
      return data_sum_;
    };

    //! Returns average value of the data set.
    Type Average() const
    {
      if (data_.empty())
      {
        return Type(0);
      }
      return data_sum_ / Type(data_.size());
    };

    //! Returns minimal value of the data set.
    Type Min() const
    {
      return data_min_;
    }

    //! Returns maximal value of the data set.
    Type Max() const
    {
      return data_max_;
    }

    //! Prints all statistical values to the string and returns it.
    std::string ToString() const
    {
      std::string text;
      text += "Statistic data: ";
      text += std::to_string(data_.size()) + " records, ";
      text += "sum of elements " + std::to_string(data_sum_) + ", ";
      text += "min " + std::to_string(data_min_) + ", ";
      text += "max " + std::to_string(data_max_) + ", ";
      text += "average " + std::to_string(Average()) + ".";
      return text;
    }

  private:
    std::vector<Type> data_;
    Type data_sum_ = Type(0);
    Type data_min_ = std::numeric_limits<Type>::max();
    Type data_max_ = std::numeric_limits<Type>::lowest();
  };

}

#endif /* !UTILS_STATISTICS_H */