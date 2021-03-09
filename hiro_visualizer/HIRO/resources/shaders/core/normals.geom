#version 430
#include "api_definitions.glsl"

layout(points) in;
layout(line_strip, max_vertices = 2) out;

/// INPUT
layout (location = 0) in Vertex in_vert[1];

/// UNIFORMS
layout (location = ULOC_CUSTOM_0) uniform float normal_length;
layout (location = ULOC_CUSTOM_1) uniform vec3 normal_color;

/// OUTPUT
layout (location = 0) out vec3 out_color;

/// SOURCE
void main()
{
    if (length(in_vert[0].normal_eye) < 0.1)
    {
        return;
    }

	out_color = vec3(0,0,0);
    gl_Position = PROJ_MAT * vec4(in_vert[0].position_eye, 1.0); 
    EmitVertex();

	out_color = normal_color;
	gl_Position = PROJ_MAT * vec4(in_vert[0].position_eye + normal_length * in_vert[0].normal_eye, 1.0); 
    EmitVertex();

    EndPrimitive();
}

