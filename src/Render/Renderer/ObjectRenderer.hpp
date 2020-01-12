#ifndef RENDER_OBJECT_RENDERER_HPP
#define RENDER_OBJECT_RENDERER_HPP

#include "GBuffer.hpp"
#include "RenderStore.hpp"
#include "LightPass.hpp"
#include "SSAOPass.hpp"

#include "Library/StaticCounter.hpp"

#include "Render/Scene/Scene.hpp"
#include "Render/VertexFormat/PosNormUVDescriptor.hpp"

#include "Library/GL/Buffer.hpp"
#include "Library/GL/Program.hpp"

#include <vector>

namespace Render {
class Scene;
}

namespace Render {

class ObjectRenderer {
public:
    ObjectRenderer(Scene& _scene, RenderStore& _store);

    void ResizeViewPort(int newWidth, int newHeight);
    void Render();

private:
    Scene& scene;
    RenderStore& store;
    Render::GBuffer gBuffer;
	SSAOPass ssaoPass;
    LightPass lightPass;

    PosNormUVDescriptor descriptor;

    unsigned width = 1000;
    unsigned height = 1000;
};

} //namespace Render

#endif //RENDER_OBJECT_RENDERER_HPP
