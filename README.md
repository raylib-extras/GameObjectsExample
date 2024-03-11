# Game Object Example
Example of a basic game object system using components.

## Game Objects
A game object is an entity type class that can have children and a list of components. Game Objects are stored in a heiriachy.

## Components
Components are generic classes that can be derived from and attached to entities. They get update and render calls each frame where they can perform work.

## Scene
A scene is a collection of top level game objects.

# Is this an ECS?
No this is not an ECS, this is a game object system that uses components. It is written to perform in a similar way to how the Unity GameObject/Monobehavior system works.

## Why is this not an ECS?
The acronym of ECS stands for 3 things
  * Entities
  * Components
  * Systems

This project has entities(GameObjects) and Components, but does not contain systems. In a pure ECS the components themselves are data only and do not have logic. Additionaly ECS systems store all components together for rapid processing. This system stores the components on each entity to allow simple heirarchical trees.

## Example ECS
You can find an example ECS written in raylib here.

https://github.com/raylib-extras/simple_ecs

