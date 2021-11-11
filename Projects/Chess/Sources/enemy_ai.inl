#include <ecs/ecs.h>
#include <Engine/time.h>
#include <Engine/transform2d.h>
#include "game_structs.h"




template<typename Callable> void get_info(Callable);

SYSTEM(ecs::SystemOrder::LOGIC, ecs::Tag enemy) path_finder(
  Transform2D &transform,
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
  debug_log("dir: %f %f", dir[0], dir[1]);
  dir = ((dir + vel) / -2.0f) * 10.0f;
  debug_log("target place: %f %f", dir[0], dir[1]);
  vec2 target_point = dir + pos;
  if (length(target_point - transform.position) > 1.0f & length(pos - transform.position) > 10.0f){
    velocity = normalize(target_point - transform.position);
    transform.rotation = acos(velocity[0] * .0f + velocity[1] * 1.0f) * sign(velocity[0]);
    velocity *= 5.0f;
  } else {
    velocity = vec2(0.0f, 0.0f);
  }  
}