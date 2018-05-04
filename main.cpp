#include <SDL/SDL.h>
#include "SDL/SDL_opengl.h"
#include <GL/glu.h>
#include <stdio.h>
#include <math.h>

bool running = true;
bool jumperUP =  false;
bool jumperDOWN =  false;
bool walk_left = false;
bool walk_right = false;
float avatarX = 300;
float avatarY = 380; 
float avatayHaltura = 120;
float floor_level = 400;

float birdSpeedX = 0.3;
float birdSpeedXX = 0.4;
float sunSpeedy = 0.2;
float jumpeAlt = 0;

int creditos = 0;

int noite = 0;

float MaxX = 600;
float MaxY = 400;
float blocoComp = 50;
float blocoAlt = 10;
float sunX = 0;
float sunY = 20;

int NUM_ESPACE = 12;
int ESPACEATIVO[12];


bool birdDirection = false;
bool sunDirection = false;

SDL_Event events;

struct Espaco
{
	float x;
	float y;	
};

struct Passaro
{
	float x;
	float y;
	int tipo;
};

Passaro passaros[5];
Espaco espacos[12];

void initBird(){
	passaros[0].x = 600;
	passaros[0].y = 330;
	passaros[0].tipo = 0;

	passaros[1].x = 0;
	passaros[1].y = 280;
	passaros[1].tipo = 1;

	passaros[2].x = 0;
	passaros[2].y = 230;
	passaros[2].tipo = 1;

	passaros[3].x = 600;
	passaros[3].y = 180;
	passaros[3].tipo = 0;

	passaros[4].x = 0;
	passaros[4].y = 130;
	passaros[4].tipo = 1;
}


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

struct Bloco{
	float x;
	float y;
	float comp;
	float alt;
};

//Bloco blocos [5];

//Quit of game
void exitGame(){
	if(events.type == SDL_QUIT || (events.type == SDL_KEYUP && events.key.keysym.sym == SDLK_ESCAPE) ) {
 		running = false;
 	}	
}

//jumper avatar
void jumperEvent(){
	if(events.type == SDL_KEYDOWN && events.key.keysym.sym == SDLK_UP) {
		if(jumperUP == false){
			jumperUP = true;
		}
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
    glBegin(GL_POLYGON);
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


void sky(){

	if(noite == 1){
		glColor4ub(0,0,51,255);
	}else{
		glColor4ub(153,153,255,255);	
	}

	glBegin(GL_QUADS);

	glVertex2f(0,0);
	glVertex2f(0,400);
	glVertex2f(600 ,400);
	glVertex2f(600,0);
    glEnd();	
}

void bloco(float x, float y){

	glBegin(GL_QUADS);

	glVertex2f(x,y);
	glVertex2f(x + blocoComp ,y);
	glVertex2f(x + blocoComp ,y + blocoAlt);
	glVertex2f(x,y + blocoAlt);
    glEnd();
}

void blocoFlag(float x, float y){

	glBegin(GL_QUADS);
	glVertex2f(x,y);
	glVertex2f(x + 100 ,y);
	glVertex2f(x + 100 ,y + blocoAlt);
	glVertex2f(x,y + blocoAlt);
    glEnd();

    glBegin(GL_LINES);
	glVertex2f(x+50,y);
	glVertex2f(x+50,y-40);
    glEnd();

    glColor4ub(0,255,0,255);

    glBegin(GL_TRIANGLES);

	glVertex2f(x+50,y-20);
	glVertex2f(x+60,y-30);
    glVertex2f(x+50,y-40);

    glEnd();
}


void initEspacos(){

	for(int i=0;i<NUM_ESPACE;i++){
		ESPACEATIVO[i] = 0;
	}

	espacos[0].x = 100;
	espacos[0].y = 350;
	espacos[1].x = 300;
	espacos[1].y = 350;
	espacos[2].x = 450;
	espacos[2].y = 350;
	espacos[3].x = 150;
	espacos[3].y = 300;
	espacos[4].x = 320;
	espacos[4].y = 300;
	espacos[5].x = 200;
	espacos[5].y = 300;
	espacos[6].x = 150;
	espacos[6].y = 250;
	espacos[7].x = 400;
	espacos[7].y = 250;
	espacos[8].x = 260;
	espacos[8].y = 250;
	espacos[9].x = 200;
	espacos[9].y = 200;
	espacos[10].x = 300;
	espacos[10].y = 200;
	espacos[11].x = 190;
	espacos[11].y = 150;
	espacos[11].x = 350;
	espacos[11].y = 150;
}


void plataforma(){
	
	glColor4ub(51,25,0,255);
	
	for(int index=0;index<NUM_ESPACE;index++){
		bloco(espacos[index].x,espacos[index].y);
	}	
	blocoFlag(250,100);
}

void sun(){
	glColor4ub(255,255,102,255);	
	DrawCircle(sunX,sunY, 20.0, 100);
}


//mountain
void mountain (){

	glColor4ub(255,153,51,255);
	glLineWidth(10);

	glBegin(GL_TRIANGLES);
    glVertex2f(MaxX,floor_level);
    glVertex2f(0,floor_level);   
    glVertex2f(300,0);
	glEnd();

	glBegin(GL_TRIANGLES);
    glVertex2f(200,floor_level);
    glVertex2f(50,100);   
    glVertex2f(-50,400);
	glEnd();

	glBegin(GL_TRIANGLES);
    glVertex2f(400,floor_level);
    glVertex2f(600,250);   
    glVertex2f(800,floor_level);
	glEnd();	

    glLineWidth(1);	
}

void bird(float x,float y,int tipo){
	

	glColor4ub(0,0,0,255);

	if(tipo == 0){
		DrawCircle(x, y, 3.0, 100);
	}else{
		DrawCircle(x, y, 3.0, 100);	
	}
 	
}

void avatar(float avatarX){
	glColor4ub(0,0,0,255);
	
	//glPointSize(20);
	
	//Head and Body
	DrawCircle(avatarX,avatarY, 3.0, 100);

	//Body
	DrawCircle(avatarX, 4+ avatarY, 2.0, 100);
	DrawCircle(avatarX, 7 + avatarY, 2.0, 100);
	DrawCircle(avatarX, 10 + avatarY, 2.0, 100);
	
	//army
	DrawCircle(avatarX - 3, 4 + avatarY, 2.0, 100);
	DrawCircle(avatarX - 6, 6 + avatarY, 2.0, 100);
	DrawCircle(avatarX + 3, 4 + avatarY, 2.0, 100);
	DrawCircle(avatarX + 6, 6 + avatarY, 2.0, 100);
	
	//legs
	DrawCircle(avatarX-3, 13 + avatarY, 2.0, 100);
	DrawCircle(avatarX-6, 16 + avatarY, 2.0, 100);

	DrawCircle(avatarX+3, 13 + avatarY, 2.0, 100);
	DrawCircle(avatarX+6, 16 + avatarY, 2.0, 100);
}

bool collision(float Ax,float Ay,float compA, float altA,float Bx,float By,float compB,float altB){
	if( (Ay) <= By &&  By <= (Ay) + altA){		
		if (Ax-compA <= Bx && Bx <= Ax+compA){
			return true;
		}else{return false;}
		// 10 raio
	}else if (Ay > By+10){
		return false;
	}
}

bool collisionEspace(float Ax,float Ay,float compA, float altA,float Bx,float By,float compB,float altB){
	
	// 20 para pegar todo o bloco
	if( ( Bx < Ax ) && (Ax < Bx+blocoComp)){
		if( (By+2) > (Ay) ){
			return true;
		}
 	}
 	return false;
}

void avatarMove(){

	//Walk and limite
 	if (walk_right){
		if (avatarX < MaxX){
			avatarX += 0.5;
		}
		
	}else if (walk_left){
		
		if (avatarX > 0){
			avatarX -= 0.5;
		}
	}

	//Jumpe
	if(jumperUP && jumpeAlt < 130){
		//printf("%s %f\n","Jumper ",jumpeAlt );
		//printf("%s  %f  %s  %f\n","AvatarY: ", avatarY," jumpe" , jumpeAlt );
		jumpeAlt += 1;
		avatarY -= 0.5;
	}else{
		jumperUP = false;
	}

	if(jumperUP == false){
		if(avatarY < 380 && jumpeAlt > 0){
			jumpeAlt -=1;
			avatarY +=0.5;
		}		
	}		
}

void birdsMove(){

	//Pasquerda
	if(birdDirection == false){
		for (int index=0; index <= 4; index ++){
			
			if(passaros[index].tipo == 0){
				passaros[index].x -= birdSpeedX; 
			}else{
				passaros[index].x += birdSpeedX;
			}

			if(passaros[index].x <= 0){
				birdDirection = true;
			}
		}		
	}else{
		//Passaro indo para direita
		
		for (int index=0; index <= 4; index ++){
			if(passaros[index].tipo == 0){
				passaros[index].x += birdSpeedX; 
			}else{
				passaros[index].x -= birdSpeedX;
			}

			if(passaros[index].x > MaxX){
				birdDirection = false;
			}
		}
	}		
}

void sunMove(){

	//Para a esquerda
	if(sunDirection == false){
		sunX -= sunSpeedy;
		if(sunX <= 0){
			sunDirection = true;
			noite = 1; 
		}
	}else{
		//Passaro indo para direita
		sunX += sunSpeedy;
		if(sunX > MaxX){
			sunDirection = false;
			noite = 0;
		}
	}		
}

void endGame(){

}


void creditsIn(){
	creditos +=1;
}
void creditsOut(){
	creditos -=1;
}

void morrer(){
	avatarX = 300;
	avatarY = 380;
	jumpeAlt = 0;
	jumperUP = false;
	if(creditos <= 0){
		endGame();
	}else {
		creditsOut();
	}
}


void birds(){
 		
 	bird(passaros[0].x,passaros[0].y,0);
 	bird(passaros[1].x,passaros[1].y,0);
 	bird(passaros[2].x,passaros[2].y,0);
 	bird(passaros[3].x,passaros[3].y,0);
 	bird(passaros[4].x,passaros[4].y,0);
}


void cloud(){

	glBegin(GL_POLYGON);
	    glVertex2f(MaxX,floor_level);
    	glVertex2f(0,floor_level);   
    	glVertex2f(300,0);
	glEnd();
}


void start(){

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
 		birdsMove();

 		//sun move
 		sunMove();

 		//Colisao passaros
 		for(int index=0;index < 5; index ++){
			if(collision(avatarX,avatarY,10,avatayHaltura,passaros[index].x,passaros[index].y,1,1) ){
				morrer();
			}	
 		}

 		//Subir Blocos
 		
 		for(int index=0;index < NUM_ESPACE; index ++){
			if(collisionEspace(avatarX,avatarY,10,avatayHaltura,espacos[index].x,espacos[index].y,30,10) ){
				//printf("%s\n","comflito" );	
				//printf("%s  %d\n","index",ESPACEATIVO[index] );	
				if(ESPACEATIVO[index] == 0){
					//printf("%s  %f  %s  %f\n","AvatarY: ", avatarY," jumpe" , jumpeAlt );
					
					jumpeAlt = 0;
					//jumperUP = false;
					avatarY = espacos[index].y - 15;
					ESPACEATIVO[index] = 1;
				}
			}else{
				if(ESPACEATIVO[index] == 1){
					printf("%s %f\n","Errdao",avatarY );
					//jumpeAlt = 0;
					//avatarY = 380;
					ESPACEATIVO[index] = 0;	
				}				
			}
 		}
 		
	 	//clear buffer
 		glClear(GL_COLOR_BUFFER_BIT);
 		
 		//init maitrix
 		glPushMatrix();

 		//define tamanho da matrix
 		glOrtho(0,MaxX,MaxY,0,-1,1);
 		//glColor4ub(255,0,0,255);

 		sky();

 		//sol
 		sun();

 		//cloud
 		cloud();

 		//Mountaines
 		mountain();

 		//floor
 		floor();

 		//plataforma
 		plataforma();

 		//Load Avatar
 		avatar(avatarX);

 		//Load Birds
 		birds();

 		//end matrix
 		glPopMatrix();

 		//animaton
 		SDL_GL_SwapBuffers();
 	}
}

void initGame(){
 	//clear buffer
	glClear(GL_COLOR_BUFFER_BIT);
	
	//init maitrix
	glPushMatrix();

	//define tamanho da matrix
	glOrtho(0,MaxX,MaxY,0,-1,1);
	//glColor4ub(255,0,0,255);

	while(running){
		
		//Event
 		while(SDL_PollEvent(&events)){
			
 		}
	}	
}

int main (int arg,char* args[]){

 	init_set_SDL();

 	initBird();
 	initEspacos();
	//Loop game

	//initGame(); 	

 	start();

 	SDL_Quit();
    return 0;
}