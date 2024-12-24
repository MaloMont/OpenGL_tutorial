#version 330 core
layout (location = 0) in vec3 aPos; // the position variable has attribute position 0
layout (location = 1) in vec2 aTexCoord; // the color variable has attribute position 1

out vec2 texCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    vec4 pos = vec4(aPos.xyz, 1.0);

    // note that we read the multiplication from right to left
    gl_Position = projection * view * model * pos;

    texCoord = aTexCoord;
}
