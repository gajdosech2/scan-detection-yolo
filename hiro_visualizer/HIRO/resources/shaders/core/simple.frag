#version 430
#include "api_frag.glsl"

/// INPUT
layout (location = 0) in vec3 in_color;

/// SOURCE
void main()
{
	WriteFragment(in_color);
}
