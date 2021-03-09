#version 430
#include "api_definitions.glsl"

/// INPUT
layout (location = 0) in vec2 pos;

/// UNIFORMS
layout (location = ULOC_CUSTOM_0) uniform vec4 edges; 
layout (location = ULOC_CUSTOM_1) uniform ivec4 rect;
layout (location = ULOC_CUSTOM_2) uniform vec3 line_color;

layout (location = ULOC_CUSTOM_3) uniform uint draw_grid;

/// OUTPUT
layout (location = 0) out vec3 out_color;
layout (location = 1) out Vertex out_vert;

/// SOURCE
void main () 
{
	// [0,0] --> TOP LEFT CORNER
	ivec2 resolution = SCENES[SCENE_ID].resolution;

	// mapped: [edges_min, edges_max] -> [0,1]
	vec2 graph_point = vec2((pos.x - edges.x) / (edges.y - edges.x), (pos.y - edges.z) / (edges.w - edges.z));

	// inverted targrt-rectangle space
	float original_y = float(rect.y);
	float inverted_y = float(resolution.y - original_y - rect.w);
	vec2 rect_space_point = vec2(float(rect.x) + graph_point.x * float(rect.z), inverted_y + graph_point.y * float(rect.w));

	// Adjust every second vertical point
	if(draw_grid == 1 && (gl_VertexID % 2 == 0))
	{
	rect_space_point.y = resolution.y - rect.y - rect.w;
	}

	// Adjust every second horizontal point
	if(draw_grid == 2 && gl_VertexID % 2 == 0)
	{
	rect_space_point.x = rect.x;
	}

	vec2 norm_rect_space = vec2(((rect_space_point.x / float(resolution.x)) * 2.0) -1.0,((rect_space_point.y / float(resolution.y)) * 2.0) -1.0);

	out_color = line_color;
	gl_Position = vec4(norm_rect_space.x,norm_rect_space.y, 0, 1);

}