/*
Raylib example file.
This is an example main file for a simple raylib project.
Use this as a starting point or replace it with your code.

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

#include "raylib.h"
#include "raymath.h"

#include "game_object.h"
#include "simple_components.h"
#include "behavior.h"
#include "scene.h"

Scene TestScene;

Texture Wabbit = { 0 };
Texture Logo = { 0 };
Texture Sprite = { 0 };


// a simple behavior class that handles input
class PlayerController : public GameObjectBehavior
{
public:
    DEFINE_BEHAVIOR(PlayerController)

        float Speed = 300;

    void OnUpdate() override
    {
        TransformComponent* transform = GetComponent<TransformComponent>();
        if (!transform)
            return;

        Vector2 movement = { 0 };
        if (IsKeyDown(KEY_W))
            movement.y -= 1;
        if (IsKeyDown(KEY_S))
            movement.y += 1;

        if (IsKeyDown(KEY_A))
            movement.x -= 1;
        if (IsKeyDown(KEY_D))
            movement.x += 1;

        transform->SetPosition(Vector2Add(transform->GetPosition(), Vector2Scale(movement, Speed * GetFrameTime())));
    }
};

class Spiner : public GameObjectBehavior
{
public:
    DEFINE_BEHAVIOR(Spiner)

    float Speed = 180;

    void OnUpdate() override
    {
        TransformComponent* transform = GetComponent<TransformComponent>();
        if (!transform)
            return;

        transform->SetRotation(transform->GetRotation() + Speed * GetFrameTime());
        Vector2 movement = { 0 };
    }
};

void SetupScene()
{
    auto* player = TestScene.AddObject();
    player->AddComponent<TransformComponent>()->SetPosition(Vector2{ 100, 100 });
    player->AddComponent<PlayerController>();
    player->AddComponent<SpriteComponent>()->SetSprite(Wabbit);

    auto* logo = TestScene.AddObject();
    logo->AddComponent<TransformComponent>()->SetPosition(Vector2{ GetScreenWidth() * 0.5f, GetScreenHeight() * 0.5f });
    auto* sprite = logo->AddComponent<SpriteComponent>();
    sprite->SetSprite(Logo);
    sprite->SetScale(0.5f);

    auto* spinner = logo->AddChild();
    spinner->AddComponent<TransformComponent>();
    spinner->AddComponent<Spiner>();

    auto* orbit = spinner->AddChild();
    orbit->AddComponent<TransformComponent>()->SetPosition(Vector2{ 0, 200 });
    orbit->AddComponent<SpriteComponent>()->SetSprite(Wabbit);
}

void LoadResources()
{
    Wabbit = LoadTexture("resources/wabbit_alpha.png");
    Logo = LoadTexture("resources/raylib_logo.png");
    Sprite = LoadTexture("resources/scarfy.png");
}

int main()
{
    // set up the window
    InitWindow(1280, 800, "Game Object Test");

    LoadResources();
    SetupScene();

    // game loop
    while (!WindowShouldClose())
    {
        // drawing
        TestScene.Update();

        BeginDrawing();
        ClearBackground(TestScene.Background);

        TestScene.Render();

        EndDrawing();
    }

    // cleanup
    CloseWindow();
    return 0;
}