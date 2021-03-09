/*
  Copyright (C) Skeletex Research, s.r.o. - All Rights Reserved
  Unauthorized copying of this file, via any medium is strictly prohibited
  Proprietary and confidential
*/
#ifndef UTILS_IDENTIFIABLE_H
#define UTILS_IDENTIFIABLE_H

namespace utils
{
  //! An object that has an id (ideally a strong id).
  template <typename IdType>
  class Identifiable
  {
  public:
    void SetId(IdType new_id)
    {
      id_ = new_id;
    }
    IdType GetId() const
    {
      return id_;
    }

  protected:
    IdType id_;
  };
}

#endif /* !UTILS_IDENTIFIABLE_H */