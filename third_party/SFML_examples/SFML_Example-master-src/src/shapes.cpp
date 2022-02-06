#include <SFML/Graphics.hpp>

int main()
{
    // Create advanced settings for the window
    sf::ContextSettings settings;

    // Set the antialiasing level ("smoothness" level)
    // Note: might not work on all graphics cards
    settings.antialiasingLevel = 8;
    
    // Create the window
    sf::RenderWindow window {sf::VideoMode {800, 600},
        "SFML Test", sf::Style::Default, settings};

    window.setKeyRepeatEnabled(false);
    
    // create ball
    sf::CircleShape ball {32};
    ball.setFillColor(sf::Color::Blue);
    ball.setOrigin(ball.getRadius(), ball.getRadius());

    // set ball position
    ball.setPosition(42, 42);
    
    // Main loop
    bool running {true};
    while ( running )
    {
        // Handle events
        sf::Event event;
        while ( window.pollEvent(event) )
        {
            // if the window was closed from the outside
            if ( event.type == sf::Event::Closed )
                running = false;
        }

        // Update things
    
        // Clear screen
        window.clear();

        // Draw things
        window.draw(ball);
        
        // show the newly drawn things
        window.display();

        // wait before drawing the next frame
        sf::sleep(sf::milliseconds(10));
    }
}
