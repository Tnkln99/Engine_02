#ifndef OBJECT_H
#define OBJECT_H

#include "Embedded Components/Transformable.h"

#include <ctime>
#include "glad/glad.h"
#include <cmath>
#include <vector>
#include <string>
#include <memory>

class Component;
class ModelC;
class Scene;

class Object {
private:
    enum class Behavior{
        Destroy, Stack, Keep
    };

    Transformable transform;
    Scene * owner;

    std::vector<Component*> components;
    std::vector<ModelC*> modelComponents;
    Behavior behaviorOnLoad = Behavior::Destroy;

    std::string name;
public:
  Object(Scene* owner, float xP, float yP, float zP, std::string  name = "Object");
  ~Object();

  void setName(std::string name);

  void addComponent(Component * sub);
  void addModelComponents(ModelC * sub);

  template <typename T>
  T* findComponentByType() const{
      std::vector<Component*>::const_iterator it;
      for(it = components.begin(); it != components.end(); it++){
          if(T* type = dynamic_cast<T*>(*it)){
              return {type};
          }
      }
      return {nullptr};
  };

  std::vector<ModelC*> & getModelComponents();
  std::vector<Component*> & getComponents();
  const std::string & getName();
  Scene * getScene();
  Transformable & getTransform();

  virtual void updatePositionMessageSent();
  virtual void updatePerFrame(float dt);
};

#endif