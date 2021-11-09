#pragma once
#include <Engine/Render/sprite.h>

struct StartMenuEvent{};

struct StartGameEvent{};

struct KillTargetEvent{};

constexpr int FigureCount = 6;
constexpr int AsteroidsCount = 4;
struct SpriteFactory : ecs::Singleton
{
  Sprite figures[FigureCount];
  Sprite asteroids[AsteroidsCount];
  Sprite arrow, bullet, ship6, shot6_1;
};

struct ScoreBoard : ecs::Singleton
{
  int curentLevel;
  std::vector<int> kills;
};