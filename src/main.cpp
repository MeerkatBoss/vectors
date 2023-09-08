#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Window.hpp>
#include <SFML/Window/Event.hpp>
#include <cstdio>
#include <unistd.h>

#include "vectors/coord_system.h"
#include "vectors/vectors.h"

int main()
{
  Vec    a = VEC_EMPTY, b = VEC_EMPTY;
  double scale = 1.33;
  VecCtor(&a, 1, 2);
  VecCtor(&b, 4, 5);

  Vec    sum    = VecAdd(&a, &b);
  Vec    diff   = VecSub(&a, &b);
  Vec    scaled = VecScale(&a, scale);
  double angle  = VecAngle(&a, &b);

  dprintf(STDOUT_FILENO, "a = ");
  VecDump(&a, STDOUT_FILENO);
  dprintf(STDOUT_FILENO, "b = ");
  VecDump(&b, STDOUT_FILENO);
  dprintf(STDOUT_FILENO, "a + b = ");
  VecDump(&sum, STDOUT_FILENO);
  dprintf(STDOUT_FILENO, "a - b = ");
  VecDump(&diff, STDOUT_FILENO);
  dprintf(STDOUT_FILENO, "%lg * a = ", scale);
  VecDump(&scaled, STDOUT_FILENO);
  dprintf(STDOUT_FILENO, "a^b = %lg\n", angle);

  sf::RenderWindow window(sf::VideoMode(720, 480), "Draw window");
  sf::RenderTexture render_texture;
  render_texture.create(720, 480);
  render_texture.setSmooth(true);

  Point origin = VEC_EMPTY;
  Vec unit_x = VEC_EMPTY, unit_y = VEC_EMPTY;
  VecCtor(&origin, 100, 100);
  VecCtor(&unit_x, 50, 10);
  VecCtor(&unit_y, 10, 50);
  CoordSystem coord_system = COORD_SYSTEM_EMPTY;
  CoordSystemCtor(&coord_system, &origin, &unit_x, &unit_y);

  Vec drawn1 = VEC_EMPTY, drawn2 = VEC_EMPTY;
  VecCtor(&drawn1, 2, 5);
  VecCtor(&drawn2, 9, 2);

  Vec x_axis = VEC_EMPTY, y_axis = VEC_EMPTY;
  VecCtor(&x_axis, 1, 0);
  VecCtor(&y_axis, 0, 1);

  VecDraw(&drawn1, &coord_system, 3, &render_texture);
  VecDraw(&drawn2, &coord_system, 3, &render_texture);
  VecDraw(&x_axis, &coord_system, 3, &render_texture);
  VecDraw(&y_axis, &coord_system, 3, &render_texture);
  sf::Sprite sprite(render_texture.getTexture());

  while (window.isOpen())
  {
    sf::Event event;
    while (window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
      {
        window.close();
      }
    }
    window.clear(sf::Color::White);
    window.draw(sprite);
    window.display();
  }

  VecDtor(&a);
  VecDtor(&b);
  VecDtor(&sum);
  VecDtor(&diff);
  VecDtor(&scaled);
  VecDtor(&origin);
  VecDtor(&unit_x);
  VecDtor(&unit_y);
  VecDtor(&drawn1);
  VecDtor(&drawn2);
  VecDtor(&x_axis);
  VecDtor(&y_axis);
  CoordSystemDtor(&coord_system);
}
