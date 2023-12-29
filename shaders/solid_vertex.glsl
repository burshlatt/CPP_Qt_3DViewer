#version 330

attribute vec3 a_position;
attribute vec3 a_normal;

out vec3 view_pos;
out vec3 normal;

uniform mat4 u_mvp;
uniform mat4 u_mv;
uniform mat4 u_normal_mat;

void main() {
  normal = normalize(mat3(u_normal_mat) * a_normal);
  view_pos = vec3(u_mv * vec4(a_position, 1.0));
  gl_Position = u_mvp * vec4(a_position, 1.0);
}
