#pragma once
#include <Engine/Render/sprite.h>

struct StartMenuEvent{};

struct StartGameEvent{};

struct KillTargetEvent{};

struct reduceMainHeroHP{};

struct DamageHero{
  float damage;
};

struct ShowBar{
  ecs::EntityId peid;
  float damage;
};

constexpr int AsteroidsCount = 4;
struct SpriteFactory : ecs::Singleton
{
  Sprite asteroids[AsteroidsCount];
  Sprite backs[3];
  Sprite ship6, shot6_1, hp_bar, background;
  Sprite back_blue, back_purp1, back_purp2, back_green;
  Sprite shot_purp, shot_green, shot_red;
};

struct ScoreBoard : ecs::Singleton
{
  int curentLevel;
  std::vector<int> kills;
};



void create_bullet(vec2 position, float rotation, float bulletVelocity, const Sprite &bulletSpite, bool friebdly);