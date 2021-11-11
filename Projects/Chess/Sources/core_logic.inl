#include <ecs/ecs.h>
#include <Engine/time.h>
#include <Engine/Render/world_renderer.h>
#include <Engine/transform2d.h>
#include <Engine/input.h>
#include "game_structs.h"


SYSTEM(ecs::SystemOrder::LOGIC, ecs::Tag target) controll_targets(
  Transform2D &transform,
  vec2 &velocity
)
{
  float dt = Time::delta_time();
  vec2 acceleration = rand_vec2() * 15.f;

  constexpr float arenaRadius = 5.f;
  constexpr float additionalForce = 1.5f;
  if (length(transform.position) > arenaRadius)
  {
    acceleration -= normalize(transform.position) * additionalForce;
  }
  velocity += acceleration * dt;
}



EVENT(ecs::Tag mainHero) look_at_mouse_position_when_mouse_moves(
  const MouseMoveEvent &event,
  const WorldRenderer &wr,
  Transform2D &transform)
{
  vec2 worldPos = wr.screen_to_world(event.x, event.y);
  vec2 direction = worldPos - transform.position;
  transform.rotation = atan2f(direction.x, direction.y) - PIHALF;
}

void create_bullet(vec2 position, float rotation, float bulletVelocity, const Sprite &bulletSpite, bool friebdly)
{
  vec2 velocity = vec2(cos(rotation), sin(rotation));
  constexpr float bulletLifeTime = 2.f;
  float curTime = Time::time();


  if (friebdly){
    ecs::create_entity<Sprite, Transform2D, vec2, float, float, ecs::Tag, float>(
      {"sprite", bulletSpite},
      {"transform", Transform2D(position, vec2(0.5f), -rotation)},
      {"velocity", velocity * bulletVelocity},
      {"creationTime", curTime},
      {"lifeTime", bulletLifeTime},
      {"bullet", {}},
      {"damage", 10.0f}
    );
  } else {
    ecs::create_entity<Sprite, Transform2D, vec2, float, float, ecs::Tag, float>(
      {"sprite", bulletSpite},
      {"transform", Transform2D(position, vec2(0.5f), -rotation)},
      {"velocity", velocity * bulletVelocity},
      {"creationTime", curTime},
      {"lifeTime", bulletLifeTime},
      {"enemy_bullet", {}},
      {"damage", 10.0f}
    );
  }
}

EVENT(ecs::Tag mainHero) fire_when_mouse_click(
  const MouseClickEvent<MouseButton::LeftButton> &event,
  const WorldRenderer &wr,
  const SpriteFactory &sf,
  const Transform2D &transform,
  bool isWinner)
{
  if (event.action != MouseAction::Down || isWinner)
    return;
  vec2 worldPos = wr.screen_to_world(event.x, event.y);
  vec2 direction = worldPos - transform.position;
  create_bullet(transform.position, atan2f(direction.y, direction.x), 25, sf.shot6_1, true);
}

EVENT(ecs::Tag mainHero) circle_attack(
  const KeyDownEvent<SDLK_SPACE> &,
  const Transform2D &transform,
  const SpriteFactory &sf)
{
  for (float angle = 0; angle < PITWO; angle += PITWO / 6)
  {
    create_bullet(transform.position, -transform.rotation + angle, 8, sf.shot6_1, true);
  }
}

SYSTEM(ecs::SystemOrder::LOGIC+1, ecs::Tag bullet) destroy_old_bullets(
  ecs::EntityId eid,
  float creationTime,
  float lifeTime
)
{
  float curTime = Time::time();
  if (creationTime + lifeTime < curTime)
    ecs::destroy_entity(eid);
}


SYSTEM(ecs::SystemOrder::NO_ORDER, ecs::Tag mainHero) get_accel_from_keyboard(
  const Transform2D &transform,
  vec2 &accel,
  float linearAccel,
  float strafeAccel,
  bool isWinner)
{
  if (isWinner)
    return;
  //вичисляет ускорение с клавиатуры 
  accel = glm::rotate(
     vec2((Input::get_key(SDLK_w, 0.0) - Input::get_key(SDLK_s, 0.0)) * linearAccel,
          (Input::get_key(SDLK_a, 0.0) - Input::get_key(SDLK_d, 0.0)) * strafeAccel),
      -transform.rotation);
}


