#version 330 core
out vec4 FragColor;
  
in vec4 vertexColor; // the input variable from the vertex shader (same name and same type)  
in vec2 texCoord;

uniform sampler2D texture0;
uniform sampler2D texture1;

void main()
{
    vec4 color = vec4((vertexColor.x + 1) / 2.0 + 0.1,
                      (vertexColor.y + 1) / 2.0 + 0.1,
                      (vertexColor.z + 1) / 2.0 + 0.1,
                       vertexColor.w
                     );
    FragColor = mix(texture(texture0, texCoord),
                    texture(texture1, vec2(texCoord.x, (vertexColor.y / abs(vertexColor.y)) * texCoord.y)),
                    0.25)
                * color;
}
