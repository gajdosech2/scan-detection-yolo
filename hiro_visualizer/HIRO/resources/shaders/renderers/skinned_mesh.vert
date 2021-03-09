#version 430
#include "api_vert.glsl"

/// INPUT
layout (location = 0) in vec3 in_position;
layout (location = 1) in vec3 in_normal;
layout (location = 2) in vec2 in_coords;
layout (location = 3) in vec3 in_color;
layout (location = 4) in ivec4 in_skinids;
layout (location = 5) in vec4 in_skinweights;

/// OUTPUT
layout (location = 0) out Vertex out_vert;

/// UNIFORM BUFFERS
layout (std140, binding = UBIND_CUSTOM_0) uniform BoneTransformBlock1 { mat4 bindmats[@BONECOUNT@]; };
layout (std140, binding = UBIND_CUSTOM_1) uniform BoneTransformBlock2 { mat4 posemats[@BONECOUNT@]; };

vec3 Skin(vec4 element)
{
	vec4 pos_sum = vec4(0.0);
	for (int i=0; i<4; i++)
	{
		int id = in_skinids[i];
		if (id != -1)
		{
			vec4 new_point = posemats[id] * inverse(bindmats[id]) * element;
			float weight = in_skinweights[i];
			pos_sum.xyz += weight * new_point.xyz;
			pos_sum.w += weight;
		}
	}
	return pos_sum.xyz / pos_sum.w;
}

void main () 
{
	mat4 eye_transform = GetTransfView();
	vec3 position_skinned = Skin(vec4(in_position, 1.0));
	vec3 normal_skinned = Skin(vec4(in_normal, 0.0));

	out_vert.position_eye = (eye_transform * vec4(position_skinned, 1.0)).xyz;
	out_vert.normal_eye = (eye_transform * vec4(normal_skinned, 0.0)).xyz;
	out_vert.coord = in_coords;
	out_vert.color = in_color;
}