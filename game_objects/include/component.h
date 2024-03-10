#pragma once

#include <memory>

// macro to define common code that all components need
// computes a runtime unique ID for each component using the name
// NOTE that this ID is not deterministic, a real ECS would hash the name and use a better ID
#define DEFINE_COMPONENT(T) \
static const char* GetComponentName() { return #T;}  \
static size_t GetComponentId() { return reinterpret_cast<size_t>(#T); } \
inline size_t GetTypeId() const override { return GetComponentId(); } \
T(GameObject& object) : Component(object) {}

class GameObject;

class Component
{

private:
    GameObject& ParentObject;

protected:
    GameObject& GetGameObject() { return ParentObject; }
    const GameObject& GetGameObject() const { return ParentObject; }

public:
    virtual size_t GetTypeId() const = 0;

    Component(GameObject& object)
        : ParentObject(object)
    {
    }
    virtual ~Component() = default;

    // no copy
    Component(const Component&) = delete;
    Component& operator=(Component const&) = delete;

    virtual void OnCreate() {};
    virtual void OnDestoy() {};
    virtual void OnUpdate() {};
    virtual void OnRender() {};
};