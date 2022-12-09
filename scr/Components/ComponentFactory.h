#ifndef ENGINE_02_COMPONENTFACTORY_H
#define ENGINE_02_COMPONENTFACTORY_H

#include "Component.h"
#include <map>

class ComponentFactory {
public:
    static std::map<std::string,Component*> m_map;
public:
    //Fonction qui associe clé <=> prototype
    static void Register(const std::string& key,Component* obj);

    //Celle qui va créer les objets
    [[nodiscard]] static Component* Create(const std::string& key);
};


#endif //ENGINE_02_COMPONENTFACTORY_H
