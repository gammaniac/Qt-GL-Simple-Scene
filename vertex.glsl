#version 430 core

layout(location=0)in vec3 vPosition;
layout(location=1)in vec3 vColor;

out vec3 varyingColor;

uniform float twist;

void main()
{
  float angle = radians(twist);
  float cosLength = cos(angle);
  float sinLength = sin(angle);

  varyingColor = vColor;

  gl_Position = vec4(cosLength * vPosition.x +
                     -sinLength * vPosition.y,
                     sinLength * vPosition.x +
                     cosLength * vPosition.y,
                     0, 1);
}
