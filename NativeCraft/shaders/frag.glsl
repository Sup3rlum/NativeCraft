#version 330

in vec2 fTexCoord;

out vec4 fragColor;

uniform sampler2D _texture;

void main() 
{
    fragColor = texture(_texture, fTexCoord);
}