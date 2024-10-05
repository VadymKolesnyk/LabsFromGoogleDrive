#version 440 core
layout (location = 0) in vec3 position; // Устанавливаем позицию атрибута в 0

out vec4 vertexColor; // Передаем цвет во фрагментный шейдер

uniform mat4 transform;
void main()
{
    gl_Position = transform * vec4(position, 1.0f); 
    vertexColor = gl_Position; 
}