#pragma once
#include <vector>
#include <memory>
#include <typeindex>
#include <unordered_map>
#include "Component.hpp"

class Entity {
public:
    bool active = true;

    template<typename T, typename... Args>
    T* addComponent(Args&&... args) {
        auto comp = std::make_unique<T>(std::forward<Args>(args)...);
        comp->owner = this;
        T* ptr = comp.get();
        components[std::type_index(typeid(T))] = std::move(comp);
        return ptr;
    }

    template<typename T>
    T* getComponent() {
        auto it = components.find(std::type_index(typeid(T)));
        if (it != components.end())
            return static_cast<T*>(it->second.get());
        return nullptr;
    }



private:
    std::unordered_map<std::type_index, std::unique_ptr<Component>> components;
};