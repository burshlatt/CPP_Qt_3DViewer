#version 330

in vec3 view_pos;
in vec3 normal;
in vec2 tex_coords;

uniform vec3 u_ambient;
uniform vec3 u_diffuse;
uniform vec3 u_specular;
uniform vec3 u_emission;
uniform float u_shiness;
uniform float u_opacity;
uniform vec3 u_light_pos;
uniform sampler2D u_texture_a;
uniform sampler2D u_texture_d;
uniform sampler2D u_texture_s;

void main() {
  vec4 map_amb = texture2D(u_texture_a, tex_coords);
  vec4 map_diff = texture2D(u_texture_d, tex_coords);
  vec4 map_spec = texture2D(u_texture_s, tex_coords);

  vec3 x_tangent = dFdx(view_pos);
  vec3 y_tangent = dFdy(view_pos);

  vec3 n = normalize(cross(x_tangent, y_tangent));
  vec3 l = normalize(u_light_pos - view_pos);
  vec3 e = normalize(-view_pos);
  vec3 r = normalize(-reflect(l, n));

  vec3 amb = u_ambient * map_amb.rgb;
  vec3 diff = (u_diffuse + map_diff.rgb) * max(dot(n, l), 0.0f);
  diff = clamp(diff, 0.0f, 1.0f);
  vec3 spec = u_specular * pow(max(dot(r, e), 0.0f), u_shiness);
  spec = clamp(spec, 0.0f, 1.0f);

  gl_FragColor = vec4(u_emission + amb + diff + spec, u_opacity * map_diff.a);

}
