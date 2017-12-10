#version 450

uniform mat4 Mvp;

in vec3 Coordinates;

in vec2 Uv;

out vec2 UvCoord;

void main() {
    gl_Position = Mvp * vec4(Coordinates, 1.0);

    UvCoord = Uv;
}
