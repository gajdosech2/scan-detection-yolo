#version 430
#include "include/math.glsl"
#include "api_definitions.glsl"

layout(points) in;
layout(triangle_strip, max_vertices = 200) out;

/// INPUT
layout (location = 0) in vec2 in_position[1];
layout (location = 1) in float in_radius[1];
layout (location = 2) in vec3 in_color[1];

/// OUTPUT
layout (location = 0) out vec3 out_color;

vec4 Project(vec2 screen_point)
{
    return PROJ_MAT * vec4(screen_point, 0.0, 1.0);
}

vec4 GetCirclePoint(float angle)
{
    const vec2 current_npoint = vec2(cos(angle), sin(angle));
    return Project(in_position[0] + current_npoint * in_radius[0]);
}

void main()
{
    out_color = in_color[0];

    float steps = 36;
    const float angle_step = TWO_PI / steps;

    const vec4 center = Project(in_position[0]);

    vec4 prev_point = GetCirclePoint(0.0);
    float current_angle = angle_step;
    for (int i=0; i < steps; ++i)
    {
        const vec4 current_point = GetCirclePoint(current_angle);

        gl_Position = center;
        EmitVertex();
        gl_Position = current_point;
        EmitVertex();
        gl_Position = prev_point;
        EmitVertex();

        EndPrimitive();

        prev_point = current_point;
        current_angle += angle_step;
    }
}

