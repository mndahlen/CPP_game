#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>


//Kompilera med
//1. g++ -c main.cpp
//2. g++ main.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system
//3. ./sfml-app


int main()
{
    sf::RenderWindow window(sf::VideoMode(900, 700), "Wuhan Virus Defense", 
                           (sf::Style::Close | sf::Style::Titlebar));
    
    sf::Texture texture;
    if (!texture.loadFromFile("files/grass.jpg"))
      return EXIT_FAILURE;
    sf::Sprite background;
    background.setTexture(texture);
    
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        
        
        //State-machine ska läggas här eller kalla på klasser för att kontrollera. 
        
        
        
        window.clear();
        window.draw(background);        
        window.display();
    }

    return 0;
}