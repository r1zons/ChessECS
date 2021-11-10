#include "physics_systems.inl"
//Code-generator production

ecs::QueryDescription gather_all_target_colliders_descr("gather_all_target_colliders", {
  {ecs::get_type_description<ecs::EntityId>("eid"), false},
  {ecs::get_type_description<Transform2D>("transform"), false},
  {ecs::get_type_description<bool>("destroyed"), false},
  {ecs::get_type_description<ecs::Tag>("target"), false}
});

template<typename Callable>
void gather_all_target_colliders(Callable lambda)
{
  for (ecs::QueryIterator begin = gather_all_target_colliders_descr.begin(), end = gather_all_target_colliders_descr.end(); begin != end; ++begin)
  {
    lambda(
      *begin.get_component<ecs::EntityId>(0),
      *begin.get_component<Transform2D>(1),
      *begin.get_component<bool>(2)
    );
  }
}


ecs::QueryDescription check_all_colisions_descr("check_all_colisions", {
  {ecs::get_type_description<Transform2D>("transform"), false},
  {ecs::get_type_description<vec2>("velocity"), false},
  {ecs::get_type_description<bool>("destroyed"), false},
  {ecs::get_type_description<float>("mass"), false},
  {ecs::get_type_description<ecs::Tag>("target"), false}
});

template<typename Callable>
void check_all_colisions(Callable lambda)
{
  for (ecs::QueryIterator begin = check_all_colisions_descr.begin(), end = check_all_colisions_descr.end(); begin != end; ++begin)
  {
    lambda(
      *begin.get_component<Transform2D>(0),
      *begin.get_component<vec2>(1),
      *begin.get_component<bool>(2),
      *begin.get_component<float>(3)
    );
  }
}


void move_all_entity_with_velocity_func();

ecs::SystemDescription move_all_entity_with_velocity_descr("move_all_entity_with_velocity", {
  {ecs::get_type_description<Transform2D>("transform"), false},
  {ecs::get_type_description<vec2>("velocity"), false},
  {ecs::get_type_description<float>("rotationVelocity"), true}
}, move_all_entity_with_velocity_func, ecs::SystemOrder::LOGIC+1, (uint)(ecs::SystemTag::Game));

void move_all_entity_with_velocity_func()
{
  for (ecs::QueryIterator begin = move_all_entity_with_velocity_descr.begin(), end = move_all_entity_with_velocity_descr.end(); begin != end; ++begin)
  {
    move_all_entity_with_velocity(
      *begin.get_component<Transform2D>(0),
      *begin.get_component<vec2>(1),
       begin.get_component<float>(2)
    );
  }
}


void bullet_collision_detection_func();

ecs::SystemDescription bullet_collision_detection_descr("bullet_collision_detection", {
  {ecs::get_type_description<ecs::EntityId>("eid"), false},
  {ecs::get_type_description<Transform2D>("transform"), false},
  {ecs::get_type_description<ecs::Tag>("bullet"), false}
}, bullet_collision_detection_func, ecs::SystemOrder::LOGIC, (uint)(ecs::SystemTag::Game));

void bullet_collision_detection_func()
{
  for (ecs::QueryIterator begin = bullet_collision_detection_descr.begin(), end = bullet_collision_detection_descr.end(); begin != end; ++begin)
  {
    bullet_collision_detection(
      *begin.get_component<ecs::EntityId>(0),
      *begin.get_component<Transform2D>(1)
    );
  }
}


void hero_collision_detection_func();

ecs::SystemDescription hero_collision_detection_descr("hero_collision_detection", {
  {ecs::get_type_description<Transform2D>("transform"), false},
  {ecs::get_type_description<vec2>("velocity"), false},
  {ecs::get_type_description<float>("mass"), false},
  {ecs::get_type_description<ecs::Tag>("mainHero"), false}
}, hero_collision_detection_func, ecs::SystemOrder::LOGIC, (uint)(ecs::SystemTag::Game));

void hero_collision_detection_func()
{
  for (ecs::QueryIterator begin = hero_collision_detection_descr.begin(), end = hero_collision_detection_descr.end(); begin != end; ++begin)
  {
    hero_collision_detection(
      *begin.get_component<Transform2D>(0),
      *begin.get_component<vec2>(1),
      *begin.get_component<float>(2)
    );
  }
}


void update_hero_velocity_func();

ecs::SystemDescription update_hero_velocity_descr("update_hero_velocity", {
  {ecs::get_type_description<vec2>("velocity"), false},
  {ecs::get_type_description<vec2>("accel"), false},
  {ecs::get_type_description<float>("inertiaCancel"), false},
  {ecs::get_type_description<ecs::Tag>("mainHero"), false}
}, update_hero_velocity_func, ecs::SystemOrder::LOGIC - 1, (uint)(ecs::SystemTag::Game));

void update_hero_velocity_func()
{
  for (ecs::QueryIterator begin = update_hero_velocity_descr.begin(), end = update_hero_velocity_descr.end(); begin != end; ++begin)
  {
    update_hero_velocity(
      *begin.get_component<vec2>(0),
      *begin.get_component<vec2>(1),
      *begin.get_component<float>(2)
    );
  }
}



