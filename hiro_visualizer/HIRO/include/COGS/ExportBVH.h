/*
  Copyright (C) Skeletex Research, s.r.o. - All Rights Reserved
  Unauthorized copying of this file, via any medium is strictly prohibited
  Proprietary and confidential
*/
#ifndef COGS_EXPORT_BVH_H
#define COGS_EXPORT_BVH_H
#define GLM_FORCE_RADIANS

#include <glm/glm.hpp>
#include <vector>
#include <string>

#include <COGS/API.h>

namespace cogs
{
  class Skeleton;
}

namespace cogs
{

  //! Exports skeleton bone hierarchy to BVH file.
  bool COGS_API ExportBVH( const std::string &filename, const cogs::Skeleton &skeleton);

}
#endif /* !COGS_EXPORT_BVH_H */