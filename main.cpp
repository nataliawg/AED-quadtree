
#include <SFML/Graphics.hpp>
#include <iostream>
#include "quadtree.cpp"
using namespace std;

int main() {

    //crea la ventana
    sf::RenderWindow window(sf::VideoMode(800, 600), "quadtree c:");

    QuadTree<char> quadtree(400, 300);

    quadtree.insert(Punto(100, 100), 'A');
    quadtree.insert(Punto(200, 150), 'B');
    quadtree.insert(Punto(300, 200), 'C');
    quadtree.insert(Punto(500, 100), 'D');
    quadtree.insert(Punto(600, 300), 'E');

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Black);

        sf::VertexArray lines(sf::Lines);
        quadtree.draw(window, quadtree.root, lines);
        window.draw(lines);

        window.display();
    }

    return 0;
}
