#include "enemy_ai.inl"
//Code-generator production

ecs::QueryDescription get_info_descr("get_info", {
  {ecs::get_type_description<Transform2D>("transform"), false},
  {ecs::get_type_description<vec2>("velocity"), false},
  {ecs::get_type_description<vec2>("accel"), false},
  {ecs::get_type_description<float>("inertiaCancel"), false},
  {ecs::get_type_description<ecs::Tag>("mainHero"), false}
});

template<typename Callable>
void get_info(Callable lambda)
{
  for (ecs::QueryIterator begin = get_info_descr.begin(), end = get_info_descr.end(); begin != end; ++begin)
  {
    lambda(
      *begin.get_component<Transform2D>(0),
      *begin.get_component<vec2>(1),
      *begin.get_component<vec2>(2),
      *begin.get_component<float>(3)
    );
  }
}


void path_finder_func();

ecs::SystemDescription path_finder_descr("path_finder", {
  {ecs::get_type_description<vec2>("velocity"), false},
  {ecs::get_type_description<vec2>("accel"), false},
  {ecs::get_type_description<float>("inertiaCancel"), false},
  {ecs::get_type_description<ecs::Tag>("enemy"), false}
}, path_finder_func, ecs::SystemOrder::LOGIC, (uint)(ecs::SystemTag::Game));

void path_finder_func()
{
  for (ecs::QueryIterator begin = path_finder_descr.begin(), end = path_finder_descr.end(); begin != end; ++begin)
  {
    path_finder(
      *begin.get_component<vec2>(0),
      *begin.get_component<vec2>(1),
      *begin.get_component<float>(2)
    );
  }
}



