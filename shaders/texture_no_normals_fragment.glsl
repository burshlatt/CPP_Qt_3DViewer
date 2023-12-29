#version 330

in vec2 tex_coords;
uniform sampler2D u_texture_d;

void main() { gl_FragColor = texture2D(u_texture_d, tex_coords); }
