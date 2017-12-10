#version 450

in vec2 UvCoord;
out vec4 Color;

void main() {
    Color = vec4(UvCoord, 1.0, 1.0);
}
