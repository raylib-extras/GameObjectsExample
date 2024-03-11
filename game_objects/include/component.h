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

#include <memory>

// macro to define common code that all components need
// computes a runtime unique ID for each component using the name
// NOTE that this ID is not deterministic, a real system would hash the name and use a better ID
#define DEFINE_COMPONENT(T) \
static const char* GetComponentName() { return #T;}  \
static size_t GetComponentId() { return reinterpret_cast<size_t>(#T); } \
inline size_t GetTypeId() const override { return GetComponentId(); } \
T(GameObject& object) : Component(object) {}

class GameObject;

class Component
{
private:
    GameObject& HostingObject;

protected:
    GameObject& GetGameObject() { return HostingObject; }
    const GameObject& GetGameObject() const { return HostingObject; }

public:
    virtual size_t GetTypeId() const = 0;

    Component(GameObject& object)
        : HostingObject(object)
    {
    }
    virtual ~Component() = default;

    // no copy
    Component(const Component&) = delete;
    Component& operator=(Component const&) = delete;

    Component* GetComponent(size_t componentID);

    template<class T>
    T* GetComponent()
    {
        return static_cast<T*>(GetComponent(T::GetComponentId()));
    }

    virtual void OnCreate() {};
    virtual void OnDestoy() {};
    virtual void OnUpdate() {};
    virtual void OnRender() {};
};