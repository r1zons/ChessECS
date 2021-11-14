#include <ecs/ecs.h>
#include <Engine/Render/world_renderer.h>
#include <Application/application.h>
#include <Engine/Render/Shader/shader.h>
#include <Engine/transform2d.h>
#include <Engine/imgui/imgui.h>
#include <Application/application_data.h>
#include <Engine/input.h>
#include "game_structs.h"


template<typename Callable> void update_red_hp_bar_position(Callable);

SYSTEM(ecs::SystemOrder::RENDER - 1, ecs::Tag mainHero) update_red_hp_bar(
  const Transform2D &transform)
{
  vec2 heroPosition = transform.position;
  
  QUERY(ecs::Tag redHPBar) update_red_hp_bar_position([heroPosition](Transform2D &transform)
  {
    transform.position = {heroPosition.x - 1.1, heroPosition.y + 1.3};
  });
}

template<typename Callable> void update_green_hp_bar_position(Callable);

SYSTEM(ecs::SystemOrder::RENDER, ecs::Tag mainHero) update_green_hp_bar(
  const Transform2D &transform)
{
  vec2 heroPosition = transform.position;

  QUERY(ecs::Tag greenHPBar) update_green_hp_bar_position([&](Transform2D &transform)
  {
    transform.position = {heroPosition.x - 1.1, heroPosition.y + 1.3}; 
  });
}


template<typename Callable> void update_green_hp_bar_length(Callable);


EVENT(ecs::Tag mainHero) update_green_hp_bar_points(
  const DamageHero &event,
  float &curHP,
  float &lifespan,
  bool &lost,
  const float maxHP) 
{ 
  debug_log("%f %f", event.damage, curHP);
  float oldHP = curHP;
  lifespan = 0.5;
  curHP = curHP - event.damage >= 0.f ? curHP - event.damage : 0.f;
  if (curHP == 0.f) {
    // завершение уровня
    lost = true;
  }
  QUERY(ecs::Tag greenHPBar) update_green_hp_bar_length([&](Transform2D &transform)
  {
    transform.scale[0] = transform.scale[0] * (maxHP / oldHP) * (curHP / maxHP); 
  });
}


template<typename Callable> void get_data(const ecs::EntityId&, Callable);
template<typename Callable> void update_lifespan1(const ecs::EntityId&, Callable);
template<typename Callable> void update_lifespan2(const ecs::EntityId&, Callable);


EVENT() create_bar(
  const ShowBar &event,
  const SpriteFactory &sf)
{
  ecs::EntityId id = event.peid;

  
  QUERY() get_data(id, [&](
    const Transform2D &transform,
    float &curHP,
    float &maxHP,
    ecs::EntityId &healthBarEIDr,
    ecs::EntityId &healthBarEIDg
    )
    {
      int eid = healthBarEIDr;
      if (eid == 0){
        curHP -= event.damage;
        healthBarEIDr = ecs::create_entity<Sprite, Transform2D, vec4, ecs::Tag, float, ecs::EntityId>(
          {"sprite", sf.hp_bar},
          {"transform", Transform2D(transform.position, vec2(2 , 0.05))},
          {"color", {1, 0, 0, 1}},
          {"enemyGreenBar", {}},
          {"lifespan", 5.0f},
          {"parentEID", id});
        healthBarEIDg = ecs::create_entity<Sprite, Transform2D, vec4, ecs::Tag, float, ecs::EntityId>(
          {"sprite", sf.hp_bar},
          {"transform", Transform2D(transform.position, vec2(2 * curHP / maxHP, 0.05))},
          {"color", {0, 1, 0, 1}},
          {"enemyRedBar", {}},
          {"lifespan", 5.0f},
          {"parentEID", id});
      } else {
        debug_log("Here");
        QUERY() update_lifespan1(healthBarEIDr, [&](float &lifespan)
        {
          lifespan = 5.0f;
        });
        QUERY() update_lifespan2(healthBarEIDg, [&](
          float &lifespan,
          Transform2D &transform)
        {
          lifespan = 5.0f;
          debug_log("%f %f", curHP, maxHP);
          transform.scale[0] = transform.scale[0] * (maxHP / curHP) * ((curHP - event.damage) / maxHP);
          curHP -= event.damage;
        });
      }
    });
}


SYSTEM(ecs::SystemOrder::RENDER, ecs::Tag mainHero) reddingWhenHit(
  vec4 &color,
  float &lifespan)
{
  if (lifespan < 0.0001){
    color = {1, 1, 1, 1};
  } else {
    lifespan -= Time::delta_time();
    color = {1, 0, 0, 1};
  }
}



template<typename Callable> void get_pr_data(const ecs::EntityId&, Callable);


SYSTEM(ecs::SystemOrder::RENDER, ecs::Tag enemyRedBar) update_red_bars(
  ecs::EntityId eid,
  Transform2D &transform,
  float &lifespan,
  ecs::EntityId parentEID)
  {
  if (lifespan < 0.0001){
    ecs::destroy_entity(eid);
  } else {
    lifespan -= Time::delta_time();
    vec2 pos = vec2(0.0f,0.0f);
    QUERY() get_pr_data(parentEID, [&](const Transform2D &transform)
    {
      pos = transform.position;
    });
    transform.position = pos - vec2(1.1f, -1.3f);
  }
}


template<typename Callable> void get_pr_data1(const ecs::EntityId&, Callable);
SYSTEM(ecs::SystemOrder::RENDER, ecs::Tag enemyGreenBar) update_green_bars(
  ecs::EntityId eid,
  Transform2D &transform,
  float &lifespan,
  ecs::EntityId parentEID)
  {
  if (lifespan < 0.0001){
    ecs::destroy_entity(eid);
  } else {
    lifespan -= Time::delta_time();
    vec2 pos = vec2(0.0f,0.0f);
    QUERY() get_pr_data1(parentEID, [&](const Transform2D &transform)
    {
      pos = transform.position;
    });
    transform.position = pos - vec2(1.1f, -1.3f);
  }
}