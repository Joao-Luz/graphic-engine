#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D crate_texture;
uniform sampler2D smile_texture;
uniform float image_ratio;

void main()
{
    FragColor = mix(texture(crate_texture, TexCoord), texture(smile_texture, TexCoord), image_ratio);
}