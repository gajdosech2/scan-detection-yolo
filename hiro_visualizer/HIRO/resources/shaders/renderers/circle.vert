#version 430
// use glDrawArrays(GL_TRIANGLE_FAN, 0, 4) to invoke this shader

layout (location = 0) in vec2 in_position;
layout (location = 1) in float in_radius;
layout (location = 2) in vec3 in_color;

layout (location = 0) out vec2 out_position;
layout (location = 1) out float out_radius;
layout (location = 2) out vec3 out_color;

void main()
{
    out_position = in_position;
    out_radius = in_radius;
    out_color = in_color;
}