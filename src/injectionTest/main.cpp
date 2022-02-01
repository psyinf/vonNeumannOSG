#include <kangaru/kangaru.hpp>
#include <pslog.h>
#include <cassert>

// We define some normal classes with dependencies between them
struct Camera {};

struct Scene {
    Camera& camera;
};

// The following is the configuration of our user classes above.
// The structure and dependency graph is defined by these configs.

// Camera is a single service so the service has a shared instance.
// It will be injected and returned as a reference.
struct CameraService : kgr::single_service<Camera> {};

// Scene is not single, so the container return scenes by value.
// Also, we depends on a camera to be constructed.
struct SceneService : kgr::service<Scene, kgr::dependency<CameraService>> {};

//struct LogService : kgr::service<pslog::Logger> {};
int main()
{

    kgr::container container;
    
    // The service function return instances of the normal classes.
    Scene scene = container.service<SceneService>();
    Camera& camera = container.service<CameraService>();
    
    assert(&scene.camera == &camera); // passes, both cameras are the same instance.
}