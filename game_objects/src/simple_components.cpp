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

#include "simple_components.h"
#include "game_object.h"

#include "raylib.h"
#include "rlgl.h"
#include "raymath.h"

void TransformComponent::SetPosition(const Vector2& pos)
{
    Translation = pos;
}

Vector2 TransformComponent::GetPosition() const
{
    return Translation;
}

void TransformComponent::SetRotation(float rotation)
{
    Rotation = rotation;
}

float TransformComponent::GetRotation() const
{
    return Rotation;
}

void TransformComponent::PushMatrix()
{
    GameObject& object = GetGameObject();

    GameObject* parent = object.GetParent();
    if (parent)
    {
        TransformComponent* parentTransfom = parent->GetComponent<TransformComponent>();
        if (parentTransfom)
            parentTransfom->PushMatrix();
    }

    rlPushMatrix();
    rlTranslatef(Translation.x, Translation.y, 0);
    rlRotatef(Rotation, 0, 0, 1);
}

void TransformComponent::PopMatrix()
{
    rlPopMatrix();

    GameObject& object = GetGameObject();

    GameObject* parent = object.GetParent();
    if (parent)
    {
        TransformComponent* parentTransfom = parent->GetComponent<TransformComponent>();
        if (parentTransfom)
            parentTransfom->PopMatrix();
    }
}


//-----------------------SpriteComponent-------------------------//
void SpriteComponent::OnRender()
{
    if (!IsTextureReady(Sprite))
        return;

    TransformComponent* transform = GetComponent<TransformComponent>();
    if (transform)
        transform->PushMatrix();

    Rectangle destRect = { 0, 0, fabsf(SourceRect.width * Scale), fabsf(SourceRect.height * Scale) };

    DrawTexturePro(Sprite, SourceRect, destRect, Vector2{ destRect.width *0.5f, destRect.height*0.5f}, 0, Tint);

    if (transform)
        transform->PopMatrix();
}

void SpriteComponent::SetSprite(const Texture2D& texture)
{
    SetSprite(texture, Rectangle{ 0,0,float(texture.width),float(texture.height) });
}

void SpriteComponent::SetSprite(const Texture2D& texture, const Rectangle& sourceRect)
{
    Sprite = texture;
    SourceRect = sourceRect;
}

void SpriteComponent::SetSpriteRect(const Rectangle& sourceRect)
{
    SourceRect = sourceRect;
}

void SpriteComponent::SetTint(Color tint)
{
    Tint = tint;
}

Color SpriteComponent::GetTint() const
{
    return Tint;
}

void SpriteComponent::SetScale(float scale)
{
    Scale = scale;
}

float SpriteComponent::GetScale() const
{
    return Scale;
}

//-----------------------AnimationSequence-------------------------//

void AnimationSequence::FlipFrames(bool flipX, bool flipY)
{
    for (auto& rect : Frames)
    {
        if (flipX)
            rect.width *= -1;
        if (flipY)
            rect.height *= -1;
    }
}

void AnimationSequence::FromSpriteSheet(Texture2D& texture, int frameWidth, int frameHeight)
{
    Frames.clear();
    for (int y = 0; y < texture.height; y += frameHeight)
    {
        for (int x = 0; x < texture.width; x += frameWidth)
        {
            Frames.emplace_back(Rectangle{ float(x), float(y), float(frameWidth), float(frameHeight) });
        }
    }
}

//-----------------------SpriteAnimationComponent-------------------------//

void SpriteAnimationComponent::OnUpdate()
{
    auto itr = Sequences.find(CurrentSequence);
    if (itr == Sequences.end())
        return;

    AnimationSequence& sequence = itr->second;

    SpriteComponent* sprite = GetComponent<SpriteComponent>();
    if (!sprite)
        return;

    LastFrameTime += GetFrameTime();

    float fpsTime = 1.0f / sequence.FPS;

    while (LastFrameTime >= fpsTime)
    {
        LastFrameTime -= fpsTime;
        CurrentFrame++;

        if (CurrentFrame >= sequence.Frames.size())
        {
            if (sequence.Loop)
                CurrentFrame = 0;
            else
                CurrentFrame = int(sequence.Frames.size());
        }
    }

    if (CurrentFrame < sequence.Frames.size())
        sprite->SetSpriteRect(sequence.Frames[CurrentFrame]);
}

AnimationSequence& SpriteAnimationComponent::AddSequence(std::string_view name)
{
    if (CurrentSequence.empty())
        CurrentSequence = name;

    auto itr = Sequences.find(std::string(name));
    if (itr != Sequences.end())
        return itr->second;

    Sequences.emplace(name, AnimationSequence());

    return Sequences[std::string(name)];
}

void SpriteAnimationComponent::SetCurrentSequence(std::string_view sequenceName)
{
    CurrentSequence = sequenceName;
    ResetSequence();
}

void SpriteAnimationComponent::ResetSequence()
{
    CurrentFrame = 0;
    LastFrameTime = 0;
}

bool SpriteAnimationComponent::IsAnimating() const
{
    auto itr = Sequences.find(CurrentSequence);
    if (itr == Sequences.end())
        return false;

    if (itr->second.Loop)
        return true;

    return CurrentFrame < itr->second.Frames.size();
}
