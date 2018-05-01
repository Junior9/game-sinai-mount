#include <SDL/SDL.h>
#include "SDL/SDL_opengl.h"
#include <stdio.h>

bool running = true;
SDL_Event events;


//Quit of game
void exitGame(){
	running = false;
}


int main (int arg,char* args[]){

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


 	

 	//Loop game
 	while(running){

 		//Event
 		while(SDL_PollEvent(&events)){

 			//Close screem
 			if(events.type == SDL_QUIT || (events.type == SDL_KEYUP && events.key.keysym.sym == SDLK_ESCAPE) ) {
 				exitGame();
 			}
			
 		}

 	 	//Logic 


	 	//clear buffer
 		glClear(GL_COLOR_BUFFER_BIT);
 		SDL_GL_SwapBuffers();

 	}





 	//Renderização
    SDL_Quit();
    return 0;
}






