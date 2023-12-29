#version 330

attribute vec3 a_position;

flat out vec3 start_pos;
out vec3 vert_pos;

uniform mat4 u_mvp;
uniform float u_vertex_size;

void main() {
    vec4 pos    = u_mvp * vec4(a_position, 1.0);
    vert_pos     = pos.xyz / pos.w;
    start_pos    = vert_pos;
    gl_PointSize = u_vertex_size;
    gl_Position = pos;
}
