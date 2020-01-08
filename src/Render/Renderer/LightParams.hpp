#ifndef RENDER_LIGHT_PARAMS_HPP
#define RENDER_LIGHT_PARAMS_HPP

#include <Render/Scene/Light.hpp>

#include <Library/GL/Buffer.hpp>
#include <Library/GL/UniformBinding.hpp>


#include <glm/glm.hpp>

namespace GL {

class Program;

}

namespace Render {

class LightParams {
public:
    LightParams()
    {
        bindingPoint.AttachBuffer(buffer);
    }

    void Upload(const std::vector<Light> lights, const glm::mat4& view)
    {
        Data data;
        for (unsigned i = 0; i < lights.size() && i < 10; ++i) {
            data.lights[i] = lights[i];
            data.lights[i].pos = glm::vec3(view * glm::vec4(lights[i].pos, 1));
        }
        data.lightCount = lights.size() > 10 ? 10 : lights.size();

        buffer.BufferData(data, GL_STREAM_DRAW);
    }

    GL::UniformBinding& GetBinding()
    {
        return bindingPoint;
    }

private:
    GL::Buffer buffer;
    GL::UniformBinding bindingPoint;

    struct Data {
        Light lights[10];
        unsigned int lightCount = 0;
    };
};

} //namespace Render

#endif //RENDER_LIGHT_PARAMS_HPP
