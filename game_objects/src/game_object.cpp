/*
-- Copyright (c) 2020-2024 Jeffery Myers
--
--This software is provided "as-is", without any express or implied warranty. In no event
--will the authors be held liable for any damages arising from the use of this software.

--Permission is granted to anyone to use this software for any purpose, including commercial
--applications, and to alter it and redistribute it freely, subject to the following restrictions:

--  1. The origin of this software must not be misrepresented; you must not claim that you
--  wrote the original software. If you use this software in a product, an acknowledgment
--  in the product documentation would be appreciated but is not required.
--
--  2. Altered source versions must be plainly marked as such, and must not be misrepresented
--  as being the original software.
--
--  3. This notice may not be removed or altered from any source distribution.
*/

#include "game_object.h"

GameObject::~GameObject()
{
    for (auto* child : Children)
        delete(child);
}

void GameObject::Update()
{
    for (auto& [id, componentPtr] : Components)
        componentPtr->OnUpdate();

    for (auto* child : Children)
        child->Update();
}

void GameObject::Render()
{
    for (auto& [id, componentPtr] : Components)
        componentPtr->OnRender();

    for (auto* child : Children)
        child->Render();
}

Component* GameObject::AddComponent(std::unique_ptr<Component> component)
{
    component->OnCreate();
    size_t id = component->GetTypeId();
    Components.insert_or_assign(id, std::move(component));
    return GetComponent(id);
}

void GameObject::RemoveComponent(size_t componentID)
{
    auto itr = Components.find(componentID);
    if (itr == Components.end())
        return;

    itr->second->OnDestoy();
    Components.erase(itr);
}

Component* GameObject::GetComponent(size_t componentID)
{
    auto itr = Components.find(componentID);
    if (itr == Components.end())
        return nullptr;

    return itr->second.get();
}

GameObject* GameObject::AddChild()
{
    GameObject* newChild = new GameObject();
    newChild->Parent = this;
    Children.emplace_back(newChild);
    return newChild;
}

std::string_view GameObject::GetName() const
{
    return Name;
}

void GameObject::SetName(std::string_view name)
{
    Name = name;
}

//----------------Component---------------------//
Component* Component::GetComponent(size_t componentID)
{
    return HostingObject.GetComponent(componentID);
}