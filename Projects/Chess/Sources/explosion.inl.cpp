#include "explosion.inl"
//Code-generator production

void changeFrame_func();

ecs::SystemDescription changeFrame_descr("changeFrame", {
  {ecs::get_type_description<float>("lifespan"), false},
  {ecs::get_type_description<int>("frame"), false},
  {ecs::get_type_description<int>("frameCount"), false},
  {ecs::get_type_description<ecs::EntityId>("eid"), false},
  {ecs::get_type_description<Sprite>("sprite"), false},
  {ecs::get_type_description<SpriteFactory>("sf"), false},
  {ecs::get_type_description<ecs::Tag>("explosion"), false}
}, changeFrame_func, ecs::SystemOrder::RENDER, (uint)(ecs::SystemTag::Game));

void changeFrame_func()
{
  for (ecs::QueryIterator begin = changeFrame_descr.begin(), end = changeFrame_descr.end(); begin != end; ++begin)
  {
    changeFrame(
      *begin.get_component<float>(0),
      *begin.get_component<int>(1),
      *begin.get_component<int>(2),
      *begin.get_component<ecs::EntityId>(3),
      *begin.get_component<Sprite>(4),
      *begin.get_component<SpriteFactory>(5)
    );
  }
}


void deathExplosion_handler(const ShowExp &event);

ecs::EventDescription<ShowExp> deathExplosion_descr("deathExplosion", {
  {ecs::get_type_description<SpriteFactory>("sf"), false}
}, deathExplosion_handler, (uint)(ecs::SystemTag::Game));

void deathExplosion_handler(const ShowExp &event)
{
  for (ecs::QueryIterator begin = deathExplosion_descr.begin(), end = deathExplosion_descr.end(); begin != end; ++begin)
  {
    deathExplosion(
      event,
      *begin.get_component<SpriteFactory>(0)
    );
  }
}


void deathExplosion_singl_handler(const ShowExp &event, ecs::QueryIterator &begin);

ecs::SingleEventDescription<ShowExp> deathExplosion_singl_descr("deathExplosion", {
  {ecs::get_type_description<SpriteFactory>("sf"), false}
}, deathExplosion_singl_handler, (uint)(ecs::SystemTag::Game));

void deathExplosion_singl_handler(const ShowExp &event, ecs::QueryIterator &begin)
{
  deathExplosion(
    event,
      *begin.get_component<SpriteFactory>(0)
  );
}



