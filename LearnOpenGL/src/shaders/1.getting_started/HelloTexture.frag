#version 460 core
in vec3 outColor;
in vec2 outTexcoord;
out vec4 fragColor;
uniform sampler2D outTexture;

void main()
{
   fragColor = texture(outTexture, outTexcoord) * vec4(outColor, 1.f);
}