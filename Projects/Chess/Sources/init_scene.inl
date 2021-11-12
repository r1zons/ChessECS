#include <ecs/ecs.h>
#include <Application/application.h>
#include <Engine/Render/world_renderer.h>
#include <Engine/Render/Shader/shader.h>
#include <Engine/transform2d.h>
#include "game_structs.h"

EVENT() init_sprites_shaders_camera(
  const ecs::OnSceneCreated &event,
  WorldRenderer &wr,
  SpriteFactory &sf,
  ScoreBoard &sb)
{
  //use debug_log/debug_error like printf for logging (see result in debug panel)
  debug_log("scene %s created", event.scene_name.c_str());

  //feed in project_resources_path relative path from Arcada/Projects/ArcadeSample/Resources/**my_path**
  Texture2D *figuresTex = 
    wr.add_texture(new Texture2D(project_resources_path("figures.png"), RGBA));
  Texture2D *arrowTex = 
    wr.add_texture(new Texture2D(project_resources_path("arrow.png"), RGBA, UnsignedByte, Linear, ClampToBorder));
  Texture2D *bulletTex = 
    wr.add_texture(new Texture2D(project_resources_path("bullet.png"), RGBA));
  
  // ship 6 tex
  Texture2D *ship6Tex = 
    wr.add_texture(new Texture2D(project_resources_path("ship6.png"), RGBA, UnsignedByte, Linear, ClampToBorder));
  // one shoot of ship 6 tex
  Texture2D *shot6_1Tex = 
    wr.add_texture(new Texture2D(project_resources_path("shot6_1.png"), RGBA));
  // asteroids tex
    Texture2D *astersTex = 
    wr.add_texture(new Texture2D(project_resources_path("asteroids.png"), RGBA));
  // white hp_bar tex
    Texture2D *whiteHPTex = 
    wr.add_texture(new Texture2D(project_resources_path("hp_bar.png"), RGBA));
  // background
    Texture2D *backgroundTex = 
    wr.add_texture(new Texture2D(project_resources_path("purple_sample.png"), RGBA));
  
  float figureWidth = 1.f/FigureCount, figureHeight =  1.f/2.f;
  vec2 figureSize(figureWidth, figureHeight);
  for (int i = 0; i < FigureCount; i++)
    sf.figures[i] = Sprite(figuresTex, vec2(figureWidth*i, 0), figureSize);

  float asteroidWidth = 1.f/AsteroidsCount, asteroidHeight =  1.f;
  vec2 asteroidSize(asteroidWidth, asteroidHeight);
  for (int i = 0; i < AsteroidsCount; i++)
    sf.asteroids[i] = Sprite(astersTex, vec2(asteroidWidth*i, 0), asteroidSize);

  
  sf.arrow = Sprite(arrowTex);
  sf.bullet = Sprite(bulletTex);

  sf.ship6 = Sprite(ship6Tex);
  sf.shot6_1 = Sprite(shot6_1Tex);
  sf.hp_bar = Sprite(whiteHPTex);
  sf.background = Sprite(backgroundTex);

  wr.spriteShader = get_shader("standart_sprite");
  
  sb.curentLevel = 0;
  ecs::send_event<StartMenuEvent>(StartMenuEvent());
}
