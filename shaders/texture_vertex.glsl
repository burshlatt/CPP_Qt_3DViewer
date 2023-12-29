#version 330

attribute vec3 a_position;
attribute vec3 a_normal;
attribute vec2 a_tex_coords;

out vec3 view_pos;
out vec3 normal;
out vec2 tex_coords;

uniform mat4 u_mvp;
uniform mat4 u_mv;
uniform mat4 u_normal_mat;

void main() {
  view_pos = vec3(u_mv * vec4(a_position, 1.0));
  normal = normalize(mat3(u_normal_mat) * a_normal);
  tex_coords = a_tex_coords;
  gl_Position = u_mvp * vec4(a_position, 1.0);
}
