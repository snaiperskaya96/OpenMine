//
// Created by verrignij on 07/12/2017.
//

#include "Component.h"
#include "Entity/Entity.h"

void Component::Init()
{
    Initialised = true;
}

void Component::Draw()
{

}

void Component::SetOwner(Entity *NewOwner)
{
    Owner = NewOwner;
}
