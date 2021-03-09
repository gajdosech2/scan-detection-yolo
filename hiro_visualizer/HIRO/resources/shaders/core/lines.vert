#version 430

layout (location = 0) in vec2 position;

void main ()
 { 
    vec2 screen_space_pos = vec2(position.x,1-position.y) * 2.0f - 1.0f;
    gl_Position = vec4(screen_space_pos, 0.0, 1.0);
 }