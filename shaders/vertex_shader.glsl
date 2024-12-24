#version 330 core
layout (location = 0) in vec3 aPos; // the position variable has attribute position 0
layout (location = 1) in vec3 aColor; // the color variable has attribute position 1
layout (location = 2) in vec2 aTexCoord; // the color variable has attribute position 1

out vec4 vertexColor; // specify a color output to the fragment shader
out vec2 texCoord;

uniform mat4 transform;

void main()
{
    vec4 pos = transform * vec4(aPos.xyz, 1.0);
    gl_Position = pos;

    vertexColor = pos; // set the output variable to a dark-red color
    texCoord = aTexCoord;
}