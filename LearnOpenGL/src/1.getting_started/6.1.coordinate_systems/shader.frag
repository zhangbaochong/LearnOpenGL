#version 460 core
in vec2 outTexcoord;
out vec4 fragColor;
uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
   fragColor = mix(texture(texture1, outTexcoord), texture(texture2, outTexcoord), 0.2);
   
}