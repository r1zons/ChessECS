#include "enemy_ai.inl"
//Code-generator production

ecs::QueryDescription get_info_descr("get_info", {
  {ecs::get_type_description<Transform2D>("transform"), false},
  {ecs::get_type_description<vec2>("velocity"), false},
  {ecs::get_type_description<ecs::Tag>("mainHero"), false}
});

template<typename Callable>
void get_info(Callable lambda)
{
  for (ecs::QueryIterator begin = get_info_descr.begin(), end = get_info_descr.end(); begin != end; ++begin)
  {
    lambda(
      *begin.get_component<Transform2D>(0),
      *begin.get_component<vec2>(1)
    );
  }
}


ecs::QueryDescription get_info1_descr("get_info1", {
  {ecs::get_type_description<Transform2D>("transform"), false},
  {ecs::get_type_description<vec2>("velocity"), false},
  {ecs::get_type_description<ecs::Tag>("mainHero"), false}
});

template<typename Callable>
void get_info1(Callable lambda)
{
  for (ecs::QueryIterator begin = get_info1_descr.begin(), end = get_info1_descr.end(); begin != end; ++begin)
  {
    lambda(
      *begin.get_component<Transform2D>(0),
      *begin.get_component<vec2>(1)
    );
  }
}


void path_finder_func();

ecs::SystemDescription path_finder_descr("path_finder", {
  {ecs::get_type_description<Transform2D>("transform"), false},
  {ecs::get_type_description<vec2>("velocity"), false},
  {ecs::get_type_description<ecs::Tag>("enemy"), false}
}, path_finder_func, ecs::SystemOrder::LOGIC, (uint)(ecs::SystemTag::Game));

void path_finder_func()
{
  for (ecs::QueryIterator begin = path_finder_descr.begin(), end = path_finder_descr.end(); begin != end; ++begin)
  {
    path_finder(
      *begin.get_component<Transform2D>(0),
      *begin.get_component<vec2>(1)
    );
  }
}


void shoot_func();

ecs::SystemDescription shoot_descr("shoot", {
  {ecs::get_type_description<Transform2D>("transform"), false},
  {ecs::get_type_description<SpriteFactory>("sf"), false},
  {ecs::get_type_description<float>("timeSh"), false},
  {ecs::get_type_description<ecs::Tag>("enemy"), false}
}, shoot_func, ecs::SystemOrder::LOGIC, (uint)(ecs::SystemTag::Game));

void shoot_func()
{
  for (ecs::QueryIterator begin = shoot_descr.begin(), end = shoot_descr.end(); begin != end; ++begin)
  {
    shoot(
      *begin.get_component<Transform2D>(0),
      *begin.get_component<SpriteFactory>(1),
      *begin.get_component<float>(2)
    );
  }
}



