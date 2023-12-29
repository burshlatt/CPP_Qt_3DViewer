#version 330

flat in vec3 start_pos;
in vec3 vert_pos;

uniform vec2  u_resolution;
uniform vec3 u_color;

void main() {
    vec2  dir  = (vert_pos.xy-start_pos.xy) * u_resolution/2.0;
    float dist = length(dir);
    float u_dash_size = 10.0f;
    float u_gap_size = 10.0f;

    if (fract(dist / (u_dash_size + u_gap_size)) > u_dash_size/(u_dash_size + u_gap_size))
        discard; 
    gl_FragColor = vec4(u_color, 1.0);
}
