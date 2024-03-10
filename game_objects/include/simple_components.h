#pragma once

#include "component.h"
#include "raylib.h"

class TransformComponent : public Component
{
private:
    Vector2 Translation = { 0 };
    float Rotation = 0;

public:
    DEFINE_COMPONENT(TransformComponent)

};