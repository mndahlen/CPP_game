#include <SFML/Graphics.hpp> // includes most things in SFML

using namespace sf;

int const width  { 640 };
int const height { 480 };

int main ()
{
    RenderWindow window {
        VideoMode { width, height },
        "SFML DEMO"
    };

    /* skapa en cirkel */
    float const r { 16.0 };
    CircleShape circle { r };

    // placera cirkeln på skärmen
    circle.setPosition (width / 2, height / 2);
    
    // sätt vilken punkt som är origo
    // i cirkeln (det är denna punkt som
    // cirkelns position är specificerad ifrån
    circle.setOrigin (r, r);

    // sätt en bakgrundsfärg på cirkeln
    circle.setFillColor (Color::Green);
    
    // loopa sålänge fönstret finns
    while ( window.isOpen () )
    {
        /* hantera events */
        Event event;
        // hämta ett event i taget
        while ( window.pollEvent (event) )
        {
            if ( event.type == Event::Closed )
            {
                window.close ();
            }
            // har en mus-knapp tryckts?
            else if ( event.type == Event::MouseButtonPressed )
            {
                auto mouse { event.mouseButton };
                // är det vänster musknapp?
                if ( mouse.button == Mouse::Button::Left )
                {
                    // flytta cirkeln
                    circle.setPosition (mouse.x, mouse.y);
                }
            }
        }

        /* hantera logiken */

        /* rita ut */
        window.clear (); // rensa skärmen

        window.draw (circle); // rita ut cirkeln
        
        window.display (); // visa ändringarna
    }
}
