
#include "Car.hpp"

Car::Car(const threepp::Vector3 &initialPos, const threepp::Euler &initialRot)
    : pos_(initialPos), rot_(initialRot) {
}

void Car::setLinearVelocity(float speed) {
    linearVelocity_ = speed;
}

void Car::setTurnVelocity(float speed) {
    turnSpeed_ = speed;
}

void Car::update(float dt) {

    rot_.y += turnSpeed_ * dt;
    threepp::Vector3 dir = threepp::Vector3(0, 0, 1).applyEuler(rot_);
    pos_.add(dir * linearVelocity_ * dt);
}

threepp::Vector3 Car::getPosition() const {
    return pos_;
}

threepp::Euler Car::getRotation() const {
    return rot_;
}