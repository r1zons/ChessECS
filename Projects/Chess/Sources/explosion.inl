#include <ecs/ecs.h>
#include <Engine/Render/world_renderer.h>
#include <Application/application.h>
#include <Engine/Render/Shader/shader.h>
#include <Engine/transform2d.h>
#include <Engine/imgui/imgui.h>
#include <Application/application_data.h>
#include <Engine/input.h>
#include "game_structs.h"

EVENT() deathExplosion(
  const ShowExp &event,
  const SpriteFactory &sf) 
{ 
  ecs::create_entity<Sprite, int, int, Transform2D, vec4, ecs::Tag, float>(
    {"sprite", sf.exp1[0]},
    {"frame", 0},
    {"frameCount", 8},
    {"transform", Transform2D(event.pos, vec2(1.f))},
    {"color", {1, 1, 1, 1}},
    {"explosion", {}},
    {"lifespan", 0.1f});

}

SYSTEM(ecs::SystemOrder::RENDER, ecs::Tag explosion) changeFrame(
  float &lifespan,
  int &frame,
  const int &frameCount,
  ecs::EntityId eid,
  Sprite &sprite,
  const SpriteFactory &sf)
{
  if (lifespan < 0.0001){
    if (frame == frameCount - 1) {
      ecs::destroy_entity(eid);
      return;
    } else {
      frame++;
      sprite = sf.exp1[frame];
      lifespan = 0.1f;
    }
  } else {
    lifespan -= Time::delta_time();
  }
}
