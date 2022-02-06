#include <SFML/Graphics.hpp>

int main()
{
    // Create the window
    sf::RenderWindow window {sf::VideoMode { 800, 600 },
        "SFML Test"};

    // Main loop
    bool running {true};
    while ( running )
    {
        // Handle events
        sf::Event event;
        while ( window.pollEvent(event) )
        {
            if ( event.type == sf::Event::Closed )
                running = false;
        }

        // Update things

        // Clear screen
        window.clear();

        // Draw things

        // show the newly drawn things
        window.display();

        // wait before drawing the next frame
        sf::sleep(sf::milliseconds(100));
    }
}
