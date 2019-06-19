#include <stdio.h>
#include <stdlib.h>
#include<GL/gl.h>
#include <gl/glut.h>
#include <math.h>
#include<string.h>
#include<string>
#include<iostream>
#include<windows.h>
#include<MMsystem.h>
#include <string>
#define PI 3.14159
#define GAME_SCREEN 0			//Constant to identify background color
#define MENU_SCREEN 4

using namespace std;

string name;
GLint m_viewport[4];
GLint CI=0;
int bullet=12;
int x,y;
int i;
int openS=1;
int inGame=0;   //Check variable if is in game or not
int index;
int Score=0;
int Life=100;
int GameLvl= 1;
float mouseX ,mouseY ;				//Cursor coordinates;
float xOne=0,yOne=0;
float ll=0.0f;				//Spaceship coordinates //coordinates of stones
float xStart = 1200;				//Health bar starting coordinate		//check to see if stone is killed
float pointerX=600, pointerY=350;   //Gun pointer
float gunMX=0,gunMY=0;              //Gun Position;
bool mButtonPressed= false,startGame=false,gameOver=false;		//boolean values to check state of the game
bool startScreen = true ,nextScreen=false,previousScreen=false;
bool gameQuit = false,instructionsGame = false, optionsGame = false;
int nOfhuman=0;
float hStay=0.46;
GLfloat a[][2]={0,-50, 70,-50, 70,70, -70,70};

char highScore[100],ch;

void update(int value)
{
    if(GameLvl==1){
            hStay+=0.02f;
    if(hStay>=1.0)
    {
        hStay=0.00f;
        if(nOfhuman!=(double)(rand()%5+1))
          nOfhuman=(double)(rand()% 5+1);
        else
            nOfhuman=(double)(rand()% 5+1);
        cout<<nOfhuman<<endl<<endl;
    }
    }
    else if(GameLvl==2)
    {
             hStay+=0.04f;
    if(hStay>=1.0)
    {
        hStay=0.00f;
        if(nOfhuman!=(double)(rand()%5+1))
          nOfhuman=(double)(rand()% 5+1);
        else
            nOfhuman=(double)(rand()% 5+1);
        cout<<nOfhuman<<endl<<endl;
    }
    }
    else if(GameLvl==100){
       if(ll<1.0f)
       ll+=0.02f;
       else{
        ll=0.0f;
        GameLvl=2;
       }
    }

    glutPostRedisplay();
    glutTimerFunc(20,update,0);

}

void DrawCircle(float cx, float cy, float r, int num_segments) {

	glBegin(GL_TRIANGLE_FAN);
	for (int i = 0; i < num_segments; i++)
	{
		float theta = 2.0f * 3.1415926f * float(i) / float(num_segments);//get current angle
		float x = r * cosf(theta);//calculate x
		float y = r * sinf(theta);//calculate y

		glVertex2f(x + cx, y + cy);//output vertex
	}
	glEnd();
	glFlush();
}
void human();
void display();
//void StoneGenerate();
void displayRasterText(float x ,float y ,float z ,char *stringToDisplay) {
	int length;
	glRasterPos3f(x, y, z);
    length = strlen(stringToDisplay);

	for(int i=0 ;i<length ;i++){
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24 ,stringToDisplay[i]);
	}
}
void SetDisplayMode(int modeToDisplay) {
		switch(modeToDisplay){
		case GAME_SCREEN: glClearColor(0.0, (184/255), (230/255), 0);glColor3f(0 ,0 ,1);break;
		case MENU_SCREEN : glClearColor(1, 0 , 0, 1);break;
	}
}


void DisplayHealthBar() {

	glColor3f(0 ,0 ,0);
	glBegin(GL_POLYGON);
		glVertex2f(-xStart ,700);
		glVertex2f(1200 ,700);
		glVertex2f(1200 ,670);
		glVertex2f(-xStart, 670);
	glEnd();
	char temp[200];
	glColor3f(0 ,0 ,1);
	sprintf(temp,"SCORE = %d",Score);
	displayRasterText(-1100 ,600 ,0.4 ,temp); //<---display variable score ?
	sprintf(temp,"  LIFE = %d",Life);
	displayRasterText(800 ,600 ,0.4 ,temp);
	sprintf(temp,"  LEVEL : %d",GameLvl);
	displayRasterText(-100 ,600 ,0.4 ,temp);
	glColor3f(1 ,0 ,0);
    if(bullet>=1)
	   sprintf(temp,"GUN BULLET: %d",bullet);
	else
        sprintf(temp,"GUN BULLET: Reload");
	displayRasterText(-1100 ,550 ,0.4 ,temp);
	glColor3f(1 ,0 ,0);
}

void startScreenDisplay()
{
	glLineWidth(50);
	SetDisplayMode(MENU_SCREEN);

	glColor3f(0,0,1);
	glBegin(GL_LINE_LOOP);               //Border
		glVertex3f(-750 ,-500 ,0.5);
		glVertex3f(-750 ,550 ,0.5);
		glVertex3f(750 ,550 ,0.5);
		glVertex3f(750 ,-500, 0.5);
	glEnd();

	glLineWidth(1);

	glColor3f(0,1,1);
	glBegin(GL_POLYGON);				//START GAME PLOYGON
		glVertex3f(-200 ,300 ,0.5);
		glVertex3f(-200 ,400 ,0.5);
		glVertex3f(200 ,400 ,0.5);
		glVertex3f(200 ,300, 0.5);
	glEnd();

	glBegin(GL_POLYGON);				//INSTRUCTIONS POLYGON
		glVertex3f(-200, 50 ,0.5);
		glVertex3f(-200 ,150 ,0.5);
		glVertex3f(200 ,150 ,0.5);
		glVertex3f(200 ,50, 0.5);
	glEnd();

	glBegin(GL_POLYGON);				//QUIT POLYGON
		glVertex3f(-200 ,-200 ,0.5);
		glVertex3f(-200 ,-100 ,0.5);
		glVertex3f(200, -100 ,0.5);
		glVertex3f(200, -200 ,0.5);
	glEnd();

	if(mouseX>=-100 && mouseX<=100 && mouseY>=150 && mouseY<=200){
		glColor3f(0 ,0 ,1) ;
		if(mButtonPressed){
			startGame = true ;
			 PlaySound(TEXT("D:\\UNIVERSITY\\11th Semister\\COMPUTER GRAPHICS\\FinalProject\\gun_Fire\\music\\stopSound.wav"), NULL, SND_FILENAME | SND_ASYNC);
			gameOver = false;
			mButtonPressed = false;
		}
	} else
		glColor3f(0 , 0, 0);

	displayRasterText(-100 ,340 ,0.4 ,"Start Game");

	if(mouseX>=-100 && mouseX<=100 && mouseY>=30 && mouseY<=80) {
		glColor3f(0 ,0 ,1);
		if(mButtonPressed){
			instructionsGame = true ;
			mButtonPressed = false;
		}
	} else
		glColor3f(0 , 0, 0);
	displayRasterText(-120 ,80 ,0.4 ,"Instructions");

	if(mouseX>=-100 && mouseX<=100 && mouseY>=-90 && mouseY<=-40){
		glColor3f(0 ,0 ,1);
		if(mButtonPressed){
			gameQuit = true ;
			mButtonPressed = false;
		}
	}
	else
		glColor3f(0 , 0, 0);
	displayRasterText(-100 ,-170 ,0.4 ,"    Quit");



}
int lowX(int x)
{
    return  x-1200;

}

void gunPointer()
{
    //display width 1200 height 700
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINES);

        glVertex2f(pointerX-15,pointerY);
        glVertex2f(pointerX+15,pointerY);
        glVertex2f(pointerX,pointerY-15);
        glVertex2f(pointerX,pointerY+15);
    glEnd();



}


void gun()
{
    glBegin(GL_QUADS);
    glColor3f (.0, 0.0, 0.0);
    glVertex2i(gunMX-10,gunMY-40);
    glVertex2i(gunMX+10,gunMY-40);
    glVertex2i(gunMX+10,gunMY+40);
    glVertex2i(gunMX-10,gunMY+40);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f (1.0, 0.0, 0.0);
    glVertex2i(gunMX+10,gunMY-40);
    glVertex2i(gunMX+40,gunMY-40);
    glVertex2i(gunMX+40,gunMY-10);
    glVertex2i(gunMX+10,gunMY-10);
    glEnd();

}

//human
void human(){

    glPushMatrix();
    glScalef(1.5,1.5,0);

//body
glBegin(GL_POLYGON);
    glColor3f (1.0, 0.0, 0.0);
    glVertex2i(100,100);
    glVertex2i(180,100);
    glVertex2i(180,200);
    glVertex2i(100,200);
    glEnd();
//right hand
    glBegin(GL_POLYGON);
    glColor3f (1.0, 0.0, 0.0);
    glVertex2i(90,180);
    glVertex2i(100,180);
    glVertex2i(100,200);
    glVertex2i(70,200);
    glVertex2i(70,140);
    glVertex2i(90,140);
    glEnd();
     glBegin(GL_POLYGON);
    glColor3f (.8, .6, 0.4);
    glVertex2i(75,130);
    glVertex2i(85,130);
    glVertex2i(85,140);
    glVertex2i(75,140);
    glEnd();
//left hand

    glBegin(GL_POLYGON);
    glColor3f (1.0, 0.0, 0.0);


    glVertex2i(210,200);
    glVertex2i(180,200);
    glVertex2i(180,180);
    glVertex2i(190,180);
    glVertex2i(190,140);
    glVertex2i(210,140);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f (.8, .6, .4);
    glVertex2i(195,130);
    glVertex2i(205,130);
    glVertex2i(205,140);
    glVertex2i(195,140);
    glEnd();

    //left leg
    glBegin(GL_POLYGON);
    glColor3f (.0, .0, 0.0);
    glVertex2i(100,20);
    glVertex2i(130,20);
    glVertex2i(130,100);
    glVertex2i(100,100);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f (.8, .6, .4);
    glVertex2i(110,10);
    glVertex2i(120,10);
    glVertex2i(120,20);
    glVertex2i(110,20);

    glEnd();
    glBegin(GL_POLYGON);
    glColor3f (1.0, .0, 0.0);
    glVertex2i(100,0);
    glVertex2i(120,0);
    glVertex2i(120,10);
    glVertex2i(100,10);
    glEnd();
    //right leg
    glBegin(GL_POLYGON);
    glColor3f (.0, .0, 0.0);
    glVertex2i(150,20);
    glVertex2i(180,20);
    glVertex2i(180,100);
    glVertex2i(150,100);

    glEnd();
     glBegin(GL_POLYGON);
    glColor3f (.8, .6, .4);
    glVertex2i(160,10);
    glVertex2i(170,10);
    glVertex2i(170,20);
    glVertex2i(160,20);

    glEnd();
    glBegin(GL_POLYGON);
    glColor3f (1.0, .0, 0.0);
    glVertex2i(150,0);
    glVertex2i(170,0);
    glVertex2i(170,10);
    glVertex2i(150,10);

    glEnd();
    glColor3f(.8,.6,.4);
    DrawCircle(140, 225, 25, 1000);
    glColor3f(0,.0,0);
    DrawCircle(130, 225, 5, 1000);
    glColor3f(0,.0,0);
    DrawCircle(150, 225, 5, 1000);
    glPopMatrix();
}

void humanPosition()
{
    switch(nOfhuman){
   case 5:
    ///human5
    glPushMatrix();
    glTranslatef(620,-298,0);
    human();
    glPopMatrix();
   break;
   case 4:
///human4
    glPushMatrix();
    glTranslatef(200,-298,0);
    human();
    glPopMatrix();
    break;
    case 3:
    ///human3
    glPushMatrix();
    glTranslatef(-250,-500,0);
    glScalef(1,1.5,1);
    human();
    glPopMatrix();
    break;
    case 2:
    ///human2
    glPushMatrix();
    glTranslatef(-600,-298,0);
    human();
    glPopMatrix();
    break;
    default:
    ///human1
    glPushMatrix();
    glTranslatef(-1100,-298,0);
    human();
    glPopMatrix();
    break;
 }
}
void levelTwoBackGround()
{
    glClear (GL_COLOR_BUFFER_BIT);
glColor3f (1.0, 0.0, 0.0);
glPointSize(10.0);

//start**********************************************************************************900 -400
glBegin(GL_QUADS);
    glColor3f (1.0, 1.0, 1.0);
    glVertex2i(-1200,-700);
    glVertex2i(1200,-700);
    glVertex2i(1200,700);
    glVertex2i(-1200,700);
    glEnd();



//skyyyyyyyyyyyyy
glBegin(GL_QUADS);
    glColor3f (0.0, 0.05, 0.2);
    glVertex2i(-1200,-50);
    glVertex2i(1200,-50);
    glVertex2i(1200,700);
    glVertex2i(-1200,700);
    glEnd();
    //star
 glColor3f(1.0,1.0,1.0);
    DrawCircle(800,500,5,2000);
    DrawCircle(-100,450,5,2000);
    DrawCircle(-700,550,5,2000);
    DrawCircle(-300,600,5,2000);
    DrawCircle(300,620,5,2000);
    DrawCircle(620,570,5,2000);

    //sun
    glColor3f(1.0,1.0,1.0);
    DrawCircle(-1000,500,100,2000);
//green**************
glBegin(GL_QUADS);
    glColor3f (0.0, 0.1, 0.0);
    glVertex2i(-1200,-390);
    glVertex2i(1200,-390);
    glVertex2i(1200,-50);
    glVertex2i(-1200,-50);
    glEnd();
    //store start*********************************8tonmoy
glPushMatrix();
glScalef(.8,.7,0);
glTranslatef(300,0,0);
glBegin(GL_QUADS);
    glColor3f (1.0, 0.8, 1.0);
    glVertex2i(-1050,-500);
    glVertex2i(1050,-500);
    glVertex2i(1050,310);
    glVertex2i(-1050,310);
    glEnd();
    humanPosition();
//1st quads
glBegin(GL_QUADS);
    glColor3f (0.8, 0.4, 0.0);
    glVertex2i(-1050,-500);
    glVertex2i(-200,-500);
    glVertex2i(-200,-150);
    glVertex2i(-1050,-150);
    glEnd();

//2nd Quads--
glBegin(GL_QUADS);
    glColor3f (0.8, 0.4, 0.0);
    glVertex2i(100,-500);
    glVertex2i(1050,-500);
    glVertex2i(1050,-150);
    glVertex2i(100,-150);
    glEnd();
//3rd quads store ground
glBegin(GL_QUADS);
    glColor3f (0.4, 0.24, 0.0);
    glVertex2i(-1100,-550);
    glVertex2i(1100,-550);
    glVertex2i(1050,-500);
    glVertex2i(-1050,-500);
    glEnd();
//store tin
glBegin(GL_QUADS);
    glColor3f (0.2, 0.2, 0.0);
    glVertex2i(-1150,180);
    glVertex2i(1150,180);
    glVertex2i(1050,310);
    glVertex2i(-1050,310);
    glEnd();
//1st wall
glBegin(GL_QUADS);
    glColor3f (0.6, 0.0, 0.0);
    glVertex2i(-1050,-150);
    glVertex2i(-1020,-150);
    glVertex2i(-1020,180);
    glVertex2i(-1050,180);
    glEnd();
//2nd wall
glBegin(GL_QUADS);
    glColor3f (0.6, 0.0, 0.0);
    glVertex2i(-230,-150);
    glVertex2i(-200,-150);
    glVertex2i(-200,180);
    glVertex2i(-230,180);
    glEnd();
//middle wall
glBegin(GL_QUADS);
    glColor3f (0.6, 0.0, 0.0);
    glVertex2i(-700,-150);
    glVertex2i(-580,-150);
    glVertex2i(-580,180);
    glVertex2i(-700,180);
    glEnd();
//1st wall
glBegin(GL_QUADS);
    glColor3f (0.6, 0.0, 0.0);
    glVertex2i(100,-150);
    glVertex2i(130,-150);
    glVertex2i(130,180);
    glVertex2i(100,180);
    glEnd();
//2nd wall
glBegin(GL_QUADS);
    glColor3f (0.6, 0.0, 0.0);
    glVertex2i(1050,-150);
    glVertex2i(1020,-150);
    glVertex2i(1020,180);
    glVertex2i(1050,180);
    glEnd();
//middle wall
glBegin(GL_QUADS);
    glColor3f (0.6, 0.0, 0.0);
    glVertex2i(570,-150);
    glVertex2i(690,-150);
    glVertex2i(690,180);
    glVertex2i(570,180);
    glEnd();
//store top
glBegin(GL_QUADS);
    glColor3f (0.8, 0.4, 0.0);
    glVertex2i(-1050,310);
    glVertex2i(1050,310);
    glVertex2i(1050,450);
    glVertex2i(-1050,450);
    glEnd();
//store top
glBegin(GL_QUADS);
    glColor3f (1.0, 0.0, 0.0);
    glVertex2i(1050,450);
    glVertex2i(850,450);
    glVertex2i(850,430);
    glVertex2i(1050,430);
    glEnd();
//store top
glBegin(GL_QUADS);
    glColor3f (1.0, 0.0, 0.0);
    glVertex2i(-1050,450);
    glVertex2i(-850,450);
    glVertex2i(-850,430);
    glVertex2i(-1050,430);
    glEnd();
//store top
glBegin(GL_QUADS);
    glColor3f (0.8, 0.4, 0.0);
    glVertex2i(850,450);
    glVertex2i(-850,450);
    glVertex2i(-850,520);
    glVertex2i(850,520);
    glEnd();
//store top
glBegin(GL_QUADS);
    glColor3f (1.0, 0.0, 0.0);
    glVertex2i(-850,520);
    glVertex2i(850,520);
    glVertex2i(850,540);
    glVertex2i(-850,540);
    glEnd();
glPopMatrix();
//store front road
glBegin(GL_QUADS);
    glColor3f (0.0, 0.0, 0.0);
    glVertex2i(-1200,-700);
    glVertex2i(1200,-700);
    glVertex2i(1200,-390);
    glVertex2i(-1200,-390);

//store front road white line
glBegin(GL_QUADS);
    glColor3f (1.0, 1.0, 1.0);
    glVertex2i(-1200,-560);
    glVertex2i(-900,-560);
    glVertex2i(-900,-575);
    glVertex2i(-1200,-575);
glBegin(GL_QUADS);
    glColor3f (1.0, 1.0, 1.0);
    glVertex2i(-800,-560);
    glVertex2i(-500,-560);
    glVertex2i(-500,-575);
    glVertex2i(-800,-575);
glBegin(GL_QUADS);
    glColor3f (1.0, 1.0, 1.0);
    glVertex2i(-400,-560);
    glVertex2i(-100,-560);
    glVertex2i(-100,-575);
    glVertex2i(-400,-575);
glBegin(GL_QUADS);
    glColor3f (1.0, 1.0, 1.0);
    glVertex2i(0,-560);
    glVertex2i(300,-560);
    glVertex2i(300,-575);
    glVertex2i(0,-575);
glBegin(GL_QUADS);
    glColor3f (1.0, 1.0, 1.0);
    glVertex2i(400,-560);
    glVertex2i(700,-560);
    glVertex2i(700,-575);
    glVertex2i(400,-575);
glBegin(GL_QUADS);
    glColor3f (1.0, 1.0, 1.0);
    glVertex2i(800,-560);
    glVertex2i(1100,-560);
    glVertex2i(1100,-575);
    glVertex2i(800,-575);
//#################### TREE  #####################
glBegin(GL_QUADS);
    glColor3f (0.4, 0.10, 0.0);
    glVertex2i(-1000,-390);
    glVertex2i(-930,-390);
    glVertex2i(-930,-150);
    glVertex2i(-1000,-150);
glBegin(GL_QUADS);
    glColor3f (0.0, 0.2, 0.0);
    glVertex2i(-1150,-150);
    glVertex2i(-780,-150);
    glVertex2i(-860,-10);
    glVertex2i(-1070,-10);
glBegin(GL_QUADS);
    glColor3f (0.0, 0.2, 0.0);
    glVertex2i(-1100,-10);
    glVertex2i(-820,-10);
    glVertex2i(-870,80);
    glVertex2i(-1050,80);
glBegin(GL_QUADS);
    glColor3f (0.0, 0.2, 0.0);
    glVertex2i(-1070,80);
    glVertex2i(-830,80);
    glVertex2i(-960,180);
    glVertex2i(-960,180);
    glEnd();

//lampPost
glBegin(GL_QUADS);
    glColor3f (0.0, 0.0, 0.0);
    glVertex2i(-700,-390);
    glVertex2i(-750,-390);
    glVertex2i(-750,-120);
    glVertex2i(-700,-120);
    glEnd();
glBegin(GL_QUADS);
    glColor3f (0.0, 0.0, 0.0);
    glVertex2i(1170,-390);
    glVertex2i(1120,-390);
    glVertex2i(1120,-120);
    glVertex2i(1170,-120);
    glEnd();
glColor3f(1.0,1.0,1.0);
    DrawCircle(-725,-90,50,2000);
glColor3f(1.0,1.0,1.0);
    DrawCircle(1145,-90,50,2000);
glEnd();
}

void levelOneBackground()
{
glClear (GL_COLOR_BUFFER_BIT);
glColor3f (1.0, 0.0, 0.0);
glPointSize(10.0);

//start**********************************************************************************900 -400
glBegin(GL_QUADS);
    glColor3f (1.0, 1.0, 1.0);
    glVertex2i(-1200,-700);
    glVertex2i(1200,-700);
    glVertex2i(1200,700);
    glVertex2i(-1200,700);
    glEnd();


//skyyyyyyyyyyyyy
glBegin(GL_QUADS);
    glColor3f (0.0, 1.0, 1.0);
    glVertex2i(-1200,-50);
    glVertex2i(1200,-50);
    glVertex2i(1200,700);
    glVertex2i(-1200,700);
    glEnd();
//green**************
glBegin(GL_QUADS);
    glColor3f (0.0, 1.0, 0.0);
    glVertex2i(-1200,-390);
    glVertex2i(1200,-390);
    glVertex2i(1200,-50);
    glVertex2i(-1200,-50);
    glEnd();


    //store start*********************************8
glPushMatrix();
glScalef(.8,.7,0);
glTranslatef(300,0,0);
glBegin(GL_QUADS);
    glColor3f (1.0, 0.8, 1.0);
    glVertex2i(-1050,-500);
    glVertex2i(1050,-500);
    glVertex2i(1050,310);
    glVertex2i(-1050,310);
    glEnd();

    //humannnnnnnnnnn
   humanPosition();
//1st quads
glBegin(GL_QUADS);
    glColor3f (0.8, 0.4, 0.0);
    glVertex2i(-1050,-500);
    glVertex2i(-200,-500);
    glVertex2i(-200,-150);
    glVertex2i(-1050,-150);
    glEnd();

//2nd Quads
glBegin(GL_QUADS);
    glColor3f (0.8, 0.4, 0.0);
    glVertex2i(100,-500);
    glVertex2i(1050,-500);
    glVertex2i(1050,-150);
    glVertex2i(100,-150);
    glEnd();
//3rd quads store ground
glBegin(GL_QUADS);
    glColor3f (0.4, 0.24, 0.0);
    glVertex2i(-1100,-550);
    glVertex2i(1100,-550);
    glVertex2i(1050,-500);
    glVertex2i(-1050,-500);
    glEnd();
//store tin
glBegin(GL_QUADS);
    glColor3f (0.2, 0.2, 0.0);
    glVertex2i(-1150,180);
    glVertex2i(1150,180);
    glVertex2i(1050,310);
    glVertex2i(-1050,310);
    glEnd();
//1st wall
glBegin(GL_QUADS);
    glColor3f (0.6, 0.0, 0.0);
    glVertex2i(-1050,-150);
    glVertex2i(-1020,-150);
    glVertex2i(-1020,180);
    glVertex2i(-1050,180);
    glEnd();
//2nd wall
glBegin(GL_QUADS);
    glColor3f (0.6, 0.0, 0.0);
    glVertex2i(-230,-150);
    glVertex2i(-200,-150);
    glVertex2i(-200,180);
    glVertex2i(-230,180);
    glEnd();
//middle wall
glBegin(GL_QUADS);
    glColor3f (0.6, 0.0, 0.0);
    glVertex2i(-700,-150);
    glVertex2i(-580,-150);
    glVertex2i(-580,180);
    glVertex2i(-700,180);
    glEnd();


//1st wall
glBegin(GL_QUADS);
    glColor3f (0.6, 0.0, 0.0);
    glVertex2i(100,-150);
    glVertex2i(130,-150);
    glVertex2i(130,180);
    glVertex2i(100,180);
    glEnd();
//2nd wall
glBegin(GL_QUADS);
    glColor3f (0.6, 0.0, 0.0);
    glVertex2i(1050,-150);
    glVertex2i(1020,-150);
    glVertex2i(1020,180);
    glVertex2i(1050,180);
    glEnd();
//middle wall
glBegin(GL_QUADS);
    glColor3f (0.6, 0.0, 0.0);
    glVertex2i(570,-150);
    glVertex2i(690,-150);
    glVertex2i(690,180);
    glVertex2i(570,180);
    glEnd();
//store top
glBegin(GL_QUADS);
    glColor3f (0.8, 0.4, 0.0);
    glVertex2i(-1050,310);
    glVertex2i(1050,310);
    glVertex2i(1050,450);
    glVertex2i(-1050,450);
    glEnd();
//store top
glBegin(GL_QUADS);
    glColor3f (1.0, 0.0, 0.0);
    glVertex2i(1050,450);
    glVertex2i(850,450);
    glVertex2i(850,430);
    glVertex2i(1050,430);
    glEnd();
//store top
glBegin(GL_QUADS);
    glColor3f (1.0, 0.0, 0.0);
    glVertex2i(-1050,450);
    glVertex2i(-850,450);
    glVertex2i(-850,430);
    glVertex2i(-1050,430);
    glEnd();
//store top
glBegin(GL_QUADS);
    glColor3f (0.8, 0.4, 0.0);
    glVertex2i(850,450);
    glVertex2i(-850,450);
    glVertex2i(-850,520);
    glVertex2i(850,520);
    glEnd();
//store top
glBegin(GL_QUADS);
    glColor3f (1.0, 0.0, 0.0);
    glVertex2i(-850,520);
    glVertex2i(850,520);
    glVertex2i(850,540);
    glVertex2i(-850,540);
    glEnd();
glPopMatrix();



//store front road
glBegin(GL_QUADS);
    glColor3f (0.0, 0.0, 0.0);
    glVertex2i(-1200,-700);
    glVertex2i(1200,-700);
    glVertex2i(1200,-390);
    glVertex2i(-1200,-390);

//store front road white line
glBegin(GL_QUADS);
    glColor3f (1.0, 1.0, 1.0);
    glVertex2i(-1200,-560);
    glVertex2i(-900,-560);
    glVertex2i(-900,-575);
    glVertex2i(-1200,-575);
glBegin(GL_QUADS);
    glColor3f (1.0, 1.0, 1.0);
    glVertex2i(-800,-560);
    glVertex2i(-500,-560);
    glVertex2i(-500,-575);
    glVertex2i(-800,-575);
glBegin(GL_QUADS);
    glColor3f (1.0, 1.0, 1.0);
    glVertex2i(-400,-560);
    glVertex2i(-100,-560);
    glVertex2i(-100,-575);
    glVertex2i(-400,-575);
glBegin(GL_QUADS);
    glColor3f (1.0, 1.0, 1.0);
    glVertex2i(0,-560);
    glVertex2i(300,-560);
    glVertex2i(300,-575);
    glVertex2i(0,-575);
glBegin(GL_QUADS);
    glColor3f (1.0, 1.0, 1.0);
    glVertex2i(400,-560);
    glVertex2i(700,-560);
    glVertex2i(700,-575);
    glVertex2i(400,-575);
glBegin(GL_QUADS);
    glColor3f (1.0, 1.0, 1.0);
    glVertex2i(800,-560);
    glVertex2i(1100,-560);
    glVertex2i(1100,-575);
    glVertex2i(800,-575);
//#################### TREE  #####################
glBegin(GL_QUADS);
    glColor3f (0.4, 0.10, 0.0);
    glVertex2i(-1000,-390);
    glVertex2i(-930,-390);
    glVertex2i(-930,-150);
    glVertex2i(-1000,-150);
glBegin(GL_QUADS);
    glColor3f (0.0, 0.9, 0.0);
    glVertex2i(-1150,-150);
    glVertex2i(-780,-150);
    glVertex2i(-860,-10);
    glVertex2i(-1070,-10);
glBegin(GL_QUADS);
    glColor3f (0.0, 0.9, 0.0);
    glVertex2i(-1100,-10);
    glVertex2i(-820,-10);
    glVertex2i(-870,80);
    glVertex2i(-1050,80);
glBegin(GL_QUADS);
    glColor3f (0.0, 0.9, 0.0);
    glVertex2i(-1070,80);
    glVertex2i(-830,80);
    glVertex2i(-960,180);
    glVertex2i(-960,180);
glEnd();
}
void lvlCng()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	SetDisplayMode(MENU_SCREEN);
	//colorBackground();
	glColor3f(0, 0, 0);

	displayRasterText(-100 ,250 ,0.9 ,"Next Level");

}
// background of game screen //
void backgroundOfGame()
{
     if(GameLvl==1){
        levelOneBackground();
     }
     else if(GameLvl==2)
     {
         levelTwoBackGround();
     }
     else if(GameLvl==100)
     {
         lvlCng();
        // ll=0.00;
     }
    gun();
    gunPointer();

    glFlush ();

    inGame=1;

}


void GameScreenDisplay()
{
    //full background//

	SetDisplayMode(GAME_SCREEN);
	backgroundOfGame();
	DisplayHealthBar();
	glScalef(2, 2 ,0);
	if(Life>0){
        gameOver=false;
	}
	else {
		gameOver=true;
		instructionsGame = false;
		startScreen = false;
	}								//<----------------------gameover screen
}

void readFromFile() {

	FILE *fp = fopen("HighScoreFile.txt" ,"r");
	int i=0;
	if(fp!= NULL){
		while(fread(&ch,sizeof(char),1 ,fp)){
			highScore[i++] = ch;
		}
		highScore[i] = '\0';
	}
	fclose(fp);
}
void writeIntoFile() {	//To write high score on to file
	FILE *fp = fopen("HighScoreFile.txt" ,"w");
	int i=0;
	char temp[40];
	if(fp!= NULL){
		int n= Score;

		while(n){
			ch = (n%10)+ '0';
			n/=10;
			temp[i++] = ch;
		}


		temp[i] = '\0';
		strrev(temp);
		puts(temp);
		if(temp[0] == '\0')
			temp[i++] = '0' ,temp[i++] = '\0';
		fwrite(temp ,sizeof(char)*i ,i ,fp);
	}
 fclose(fp);
}
int hh=0;

void GameOverScreen()
{

	SetDisplayMode(MENU_SCREEN);
	glColor3f(0,0,0);
	glLineWidth(50);
	glBegin(GL_LINE_LOOP);               //Border
		glVertex3f(-650 ,-500 ,0.5);
		glVertex3f(-650 ,520 ,0.5);
		glVertex3f(650 ,520 ,0.5);
		glVertex3f(650 ,-500, 0.5);
	glEnd();

	glLineWidth(1);

	glColor3f(0, 1, 0);
	glBegin(GL_POLYGON);				//GAME OVER
		glVertex3f(-550 ,810,0.5);
		glVertex3f(-550 ,610 ,0.5);
		glVertex3f(550 ,610 ,0.5);
		glVertex3f(550 ,810, 0.5);
	glEnd();

	glColor3f(1, 1, 0);
	glBegin(GL_POLYGON);				//RESTART POLYGON
		glVertex3f(-200, 50 ,0.5);
		glVertex3f(-200 ,150 ,0.5);
		glVertex3f(200 ,150 ,0.5);
		glVertex3f(200 ,50, 0.5);
	glEnd();

	glBegin(GL_POLYGON);				//QUIT POLYGON
		glVertex3f(-200 ,-200 ,0.5);
		glVertex3f(-200 ,-100 ,0.5);
		glVertex3f(200, -100 ,0.5);
		glVertex3f(200, -200 ,0.5);
	glEnd();


	displayRasterText(-300 ,640 ,0.4 ,"G A M E    O V E R ! ! !");
	glColor3f(0 , 0, 0);
	char temp[40];

	sprintf(temp,"Score : %d",Score);
	displayRasterText(-100 ,340 ,0.4 ,temp);
	readFromFile();
	char temp2[40];
	//new high score
	if(atoi(highScore) < Score){
         hh=atoi(highScore);
		writeIntoFile();
		PlaySound(TEXT("D:\\UNIVERSITY\\11th Semister\\COMPUTER GRAPHICS\\FinalProject\\gun_Fire\\music\\clap.wav"), NULL, SND_FILENAME | SND_ASYNC );
		sprintf(temp2 ,"Highest Score :%d" ,Score);
	} else{

		sprintf(temp2 ,"Highest Score :%s" ,highScore);
	}
	displayRasterText(-250 ,400 ,0.4 ,temp2);

	if(mouseX>=-100 && mouseX<=100 && mouseY>=25 && mouseY<=75){
		glColor3f(0 ,0 ,1);
		if(mButtonPressed){                                                       //Reset game default values
			startGame = true ;
			gameOver=false;
			mButtonPressed = false;

			Life=100;
			xStart=1200;
			Score=0;
			GameLvl=1;
			GameScreenDisplay();
		}
	} else
		glColor3f(0 , 0, 0);
	displayRasterText(-70 ,80 ,0.4 ,"Restart");

	if(mouseX>=-100 && mouseX<=100 && mouseY>=-100 && mouseY<=-50){
		glColor3f(0 ,0 ,1);
		if(mButtonPressed){
			exit(0);
			mButtonPressed = false;
		}
	}
	else
		glColor3f(0 , 0, 0);
	displayRasterText(-100 ,-170 ,0.4 ,"    Quit");

}

void backButton() {
	if(mouseX <= -450 && mouseX >= -500 && mouseY >= -275 && mouseY <= -250){
			glColor3f(0, 0, 1);
			if(mButtonPressed){
				mButtonPressed = false;
				instructionsGame = false;
				startScreenDisplay();
			}
	}
	else glColor3f(0, 0, 0);
	displayRasterText(-1000 ,-550 ,0, "Back");
}
void InstructionsScreenDisplay()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	SetDisplayMode(MENU_SCREEN);
	//colorBackground();
	glColor3f(0, 0, 0);
	displayRasterText(-900 ,400 ,0.4 ,"Left mouse click to shoot");
	displayRasterText(-900 ,300 ,0.4 ,"Right mouse click to reload");
	displayRasterText(-900 ,200 ,0.4 ,"One successful shoot gets 10 points");
	displayRasterText(-900 ,100 ,0.4 ,"One unsuccessful shoot loses 5 health point");
	displayRasterText(-900 ,45 ,0.4 ,"Press \'P\' to play or pause");
	displayRasterText(-900 ,10 ,0.4 ,"Press \'R\' to Restart Game");
	backButton();
	if(previousScreen)
		nextScreen = false ,previousScreen = false; //as set by backButton()


}


void openingSound()
{
    if(openS==1){
    PlaySound(TEXT("D:\\UNIVERSITY\\11th_Semister\\COMPUTER GRAPHICS\\FinalProject\\gun_Fire\\music\\startSong.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
        openS=0;
      }
      else if(openS==-1)
      {

          openS=0;
	      //return EXIT_SUCCESS;
      }
}

void passiveFuntion(int x,int y)
{
    pointerX = x/1.0;
    pointerY = 700.0 - (y/1.0);
    glutPostRedisplay();
}
void display() {

	glClear(GL_COLOR_BUFFER_BIT);
	glViewport(0,0,1200,700);

	if(startGame && !gameOver)
    {
		GameScreenDisplay();
		openS=-1;
		if(openS==-1)
		openingSound();

    }
	else if(instructionsGame)
		InstructionsScreenDisplay();

	else if(gameOver)
		GameOverScreen();

	//Make spaceship bigger
	else if(startScreen){

			startScreenDisplay();
			openS=1;
			if(gameQuit || startGame || optionsGame || instructionsGame){
				//startScreen = false;

				if(startGame){
					SetDisplayMode(GAME_SCREEN);
					startScreen = false;

				} else if(gameQuit)
					exit(0);

				} else if(instructionsGame) {
					SetDisplayMode(GAME_SCREEN);
					InstructionsScreenDisplay();
				}

		}

	//Reset Scaling values
	glScalef(1/2 ,1/2 ,0);
	glFlush();
	glLoadIdentity();
	glutSwapBuffers();
}
void somethingMovedRecalculateLaserAngle() {

	float mouseXForTan = (-50 - mouseX) + xOne;
	float mouseYForTan = (35 - mouseY) + yOne;

}

void myinit()
{
	glClearColor(1.0,0.0,0.0,0);
	glColor3f(1.0,1.0,1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

    gluOrtho2D(-1200,1200,-700,700);                   //<-----CHANGE THIS TO GET EXTRA SPACE
//  gluOrtho2D(-200,200,-200,200);
	glMatrixMode(GL_MODELVIEW);
   openingSound();


}
void passiveMotionFunc(int x,int y) {

	//when mouse not clicked
	mouseX = float(x)/(m_viewport[2]/1200.0)-600.0;  //converting screen resolution to ortho 2d spec
	mouseY = -(float(y)/(m_viewport[3]/700.0)-350.0);

	//Do calculations to find value of LaserAngle
	somethingMovedRecalculateLaserAngle();
   gunMX=((x*2.0)-1200);
   pointerX=((x*2.0)-1200);
    pointerY =700.0-(y*1.5);
    gunMY=700.0-(y*2);


    glutPostRedisplay();

}

//Game sound controller
void gameLvl1(int x,int y)
{
      bullet--;
   if(bullet>=1){
      PlaySound(TEXT("D:\\UNIVERSITY\\11th Semister\\COMPUTER GRAPHICS\\FinalProject\\gun_Fire\\music\\shootSound.wav"), NULL, SND_FILENAME | SND_ASYNC );
      switch(nOfhuman){
         case 5:
           if(pointerX<984 && pointerX>830 && pointerY<50 && pointerY>-95)
           {
              Score+=10;
              PlaySound(TEXT("D:\\UNIVERSITY\\11th Semister\\COMPUTER GRAPHICS\\FinalProject\\gun_Fire\\music\\uh.wav"), NULL, SND_FILENAME | SND_ASYNC );
           }
           else
             Life-=5;
        break;
        case 4:
           if(pointerX<640 && pointerX>490 && pointerY<50 && pointerY>-95)
               {
              Score+=10;
              PlaySound(TEXT("D:\\UNIVERSITY\\11th Semister\\COMPUTER GRAPHICS\\FinalProject\\gun_Fire\\music\\uh.wav"), NULL, SND_FILENAME | SND_ASYNC );
           }
           else
             Life-=5;
        break;
        case 3:
           if(pointerX<284 && pointerX>128 && pointerY<38 && pointerY>-342)
               {
             Score+=10;
              PlaySound(TEXT("D:\\UNIVERSITY\\11th Semister\\COMPUTER GRAPHICS\\FinalProject\\gun_Fire\\music\\uh.wav"), NULL, SND_FILENAME | SND_ASYNC );
           }
           else
             Life-=5;
        break;
        case 2:
           if(pointerX<6 && pointerX>-146 && pointerY<50 && pointerY>-95)
              {
              Score+=10;
              PlaySound(TEXT("D:\\UNIVERSITY\\11th Semister\\COMPUTER GRAPHICS\\FinalProject\\gun_Fire\\music\\uh.wav"), NULL, SND_FILENAME | SND_ASYNC );
           }
           else
             Life-=5;
        break;
        default:
           if(pointerX<-394 && pointerX>-548 && pointerY<50 && pointerY>-95)
               {
              Score+=10;
              PlaySound(TEXT("D:\\UNIVERSITY\\11th Semister\\COMPUTER GRAPHICS\\FinalProject\\gun_Fire\\music\\uh.wav"), NULL, SND_FILENAME | SND_ASYNC );
           }
           else
             Life-=5;
        break;
      }

   }
   else{
      Life-=5;
      PlaySound(TEXT("D:\\UNIVERSITY\\11th Semister\\COMPUTER GRAPHICS\\FinalProject\\gun_Fire\\music\\emptyGun.wav"), NULL, SND_FILENAME | SND_ASYNC );
   }

       cout<<"x= "<<x<<" y="<<y<<" PointerX="<<pointerX<<" PointerY="<<pointerY<<endl;

       if(Life<=0 && hh<Score)
       {
           PlaySound(TEXT("D:\\UNIVERSITY\\11th Semister\\COMPUTER GRAPHICS\\FinalProject\\gun_Fire\\music\\clap.wav"), NULL, SND_FILENAME | SND_ASYNC );
       }
       else if(Life<=0){
        PlaySound(TEXT("D:\\UNIVERSITY\\11th Semister\\COMPUTER GRAPHICS\\FinalProject\\gun_Fire\\music\\maybe-next-time-huh.wav"), NULL, SND_FILENAME | SND_ASYNC );
       }
      if(Score==300)
        GameLvl=2;
}
 void mouseClick(int buttonPressed ,int state ,int x, int y) {

	if(buttonPressed == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
		    mButtonPressed = true;

		    if(inGame==1 && (GameLvl==1 || GameLvl==2))
            {
                gameLvl1(x,y);
            }
		}
		else if(buttonPressed == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
        {
            bullet=12;
            PlaySound(TEXT("D:\\UNIVERSITY\\11th Semister\\COMPUTER GRAPHICS\\FinalProject\\gun_Fire\\music\\reload.wav"), NULL, SND_FILENAME | SND_ASYNC );
        }
	else
		mButtonPressed = false;
	display();
}

 void idleCallBack() {			//when no mouse or keybord pressed
	 display();
 }
 int pp=0;
 int ph=0;
 void keyboard(unsigned char key, int x, int y)
{
switch (key){
 case 'p':
     if( !startScreen )
     {
         startScreen=true;
         startGame=false;
         pp=Score;
         ph=Life;

     }else{
        startScreen=false;
         startGame=true;
         Score=pp;
          if(ph<=0)
          {
            Life=100;
             PlaySound(TEXT("D:\\UNIVERSITY\\11th Semister\\COMPUTER GRAPHICS\\FinalProject\\gun_Fire\\music\\stopSound.wav"), NULL, SND_FILENAME | SND_ASYNC);
          }
         else
           Life=ph;
     }
   break;
 case 'r':
     if(startGame)
    {
        Score=0;
        Life=100;
        GameLvl=1;
    }
    break;
}
}
 int main(int argc, char** argv) {

	 FILE *fp = fopen("HighScoreFile.txt" ,"r") ;      //check if HighScoreFile.txt exist if not create
	 if(fp!=NULL)
		fclose(fp);
	 else
		 writeIntoFile();
    //cout<<"Enter Your Name: ";
    //getline(cin,name);

	glutInit(&argc, argv);
	glutInitWindowSize(1200,700);
	glutInitWindowPosition(90 ,0);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
	//glutTimerFunc(50,Update,0);
	glutCreateWindow("THE  SHOOTING GAME");
	glutDisplayFunc(display);
	//glutKeyboardFunc(keys);
	glutPassiveMotionFunc(passiveMotionFunc);
	glBlendFunc(GL_SRC_ALPHA ,GL_ONE_MINUS_SRC_ALPHA);
	glutIdleFunc(idleCallBack);
	glutMouseFunc(mouseClick);
	glGetIntegerv(GL_VIEWPORT ,m_viewport);
	myinit();
	glutTimerFunc(20,update,0);
	glutKeyboardFunc(keyboard);
	SetDisplayMode(GAME_SCREEN);
	glutMainLoop();

	return 0;
 }
