#include "hpbar_update.inl"
//Code-generator production

ecs::QueryDescription update_red_hp_bar_position_descr("update_red_hp_bar_position", {
  {ecs::get_type_description<Transform2D>("transform"), false},
  {ecs::get_type_description<ecs::Tag>("redHPBar"), false}
});

template<typename Callable>
void update_red_hp_bar_position(Callable lambda)
{
  for (ecs::QueryIterator begin = update_red_hp_bar_position_descr.begin(), end = update_red_hp_bar_position_descr.end(); begin != end; ++begin)
  {
    lambda(
      *begin.get_component<Transform2D>(0)
    );
  }
}


ecs::QueryDescription update_green_hp_bar_position_descr("update_green_hp_bar_position", {
  {ecs::get_type_description<Transform2D>("transform"), false},
  {ecs::get_type_description<ecs::Tag>("greenHPBar"), false}
});

template<typename Callable>
void update_green_hp_bar_position(Callable lambda)
{
  for (ecs::QueryIterator begin = update_green_hp_bar_position_descr.begin(), end = update_green_hp_bar_position_descr.end(); begin != end; ++begin)
  {
    lambda(
      *begin.get_component<Transform2D>(0)
    );
  }
}


ecs::QueryDescription update_green_hp_bar_length_descr("update_green_hp_bar_length", {
  {ecs::get_type_description<Transform2D>("transform"), false},
  {ecs::get_type_description<ecs::Tag>("greenHPBar"), false}
});

template<typename Callable>
void update_green_hp_bar_length(Callable lambda)
{
  for (ecs::QueryIterator begin = update_green_hp_bar_length_descr.begin(), end = update_green_hp_bar_length_descr.end(); begin != end; ++begin)
  {
    lambda(
      *begin.get_component<Transform2D>(0)
    );
  }
}


void update_red_hp_bar_func();

ecs::SystemDescription update_red_hp_bar_descr("update_red_hp_bar", {
  {ecs::get_type_description<Transform2D>("transform"), false},
  {ecs::get_type_description<ecs::Tag>("mainHero"), false}
}, update_red_hp_bar_func, ecs::SystemOrder::RENDER - 1, (uint)(ecs::SystemTag::Game));

void update_red_hp_bar_func()
{
  for (ecs::QueryIterator begin = update_red_hp_bar_descr.begin(), end = update_red_hp_bar_descr.end(); begin != end; ++begin)
  {
    update_red_hp_bar(
      *begin.get_component<Transform2D>(0)
    );
  }
}


void update_green_hp_bar_func();

ecs::SystemDescription update_green_hp_bar_descr("update_green_hp_bar", {
  {ecs::get_type_description<Transform2D>("transform"), false},
  {ecs::get_type_description<ecs::Tag>("mainHero"), false}
}, update_green_hp_bar_func, ecs::SystemOrder::RENDER, (uint)(ecs::SystemTag::Game));

void update_green_hp_bar_func()
{
  for (ecs::QueryIterator begin = update_green_hp_bar_descr.begin(), end = update_green_hp_bar_descr.end(); begin != end; ++begin)
  {
    update_green_hp_bar(
      *begin.get_component<Transform2D>(0)
    );
  }
}


void update_green_hp_bar_points_handler(const DamageHero &event);

ecs::EventDescription<DamageHero> update_green_hp_bar_points_descr("update_green_hp_bar_points", {
  {ecs::get_type_description<float>("curHP"), false},
  {ecs::get_type_description<float>("maxHP"), false},
  {ecs::get_type_description<ecs::Tag>("mainHero"), false}
}, update_green_hp_bar_points_handler, (uint)(ecs::SystemTag::Game));

void update_green_hp_bar_points_handler(const DamageHero &event)
{
  for (ecs::QueryIterator begin = update_green_hp_bar_points_descr.begin(), end = update_green_hp_bar_points_descr.end(); begin != end; ++begin)
  {
    update_green_hp_bar_points(
      event,
      *begin.get_component<float>(0),
      *begin.get_component<float>(1)
    );
  }
}


void update_green_hp_bar_points_singl_handler(const DamageHero &event, ecs::QueryIterator &begin);

ecs::SingleEventDescription<DamageHero> update_green_hp_bar_points_singl_descr("update_green_hp_bar_points", {
  {ecs::get_type_description<float>("curHP"), false},
  {ecs::get_type_description<float>("maxHP"), false},
  {ecs::get_type_description<ecs::Tag>("mainHero"), false}
}, update_green_hp_bar_points_singl_handler, (uint)(ecs::SystemTag::Game));

void update_green_hp_bar_points_singl_handler(const DamageHero &event, ecs::QueryIterator &begin)
{
  update_green_hp_bar_points(
    event,
      *begin.get_component<float>(0),
      *begin.get_component<float>(1)
  );
}



