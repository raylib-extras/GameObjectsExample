// C library
#include "game_object.h"


size_t NextObjectID = 0;

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
        return;

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
