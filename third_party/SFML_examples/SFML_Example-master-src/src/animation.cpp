#include <SFML/Graphics.hpp>
#include <vector>

double sqr(double a)
{
    return a*a;
}

bool collides(sf::CircleShape const& a, sf::CircleShape const& b)
{
    return (sqr(a.getPosition().x - b.getPosition().x) +
            sqr(a.getPosition().y - b.getPosition().y) <=
            sqr(a.getRadius() + b.getRadius()));
}

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
    window.setMouseCursorVisible(false);

    // load textures
    // add 2 standard constructed textures
    std::vector<sf::Texture> textures{2};
    
    if (!textures[0].loadFromFile("texture1.png"))
        return 1;
    if (!textures[1].loadFromFile("texture2.png"))
        return 1;

    std::vector<sf::Color> colors{ sf::Color::Blue, sf::Color::Red };
    
    unsigned animationIndex {0};
    unsigned animationProgress {0};
    unsigned framesPerImage {30};
    
    // create balls
    sf::CircleShape blue {32};
    blue.setFillColor(colors[0]);
    blue.setTexture(&textures[0]);
    blue.setTextureRect(sf::IntRect{0,0,128,128});
    blue.setOrigin(blue.getRadius(), blue.getRadius());

    sf::CircleShape green {32};
    green.setFillColor(sf::Color::Green);
    green.setOrigin(green.getRadius(), green.getRadius());
    
    // set ball position
    blue.setPosition(42, 42);
    green.setPosition(100, 100);
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
            else if (event.type == sf::Event::KeyPressed)
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
            else if ( event.type == sf::Event::MouseButtonPressed )
            {
                if ( event.mouseButton.button == sf::Mouse::Button::Left )
                    blue.setPosition(event.mouseButton.x, event.mouseButton.y);
            }
        }
        
        // Update things
        if ( collides(blue, green) )
        {
            xSpeed = -xSpeed;
            ySpeed = -ySpeed;
        }
        
        blue.move(xSpeed, ySpeed);

        // set the position of the green ball to the mouse position
        auto mouse = sf::Mouse::getPosition(window);
        green.setPosition(mouse.x, mouse.y);
        
        // bounce at the screen borders
        if ( blue.getPosition().x + blue.getRadius() > window.getSize().x ||
             blue.getPosition().x - blue.getRadius() < 0 )
            xSpeed = -xSpeed;
        
        if ( blue.getPosition().y + blue.getRadius() > window.getSize().y ||
             blue.getPosition().y - blue.getRadius() < 0 )
            ySpeed = -ySpeed;

        // animate
        if ( ++animationProgress % framesPerImage == 0 )
        {
            blue.setFillColor(colors[animationIndex]);
            blue.setTexture(&textures[animationIndex]);
            animationIndex = (animationIndex+1) % textures.size();
        }
        
        // Clear screen
        window.clear();

        // Draw things
        window.draw(blue);
        window.draw(green);
        
        // show the newly drawn things
        window.display();

        // wait before drawing the next frame
        sf::sleep(sf::milliseconds(10));
    }
}
