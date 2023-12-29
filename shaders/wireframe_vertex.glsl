#version 330

attribute vec3 a_position;

uniform mat4 u_mvp;
uniform float u_vertex_size;

void main() {
    gl_PointSize = u_vertex_size;
    gl_Position = u_mvp * vec4(a_position, 1.0);
}
