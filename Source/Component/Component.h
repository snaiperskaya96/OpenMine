//
// Created by verrignij on 07/12/2017.
//

#ifndef OPENMINE_COMPONENT_H
#define OPENMINE_COMPONENT_H


class Component
{
public:
    virtual void Init();
    virtual void Draw();

    void SetOwner(class Entity* NewOwner);
protected:
    bool Initialised = false;
    class Entity* Owner = nullptr;
};


#endif //OPENMINE_COMPONENT_H
