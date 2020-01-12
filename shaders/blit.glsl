#version 450

in VertexData
{
	vec2 uv;
};

out vec3 fs_color;

uniform sampler2D colorTexture;

void main()
{
	fs_color = texture(colorTexture, uv).rgb;
}