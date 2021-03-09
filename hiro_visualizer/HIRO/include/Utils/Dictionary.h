/*
  Copyright (C) Skeletex Research, s.r.o. - All Rights Reserved
  Unauthorized copying of this file, via any medium is strictly prohibited
  Proprietary and confidential
*/
#ifndef UTILS_DICTIONARY_H
#define UTILS_DICTIONARY_H
#include <string>
#include <array>
#include <vector>
#include <memory>



namespace utils
{

  //! Enables mapping string keys to string words efficiently.
  class Dictionary
  {
  public:
    Dictionary() = default;

    //! Clears whole database of words and keys.
    void Clear()
    {
      root_.ClearAll();
    }

    //! Checks if there is a word available for a given key.
    bool IsAvailable(const std::string &key) const
    {
      return root_.Find(key.c_str()) != nullptr;
    }

    //! Creates or changes the word of a given key.
    void Set(const std::string &key, const std::string &word)
    {
      auto node = root_.CreateOrFind(key.c_str());
      node->SetWord(word);
    }

    //! Returns a word for a given key. If word for such key does not exists, returns default_word.
    std::string Get(const std::string &key, const std::string &default_word = "") const
    {
      const auto node = root_.Find(key.c_str());
      return (node == nullptr) ? default_word : node->GetWord();
    }

    //! Removes word for a given key. Results in true if an existing word was cleared.
    bool Remove(const std::string &key)
    {
      const auto node = root_.Find(key.c_str());
      if (node == nullptr)
      {
        return false;
      }
      return node->ClearWord();
    }

    //! Returns all stored words.
    std::vector<std::string> GetAllWords() const
    {
      std::vector<std::string> result;
      root_.CumulateWords(result);
      return result;
    }

    //! Returns all stored words whose key starts with defined key_prefix.
    std::vector<std::string> GetAllWords(const std::string &key_prefix) const
    {
      std::vector<std::string> result;
      root_.CumulateWords(key_prefix.c_str(), result);
      return result;
    }

  private:

    class Node
    {
    public:
      Node() = default;

      Node(Node *parent)
        : parent_(parent)
      {
      }

      void ClearAll()
      {
        for (auto &c : child_)
        {
          c.reset();
        }
      }

      const Node *Find(const char *key) const
      {
        if (*key == '\0')
        {
          return this;
        }
        const auto child_id = CharToChildId(*key);
        const auto child = child_[child_id].get();
        return (child == nullptr) ? nullptr : child->Find(key + 1);
      }

      Node *Find(const char *key)
      {
        if (*key == '\0')
        {
          return this;
        }
        const auto child_id = CharToChildId(*key);
        const auto child = child_[child_id].get();
        return (child == nullptr) ? nullptr : child->Find(key + 1);
      }

      Node *CreateOrFind(const char *key)
      {
        if (*key == '\0')
        {
          return this;
        }
        const auto child_id = CharToChildId(*key);
        if (child_[child_id] == nullptr)
        {
          child_[child_id] = std::make_unique<Node>(this);
        }
        return child_[child_id]->CreateOrFind(key + 1);
      }

      const std::string &GetWord() const
      {
        return word_;
      }

      void SetWord(const std::string &val)
      {
        word_ = val;
      }

      bool ClearWord()
      {
        if (word_.empty())
        {
          return false;
        }
        word_.clear();
        if (!HasAnyChildren() && parent_ != nullptr)
        {
          parent_->DestroyChild(this);
        }
        return true;
      }

      void CumulateWords(std::vector<std::string> &result) const
      {
        if (!word_.empty())
        {
          result.push_back(word_.c_str());
        }
        for (auto &child : child_)
        {
          if (child != nullptr)
          {
            child->CumulateWords(result);
          }
        }
      }

      bool HasAnyChildren() const
      {
        for (const auto &ch : child_)
        {
          if (ch != nullptr)
          {
            return true;
          }
        }
        return false;
      }

      void DestroyChild(Node *child)
      {
        for (auto &c : child_)
        {
          if (child == c.get())
          {
            c.reset();
          }
        }
        if (!HasAnyChildren() && parent_ != nullptr)
        {
          parent_->DestroyChild(this);
        }
      }

      void CumulateWords(const char *key_prefix, std::vector<std::string> &result) const
      {
        if (*key_prefix == '\0')
        {
          CumulateWords(result);
        }
        else
        {
          const auto child_id = CharToChildId(*key_prefix);
          if (child_[child_id] != nullptr)
          {
            child_[child_id]->CumulateWords(key_prefix + 1, result);
          }
        }
      }

    private:
      Node *parent_ = nullptr;
      std::string word_;
      std::array<std::unique_ptr<Node>, 94> child_;
      static size_t CharToChildId(char c)
      {
        if (c < 32 || c > 126)
        {
          throw std::invalid_argument("Unsupported character in dictionary key.");
        }
        return c - 32;
      }
    };

    Node root_;
  };


}
#endif /* !UTILS_DICTIONARY_H */