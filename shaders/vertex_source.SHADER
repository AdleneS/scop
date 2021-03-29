#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexture;
layout (location = 2) in vec3 aNormal;
layout (location = 3) in vec3 aColor;
layout (location = 4) in vec3 fColor;

out vec3 FragPos;
out vec3 Normal = vec3(1.0);
out vec3 ourColor;
out vec3 faceColor;
out vec2 UV;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    FragPos = vec3(model * vec4(aPos, 1.0));
    Normal = aNormal;
    ourColor = aColor;
    faceColor = fColor;
    gl_Position = projection * view * vec4(FragPos, 1.0);
    UV = aTexture;
}