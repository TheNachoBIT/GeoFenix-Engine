#version 130
#extension GL_ARB_explicit_attrib_location : require

in vec3 vertex_position;
in vec3 vertex_color;
in vec2 vertex_texcoord;

out vec3 vs_position;
out vec3 vs_color;
out vec2 vs_texcoord;

uniform mat4 ModelMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;

void main()
{
	vs_position = vec4(ModelMatrix * vec4(vertex_position, 1.f)).xyz;
	vs_color = vertex_color;
	vs_texcoord = vec2(vertex_texcoord.x, vertex_texcoord.y * -1.f);

	gl_Position = ProjectionMatrix * ViewMatrix * vec4(vs_position, 1.f);
}
