#version 450

const vec2 Triangle[3] = { vec2(-1, -1), vec2(4, -1), vec2(-1, 4) };
const vec2 UV[3] = { vec2(0, 0), vec2(2, 0), vec2(0, 2) };

out VertexData
{
	vec2 uv;
};

void main()
{
    gl_Position = vec4(Triangle[gl_VertexID], 0, 1);
    uv = UV[gl_VertexID];
}