/*
  Copyright (C) Skeletex Research, s.r.o. - All Rights Reserved
  Unauthorized copying of this file, via any medium is strictly prohibited
  Proprietary and confidential
*/
#ifndef UTILS_EXT_STD_H
#define UTILS_EXT_STD_H
#include <optional>
#include <vector>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <cmath>

#include <iostream>
#include <fstream>
#include <algorithm>
#include <iomanip>

#include <locale>
#include <functional>

#include <string>
#include <sstream>
#include <regex>
#include <iterator>
#include <numeric>



//! Extensions to the standard libraries.
namespace std_ext
{

  const std::string WHITESPACES = " \t\n\r\f\v";


  inline void StringTo(const std::string &str, float &out)
  {
    out = std::stof(str);
  }
  inline void StringTo(const std::string &str, double &out)
  {
    out = std::stod(str);
  }
  inline void StringTo(const std::string &str, int32_t &out)
  {
    out = std::stoi(str);
  }
  inline void StringTo(const std::string &str, int64_t &out)
  {
    out = std::stol(str);
  }
  inline void StringTo(const std::string &str, uint32_t &out)
  {
    out = static_cast<unsigned>(std::stoul(str));
  }
  inline void StringTo(const std::string &str, uint64_t &out)
  {
    out = std::stoul(str);
  }

  /*!
    \brief Convert single-byte std::string to std::wstring.
    \warning This only works if all the characters are single byte, i.e. ASCII or ISO-8859-1. Anything multi-byte will fail miserably, including UTF-8. (https://stackoverflow.com/a/8969776/2621721)
  */
  inline std::wstring ToWString(const std::string &text)
  {
    return std::wstring(text.begin(), text.end());
  }

  //! Convert std::wstring to std::string.
  inline std::string ToStdString(const std::wstring &text)
  {
    return std::string(text.begin(), text.end());
  }

  //! Counts how many of specified key_to_search substrings does text contain.
  inline size_t CountOccurrences(const std::string &text, const std::string &key_to_search)
  {
    size_t count = 0;
    for (size_t found_at_pos = 0; ; found_at_pos += key_to_search.length())
    {
      found_at_pos = text.find(key_to_search, found_at_pos);
      if (found_at_pos == std::string::npos)
      {
        break;
      }
      count++;
    }
    return count;
  }

  //! Counts how many of specified key_to_search substrings does text contain in a specific range.
  inline size_t CountOccurrences(const std::string &text, const std::string &key_to_search, const size_t &off, const size_t &length)
  {
    if (length < key_to_search.length())
    {
      return size_t(0);
    }
    size_t count = 0;
    auto last_pos = off + length - key_to_search.length();
    for (size_t found_at_pos = off; ; found_at_pos += key_to_search.length())
    {
      found_at_pos = text.find(key_to_search, found_at_pos);
      if (found_at_pos == std::string::npos || found_at_pos >= last_pos)
      {
        break;
      }
      count++;
    }
    return count;
  }

  //! Replaces all occurrences of key_to_search with replace_text in specified text.
  inline std::string Replace(const std::string &text, const std::string &key_to_search, const std::string &replace_text)
  {
    std::string result = text;
    for (size_t found_at_pos = 0; ; found_at_pos += replace_text.length())
    {
      found_at_pos = result.find(key_to_search, found_at_pos);
      if (found_at_pos == std::string::npos)
      {
        break;
      }
      result.replace(found_at_pos, key_to_search.length(), replace_text);
    }
    return result;
  }

  /*!
    \brief Replaces all occurrences of key_to_search with replace_text in specified text.
    \param replacement_map Contains pairs of <key_to_search, replace_text>.
  */
  inline std::string Replace(const std::string &text, const std::map<std::string, std::string> &replacement_map)
  {
    std::string result = text;
    for (const auto &mapped : replacement_map)
    {
      result = Replace(result, mapped.first, mapped.second);
    }
    return result;
  }

  //! Replaces all occurrences of old_elem in a vector with a new_elem.
  template <typename T>
  inline void Replace(std::vector<T> &vector, const T old_elem, const T new_elem)
  {
    for (unsigned int i = 0; i < vector.size(); i++)
    {
      if (vector[i] == old_elem)
      {
        vector[i] = new_elem;
      }
    }
  }

  //! Converts bool to string ("true" or "false").
  inline std::string BoolToString(const bool value)
  {
    return value ? "true" : "false";
  }

  /*!
    \brief
      Converts double to string with decimal digits until max_digits are reached.
    \param value
      Value which will be converted to string.
    \param max_digits
      Value that represents maximum number of decimal digits that will be converted.
  */
  inline std::string ToStringAutoPrecision(const double value, int max_digits = 6)
  {
    unsigned uvalue = static_cast<unsigned>(std::round(std::abs(value * std::pow(10, max_digits))));
    while (uvalue % 10 == 0)
    {
      uvalue /= 10;
      max_digits--;
    }

    std::string result;
    if (uvalue > 0)
    {
      while (uvalue > 0 && max_digits > 0)
      {
        result += ('0' + uvalue % 10);

        uvalue /= 10;
        max_digits--;
      }
      while (max_digits-- > 0)
      {
        result += "0";
      }
    }
    std::reverse(result.begin(), result.end());
    if (result.empty())
    {
      result = std::to_string(static_cast<int>(value));
    }
    else if (static_cast<int>(value) != 0)
    {
      result = std::to_string(static_cast<int>(value)) + "." + result;
    }
    else
    {
      result = value > 0.0 ? "0." + result : "-0." + result;
    }
    return result;
  }

  //! Converts type to string with specified number of decimal digits.
  template <typename T>
  inline std::string ToStringWithPrecision(const T value, const int n = 6)
  {
    std::ostringstream out;
    out << std::setprecision(n) << value;
    return out.str();
  }

  //! Converts int to string with zeros at the beginning to match specified number of digits.
  template <typename T>
  inline std::string ToStringWithZeroes(const T value, const int n = 6)
  {
    std::stringstream ss;
    ss << std::setw(n) << std::setfill('0') << value;
    return ss.str();
  }

  //! Converts all values in the vector to a string and joins them using specified separator.
  template <typename T>
  inline std::string ToString(const std::vector<T> &container, const std::string &separator = ", ")
  {
    std::string result;
    for (auto i = 0; i < container.size(); i++)
    {
      result += std::to_string(container[i]);
      if (i < container.size() - 1)
      {
        result += separator;
      }
    }
    return result;
  }

  //! Joins all values in a string vector using specified separator.
  inline std::string ToString(const std::vector<std::string> &container, const std::string &separator = ", ")
  {
    std::string result;
    for (size_t i = 0; i < container.size(); i++)
    {
      result += container[i];
      if (i < container.size() - 1)
      {
        result += separator;
      }
    }
    return result;
  }

  /*!
    \brief Converts a numeric value to string using thousand separators.

    Example:
      10235 => "10'235"
      1000000000 => 1'000'000'000
  */
  template<typename T>
  inline std::string ToStringWithThousandSeparators(const T &input)
  {
    std::stringstream temp_stream;
    temp_stream.imbue(std::locale(""));
    temp_stream << input;
    return temp_stream.str();
  }

  //! Converts text into all uppercase.
  inline void MakeUppercase(char *text)
  {
    std::transform(text, text + strlen(text), text, [](char c) {return static_cast<char>(::toupper(c)); });
  }

  //! Converts text into all uppercase.
  inline void MakeUppercase(std::string &text)
  {
    MakeUppercase(const_cast<char *>(text.c_str()));
  }

  //! Converts text into all uppercase.
  inline std::string Uppercase(const std::string &text)
  {
    std::string upper = text;
    std::transform(upper.begin(), upper.end(), upper.begin(), ::toupper);
    return upper;
  }

  //! Converts text into all lowercase.
  inline void MakeLowercase(char *text)
  {
    std::transform(text, text + strlen(text), text, [](char c) {return static_cast<char>(::towlower(c)); });
  }

  //! Converts text into all lowercase.
  inline void MakeLowercase(std::string &text)
  {
    MakeLowercase(const_cast<char *>(text.c_str()));
  }

  //! Converts text into all lowercase.
  inline std::string Lowercase(const std::string &text)
  {
    std::string lower = text;
    std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);
    return lower;
  }

  //! Checks if the text ends with a string.
  inline bool EndsWith(const std::string &ending, const std::string &text)
  {
    return
      ending.size() <= text.size() &&
      std::equal(ending.rbegin(), ending.rend(), text.rbegin());
  }

  //! Checks if the text contains substring.
  inline bool Contains(const std::string &substring, const std::string &text)
  {
    return text.find(substring) != std::string::npos;
  }

  //! Checks if the text contains character.
  inline bool Contains(const char character, const std::string &text)
  {
    return text.find(character) != std::string::npos;
  }

  /*!
    \brief Replaces a patter in specified string with a number.
    \note Example: ("example-###", "#", 2)  --> "example-002"
  */
  inline std::string ReplacePatternWithNumber(const std::string &base_string, const std::string &pattern, const int number)
  {
    const auto regex = std::regex("(" + pattern + ")+");

    const auto it_begin = std::sregex_iterator(base_string.begin(), base_string.end(), regex);
    const auto it_end = std::sregex_iterator();

    auto res_string = base_string;
    for (std::sregex_iterator i = it_begin; i != it_end; ++i)
    {
      const std::string match_str = i->str();
      res_string = std::regex_replace(res_string, std::regex(match_str), ToStringWithZeroes(number, static_cast<int>(match_str.length())), std::regex_constants::format_first_only);
    }

    return res_string;
  }

  //! Check if the initializer list contains an element.
  template <typename T>
  bool Contains(const T &element, const std::initializer_list<T> &list)
  {
    return std::find(list.begin(), list.end(), element) != list.end();
  }

  //! Check if the vector contains an element.
  template <typename Type>
  bool Contains(const Type &element, const std::vector<Type> &vector)
  {
    return std::find(vector.begin(), vector.end(), element) != vector.end();
  }

  //! If an element exists in the vector, returns its index.
  template <typename Type>
  std::optional<size_t> GetIndex(const Type element, const std::vector<Type> &vector)
  {
    const auto found_element = std::find(vector.begin(), vector.end(), element);
    if (found_element == vector.end())
    {
      return std::nullopt;
    }
    return found_element - vector.begin();
  }

  //! Check if the set contains an element.
  template <typename Type>
  bool Contains(const Type element, const std::set<Type> &set)
  {
    return !set.empty() && set.find(element) != set.end();
  }

  //! Check if an unordered_set contains an element.
  template <typename T1, typename T2>
  bool Contains(const T1 element, const std::unordered_set<T1, T2> &set)
  {
    return set.find(element) != set.end();
  }

  //! Check if the mat contains an element.
  template <typename T1, typename T2>
  bool Contains(const T1 element, const std::map<T1, T2> &map)
  {
    return map.find(element) != map.end();
  }

  //! Check if an unordered_map contains an element.
  template <typename T1, typename T2>
  bool Contains(const T1 element, const std::unordered_map<T1, T2> &map)
  {
    return map.find(element) != map.end();
  }

  //! Check if there is at least a single common element in two vectors.
  template <typename Type>
  bool ContainsCommonElement(const std::vector<Type> &elements1, const std::set<Type> &elements2)
  {
    return AnyOf(elements1, [&elements2](const auto & el) { return elements2.find(el) != elements2.end(); });
  }

  //! Sorts the array and removes duplicate elements.
  template <typename Type>
  void SortAndRemoveDuplicates(std::vector<Type> &vec)
  {
    std::sort(vec.begin(), vec.end());
    vec.erase(std::unique(vec.begin(), vec.end()), vec.end());
  }

  //! Returns vector similar to input, but without duplicate elements.
  template <typename Type>
  std::vector<Type> RemoveDuplicates(std::vector<Type> &vector)
  {
    std::vector<Type> res;
    res.reserve(vector.size());
    for (unsigned i = 0; i < vector.size(); i++)
    {
      if (!Contains(vector[i], res))
      {
        res.push_back(vector[i]);
      }
    }
    return res;
  }

  //! Removes an element from the vector. Returns success.
  template <typename Type>
  bool Erase(const Type &element, std::vector<Type> &vector)
  {
    const std::optional<size_t> loc = GetIndex(element, vector);
    if (loc.has_value())
    {
      vector.erase(vector.begin() + loc.value());
    }
    return loc.has_value();
  }

  //! Removes an element with from the set. Returns success.
  template <typename Type>
  bool Erase(const Type &element, std::set<Type> &set)
  {
    if (Contains(element, set))
    {
      set.erase(element);
      return true;
    }
    return false;
  }

  //! Collect all indices of elements in a vector with a specified value.
  template <typename IndicesType, typename Type>
  std::vector<IndicesType> CollectIndices(const std::vector<Type> &vector, const Type value)
  {
    std::vector<IndicesType> indices;
    for (IndicesType i = 0; i < static_cast<IndicesType>(vector.size()); ++i)
    {
      if (vector[i] == value)
      {
        indices.emplace_back(i);
      }
    }
    return indices;
  }

  //! Execute a function for every element in the container.
  template <typename T, typename F>
  inline void Foreach(const T &container, const F &Function)
  {
    std::for_each(container.begin(), container.end(), Function);
  }

  //! Finds a maximum value in a vector, return an iterator pointing to it.
  template <typename T>
  [[nodiscard]]
  inline auto MaxIt(const std::vector<T> &vector)
  {
    return std::max_element(vector.begin(), vector.end());
  }

  //! Finds a minimal value in a vector, return an iterator pointing to it.
  template <typename T>
  [[nodiscard]]
  inline auto MinIt(const std::vector<T> &vector)
  {
    return std::min_element(vector.begin(), vector.end());
  }

  //! Finds a maximum value in a vector.
  template <typename T>
  [[nodiscard]]
  inline T Max(const std::vector<T> &vector)
  {
    return *MaxIt(vector);
  }

  //! Finds a minimal value in a vector.
  template <typename T>
  [[nodiscard]]
  inline T Min(const std::vector<T> &vector)
  {
    return *MinIt(vector);
  }

  //! Finds a maximum value from a single element. Boundary case for the variadic expansion.
  template <typename T>
  [[nodiscard]]
  inline T Max(const T val)
  {
    return val;
  }

  //! Finds a maximum value from variadic argument list.
  template <typename T, typename ... TS>
  [[nodiscard]]
  T Max(const T val1, const T val2, const TS ... vals)
  {
    return Max(val1 > val2 ? val1 : val2, vals...);
  }

  //! Finds a minimal value from a single element. Boundary case for the variadic expansion.
  template <typename T>
  [[nodiscard]]
  inline T Min(const T val)
  {
    return val;
  }

  //! Finds a minimal value from variadic argument list.
  template <typename T, typename... TS>
  [[nodiscard]]
  inline T Min(const T val1, const T val2, const TS ... vals)
  {
    return Min(val1 < val2 ? val1 : val2, vals ...);
  }

  //! Finds the object in a vector, which when transformed by a function gives a maximum value.
  template <typename T, typename F>
  [[nodiscard]]
  inline auto Max(const std::vector<T> &vector, const F &Function)
  {
    return *std::max_element(vector.begin(), vector.end(), [&](T const & lhs, T const & rhs) { return Function(lhs) < Function(rhs); });
  }

  //! Finds the object in a vector, which when transformed by a function gives a minimal value.
  template <typename T, typename F>
  [[nodiscard]]
  inline auto Min(const std::vector<T> &vector, const F &Function)
  {
    return *std::min_element(vector.begin(), vector.end(), [&](T const & lhs, T const & rhs) { return Function(lhs) < Function(rhs); });
  }

  //! Finds a maximum value transformed by a function in a vector.
  template <typename T, typename F>
  [[nodiscard]]
  inline auto MaxValue(const std::vector<T> &vector, const F &Function)
  {
    return Function(Max(vector, Function));
  }

  //! Finds a minimal value transformed by a function in a vector.
  template <typename T, typename F>
  [[nodiscard]]
  inline auto MinValue(const std::vector<T> &vector, const F &Function)
  {
    return Function(Min(vector, Function));
  }

  //! Finds a middle (average of min, max) value transformed by a function in a vector.
  template <typename T, typename F>
  [[nodiscard]]
  inline auto MiddleValue(const std::vector<T> &vector, const F &Function)
  {
    const auto min_value = MinValue(vector, Function);
    const auto max_value = MaxValue(vector, Function);
    return (min_value + max_value) / 2.0f;
  }

  //! Wrapper for std::accumulate.
  template <typename T>
  [[nodiscard]]
  inline auto Accumulate(const std::vector<T> &vector, const T start_value)
  {
    return std::accumulate(vector.begin(), vector.end(), start_value);
  }

  //! Sum all elements in a vector.
  template <typename T>
  [[nodiscard]]
  inline auto Sum(const std::vector<T> &vector)
  {
    return Accumulate(vector, static_cast<T>(0));
  }

  //! Compute average element of a vector. In case of empty vector, return 0.
  template <typename T>
  [[nodiscard]]
  inline auto Average(const std::vector<T> &vector)
  {
    return vector.empty()
      ? static_cast<T>(0)
      : Sum(vector) * (1.0f / vector.size());
  }

  /*!
    \brief Wrapper for std::accumulate - https://en.cppreference.com/w/cpp/algorithm/accumulate - values transformed by a function.
    \note This will make a sum of every element of the input vector transformed by a function plus the initial element.
    \param vector The input vector (will be transformed by a function).
    \param initial_value The initial_value will be added to the resulting sum.
    \param function The function that will transform every element of the vector.
  */
  template <typename T, typename F>
  [[nodiscard]]
  inline auto Accumulate(const std::vector<T> &vector, const T initial_value, const F &function)
  {
    return std::accumulate(vector.begin(), vector.end(), initial_value, [&function](const T total, const T value)->T { return function(value) + total; });
  }

  //! Sum all elements in a vector transformed by a function.
  template <typename T, typename F>
  [[nodiscard]]
  inline auto Sum(const std::vector<T> &vector, const F &function)
  {
    return Accumulate(vector, static_cast<T>(0), function);
  }

  //! Compute average element of a vector transformed by a function. In case of empty vector, return 0.0f.
  template <typename T, typename F>
  [[nodiscard]]
  inline float Average(const std::vector<T> &vector, const F &function)
  {
    return vector.empty()
      ? 0.0f
      : Sum(vector, function) / static_cast<float>(vector.size());
  }

  //! Compute median value of a vector. In case of empty vector, return 0.
  template <typename T>
  [[nodiscard]]
  inline auto Median(const std::vector<T> &vector)
  {
    if (vector.empty())
    {
      return static_cast<T>(0);
    }

    auto vec = vector;
    const size_t n = vec.size() / 2;
    std::nth_element(vec.begin(), vec.begin() + n, vec.end());
    return vec[n];
  }


  //! Insert the source vector to the back of target vector.
  template <typename T, typename S>
  void InsertBack(T &target, const S &source)
  {
    target.insert(target.end(), source.begin(), source.end());
  }

  //! Insert the source vector to the front of target vector.
  template <typename T, typename S>
  void InsertFront(T &target, const S &source)
  {
    target.insert(target.begin(), source.begin(), source.end());
  }

  //! Insert the source container to the target container.
  template <typename T, typename S>
  void InsertTo(T &target, const S &source)
  {
    target.insert(source.begin(), source.end());
  }


  //! Emplace back an element if it is unique to the vector.
  template <typename Type>
  void EmplaceBackUnique(const Type &element, std::vector<Type> &vector)
  {
    if (!Contains(element, vector))
    {
      vector.emplace_back(element);
    }
  }


  //! Trims characters from beginning of string (left).
  inline std::string &TrimBegin(std::string &s, const std::string &t = WHITESPACES)
  {
    s.erase(0, s.find_first_not_of(t));
    return s;
  }

  //! Trims characters from end of string (right).
  inline std::string &TrimEnd(std::string &s, const std::string &t = WHITESPACES)
  {
    s.erase(s.find_last_not_of(t) + 1);
    return s;
  }

  //! Trims from both ends of string (left & right).
  inline std::string &Trim(std::string &s, const std::string &t = WHITESPACES)
  {
    TrimBegin(s, t);
    TrimEnd(s, t);
    return s;
  }

  //! Trim the end of a string to removes forward and backward slashes (/, \) and add one single forward slash /.
  inline std::string EndWithASingleSlash(const std::string &s)
  {
    auto result = s;
    TrimEnd(result, "/\\");
    return result + "/";
  }

  //! Parses the input text to sub strings by a given list of separators.
  inline std::vector<std::string> Parse(const std::string &text, const std::string &separators = WHITESPACES)
  {
    std::vector<std::string> result;
    result.reserve(text.length());
    size_t last_end_pos = 0;
    while (true)
    {
      auto start_pos = text.find_first_not_of(separators, last_end_pos);
      if (start_pos == std::string::npos)
      {
        break;
      }
      last_end_pos = text.find_first_of(separators, start_pos);
      auto length = last_end_pos - start_pos;
      result.emplace_back(text.substr(start_pos, length));
    }
    result.shrink_to_fit();
    return result;
  }



  //! Reads a value from the binary stream, number of bytes red is determined by a template type.
  template <typename T>
  inline void Read(T &val, std::istream &str)
  {
    str.read(reinterpret_cast<char *>(&val), sizeof(T));
  }

  //! Reads a value from the binary stream, number of bytes red is determined by a template type.
  template <typename T>
  inline T Read(std::istream &str)
  {
    T val;
    str.read(reinterpret_cast<char *>(&val), sizeof(T));
    return val;
  }

  //! Writes a value to the binary stream, bytes written are determined by a template type.
  template <typename T>
  inline void Write(const T val, std::ostream &str)
  {
    str.write(reinterpret_cast<const char *>(&val), sizeof(T));
  }

  inline void Read(std::string &, std::istream &)
  {
    throw std::invalid_argument("Function std_ext::Read() cannot be used for reading strings. Use std_ext::ReadString() instead.");
  }

  inline void Write(const std::string &, std::ostream &)
  {
    throw std::invalid_argument("Function std_ext::Write() cannot be used for writing strings. Use std_ext::WriteString() instead.");
  }

  //! Reads a string from the binary stream.
  inline void ReadString(std::string &text, std::istream &str)
  {
    unsigned int len = 0u;
    str.read((char *)&len, sizeof(unsigned int));
    char *temp = new char[len + 1];
    str.read(temp, len);
    temp[len] = '\0';
    text = temp;
    delete[] temp;
  }

  //! Reads a value from the binary stream, number of bytes red is determined by a template type.
  inline std::string ReadString(std::istream &str)
  {
    std::string val;
    ReadString(val, str);
    return val;
  }

  //! Writes a value to the binary stream, number of bytes written is determined by a template type.
  inline void WriteString(const std::string &text, std::ostream &str)
  {
    auto len = unsigned(text.size());
    str.write((char *)&len, sizeof(unsigned));
    str.write(text.c_str(), text.size());
  }



  //! Simplified wrapper for std::find.
  template<class C, class T>
  [[nodiscard]]
  auto Find(C &container, const T &value)
  {
    return std::find(container.begin(), container.end(), value);
  }

  //! Simplified wrapper for std::transform.
  template<class C, class F>
  [[nodiscard]]
  auto Transformed(const C &container, F Function)
  {
    std::vector<decltype(Function(std::declval<typename C::value_type>()))> result;
    std::transform(container.begin(), container.end(), std::back_inserter(result), Function);
    return result;
  }

  //! Simplified wrapper for std::all_of.
  template<class C, class P>
  [[nodiscard]]
  auto AllOf(const C &container, const P &Predicate)->bool
  {
    return std::all_of(container.begin(), container.end(), Predicate);
  }

  //! Simplified wrapper for std::any_of.
  template<class C, class P>
  [[nodiscard]]
  auto AnyOf(const C &container, const P &Predicate)->bool
  {
    return std::any_of(container.begin(), container.end(), Predicate);
  }

  //! Simplified wrapper for std::any_of (writable).
  template<class C, class P>
  [[nodiscard]]
  auto AnyOfW(C &container, const P &Predicate)->bool
  {
    return std::any_of(container.begin(), container.end(), Predicate);
  }

  //! Simplified wrapper for std::none_of.
  template<class C, class P>
  [[nodiscard]]
  auto NoneOf(const C &container, const P &Predicate)->bool
  {
    return std::none_of(container.begin(), container.end(), Predicate);
  }

  //! Simplified wrapper for std::count.
  template<class C, class T>
  [[nodiscard]]
  auto Count(const C &container, const T &val)
  {
    return std::count(container.begin(), container.end(), val);
  }

  //! Simplified wrapper for std::count_if.
  template<class C, class P>
  [[nodiscard]]
  auto CountIf(const C &container, const P &Predicate)
  {
    return std::count_if(container.begin(), container.end(), Predicate);
  }

  //! Simplified wrapper for std::find_if.
  template<class C, class P>
  [[nodiscard]]
  auto FindIf(C &container, const P &Predicate)
  {
    return std::find_if(container.begin(), container.end(), Predicate);
  }

  //! Simplified wrapper for reversed std::find_if.
  template<class C, class P>
  [[nodiscard]]
  auto RevFindIf(C &container, const P &Predicate)
  {
    return std::find_if(container.rbegin(), container.rend(), Predicate);
  }

  /*!
    \brief Simplified wrapper for std::find_if that expects a vector of pointers as input and returns a pointer.
    \note The motivation is instead of returning an iterator to a pointer, to return the pointer itself or null.
    \return Return the pointer itself if found, else it returns null pointer.
  */
  template<class C, class P>
  [[nodiscard]]
  auto FindIfPtr(C &container, const P &Predicate)
  {
    const auto it = std::find_if(container.begin(), container.end(), Predicate);
    return it == container.end()
      ? nullptr
      : *it;
  }

  //! Simplified wrapper for std::remove_if and std::erase.
  template<class C, class P>
  auto EraseIf(C &container, const P &Predicate)
  {
    auto rem = std::remove_if(container.begin(), container.end(), Predicate);
    container.erase(rem, container.end());
  }

  //! Copies all elements fulfilling a given condition into a new vector. Uses std::copy_if.
  template<class C, class P>
  [[nodiscard]]
  auto SelectIf(const C &container, const P &Predicate)
  {
    C result;
    std::copy_if(container.begin(), container.end(), std::back_inserter(result), Predicate);
    return result;
  }

  /*!
    \brief Partitions all elements based on a given condition.
    \note Uses std::partition_copy.
    \return A pair of container. The first contains all elements that satisfy the condition, the second all elements that do not.
  */
  template<class C, class P>
  [[nodiscard]]
  std::pair<C, C> Partition(const C &container, const P &Predicate)
  {
    C result_true;
    C result_false;
    std::partition_copy(container.begin(), container.end(), std::back_inserter(result_true), std::back_inserter(result_false), Predicate);
    return std::make_pair(result_true, result_false);
  }

  /*!
    \brief Finds all intervals on the vector where a given condition holds.
    \return A vector of interval indices pairs.
  */
  template<class T, class P>
  [[nodiscard]]
  std::vector<std::pair<size_t, size_t>> FindIntervals(const std::vector<T> &vec, const P &Predicate)
  {
    std::vector<std::pair<size_t, size_t>> intervals;
    std::optional<size_t> interval_start = std::nullopt;

    for (size_t i = 0; i < vec.size(); i++)
    {
      if (Predicate(vec[i]))
      {
        if (!interval_start)
        {
          interval_start = i;
        }
      }
      else if (interval_start)
      {
        intervals.emplace_back(std::make_pair(*interval_start, i - 1));
        interval_start = std::nullopt;
      }
    }

    return intervals;
  }

  template<typename T>
  std::vector<T> Joined(const std::vector<std::vector<T>> &vector_of_vectors)
  {
    std::vector<T> result;
    for (const auto &vec : vector_of_vectors)
    {
      InsertBack(result, vec);
    }
    return result;
  }

  template<typename T, typename F>
  std::vector<T> JoinTransformed(const std::vector<std::vector<T>> &vector_of_vectors, const F &Function)
  {
    std::vector<T> result;
    for (const auto &vec : vector_of_vectors)
    {
      InsertBack(result, Transformed(vec, Function));
    }
    return result;
  }

  //! Creates binding for an object method with a single argument.
  template<typename F, typename O>
  inline auto Bind1(F method, O object)
  {
    return std::bind(method, object, std::placeholders::_1);
  }


  //! Check std::string for non-ASCII characters.
  inline bool IsASCII(const std::string &s)
  {
    return AllOf(s, [](unsigned char c)
    {
      return isprint(c);
    });
  }
}

#endif /* !UTILS_EXT_STD_H */