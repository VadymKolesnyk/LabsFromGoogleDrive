#version 440 core
in vec4 vertexColor; // Входная переменная из вершинного шейдера (то же название и тот же тип)

out vec4 color;

//uniform vec4 ourColor;
void main()
{
    color = vec4(0.0f, 0.5f, 0.5f, 1.0f);
} 