#pragma once
class Entity; 

class Component {
public:
    Entity* owner = nullptr;

    virtual ~Component() = default;
};