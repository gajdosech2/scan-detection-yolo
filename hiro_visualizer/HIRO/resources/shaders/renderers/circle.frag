#version 430
#include "api_frag.glsl"

layout (location = 0) in vec3 in_color;

void main()
{
	WriteFragment(in_color);
}
