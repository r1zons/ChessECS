#include <ecs/ecs.h>
#include <Engine/transform2d.h>
#include "game_structs.h"


EVENT() init_game(const StartGameEvent &, const SpriteFactory &sf, const ScoreBoard &sb)
{
  int targetCount = 100 * (sb.curentLevel + 1);
  float areaRadius = 25.f;
  float safeZone = 5.f;
  float density = 5.f;
  float minSize = 0.5f, maxSize = 1.5f;
  
  for (int i = 0; i < targetCount; i++)
  {
    Transform2D tr = Transform2D(normalize(rand_vec2()) * rand_float(safeZone, areaRadius),
                                vec2(rand_float(minSize, maxSize)),
                                rand_float() * PITWO);
    float m = tr.scale[0] * tr.scale[1] * density;
    ecs::create_entity<Sprite, Transform2D, vec2, float, vec4, bool, float, ecs::Tag>(
      {"sprite", sf.asteroids[rand_int(AsteroidsCount)]},
      {"transform", tr},
      {"velocity", rand_vec2()},
      {"rotationVelocity", rand_float()*PI},
      {"color", vec4(rand_vec3(0.f, 1.f), 1)},
      {"destroyed", false},
      {"mass", m},
      {"target", {}}
    );
  }

  ecs::create_entity<Sprite, Transform2D, vec2, vec2, vec4, int, bool, int, int, ecs::Tag, float, float, float, float>(
    {"sprite", sf.ship6},
    {"transform", Transform2D(vec2(0.f), vec2(1.f))},
    {"velocity", vec2(0.f)},
    {"accel", vec2(0.0, 0.0)},
    // {"color", vec4(1, 0.84f, 0, 1)},
    {"color", {1, 1, 1, 1}},
    {"killsCount", 0},
    {"isWinner", false},
    {"maxHP", 100},
    {"curHP", 100},
    {"mainHero", {}},
    {"linearAccel", 35.0},
    {"strafeAccel", 20.0},
    {"inertiaCancel", 50.0},
    {"mass", 5.0}
  );

}