#include "Game.h"

int main()
{
    Game game("game", 1920, 1080, 4, 5, GL_TRUE);



    //main loop
    while (!game.getWindowShouldClose())
    {   
        //update input
        game.update();
        //render
        game.render();

    }

    return 0;
}