#include <SDL/SDL.h>
#include "SDL/SDL_opengl.h"
#include <stdio.h>

int main (int arg,char* args[])
{
    SDL_Init(SDL_INIT_EVERYTHING);

    // memory
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE,8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE,8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE,8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE,8);
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE,32);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,16);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);

    //Screen name and icon screen
 	SDL_WM_SetCaption("Sinai Mount",NULL);

 	//Size Screen (X,Y)
 	SDL_SetVideoMode(600,400,32,SDL_OPENGL);


 	//init color
 	glClearColor(1,1,1,1);

 	//area exibida da janela
 	glViewport(0,0,600,400);

 	//sombreamento
 	glShadeModel(GL_SMOOTH);

 	//2D
 	glMatrixMode(GL_PROJECTION);
 	glLoadIdentity();

 	//Desable 3D
 	glDisable(GL_DEPTH_TEST);



 	//Logic 



 	//Renderização

 	//clear buffer
 	glClear(GL_COLOR_BUFFER_BIT);
 	SDL_GL_SwapBuffers();


    SDL_Delay(5000);
    SDL_Quit();
    return 0;
}