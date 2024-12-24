#version 330 core
layout (location = 0) in vec3 aPos; // the position variable has attribute position 0
layout (location = 1) in vec3 aColor; // the color variable has attribute position 1
layout (location = 2) in vec2 aTexCoord; // the color variable has attribute position 1

out vec2 texCoord;

void main()
{
    vec4 pos = vec4(aPos.xyz, 1.0);
    gl_Position = pos;

    texCoord = aTexCoord;
}