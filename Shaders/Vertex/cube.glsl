#version 450

uniform mat4 Mvp;

in vec3 VertexPosition;
in mat4 ModelMatrix;

void main() {
    mat4 PositionMatrix = Mvp * ModelMatrix;
    gl_Position = PositionMatrix * vec4(VertexPosition, 1.f);
    //Mvp * vec4(VertexPosition, 1.f) * ModelMatrix;
}
