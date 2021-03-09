/*
  Copyright (C) Skeletex Research, s.r.o. - All Rights Reserved
  Unauthorized copying of this file, via any medium is strictly prohibited
  Proprietary and confidential
*/
#ifndef UTILS_CHECK_USER_RIGHTS_H
#define UTILS_CHECK_USER_RIGHTS_H
#include <fstream>

#include <Utils/Filesystem.h>

namespace utils
{
  /*!
    \brief Function returns if the current user has the right to write into the project directory.
  */
  [[nodiscard]]
  inline bool HasPermissionToWriteHere()
  {
    const auto testfile_name = "tester.txt";
    if (std::ofstream(testfile_name).good())
    {
      fs::FileRemove(testfile_name);
      return true;
    }
    return false;
  }
}
#endif /* !UTILS_CHECK_USER_RIGHTS_H */