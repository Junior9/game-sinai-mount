#include <SDL/SDL.h>
#include "SDL/SDL_opengl.h"
#include <stdio.h>
#include <math.h>

bool running = true;
bool jumper =  false;
bool walk_left = false;
bool walk_right = false;
float avatarX = 300;
float avatarY = 0; 
float avatayHaltura = 120;
float floor_level = 390;
float birdSpeedX = 0.1;
float birdSpeedY = 0;


float MaxX = 600;
float MaxY = 400;

float birdX = 600;
float birdY = 100;
bool birdDirection = false;

SDL_Event events;

//init set
void init_set_SDL(){
    SDL_Init(SDL_INIT_EVERYTHING);

    // memory'
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
 	SDL_SetVideoMode(MaxX,MaxY,32,SDL_OPENGL);


 	//init color
 	glClearColor(1,1,1,1);

 	//area exibida da janela
 	glViewport(0,0,MaxX,MaxY);

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

//jumper avatar
void jumperEvent(){
	if(events.type == SDL_KEYDOWN && events.key.keysym.sym == SDLK_UP) {
 		jumper = true;
 	}else{
 		jumper = false;
 	}
}

// walking avatar
void walk(){
	if(events.type == SDL_KEYDOWN && events.key.keysym.sym == SDLK_LEFT) {
 		walk_left = true;
 	}else if(events.type == SDL_KEYDOWN && events.key.keysym.sym == SDLK_RIGHT){
 		walk_right = true;
 	}

 	if(events.type == SDL_KEYUP && events.key.keysym.sym == SDLK_LEFT) {
 		walk_left = false;
 	}else if(events.type == SDL_KEYUP && events.key.keysym.sym == SDLK_RIGHT){
 		walk_right = false;
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



//floor
void floor(){

	glLineWidth(10);

	glColor4ub(139,69,19,255);
 	glBegin(GL_LINES);
    glVertex2f(0,floor_level);
    glVertex2f(600,floor_level);   
    glEnd();

    glLineWidth(1);
}

//mountain
void mountain (){

	glLineWidth(10);
 	glBegin(GL_LINE_LOOP);
    glVertex2f(MaxX,floor_level);
    glVertex2f(0,floor_level);   
    glVertex2f(0,200);
    glEnd();
    glLineWidth(1);	
}

void bird(){
	glColor4ub(30,145,130,255);
 	DrawCircle(birdX, birdY, 10.0, 100);
}

void leg_avatar(){
	DrawCircle(avatarX, 290 + avatarY, 10.0, 100);
	DrawCircle(avatarX, 310 + avatarY, 10.0, 100);
	DrawCircle(avatarX, 330 + avatarY, 10.0, 100);
}

void avatar(float avatarX){
	glColor4ub(0,0,0,255);
	glPointSize(20);
	
	//Head and Body
	DrawCircle(avatarX, 200 + avatarY, 20.0, 100);

	//Body
	DrawCircle(avatarX, 230 + avatarY, 10.0, 100);
	DrawCircle(avatarX, 250 + avatarY, 10.0, 100);
	DrawCircle(avatarX, 270 + avatarY, 10.0, 100);
	
	//right army
	DrawCircle(avatarX, 230 + avatarY, 10.0, 100);
	DrawCircle(avatarX, 250 + avatarY, 10.0, 100);
	DrawCircle(avatarX, 270 + avatarY, 10.0, 100);

	//left army
	DrawCircle(avatarX, 230 + avatarY, 10.0, 100);
	DrawCircle(avatarX, 250 + avatarY, 10.0, 100);
	DrawCircle(avatarX, 270 + avatarY, 10.0, 100);

	//Right leg
	leg_avatar();
	//Left leg
	leg_avatar();
}

bool collision(float Ax,float Ay,float compA, float altA,float Bx,float By,float compB,float altB){
	

	printf("%s %f %f %s %f %f \n","Avatar",Ax,Ay," Bird",Bx,By);
	//passando por cima do avatar
	if((Ay+200) + altA < By){
		printf("%s\n","Passando por meio" );
		return false;
		// 10 raio 
	}else if (Ay+200 > By+10){
		printf("%s\n","Passando por cima " );
		return false;
	}else if(Ay+200 <= By+10 <= (Ay+200) + altA) {

		printf("%s\n","Dentro 1");

		if((Ax + compA) <= (Bx - compB) && (Ax - compA) >= (Bx + compB)){
			
			printf("%s\n","Dentro 2");			
			avatarX = 300;
			avatarY = 0;


			return true;
		}else{return false;}
	}
}


void avatarMove(){

	//Walk and limite
 	if (walk_right){
		if (avatarX < MaxX){
			avatarX += 1;
		}
		
	}else if (walk_left){
		
		if (avatarX > 0){
			avatarX -= 1;
		}
	}

	//Jumpe
	if(jumper){
		avatarY -= 1;
	}
}

void birdMove(){

	//Pasquerda
	if(birdDirection == false){
		birdX -= birdSpeedX;
		if(birdX <= 0){
			birdDirection = true;
		}
	}else{
		//Passaro indo para direita
		birdX += birdSpeedX;
		if(birdX > MaxX){
			birdDirection = false;
		}
	}		
}

int main (int arg,char* args[]){

 	init_set_SDL();

 	//Loop game
 	while(running){

 		//Event
 		while(SDL_PollEvent(&events)){
			exitGame();		
			walk();
			jumperEvent();
 		}

 	 	//Logic 

 		//Movimento avatar
 		
 		avatarMove();

 		//Movimento Passaro 	

 		birdMove();

 		//Renderização

 		collision(avatarX,avatarY,avatayHaltura,10,birdX,birdY,10,10);

	 	//clear buffer
 		glClear(GL_COLOR_BUFFER_BIT);
 		

 		//init maitrix
 		glPushMatrix();

 		//define tamanho da matrix
 		glOrtho(0,MaxX,MaxY,0,-1,1);
 		glColor4ub(255,0,0,255);


 		//floor
 		floor();

 		//Load Avatar
 		avatar(avatarX);

 		//Load Bird
 		bird();

 		//end matrix
 		glPopMatrix();

 		//animaton
 		SDL_GL_SwapBuffers();

 	}

 	SDL_Quit();
    return 0;
}