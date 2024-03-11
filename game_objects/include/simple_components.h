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

#include <vector>
#include <string>
#include <unordered_map>

class TransformComponent : public Component
{
private:
    Vector2 Translation = { 0 };
    float Rotation = 0;

public:
    DEFINE_COMPONENT(TransformComponent)

    void SetPosition(const Vector2& pos);
    Vector2 GetPosition() const;

    void SetRotation(float rotation);
    float GetRotation() const;

    void PushMatrix();
    void PopMatrix();
};

class SpriteComponent : public Component
{
private:
    Texture2D Sprite = { 0 };
    Rectangle SourceRect = { 0,0,-1,-1 };
    Color Tint = WHITE;
    float Scale = 1.0f;

public:
    DEFINE_COMPONENT(SpriteComponent)

    void OnRender() override;

    void SetSprite(const Texture2D& texture);
    void SetSprite(const Texture2D& texture, const Rectangle& sourceRect);
    void SetSpriteRect(const Rectangle& sourceRect);

    void SetTint(Color tint);
    Color GetTint() const;

    void SetScale(float scale);
    float GetScale() const;
};

struct AnimationSequence
{
    std::vector<Rectangle> Frames;
    float FPS = 15;
    bool Loop = true;

    void FlipFrames(bool flipX, bool flipY);

    void FromSpriteSheet(Texture2D& texture, int frameWidth, int frameHeight);
};

class SpriteAnimationComponent : public Component
{
private:
    std::unordered_map<std::string, AnimationSequence> Sequences;
    std::string CurrentSequence;

    int CurrentFrame = 0;
    float LastFrameTime = 0;

public: 
    DEFINE_COMPONENT(SpriteAnimationComponent)

    void OnUpdate() override;

    AnimationSequence& AddSequence(std::string_view name);

    void SetCurrentSequence(std::string_view sequenceName);
    void ResetSequence();

    bool IsAnimating() const;
};