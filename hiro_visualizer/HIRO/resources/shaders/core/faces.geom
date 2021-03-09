#version 430
#include "include/math.glsl";
#include "api_definitions.glsl"

layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;

/// INPUT
layout (location = 0) in Vertex in_vert[3];
layout (location = 4) in vec3 in_face_color[3];
layout (location = 5) in vec4 in_tangents[3];
layout (location = 6) in uint in_label[3];

/// OUTPUT
layout (location = 0) out flat uint out_is_back_facing;
layout (location = 1) out Vertex out_vert;
layout (location = 5) out vec4 out_tangents;
layout (location = 6) out flat vec3 out_face_normal;
layout (location = 9) out flat uint out_label;

/// UNIFORMS
layout(location = ULOC_CUSTOM_0) uniform bool cull_backfaces;

void main()
{
    out_face_normal = GetNormalCCW(in_vert[0].position_eye, in_vert[1].position_eye, in_vert[2].position_eye);
    bool is_back_facing = dot(out_face_normal, in_vert[0].position_eye) > 0.0;
    if (cull_backfaces && is_back_facing)
    {
        return;
    }

    out_is_back_facing = is_back_facing ? 1 : 0;
    for (int i = 0; i < 3; i++)
    {
        out_vert = in_vert[i];
        out_tangents = in_tangents[i];
        gl_Position = GetProjMat() * vec4(in_vert[i].position_eye, 1.0);
        out_label = in_label[i];
        EmitVertex();
    }

    EndPrimitive();
}
