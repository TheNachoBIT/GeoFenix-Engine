#version 130
#extension GL_ARB_explicit_attrib_location : require

in vec3 vs_position;
in vec3 vs_color;
in vec2 vs_texcoord;

out vec4 fs_color;

uniform sampler2D texture0;

void main()
{
	//fs_color = vec4(vs_color, 1);
	fs_color = texture(texture0, vs_texcoord) * vec4(vs_color, 1);
}
