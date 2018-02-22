#version 150 core

//inputs

in vec3 in_Vertex;
in vec3 in_Color;

uniform mat4 matrices;

//Outputs

out vec4 colors;

void main()
{
	gl_Position = matrices * vec4(in_Vertex, 1.0);

	colors = vec4(in_Color, 1.0);
}