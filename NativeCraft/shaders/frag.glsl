#version 330

in vec2 texCoord;

out vec4 fragColor;

uniform sampler2D _texture;

void main() 
{
    fragColor = texture(_texture, texCoord);
}