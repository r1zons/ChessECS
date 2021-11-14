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
  // ship 6 tex
  Texture2D *ship6Tex = 
    wr.add_texture(new Texture2D(project_resources_path("ship6.png"), RGBA, UnsignedByte, Linear, ClampToBorder));
  sf.ship6 = Sprite(ship6Tex);
  
  // one shoot of ship 6 tex
  Texture2D *shot6_1Tex = 
    wr.add_texture(new Texture2D(project_resources_path("neon_purple_shot.png"), RGBA));
  sf.shot6_1 = Sprite(shot6_1Tex);
  
  // asteroids tex
  Texture2D *astersTex = 
    wr.add_texture(new Texture2D(project_resources_path("asteroids.png"), RGBA));
  float asteroidWidth = 1.f/AsteroidsCount, asteroidHeight =  1.f;
  vec2 asteroidSize(asteroidWidth, asteroidHeight);
  for (int i = 0; i < AsteroidsCount; i++)
    sf.asteroids[i] = Sprite(astersTex, vec2(asteroidWidth*i, 0), asteroidSize);

  // white hp_bar tex
  Texture2D *whiteHPTex = 
    wr.add_texture(new Texture2D(project_resources_path("hp_bar.png"), RGBA));
  sf.hp_bar = Sprite(whiteHPTex);

  // background
  Texture2D *backgroundTex = 
    wr.add_texture(new Texture2D(project_resources_path("bkg_green.png"), RGBA));
  sf.background = Sprite(backgroundTex);
    
    // Texture2D *b1 = 
    // wr.add_texture(new Texture2D(project_resources_path("back_blue.png"), RGBA));

  Texture2D *b2 = 
    wr.add_texture(new Texture2D(project_resources_path("back_green.png"), RGBA));
  sf.back_green = Sprite(b2);

  Texture2D *b3 = 
    wr.add_texture(new Texture2D(project_resources_path("back_purple.png"), RGBA));
  sf.back_purp1 = Sprite(b3);

  // Texture2D *b4 = 
  //   wr.add_texture(new Texture2D(project_resources_path("back_purple2.png"), RGBA));
  // sf.back_purp2 = Sprite(b4);



  wr.spriteShader = get_shader("standart_sprite");

  sb.curentLevel = 0;
  ecs::send_event<StartMenuEvent>(StartMenuEvent());
}
