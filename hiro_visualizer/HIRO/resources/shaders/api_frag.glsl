#include "api_definitions.glsl"

layout (location = 0) out vec4 out_position;
layout (location = 1) out vec4 out_normal;
layout (location = 2) out uvec4 out_material;
layout (location = 3) out uint out_label;
layout (location = 4) out float out_shadow;

layout (binding = 0) uniform sampler2D shadowmap;

#define LIGHTING_BIT 0
#define METALIC_BIT 1

//! Projects position from camera space to global and then to specified projection_space.
//! Resulting projection is in range <0,1> space.
vec3 Project(in vec3 position_eye, in mat4 projection)
{
  const vec4 proj_position = projection * VIEW_INV_MAT * vec4(position_eye, 1.0);
  return proj_position.xyz / proj_position.w;
}

//! Returns (camera space) direction from point to light.
vec3 GetDirectionToLight(in vec3 position_eye)
{
  const vec3 light_eye = (VIEW_MAT * SHADOW_LIGHT.position).xyz;
  if (SHADOW_LIGHT.position.w > 0.5)
  {
    return light_eye - position_eye; // point light
  }
  return -light_eye; // directional light
}

//! Check if point is on the surface turned away from the light.
bool IsOnDarkSide(in vec3 position_eye, in vec3 normal_eye)
{
  return dot(normal_eye, GetDirectionToLight(position_eye)) < 0.0;
}

//! Checks if there is shadow casted on a specified position.
float TestShadow(in vec3 position_eye, in vec3 normal_eye)
{
  if (SHADOWING_METHOD == 0)
  {
    return 0.0;
  }
  if (IsOnDarkSide(position_eye, normal_eye))
  {
    return 1.0;
  }

  const vec3 proj_point = Project(position_eye, SHADOW_LIGHT.view);
  if (proj_point.z >= 1.0) // the points behing light far clipping plane
  { 
    return SHADOWING_METHOD == 1 ? 0.0 : 1.0; 
  }
  const vec3 proj_point_01 = proj_point * 0.5 + 0.5;
  float shadow_depth = texture(shadowmap, proj_point_01.xy).x;
  
  const float bias = 0.0005; 
  // This calculation is addaptive bias. However, the behaviour is somewhat suspicions. Explore more. -Adam
  //const vec3 normal = (VIEW_INV_MAT * vec4(normal_eye, 0.0)).xyz;
  //const float bias = max(0.01 * (1.0 - dot(normal, SHADOW_LIGHT.position.xyz)), 0.0001);  

  return shadow_depth < proj_point_01.z - bias ? 1.0 : 0.0;
}

void WriteFragment(in vec3 position_eye, in vec3 normal_eye, in Material material, in uint label = 0)
{
    // Store the fragment position vector in the first gbuffer texture.
    out_position.rgb = position_eye;
    // As the alpha value we store shininess.
    out_position.a = material.shininess;

    // Store the per-fragment normals.
    out_normal.rgb = normal_eye;
    // As the alpha value we store specular intensity.
    out_normal.a = material.specular;

    // Material color
    out_material.rgb = uvec3(material.color * 255.0);
    // boolean parameter bits
    out_material.a = 0;
    if (material.use_lighting)
        out_material.a |= 1 << LIGHTING_BIT;
    if (material.is_metalic)
        out_material.a |= 1 << METALIC_BIT;

    // Store label
    out_label = label;

    // Store shadow information
    out_shadow = SHADOW_LIGHT.cast_shadow ? TestShadow(position_eye, normal_eye) : 0;
}

void WriteFragment(in vec3 color)
{
    out_position = vec4(0.0);
    out_normal = vec4(0.0);
    out_material = uvec4(uvec3(color * 255.0), 0);
    out_label = uint(0);
}
