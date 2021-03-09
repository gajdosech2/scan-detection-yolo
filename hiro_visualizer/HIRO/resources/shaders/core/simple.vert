#version 430
#include "api_vert.glsl"

/// INPUT
layout (location = 0) in vec3 in_position;
layout (location = 1) in vec3 in_color;

/// OUTPUT
layout (location = 0) out vec3 out_color;

/// UNIFORMS
layout (location = ULOC_CUSTOM_0) uniform bool use_uniform_color = false;
layout (location = ULOC_CUSTOM_1) uniform vec3 uniform_color;
layout (location = ULOC_CUSTOM_2) uniform float z_bias;

/// SOURCE
void main () 
{
	gl_Position = GetTransfProjection() * vec4(in_position, 1.0);
	gl_Position.z -= z_bias;
	out_color = (use_uniform_color) ? uniform_color : in_color;
}