#version 450

in vec2 UvCoord;
out vec4 Color;

layout(binding=0) uniform sampler2D Texture;

void main() {
    Color = texture (Texture, UvCoord).rgba;
//Color = vec3(0.f, 1.f, 0.f);
}
