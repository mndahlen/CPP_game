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
        }

        /* hantera logiken */

        /* rita ut */
        window.clear (); // rensa skärmen

        window.display (); // visa ändringarna
    }
}
