
#ifndef CAR_HPP
#define CAR_HPP

#include "threepp/math/Euler.hpp"
#include "threepp/math/Vector3.hpp"

class Car {

public:
    Car(const threepp::Vector3 &initialPos = {}, const threepp::Euler &initialRot = threepp::Euler{});

    void setLinearVelocity(float speed);

    void setTurnVelocity(float speed);

    void update(float dt);

    [[nodiscard]] threepp::Vector3 getPosition() const;

    [[nodiscard]] threepp::Euler getRotation() const;

private:
    threepp::Vector3 pos_;
    threepp::Euler rot_;
    float linearVelocity_ = 0;
    float turnSpeed_ = 0;// rad
};

#endif//CAR_HPP
