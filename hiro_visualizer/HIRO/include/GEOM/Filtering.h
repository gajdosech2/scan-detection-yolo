/*
  Copyright (C) Skeletex Research, s.r.o. - All Rights Reserved
  Unauthorized copying of this file, via any medium is strictly prohibited
  Proprietary and confidential
*/
#ifndef GEOM_FILTERING_H
#define GEOM_FILTERING_H

#include <memory>
#include <vector>

#include <glm/glm.hpp>

#include <GEOM/API.h>

namespace geom
{

  class GEOM_API KalmanFilterObject
  {
  public:

    KalmanFilterObject();
    KalmanFilterObject(int size);

    ~KalmanFilterObject();

    void SetSize(int size);

    std::vector<glm::vec3> ApplyKalmanFilter(const std::vector<glm::vec3> &values);
    void InitKalmanFilter(glm::vec3 *initVal);
    glm::vec3 NextKalmanFilter(glm::vec3 *nextVal);

  private:
    struct Impl;
    std::unique_ptr<Impl> m;
  };

}


#endif /* !GEOM_FILTERING_H */