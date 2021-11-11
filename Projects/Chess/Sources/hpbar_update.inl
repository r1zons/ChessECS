#include <ecs/ecs.h>
#include <Engine/Render/world_renderer.h>
#include <Application/application.h>
#include <Engine/Render/Shader/shader.h>
#include <Engine/transform2d.h>
#include <Engine/imgui/imgui.h>
#include <Application/application_data.h>
#include <Engine/input.h>
#include "game_structs.h"

template<typename Callable> void update_red_hp_bar_position(Callable);
template<typename Callable> void update_green_hp_bar_position(Callable);

SYSTEM(ecs::SystemOrder::RENDER, ecs::Tag mainHero) update_red_hp_bar(
  const Transform2D &transform)
{
  vec2 heroPosition = transform.position;
  
  QUERY(ecs::Tag redHPBar) update_red_hp_bar_position([heroPosition](Transform2D &transform)
  {
    transform.position = {heroPosition.x, heroPosition.y + 1.3};
  });
}

SYSTEM(ecs::SystemOrder::RENDER, ecs::Tag mainHero) update_green_hp_bar(
  const Transform2D &transform)
{
  vec2 heroPosition = transform.position;
  
  QUERY(ecs::Tag greenHPBar) update_green_hp_bar_position([heroPosition](Transform2D &transform)
  {
    transform.position = {heroPosition.x, heroPosition.y + 1.3};
  });
}