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

#pragma once

#include "component.h"
#include <unordered_map>
#include <memory>
#include <string>
#include <vector>

class GameObject
{
private:
    GameObject* Parent = nullptr;
    std::vector<GameObject*> Children;

    std::string Name;

protected:
    std::unordered_map<size_t, std::unique_ptr<Component>> Components;

public:
    ~GameObject();

    void Update();
    void Render();

    Component* AddComponent(std::unique_ptr<Component> component);
    void RemoveComponent(size_t componentID);
    Component* GetComponent(size_t componentID);

    template<class T>
    T* AddComponent()
    {
        return static_cast<T*>(AddComponent(std::make_unique<T>(*this)));
    }

    template<class T>
    void RemoveComponent()
    {
        RemoveComponent(T::GetComponentId());
    }

    template<class T>
    T* GetComponent()
    {
        return static_cast<T*>(GetComponent(T::GetComponentId()));
    }

    const std::vector<GameObject*>& GetChildren() const { return Children; }
    GameObject* GetParent() const { return Parent; }

    GameObject* AddChild();

    std::string_view GetName() const;
    void SetName(std::string_view name);
};