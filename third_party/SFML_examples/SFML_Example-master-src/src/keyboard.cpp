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
    
    // load texture
    sf::Texture texture;
    if (!texture.loadFromFile("texture1.png"))
        return 1;
    
    // create ball
    sf::CircleShape ball {32};
    ball.setFillColor(sf::Color::Blue);
    ball.setTexture(&texture);
    ball.setTextureRect(sf::IntRect{0,0,128,128});
    ball.setOrigin(ball.getRadius(), ball.getRadius());

    // set ball position
    ball.setPosition(42, 42);
    int xSpeed{10};
    int ySpeed{10};
    
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

            if (event.type == sf::Event::KeyPressed)
            {
                // if the 'X' key was pressed
                if ( event.key.code == sf::Keyboard::X )
                    xSpeed = -xSpeed;
                // if the 'Y' key was pressed
                else if ( event.key.code == sf::Keyboard::Y )
                    ySpeed = -ySpeed;
                // if the 'Escape' key was pressed
                else if ( event.key.code == sf::Keyboard::Escape )
                    running = false;
            }
        }

        // Update things
        ball.move(xSpeed, ySpeed);

        // bounce at the screen borders
        if ( ball.getPosition().x + ball.getRadius() > window.getSize().x ||
             ball.getPosition().x - ball.getRadius() < 0 )
            xSpeed = -xSpeed;
        
        if ( ball.getPosition().y + ball.getRadius() > window.getSize().y ||
             ball.getPosition().y - ball.getRadius() < 0 )
            ySpeed = -ySpeed;
        
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
