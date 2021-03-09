#ifndef UTILS_SCANNER_DEFINITIONS_H
#define UTILS_SCANNER_DEFINITIONS_H
#include <Utils/ScannerParams.h>



namespace utils
{
  //! Scanner parameter definition for PhoXi XS device.
  const ScannerParams PHOXI_XS = []()
  {
    ScannerParams phoxi_xs;
    phoxi_xs.resolution = glm::uvec2(2064, 1544);
    phoxi_xs.fx = 3626.18f;
    phoxi_xs.fy = 3627.91f;
    phoxi_xs.cx = 1188.59f;
    phoxi_xs.cy = 684.239f;
    phoxi_xs.baseline = 85.0f;
    phoxi_xs.camera_angle = 0.0f;
    phoxi_xs.projector_angle = 17.0f;
    phoxi_xs.projector_fovx = 47.5f;
    phoxi_xs.projector_fovy = 36.0f;
    phoxi_xs.near_range = 161.0f;
    phoxi_xs.far_range = 205.0f;
    return phoxi_xs;
  }
  ();

  //! Scanner parameter definition for PhoXi S device.
  const ScannerParams PHOXI_S = []()
  {
    ScannerParams phoxi_s;
    phoxi_s.resolution = glm::uvec2(2064, 1544);
    phoxi_s.fx = 2245.92f;
    phoxi_s.fy = 2246.5f;
    phoxi_s.cx = 1042.98f;
    phoxi_s.cy = 772.933f;
    phoxi_s.baseline = 230.0f;
    phoxi_s.camera_angle = 15.45f;
    phoxi_s.projector_angle = 15.45f;
    phoxi_s.projector_fovx = 47.5f;
    phoxi_s.projector_fovy = 36.0f;
    phoxi_s.near_range = 384.0f;
    phoxi_s.far_range = 520.0f;
    return phoxi_s;
  }
  ();

  //! Scanner parameter definition for PhoXi M device.
  const ScannerParams PHOXI_M = []()
  {
    ScannerParams phoxi_m;
    phoxi_m.resolution = glm::uvec2(2064, 1544);
    phoxi_m.fx = 2268.68f;
    phoxi_m.fy = 2268.88f;
    phoxi_m.cx = 1032.65f;
    phoxi_m.cy = 799.183f;
    phoxi_m.baseline = 350.0f;
    phoxi_m.camera_angle = 11.75f;
    phoxi_m.projector_angle = 11.75f;
    phoxi_m.projector_fovx = 47.5f;
    phoxi_m.projector_fovy = 36.0f;
    phoxi_m.near_range = 458.0f;
    phoxi_m.far_range = 1118.0f;
    return phoxi_m;
  }
  ();

  //! Scanner parameter definition for PhoXi L device.
  const ScannerParams PHOXI_L = []()
  {
    ScannerParams phoxi_l;
    phoxi_l.resolution = glm::uvec2(2064, 1544);
    phoxi_l.fx = 2263.31f;
    phoxi_l.fy = 2263.29f;
    phoxi_l.cx = 1054.4f;
    phoxi_l.cy = 770.566f;
    phoxi_l.baseline = 550.0f;
    phoxi_l.camera_angle = 9.45f;
    phoxi_l.projector_angle = 9.45f;
    phoxi_l.projector_fovx = 47.5f;
    phoxi_l.projector_fovy = 36.0f;
    phoxi_l.near_range = 870.0f;
    phoxi_l.far_range = 2150.0f;
    return phoxi_l;
  }
  ();

  //! Scanner parameter definition for PhoXi XL device.
  const ScannerParams PHOXI_XL = []()
  {
    ScannerParams phoxi_xl;
    phoxi_xl.resolution = glm::uvec2(2064, 1544);
    phoxi_xl.fx = 2245.37f;
    phoxi_xl.fy = 2244.88f;
    phoxi_xl.cx = 998.051f;
    phoxi_xl.cy = 756.269f;
    phoxi_xl.baseline = 850.0f;
    phoxi_xl.camera_angle = 7.5f;
    phoxi_xl.projector_angle = 7.5f;
    phoxi_xl.projector_fovx = 47.5f;
    phoxi_xl.projector_fovy = 36.0f;
    phoxi_xl.near_range = 1680.0f;
    phoxi_xl.far_range = 3780.0f;
    return phoxi_xl;
  }
  ();

}
#endif /* !UTILS_SCANNER_DEFINITIONS_H */