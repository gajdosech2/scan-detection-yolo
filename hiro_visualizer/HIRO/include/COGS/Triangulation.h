/*
  Copyright (C) Skeletex Research, s.r.o. - All Rights Reserved
  Unauthorized copying of this file, via any medium is strictly prohibited
  Proprietary and confidential
*/
#ifndef COGS_TRIANGULATION_H
#define COGS_TRIANGULATION_H
#include <vector>

#include <glm/gtc/type_ptr.hpp>

#include <COGS/API.h>


namespace cogs
{

  /*!
    \brief A Triangulation is a vector of faces (triplets of indices from a point-cloud).
    \note Independence from a point-cloud is intentional - it is here to enable the case of multiple triangulations of it.
  */
  class COGS_API Triangulation
  {
  public:
    uint32_t GetFaceCount() const;
    uint32_t GetIndexCount() const;

    void SetFaceCount(const uint32_t &new_count);
    void SetIndexCount(const uint32_t &new_count);

    void SetFaces(const std::vector<glm::uvec3> &faces);

    std::vector<glm::uvec3> &GetFaces();
    const std::vector<glm::uvec3> &GetFaces() const;

    uint32_t *GetIndices();
    const uint32_t *GetIndices() const;

  private:
    //! A vector of faces - each face is a triplet of indices into a point-cloud structure.
    std::vector<glm::tvec3<uint32_t>> faces_;
  };

}
#endif /* !COGS_TRIANGULATION_H */