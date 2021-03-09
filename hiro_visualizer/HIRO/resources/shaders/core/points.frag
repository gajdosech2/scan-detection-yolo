#version 430
#include "core/frag_definitions.glsl"

void main()
{
	WriteFragment(
		in_vert.position_eye, 
		in_vert.normal_eye, 
		GetMaterial(in_vert.normal_eye)
	);
}
