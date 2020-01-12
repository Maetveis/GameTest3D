#version 450

in VertexData
{
	vec2 uv;
};

out vec3 fs_color;

layout(location = 0) uniform sampler2D positionTexture;

void main()
{
	vec3 pos = texture(positionTexture, uv).rgb;
	if(all(lessThan(abs(pos), vec3(0.05))))
		discard;
		
	fs_color = vec3(1, 1, 1);
}
