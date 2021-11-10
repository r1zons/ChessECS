#include <ecs/ecs.h>
#include <Engine/transform2d.h>
#include "game_structs.h"




template<typename Callable> void get_info(Callable);

SYSTEM(ecs::SystemOrder::LOGIC, ecs::Tag enemy) path_finder(
  vec2 &velocity,
  vec2 &accel,
  float inertiaCancel
){
  QUERY (ecs::Tag mainHero) get_info([&](
    const Transform2D &transform,
    const vec2 &velocity,
    const vec2 &accel,
    const float inertiaCancel)
  {

  });
}