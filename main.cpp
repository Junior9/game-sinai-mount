#include <SDL/SDL.h>
#include "SDL/SDL_opengl.h"
#include <stdio.h>
#include <math.h>

bool running = true;
SDL_Event events;


//init set
void init_set_SDL(){
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

}


//Quit of game
void exitGame(){
	if(events.type == SDL_QUIT || (events.type == SDL_KEYUP && events.key.keysym.sym == SDLK_ESCAPE) ) {
 		running = false;
 	}	
}

// GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGULES, GL_POLIGNON
void DrawCircle(float cx, float cy, float r, int num_segments) {
    glBegin(GL_LINE_LOOP);
    for (int ii = 0; ii < num_segments; ii++)   {
        float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);//get the current angle 
        float x = r * cosf(theta);//calculate the x component 
        float y = r * sinf(theta);//calculate the y component 
        glVertex2f(x + cx, y + cy);//output vertex 
    }
    glEnd();
}


void leg_avatar(){
	DrawCircle(300, 290, 10.0, 100);
	DrawCircle(300, 310, 10.0, 100);
	DrawCircle(300, 330, 10.0, 100);
}

void avatar(){
	
	glPointSize(20);
		
	//Head and Body
	DrawCircle(300, 200, 20.0, 100);

	//Body
	DrawCircle(300, 230, 10.0, 100);
	DrawCircle(300, 250, 10.0, 100);
	DrawCircle(300, 270, 10.0, 100);
	
	//right army
	DrawCircle(300, 230, 10.0, 100);
	DrawCircle(300, 250, 10.0, 100);
	DrawCircle(300, 270, 10.0, 100);


	//left army
	DrawCircle(300, 230, 10.0, 100);
	DrawCircle(300, 250, 10.0, 100);
	DrawCircle(300, 270, 10.0, 100);


	//Right leg
	leg_avatar();
	//Left leg
	leg_avatar();
}


int main (int arg,char* args[]){

 	init_set_SDL();

 	//Loop game
 	while(running){

 		//Event
 		while(SDL_PollEvent(&events)){
			exitGame();			
 		}

 	 	//Logic 




 		//Renderização

	 	//clear buffer
 		glClear(GL_COLOR_BUFFER_BIT);
 		

 		//init maitrix
 		glPushMatrix();

 		//define tamanho da matrix
 		glOrtho(0,600,400,0,-1,1);
 		glColor4ub(255,0,0,255);



 		//Load Avatar
 		avatar();




 		//end matrix
 		glPopMatrix();

 		//animaton
 		SDL_GL_SwapBuffers();

 	}

 	SDL_Quit();
    return 0;
}