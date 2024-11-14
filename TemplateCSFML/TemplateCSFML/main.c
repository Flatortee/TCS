#include <stdlib.h>
#include <stdio.h>
#include "SFML/Graphics.h"
#include <Windows.h>

void main()
{
    //init, variable HERE :




    sfVideoMode mode = { 800,600,32 };
    sfRenderWindow* window = sfRenderWindow_create(mode, "Template Flatorte", sfDefaultStyle, NULL);

    // Boucle du jeu
    sfEvent event;
    while (sfRenderWindow_isOpen(window))
    {
        //gestion des events
        while (sfRenderWindow_pollEvent(window, &event))
        {
            if (event.type == sfEvtClosed)
            {
                sfRenderWindow_close(window);
            }
        }

        // draw, display, show HERE :


        sfRenderWindow_clear(window, sfWhite); // met la fenetre blanche
        sfRenderWindow_display(window);
    }

    // destroy HERE :



    sfRenderWindow_destroy(window);
}

// faire doc + creator projet