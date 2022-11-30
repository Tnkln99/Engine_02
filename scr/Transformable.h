#ifndef TRANSFORMABLE_H
#define TRANSFORMABLE_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Transformable {
private:
    glm::mat4 mvMatrix;
    glm::vec3 position;

    glm::vec3 direction;

    float yaw;
    float pitch;
    float roll;
public:
    const glm::vec3 & getPosition() const;
    const glm::mat4 & getMoveMatrix() const;
    [[nodiscard]] float getYaw() const;
    [[nodiscard]] float getPitch() const;
    [[nodiscard]] float getRoll() const;

    void setPosition(float x, float y, float z);
    void setPosition(glm::vec3 position);
    void setYaw(float yaw);
    void setPitch(float pitch);
    void setRoll(float fov);

    void computeDirection();
};

#endif