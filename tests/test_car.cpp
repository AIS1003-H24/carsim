
#include "Car.hpp"
#include <catch2/catch_test_macros.hpp>

inline bool eulerEquals(const threepp::Euler &a, const threepp::Euler &b, float tolerance = 0.001) {

    const auto diff = std::abs(a.x - b.x) + std::abs(a.y - b.y) + std::abs(a.z - b.z);
    return diff < tolerance;
}

TEST_CASE("Test setLinearVelocity") {

    threepp::Euler initialRotation;
    threepp::Vector3 initialPosition = {0, 0, 10};

    Car c(initialPosition, initialRotation);
    CHECK(c.getPosition() == initialPosition);
    c.setLinearVelocity(1);

    c.update(1);

    CHECK(c.getPosition().z > initialPosition.z);
    threepp::Euler currentRot = c.getRotation();
    CHECK(eulerEquals(initialRotation, c.getRotation()));
}

TEST_CASE("Test turning") {
    threepp::Euler initialRotation;
    Car c({}, initialRotation);

    c.setTurnVelocity(1);
    c.update(1);
    auto currentRot = c.getRotation();

    CHECK(initialRotation.y < currentRot.y);

    auto prevRotation = currentRot;
    c.setTurnVelocity(-1);
    c.update(0.1);
    currentRot = c.getRotation();
    CHECK(prevRotation.y > currentRot.y);
}