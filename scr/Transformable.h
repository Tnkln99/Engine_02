#ifndef TRANSFORMABLE_H
#define TRANSFORMABLE_H

#include <glm/glm.hpp>

class Transformable {
private:
    glm::mat4 mvMatrix = glm::mat4(1.0f);
    glm::vec3 position = glm::vec3(0,0,0);

    glm::vec3 direction = glm::vec3(0.0f, 0.0f, -1.0f);;

    float yaw;
    float pitch;
    float roll;
public:
    [[nodiscard]] const glm::vec3 & getPosition() const;
    [[nodiscard]] const glm::mat4 & getMoveMatrix() const;
    [[nodiscard]] const glm::vec3 & getDirection() const;
    [[nodiscard]] float getYaw() const;
    [[nodiscard]] float getPitch() const;
    [[nodiscard]] float getRoll() const;

    void setPosition(float x, float y, float z);
    void setPosition(glm::vec3 position);

    void computeDirection(float yaw, float pitch);
};

#endif