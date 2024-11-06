#include "threepp/threepp.hpp"

#include "Car.hpp"

using namespace threepp;

namespace {

    std::shared_ptr<Mesh> createBox(const Color &color) {
        const auto geometry = BoxGeometry::create();
        const auto material = MeshBasicMaterial::create();
        material->color.copy(color);
        auto mesh = Mesh::create(geometry, material);

        return mesh;
    }

    class CarController : public KeyListener {

    public:
        CarController(Car &car) : car_(&car) {}

        void onKeyPressed(KeyEvent evt) override {
            float turnVelocity = 1;
            float linearVelocity = 1;
            if (evt.key == Key::W) {
                car_->setLinearVelocity(linearVelocity);
            } else if (evt.key == Key::S) {
                car_->setLinearVelocity(-linearVelocity);
            } else if (evt.key == Key::A) {
                car_->setTurnVelocity(turnVelocity);
            } else if (evt.key == Key::D) {
                car_->setTurnVelocity(-turnVelocity);
            }
        }

        void onKeyReleased(KeyEvent evt) override {
            if (evt.key == Key::W) {
                car_->setLinearVelocity(0);
            } else if (evt.key == Key::S) {
                car_->setLinearVelocity(0);
            } else if (evt.key == Key::A) {
                car_->setTurnVelocity(0);
            } else if (evt.key == Key::D) {
                car_->setTurnVelocity(0);
            }
        }

    private:
        Car *car_;
    };

}// namespace

int main() {

    Canvas canvas("threepp demo", {{"aa", 4}});
    GLRenderer renderer(canvas.size());

    auto camera = PerspectiveCamera::create(50, canvas.aspect());
    camera->position.z = 5;

    OrbitControls controls{*camera, canvas};

    auto scene = Scene::create();
    scene->background = Color::aliceblue;

    Car car;
    CarController controller(car);
    canvas.addKeyListener(controller);

    auto carMesh = createBox(Color::blue);
    scene->add(carMesh);


    canvas.onWindowResize([&](const WindowSize &size) {
        camera->aspect = size.aspect();
        camera->updateProjectionMatrix();
        renderer.setSize(size);
    });

    Clock clock;
    canvas.animate([&] {
        const auto dt = clock.getDelta();

        car.update(dt);
        carMesh->position = car.getPosition();
        carMesh->rotation.copy(car.getRotation()); // bug in assignment operator, use copy

        renderer.render(*scene, *camera);
    });
}
