#ifndef GEOM_QUADRICS_H
#define GEOM_QUADRICS_H
#include <Eigen/Core>

namespace geom
{
  namespace quadrics
  {
    double f(Eigen::VectorXf Coeff, Eigen::VectorXf Q);
    Eigen::VectorXf nablaf(Eigen::VectorXf Coeff, Eigen::VectorXf Q);
    Eigen::VectorXf SurfacePoint(Eigen::VectorXf P, Eigen::VectorXf Coeff, double epsilon);
    Eigen::VectorXf FootPoint(Eigen::VectorXf P, Eigen::VectorXf Coeff, double epsilon);
    Eigen::VectorXf SolveSystem(Eigen::MatrixXf points, Eigen::MatrixXf normals, Eigen::VectorXf wPoints, Eigen::VectorXf wNormals);
  }
}
#endif /* !GEOM_QUADRICS_H */