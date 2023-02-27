#ifndef TRANSFORMABLE_H
#define TRANSFORMABLE_H

#include <glm/glm.hpp>

class Transform {
private:
    glm::mat4 modelMatrix = glm::mat4(1.0f);

    glm::mat4 transformMatrix = glm::mat4(1.0f);
    glm::mat4 scaleMatrix = glm::mat4(1.0f);

    glm::vec3 position = glm::vec3(0,0,0);
    glm::vec3 scale = glm::vec3(1,1,1);

    glm::vec3 direction = glm::vec3(0.0f, 0.0f, -1.0f);;

    float yaw;
    float pitch;
    float roll;
public:
    [[nodiscard]] const glm::vec3 & getPosition() const;
    [[nodiscard]] const glm::vec3 & getScale() const;
    [[nodiscard]] const glm::mat4 & getModelMatrix() const;
    [[nodiscard]] const glm::vec3 & getDirection() const;
    [[nodiscard]] float getYaw() const;
    [[nodiscard]] float getPitch() const;
    [[nodiscard]] float getRoll() const;

    void setPosition(float x, float y, float z);
    void setPosition(glm::vec3 position);

    void setScale(float x, float y, float z);
    void setScale(glm::vec3 scale);

    void computeDirection(float yaw, float pitch);
};

#endif