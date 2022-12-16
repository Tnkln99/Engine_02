#include "ComponentFactory.h"
#include <iostream>

std::map<std::string,Component*> ComponentFactory::m_map= std::map<std::string,Component*>();

void ComponentFactory::Register(const std::string& key,Component* obj)
{
    //si la clé n'est pas déjà présente
    if(m_map.find(key)==m_map.end())
    {
        //on ajoute l'objet dans la map
        m_map[key]=obj;
    }

    //on pourrait détruire obj mais cette tâche ne revient pas à Register
}

Component* ComponentFactory::Create(const std::string& key)
{
    Component* tmp= nullptr;
    auto it=m_map.find(key);

    //si l'itérateur ne vaut pas map.end(), cela signifie que que la clé à été trouvée
    if(it!=m_map.end())
    {
        tmp=((*it).second)->clone();
    }

    //on pourrait lancer une exeption si la clé n'a pas été trouvée

    return tmp;
}

void ComponentFactory::clear() {
    for(auto & pair : m_map){
        delete pair.second;
    }
}
