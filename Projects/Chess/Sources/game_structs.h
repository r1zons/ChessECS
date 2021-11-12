#pragma once
#include <Engine/Render/sprite.h>

struct StartMenuEvent{};

struct StartGameEvent{};

struct KillTargetEvent{};

struct reduceMainHeroHP{};

struct DamageHero{
  float damage;
};

constexpr int FigureCount = 6;
constexpr int AsteroidsCount = 4;
struct SpriteFactory : ecs::Singleton
{
  Sprite figures[FigureCount];
  Sprite asteroids[AsteroidsCount];
  Sprite arrow, bullet, ship6, shot6_1, hp_bar, background;
};

struct ScoreBoard : ecs::Singleton
{
  int curentLevel;
  std::vector<int> kills;
};



void create_bullet(vec2 position, float rotation, float bulletVelocity, const Sprite &bulletSpite, bool friebdly);