#version 450

out Sphere
{
    vec3 pos;
    float radius;
} sphere;

void main()
{
    vec3 mult = vec3(gl_VertexID / 100, (gl_VertexID / 10) % 10, gl_VertexID % 10);
    sphere.pos = mult * vec3(2) - vec3(10);
    sphere.radius = 1;
}