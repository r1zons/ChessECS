#include <ecs/ecs.h>
#include <Engine/time.h>
#include <Engine/transform2d.h>
#include "game_structs.h"


SYSTEM(ecs::SystemOrder::LOGIC+1) move_all_entity_with_velocity(
  Transform2D &transform,
  const vec2 &velocity,
  float *rotationVelocity
)
{
  float dt = Time::delta_time();
  transform.position += velocity * dt;
  transform.rotation += (rotationVelocity ? *rotationVelocity : 0) * dt;
}

template<typename Callable> void gather_all_target_colliders(Callable);

SYSTEM(ecs::SystemOrder::LOGIC, ecs::Tag bullet) bullet_collision_detection(
  ecs::EntityId eid,
  const Transform2D &transform,
  const float damage
)
{
  vec2 bulletPosition = transform.position;
  float bulletRadius = transform.scale.x * 0.5f;
  bool penetrate = false;
  QUERY(ecs::Tag target) gather_all_target_colliders([&](
    ecs::EntityId eid,
    const Transform2D &transform,
    float &health)
  {
    if (health > 0.0001)
    {
      vec2 targetPosition = transform.position;
      float targetRadius = transform.scale.x * 0.5f;
      float dist = length(targetPosition - bulletPosition);
      if (dist < bulletRadius + targetRadius)
      {
        ecs::send_event<KillTargetEvent>(KillTargetEvent());
        penetrate = true;
        health -= damage;
        if (health < 0.0001){
          ecs::destroy_entity(eid);
        }
      }
    }
  });
  if (penetrate)
    ecs::destroy_entity(eid);
}


template<typename Callable> void check_all_colisions(Callable);


SYSTEM(ecs::SystemOrder::LOGIC, ecs::Tag mainHero) hero_collision_detection(
  const Transform2D &transform,
  vec2 &velocity,
  float mass)
{
  vec2 heroPosition = transform.position;
  float heroRadius = transform.scale.x * 0.5f;
  vec2 vel = velocity;
  float heroMass = mass;
  QUERY(ecs::Tag colidable) check_all_colisions([&](
    const Transform2D &transform,
    vec2 &velocity,
    const float mass
  )
  {
    float targetRadius = transform.scale.x * 0.5f;
    vec2 targetPosition = transform.position;
    float dist = length(targetPosition - heroPosition);
    if (dist < targetRadius + heroRadius)
    {
      struct DamageHero event = DamageHero();
      //event.damage = mass;
      event.damage = mass * 0.5;
      ecs::send_event<DamageHero>(event);
      float x_imp = heroMass * vel[0] + mass * velocity[0];
      float y_imp = heroMass * vel[1] + mass * velocity[1];
      //вычисляем новую скорость персонажа
      vel[0] = ((velocity[0] * 2) + (vel[0] * (heroMass / mass - 1.0))) / (heroMass / mass + 1.0);
      vel[1] = ((velocity[1] * 2) + (vel[1] * (heroMass / mass - 1.0))) / (heroMass / mass + 1.0);
      //вычисляем новую скорость цели
      velocity[0] = (x_imp - heroMass * vel[0]) / mass;
      velocity[1] = (y_imp - heroMass * vel[1]) / mass;

    }
  });
  velocity = vel;
}

SYSTEM(ecs::SystemOrder::LOGIC - 1, ecs::Tag mainHero) update_hero_velocity(
  vec2 &velocity,
  vec2 &accel,
  const float speedLimit,
  const float inertiaCancel)
{
  float dt = Time::delta_time();
  float sgn_x  = sign(velocity[0]), sgn_y = sign(velocity[1]);

  //елси не нулевое то разгоняемся
  if (length(accel) > 0.0001 & length(velocity) < speedLimit){
    velocity += accel * dt;
  }
  //иначе если не нулевая скорость тормозим
  else if (length(velocity) > 0.0001) {
    accel = (-velocity) / length(velocity);
    accel *= inertiaCancel;
    velocity += accel * dt;
    //проверяем что не летим в другую сторону
    if (abs(sign(velocity[0]) - sgn_x) > 0.0001){
      velocity[0] = 0;
    }
    if (abs(sign(velocity[1]) - sgn_y) > 0.0001){
      velocity[1] = 0;
    }
  }
}