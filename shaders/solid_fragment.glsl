#version 330

in vec3 view_pos;
in vec3 normal;

uniform vec3 u_ambient;
uniform vec3 u_diffuse;
uniform vec3 u_specular;
uniform vec3 u_emission;
uniform float u_shiness;
uniform float u_opacity;
uniform vec3 u_light_pos;
uniform vec3 u_color;

void main() {
    vec3 n = gl_FrontFacing ? normal : -normal;
    vec3 l = normalize(u_light_pos - view_pos);
    vec3 e = normalize(-view_pos);
    vec3 r = normalize(reflect(-l, n));

    vec3 diff = (u_diffuse + u_color) * max(dot(n, l), 0.0f);
    diff = clamp(diff, 0.0f, 1.0f);
    vec3 spec = u_color * u_specular * pow(max(dot(r, e), 0.0f), u_shiness);
    spec = clamp(spec, 0.0f, 1.0f);

    gl_FragColor = vec4(u_emission * u_color + u_ambient * u_color + diff + spec, u_opacity);
}
