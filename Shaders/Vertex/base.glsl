#version 450

uniform mat4 MVP;
in vec3 Coordinates;
in vec3 Color;
out vec4 VertexColor;

void main() {
    gl_Position = MVP * vec4(Coordinates, 1.0);
    VertexColor = vec4(Color, 1.0);
}