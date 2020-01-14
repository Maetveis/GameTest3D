#version 450

in VertexData
{
	vec2 uv;
};

out vec3 fs_color;

layout(location = 0) uniform sampler2D positionTexture;
layout(location = 1) uniform sampler2D ambientTexture;

void main()
{
	vec3 pos = texture(positionTexture, uv).rgb;
	if(all(lessThan(abs(pos), vec3(0.05))))
		discard;
		
	vec2 texelSize = 1.0 / vec2(textureSize(ambientTexture, 0));
    float result = 0.0;
    for (int x = -2; x < 2; ++x) 
    {
        for (int y = -2; y < 2; ++y) 
        {
            vec2 offset = vec2(float(x), float(y)) * texelSize;
            result += texture(ambientTexture, uv + offset).r;
        }
    }
		
	fs_color = result / 16 * vec3(.1, .1, .1);
}