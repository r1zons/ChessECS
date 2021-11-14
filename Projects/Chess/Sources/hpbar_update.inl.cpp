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


ecs::SingleQueryDescription get_data_descr("get_data", {
  {ecs::get_type_description<Transform2D>("transform"), false},
  {ecs::get_type_description<float>("curHP"), false},
  {ecs::get_type_description<float>("maxHP"), false},
  {ecs::get_type_description<ecs::EntityId>("healthBarEIDr"), false},
  {ecs::get_type_description<ecs::EntityId>("healthBarEIDg"), false}
});

template<typename Callable>
void get_data(const ecs::EntityId &eid, Callable lambda)
{
  ecs::QueryIterator begin;
  if (ecs::get_iterator(get_data_descr, eid, begin))
  {
    lambda(
      *begin.get_component<Transform2D>(0),
      *begin.get_component<float>(1),
      *begin.get_component<float>(2),
      *begin.get_component<ecs::EntityId>(3),
      *begin.get_component<ecs::EntityId>(4)
    );
  }
}


ecs::SingleQueryDescription update_lifespan1_descr("update_lifespan1", {
  {ecs::get_type_description<float>("lifespan"), false}
});

template<typename Callable>
void update_lifespan1(const ecs::EntityId &eid, Callable lambda)
{
  ecs::QueryIterator begin;
  if (ecs::get_iterator(update_lifespan1_descr, eid, begin))
  {
    lambda(
      *begin.get_component<float>(0)
    );
  }
}


ecs::SingleQueryDescription update_lifespan2_descr("update_lifespan2", {
  {ecs::get_type_description<float>("lifespan"), false},
  {ecs::get_type_description<Transform2D>("transform"), false}
});

template<typename Callable>
void update_lifespan2(const ecs::EntityId &eid, Callable lambda)
{
  ecs::QueryIterator begin;
  if (ecs::get_iterator(update_lifespan2_descr, eid, begin))
  {
    lambda(
      *begin.get_component<float>(0),
      *begin.get_component<Transform2D>(1)
    );
  }
}


ecs::SingleQueryDescription get_pr_data_descr("get_pr_data", {
  {ecs::get_type_description<Transform2D>("transform"), false}
});

template<typename Callable>
void get_pr_data(const ecs::EntityId &eid, Callable lambda)
{
  ecs::QueryIterator begin;
  if (ecs::get_iterator(get_pr_data_descr, eid, begin))
  {
    lambda(
      *begin.get_component<Transform2D>(0)
    );
  }
}


ecs::SingleQueryDescription get_pr_data1_descr("get_pr_data1", {
  {ecs::get_type_description<Transform2D>("transform"), false}
});

template<typename Callable>
void get_pr_data1(const ecs::EntityId &eid, Callable lambda)
{
  ecs::QueryIterator begin;
  if (ecs::get_iterator(get_pr_data1_descr, eid, begin))
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


void update_red_bars_func();

ecs::SystemDescription update_red_bars_descr("update_red_bars", {
  {ecs::get_type_description<ecs::EntityId>("eid"), false},
  {ecs::get_type_description<Transform2D>("transform"), false},
  {ecs::get_type_description<float>("lifespan"), false},
  {ecs::get_type_description<ecs::EntityId>("parentEID"), false},
  {ecs::get_type_description<ecs::Tag>("enemyRedBar"), false}
}, update_red_bars_func, ecs::SystemOrder::RENDER, (uint)(ecs::SystemTag::Game));

void update_red_bars_func()
{
  for (ecs::QueryIterator begin = update_red_bars_descr.begin(), end = update_red_bars_descr.end(); begin != end; ++begin)
  {
    update_red_bars(
      *begin.get_component<ecs::EntityId>(0),
      *begin.get_component<Transform2D>(1),
      *begin.get_component<float>(2),
      *begin.get_component<ecs::EntityId>(3)
    );
  }
}


void update_green_bars_func();

ecs::SystemDescription update_green_bars_descr("update_green_bars", {
  {ecs::get_type_description<ecs::EntityId>("eid"), false},
  {ecs::get_type_description<Transform2D>("transform"), false},
  {ecs::get_type_description<float>("lifespan"), false},
  {ecs::get_type_description<ecs::EntityId>("parentEID"), false},
  {ecs::get_type_description<ecs::Tag>("enemyGreenBar"), false}
}, update_green_bars_func, ecs::SystemOrder::RENDER, (uint)(ecs::SystemTag::Game));

void update_green_bars_func()
{
  for (ecs::QueryIterator begin = update_green_bars_descr.begin(), end = update_green_bars_descr.end(); begin != end; ++begin)
  {
    update_green_bars(
      *begin.get_component<ecs::EntityId>(0),
      *begin.get_component<Transform2D>(1),
      *begin.get_component<float>(2),
      *begin.get_component<ecs::EntityId>(3)
    );
  }
}


void update_green_hp_bar_points_handler(const DamageHero &event);

ecs::EventDescription<DamageHero> update_green_hp_bar_points_descr("update_green_hp_bar_points", {
  {ecs::get_type_description<float>("curHP"), false},
  {ecs::get_type_description<bool>("lost"), false},
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
      *begin.get_component<bool>(1),
      *begin.get_component<float>(2)
    );
  }
}


void create_bar_handler(const ShowBar &event);

ecs::EventDescription<ShowBar> create_bar_descr("create_bar", {
  {ecs::get_type_description<SpriteFactory>("sf"), false}
}, create_bar_handler, (uint)(ecs::SystemTag::Game));

void create_bar_handler(const ShowBar &event)
{
  for (ecs::QueryIterator begin = create_bar_descr.begin(), end = create_bar_descr.end(); begin != end; ++begin)
  {
    create_bar(
      event,
      *begin.get_component<SpriteFactory>(0)
    );
  }
}


void update_green_hp_bar_points_singl_handler(const DamageHero &event, ecs::QueryIterator &begin);

ecs::SingleEventDescription<DamageHero> update_green_hp_bar_points_singl_descr("update_green_hp_bar_points", {
  {ecs::get_type_description<float>("curHP"), false},
  {ecs::get_type_description<bool>("lost"), false},
  {ecs::get_type_description<float>("maxHP"), false},
  {ecs::get_type_description<ecs::Tag>("mainHero"), false}
}, update_green_hp_bar_points_singl_handler, (uint)(ecs::SystemTag::Game));

void update_green_hp_bar_points_singl_handler(const DamageHero &event, ecs::QueryIterator &begin)
{
  update_green_hp_bar_points(
    event,
      *begin.get_component<float>(0),
      *begin.get_component<bool>(1),
      *begin.get_component<float>(2)
  );
}


void create_bar_singl_handler(const ShowBar &event, ecs::QueryIterator &begin);

ecs::SingleEventDescription<ShowBar> create_bar_singl_descr("create_bar", {
  {ecs::get_type_description<SpriteFactory>("sf"), false}
}, create_bar_singl_handler, (uint)(ecs::SystemTag::Game));

void create_bar_singl_handler(const ShowBar &event, ecs::QueryIterator &begin)
{
  create_bar(
    event,
      *begin.get_component<SpriteFactory>(0)
  );
}



