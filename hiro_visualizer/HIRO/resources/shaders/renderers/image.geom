#version 430
#include "api_definitions.glsl"

layout(points) in;
layout(triangle_strip, max_vertices = 4) out;

/// UNIFORMS
layout (location = ULOC_CUSTOM_0) uniform uvec2 raster_size;
layout (location = ULOC_CUSTOM_1) uniform mat4 image_to_pixel;
layout (location = ULOC_CUSTOM_2) uniform uvec2 mirror;

/// OUTPUT
layout (location = 0) out vec2 out_coord;

const vec2 tex_coords[4] = vec2[4] (
   vec2(0.0, 1.0),
   vec2(1.0, 1.0),
   vec2(0.0, 0.0),
   vec2(1.0, 0.0)
);

vec2 GetPoint(in uint i)
{
    const vec2 coord = tex_coords[i];
    return raster_size * vec2(
        mirror.x != 0 ? 1.0 - coord.x : coord.x,
        mirror.y != 0 ? coord.y : 1.0 - coord.y);
}

void main()
{
    for (int i=0; i<4; ++i)
    {
        vec2 point = GetPoint(i);
        gl_Position = PROJ_MAT * image_to_pixel * vec4(point, 0.0, 1.0);
        out_coord = tex_coords[i];
        EmitVertex();
    }

    EndPrimitive();
}

