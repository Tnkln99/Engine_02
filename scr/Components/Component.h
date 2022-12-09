#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>

class Object;

class Component{
private:
    std::string name;

    int updateOrder;
    Object * owner;
public:
    Component(const std::string & name, int updateOrder = 100);
    Component() = default;
    ~Component();

    [[nodiscard]] int getUpdateOrder() const;
    const Object * getOwner();
    const std::string & getName();

    virtual void load(Object * owner);

    //update function for all components
    virtual void update(float dt);

    virtual Component * clone() = 0;
};

#endif