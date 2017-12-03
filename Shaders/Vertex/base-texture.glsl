#version 450

in vec3 Coordinates;
in vec2 TextureCoordinates;

out vec2 UV;

uniform mat4 MVP;

void main() {
    gl_Position = MVP * vec4(Coordinates, 1.0);
    UV = TextureCoordinates;
}