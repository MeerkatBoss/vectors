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
  Vec    a(1, 2), b(4, 5);
  double scale = 1.33;

  dprintf(STDOUT_FILENO, "a = ");
  a.dump(STDOUT_FILENO);
  dprintf(STDOUT_FILENO, "b = ");
  b.dump(STDOUT_FILENO);
  dprintf(STDOUT_FILENO, "a + b = ");
  (a + b).dump(STDOUT_FILENO);
  dprintf(STDOUT_FILENO, "a - b = ");
  (a + b).dump(STDOUT_FILENO);
  dprintf(STDOUT_FILENO, "%lg * a = ", scale);
  (scale * a).dump(STDOUT_FILENO);
  dprintf(STDOUT_FILENO, "a^b = %lg\n", a.angle_with(b));

  sf::RenderTexture render_texture;
  render_texture.create(720, 480);
  render_texture.setSmooth(true);

  CoordSystem coord_system(
      Point(100, 100),
      Vec(50, 10),
      Vec(10, 50)
  );


  Vec drawn1(2, 5), drawn2(9, 2);

  // Draw vectors
  drawn1.draw(coord_system, 3, render_texture);
  drawn2.draw(coord_system, 3, render_texture);

  // Draw axis
  Vec(1, 0).draw(coord_system, 3, render_texture);
  Vec(0, 1).draw(coord_system, 3, render_texture);
  sf::Sprite sprite(render_texture.getTexture());

  sf::RenderWindow window(sf::VideoMode(720, 480), "Draw window");
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
}
