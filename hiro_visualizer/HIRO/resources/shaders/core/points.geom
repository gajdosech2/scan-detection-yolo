#version 430
#include "api_definitions.glsl"

layout(points) in;
layout(points, max_vertices = 1) out;

/// INPUT
layout (location = 0) in Vertex in_vert[1];

/// UNIFORMS
layout(location = ULOC_CUSTOM_0) uniform bool cull_backfaces;

/// OUTPUT
layout (location = 0) out flat uint out_is_back_facing;
layout (location = 1) out Vertex out_vert;

void main()
{
	bool is_back_facing = dot(in_vert[0].normal_eye, in_vert[0].position_eye) > 0.0 && length(in_vert[0].normal_eye) > 0.1;

  if (cull_backfaces && is_back_facing)
  {
    return;
  }

  out_vert = in_vert[0];
  out_is_back_facing = is_back_facing ? 1 : 0;
  gl_Position = PROJ_MAT * vec4(in_vert[0].position_eye, 1.0); 
  EmitVertex();

  EndPrimitive();
}
