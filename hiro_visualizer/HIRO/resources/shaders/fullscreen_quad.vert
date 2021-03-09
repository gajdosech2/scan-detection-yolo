#version 430
// use glDrawArrays(GL_TRIANGLE_FAN, 0, 4) to invoke this shader

layout (location = 0) out vec2 out_coord;

const vec2 tex_coords[4] = vec2[4] (
   vec2(0.0, 0.0),
   vec2(1.0, 0.0),
   vec2(1.0, 1.0),
   vec2(0.0, 1.0)
);

void main()
{
   out_coord = tex_coords[gl_VertexID];
   gl_Position = vec4(out_coord * 2.0 - 1.0, 0.0, 1.0);
}