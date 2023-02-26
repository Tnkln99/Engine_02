#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>
#include <memory>


class Object;

class Component{
private:
    std::string name;

    int updateOrder{};
    Object * owner{};
public:
    explicit Component(const std::string & name, int updateOrder = 100);
    Component() = default;
    virtual ~Component();

    [[nodiscard]] int getUpdateOrder() const;
    Object * getOwner();
    const std::string & getName();

    virtual void load(Object * owner);

    //update function for all components
    virtual void update(float dt);
    virtual void positionUpdateMessageReceived();

    virtual Component* clone() = 0;
};

#endif