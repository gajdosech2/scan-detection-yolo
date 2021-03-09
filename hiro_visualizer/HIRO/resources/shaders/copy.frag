#version 430

layout (location = 0) in vec2 in_coord;

layout (binding = 0) uniform sampler2D in_pixels;

out vec4 out_pixel;

void main()
{
    out_pixel = texture(in_pixels, in_coord);
}
