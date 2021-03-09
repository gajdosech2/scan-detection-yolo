#version 430
#include "api_vert.glsl"

/// INPUT
layout (location = 0) in vec3 in_position;
layout (location = 1) in vec3 in_normal;
layout (location = 2) in vec2 in_coords;
layout (location = 3) in vec3 in_color;
layout (location = 4) in vec4 in_tangents;

/// OUTPUT
layout (location = 0) out Vertex out_vert;
layout (location = 4) out vec3 out_face_color;
layout (location = 5) out vec4 out_tangents;
layout (location = 6) out uint out_label;

/// UNIFORMS
layout(location = ULOC_CUSTOM_4) uniform uint object_id;

void main ()
{
    mat4 mv = GetTransfView();
    out_vert.position_eye = (mv * vec4(in_position, 1.0)).xyz;
    out_vert.normal_eye = (mv * vec4(in_normal, 0.0)).xyz;
    out_vert.coord = in_coords;
    out_vert.color = in_color;
    out_tangents.xyz = (mv * vec4(in_tangents.xyz, 0.0)).xyz;
    out_tangents.w = in_tangents.w;
    out_label = (USING_INSTANCING) ? gl_InstanceID + object_id : object_id;
}
