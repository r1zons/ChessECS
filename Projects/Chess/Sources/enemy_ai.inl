#include <ecs/ecs.h>
#include <Engine/time.h>
#include <Engine/transform2d.h>
#include "game_structs.h"




template<typename Callable> void get_info(Callable);

SYSTEM(ecs::SystemOrder::LOGIC, ecs::Tag enemy) path_finder(
  const Transform2D &transform,
  vec2 &velocity
){
  vec2 vel;
  vec2 pos;
  float angle;
  QUERY (ecs::Tag mainHero) get_info([&](
    const Transform2D &transform,
    const vec2 &velocity)
  {
    vel = velocity;
    pos = transform.position;
    angle = transform.rotation;
  });
  vec2 dir = vec2(cos(angle), -sin(angle));
  dir = ((dir + vel) / -2.0f) * 10.0f;
  vec2 target_point = dir + pos;
  if (length(target_point - transform.position) > 1.0f & length(pos - transform.position) > 10.0f){
    velocity = normalize(target_point - transform.position);
    velocity *= 5.0f;
  } else {
    velocity = vec2(0.0f, 0.0f);
  }  
}


//обновить учитывая упреждение

template<typename Callable> void get_info1(Callable);

SYSTEM(ecs::SystemOrder::LOGIC, ecs::Tag enemy) shoot(
  Transform2D &transform,
  const SpriteFactory &sf,
  float &timeSh
)
{
  vec2 vel;
  vec2 pos;
  float angle;
  QUERY (ecs::Tag mainHero) get_info1([&](
    const Transform2D &transform,
    const vec2 &velocity)
  {
    vel = velocity;
    pos = transform.position;
    angle = transform.rotation;
  });
  transform.rotation = acos(normalize(pos - transform.position)[0]) * sign(normalize(pos - transform.position)[1]);
  if (timeSh > 0.5){
    create_bullet(transform.position, transform.rotation, 40, sf.shot_red, false);
    timeSh = 0.0f;
  } else {
    timeSh += Time::delta_time();
  }
}