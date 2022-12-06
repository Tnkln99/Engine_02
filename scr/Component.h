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
    Component(Object * owner, const std::string & name, int updateOrder = 100);
    ~Component();

    [[nodiscard]] int getUpdateOrder() const;
    const Object * getOwner();
    const std::string & getName();

    //Calling this after every component added to the same owner
    virtual void onComponentAdd();
    //update function for all components
    virtual void update(float dt);
};

#endif