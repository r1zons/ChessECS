#include <ecs/ecs.h>
#include <Engine/transform2d.h>
#include "game_structs.h"

EVENT() init_game(const StartGameEvent &, const SpriteFactory &sf, const ScoreBoard &sb)
{
  // int targetCount = 100 * (sb.curentLevel + 1);
  int targetCount = 5 * (sb.curentLevel + 1);
  float areaRadius = 25.f;
  float safeZone = 5.f;
  float density = 20.f;
  float minSize = 0.5f, maxSize = 1.5f;
  float mainHeroMaxHP = 100.0f;
  float mainHeroStartHP = 80.0f;
  float ratioForGreenHP = mainHeroStartHP / mainHeroMaxHP; 


  for (int i = 0; i < targetCount; i++)
  {
    Transform2D tr = Transform2D(normalize(rand_vec2()) * rand_float(safeZone, areaRadius),
                                vec2(rand_float(minSize, maxSize)),
                                rand_float() * PITWO);
    float m = tr.scale[0] * tr.scale[1] * density;
    ecs::create_entity<Sprite, Transform2D, vec2, float, vec4, float, float, ecs::Tag, ecs::Tag, ecs::EntityId, ecs::EntityId>(
      {"sprite", sf.asteroids[rand_int(AsteroidsCount)]},
      {"transform", tr},
      {"velocity", rand_vec2()},
      {"rotationVelocity", rand_float()*PI},
      {"color", vec4(rand_vec3(0.f, 1.f), 1)},
      {"curHP", 10.f},
      {"mass", m},
      {"target", {}},
      {"colidable", {}},
      {"healthBarEIDg", 0},
      {"healthBarEIDr", 0}
    );
  }

  ecs::create_entity<Sprite, Transform2D, vec2, vec2, vec4, int, bool, float, float, ecs::Tag, float, float, float, float, float>(
    {"sprite", sf.ship6},
    {"transform", Transform2D(vec2(0.f), vec2(1.f))},
    {"velocity", vec2(0.f)},
    {"accel", vec2(0.0, 0.0)},
    // {"color", vec4(1, 0.84f, 0, 1)},
    {"color", {1, 1, 1, 1}},
    {"killsCount", 0},
    {"isWinner", false},
    {"maxHP", mainHeroMaxHP},
    {"curHP", mainHeroStartHP},
    {"mainHero", {}},
    {"linearAccel", 35.0},
    {"strafeAccel", 20.0},
    {"inertiaCancel", 50.0},
    {"mass", 5.0},
    {"speedLimit", 50.0f}
  );

  ecs::create_entity<Sprite, Transform2D, vec4, ecs::Tag>(
    {"sprite", sf.hp_bar},
    {"transform", Transform2D(vec2(0.f), vec2(2, 0.05))},
    {"color", {1, 0, 0, 1}},
    {"redHPBar", {}}
  );

  ecs::create_entity<Sprite, Transform2D, vec4, ecs::Tag>(
    {"sprite", sf.hp_bar},
    {"transform", Transform2D(vec2(0.f), vec2(2 * ratioForGreenHP, 0.05))},
    {"color", {0, 1, 0, 1}},
    {"greenHPBar", {}}
  );

  ecs::create_entity<Sprite, Transform2D, vec2, vec2, vec4, int, int, ecs::Tag, ecs::Tag, ecs::Tag, float, float, float, float, float, float, float, ecs::EntityId, ecs::EntityId>(
    {"sprite", sf.ship6},
    {"transform", Transform2D(vec2(25,0), vec2(1.f))},
    {"velocity", vec2(0.f)},
    {"accel", vec2(0.0, 0.0)},
    // {"color", vec4(1, 0.84f, 0, 1)},
    {"color", {1, 1, 1, 1}},
    {"maxHP", 100},
    {"curHP", 100},
    {"enemy", {}},
    {"colidable", {}},
    {"target", {}},
    {"linearAccel", 35.0},
    {"strafeAccel", 20.0},
    {"inertiaCancel", 50.0},
    {"mass", 5.0},
    {"curHP", 30.0f},
    {"maxHP", 30.0f},
    {"timeSh", 0.0f},
    {"healthBarEIDg", 0},
    {"healthBarEIDr", 0}
  );

  ecs::create_entity<Sprite, Transform2D>(
    {"sprite", sf.background},
    {"transform", Transform2D(vec2(0.f), vec2(1.f))}
  );
  
}