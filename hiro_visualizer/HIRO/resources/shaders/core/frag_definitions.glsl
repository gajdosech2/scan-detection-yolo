#include "api_frag.glsl"
#include "include/texturing.glsl"


/// INPUT
layout (location = 0) in flat uint in_is_back_facing;
layout (location = 1) in Vertex in_vert;

/// UNIFORMS
layout (binding = 0) uniform sampler2D albedo_map;
layout (binding = 1) uniform sampler2D normal_map;

layout(location = ULOC_CUSTOM_1) uniform uint color_source;

layout (std140, binding = UBIND_CUSTOM_0) uniform MaterialBlock { Material in_material; };



vec3 GetSourceColor(vec3 out_normal_eye)
{
  vec3 color = vec3(1.0, 0.0, 1.0);
  //POINT_POSITIONS
  if (color_source == 0)
  {
    color = in_material.color;
  }
  //POINT_POSITIONS
  if (color_source == 1)
  {
    color = (VIEW_INV_MAT * vec4(in_vert.position_eye, 1.0)).xyz;
  }
  //POINT_NORMALS
  else if (color_source == 2)
  {
    color = normalize((VIEW_INV_MAT * vec4(out_normal_eye, 0.0)).xyz);
  }
  //POINT_COLORS
  else if (color_source == 3)
  {
    color = in_vert.color;
  }
  //POINT_NORMALS NORMALIZED
  else if (color_source == 4)
  {
    vec3 n = normalize((VIEW_INV_MAT * vec4(out_normal_eye, 0.0)).xyz);
    color = n * 0.5 + 0.5;
  }
  //CHECKERBOARD
  else if (color_source == 5) 
  {
    color = mix(vec3(0.3), vec3(0.7), GetCheckerValue(in_vert.coord, 128));
  }
  //NORMAL_TEXTURE
  else if (color_source == 6) 
  {
    color = texture(albedo_map, in_vert.coord).rgb;
  }
  //ALBEDO_TEXTURE
  else if (color_source == 7) 
  {
    color = texture(albedo_map, in_vert.coord).rgb;
  }

// if (in_is_back_facing == 1)
// {
// 	color *= 0.3;
// }

    return color;
}

Material GetMaterial(vec3 out_normal_eye)
{
  Material modified_material = in_material;
  modified_material.color = GetSourceColor(out_normal_eye);
  return modified_material;
}