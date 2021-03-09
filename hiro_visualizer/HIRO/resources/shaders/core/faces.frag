#version 430
#include "core/frag_definitions.glsl"

struct DefFace
{
  vec3 normal;
  vec3 center;
  vec3 color;
  mat3x4 edge_volume;
};

layout (location = 5) in vec4 in_tangents;
layout (location = 6) in flat vec3 in_face_normal;
layout (location = 9) in flat uint in_label;

/// UNIFORMS
layout(location = ULOC_CUSTOM_2) uniform uint normal_source;
layout(location = ULOC_CUSTOM_3) uniform bool use_matcap;
layout(binding = 2) uniform sampler2D matcap_sampler;


vec3 GetSourceNormal()
{
    if (normal_source == 0) 
    {
        return in_face_normal;
    }
    if (normal_source == 1) 
    {
        return normalize(in_vert.normal_eye);
    }
    if (normal_source == 2)
    {
        vec3 T = normalize(in_tangents.xyz);
        vec3 N = normalize(in_vert.normal_eye);
        vec3 B = (in_tangents.w < 0) ? cross(T,N) : cross(N,T);
        mat3 TBN = mat3(T, B, N);
        vec3 loaded_normal = texture(normal_map, in_vert.coord).rgb;
        loaded_normal = normalize(loaded_normal * 2.0 - 1.0);
        return normalize(TBN * loaded_normal);
    }
    return vec3(0.0f);
}

void main()
{
    const vec3 out_normal_eye = GetSourceNormal();
    Material out_material = GetMaterial(out_normal_eye);
    if (use_matcap)
    {
        out_material.color =  texture(matcap_sampler, 0.5 + out_normal_eye.xy * 0.5).rgb;
        out_material.use_lighting = false;
    }
    WriteFragment(
        in_vert.position_eye, 
        out_normal_eye,
        out_material,
        in_label
    );
}
