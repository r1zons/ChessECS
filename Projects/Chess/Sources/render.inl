#include <ecs/ecs.h>
#include <Engine/Render/world_renderer.h>
#include <Engine/Render/Shader/shader.h>
#include <Engine/transform2d.h>
#include <Engine/Render/sprite.h>

template<typename Callable>
void gather_sprites(Callable);

SYSTEM(ecs::SystemOrder::RENDER) render_scene(
  WorldRenderer &wr,
  const mat3 &cameraProjection,
  const Transform2D &transform)
{
  mat3 viewProjection = cameraProjection * glm::inverse(transform.get_matrix());
  wr.screenToWorld = transform.get_matrix();
  glDisable(GL_DEPTH_TEST);
  glEnable(GL_BLEND); 
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  
  wr.spriteShader.use();
  int TVPId = wr.spriteShader.get_uniform_location("trasformViewProjection");
  int uvOffseId = wr.spriteShader.get_uniform_location("uvOffsetScale");
  int colorId = wr.spriteShader.get_uniform_location("color");
  QUERY() gather_sprites([&](
    const Sprite &sprite,
    const Transform2D &transform,
    const vec4 *color)
  {
    //culling
    vec2 minPos = viewProjection * vec3(transform.position - transform.scale * 0.5f, 1);
    vec2 maxPos = viewProjection * vec3(transform.position + transform.scale * 0.5f, 1);
    if (2.f < minPos.x || 2.f < minPos.y || maxPos.x < -2.f || maxPos.y < -2.f)
      return;

    if (sprite.texture)
    {
      sprite.texture->bind(wr.spriteShader, "sprite", 0);
      wr.spriteShader.set_mat3x3(TVPId, viewProjection * transform.get_matrix());
      wr.spriteShader.set_vec4(uvOffseId, vec4(sprite.offset, sprite.scale));
      wr.spriteShader.set_vec4(colorId, color ? *color : vec4(1.f));
      wr.spriteVao.render();
    }
  });
  glEnable(GL_DEPTH_TEST);

}
