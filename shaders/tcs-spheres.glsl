#version 450

layout(vertices = 1) out;

in Sphere
{
    vec3 pos;
    float radius;
} spheres[];


patch out Sphere
{
    vec3 pos;
    float radius;
} sphere;

void main()
{
    gl_TessLevelOuter[0] = 10.0;
    gl_TessLevelOuter[1] = 1.0;
    gl_TessLevelOuter[2] = 10.0;
    gl_TessLevelOuter[3] = 1.0;

    gl_TessLevelInner[0] = 10.0;
    gl_TessLevelInner[1] = 10.0;

    sphere.pos = spheres[0].pos;
    sphere.radius = spheres[0].radius;
}