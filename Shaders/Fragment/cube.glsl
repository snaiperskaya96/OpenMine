#version 450

out vec4 Colour;
in vec3 Position;

void main() {
    Colour = vec4(Position.xy, Position.yz);
}
