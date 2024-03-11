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

    DrawTextureRec(Sprite, SourceRect, Vector2Zero(), Tint);

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