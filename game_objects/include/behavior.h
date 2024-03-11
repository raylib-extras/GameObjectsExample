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
#include "raylib.h"

#define DEFINE_BEHAVIOR(T) \
T(GameObject& object) : GameObjectBehavior(object){}

class GameObjectBehavior : public Component
{
public:
    static const char* GetComponentName() { return "GameObjectBehavior"; }
    static size_t GetComponentId() { return reinterpret_cast<size_t>("GameObjectBehavior"); }
    inline size_t GetTypeId() const override { return GetComponentId(); }
    GameObjectBehavior(GameObject& object) : Component(object) {}

};
