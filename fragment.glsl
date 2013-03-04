#version 430 core

in vec3 varyingColor;
out vec4 fragColor;

void main()
{
  fragColor.rgb = varyingColor;
  fragColor.a = 1.0;
}
