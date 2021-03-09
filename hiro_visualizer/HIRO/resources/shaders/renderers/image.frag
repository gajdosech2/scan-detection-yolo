#version 430
#include "api_frag.glsl"
#include "include/texturing.glsl"
#include "include/math.glsl"

#define ALPHA_ZERO_SQUARLE_SIZE 20.0

layout(origin_upper_left, pixel_center_integer) in vec4 gl_FragCoord;

//TexCoord
layout (location = 0) in vec2 in_coord;

// Texture
layout (binding = 0) uniform sampler2D ras_tex;

layout (location = ULOC_CUSTOM_3) uniform bvec4 is_channel_enabled;
layout (location = ULOC_CUSTOM_4) uniform vec4 channel_offset;
layout (location = ULOC_CUSTOM_5) uniform vec4 channel_multiplier;
layout (location = ULOC_CUSTOM_6) uniform bool discard_transparent_pixels;

/// SOURCE
void main()
{
  vec4 image_color = (texture(ras_tex, in_coord) + channel_offset) * channel_multiplier;
  if (!is_channel_enabled.r) image_color.r = 0.0;
  if (!is_channel_enabled.g) image_color.g = 0.0;
  if (!is_channel_enabled.b) image_color.b = 0.0;
  if (!is_channel_enabled.a) image_color.a = 1.0;

  if (discard_transparent_pixels && image_color.a < 0.001)
  {
	discard;
  }

  const vec3 alpha_zero = mix(vec3(0.4),vec3(0.6),GetCheckerGridValue(gl_FragCoord.xy / ALPHA_ZERO_SQUARLE_SIZE));
  const vec3 final_color = mix(alpha_zero, image_color.rgb, Clamp01(image_color.a));

  WriteFragment(final_color);
}
