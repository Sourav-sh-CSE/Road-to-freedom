#include <bits/stdc++.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>
#include "glut.h"

//#define size 5000;
using namespace std;

//double cameraAngle;
double size=5000;
double R, Rspeed, vAngle, hAngle, angleSpeed;
double k=0,l=0,t=0,s=10,m=0,r=20,p=0,q=0,h=0,flag=0,fast=1,slow=1,fall=90,roadno,score=0;
GLfloat siz=10;
int num_texture = 0;

GLuint lava,sky,road,pilar,furr,gameoverr;

void circle(double x,double y,double r)
{

	double i;
	for(i=0;i<=2*3.14;i+=.2)
	{
	glBegin(GL_TRIANGLES);
	{
	     glVertex3f(x,y, 0);
	    glVertex3f(r*cos(i-.2)+x, (r)*sin(i-.2)+y, 0);
	    glVertex3f(r*cos(i)+x, (r)*sin(i)+y, 0);

	}
}
	glEnd();


}

int loadBitmapImage(string ff)
{
    printf("line 1\n");
	int i, j = 0;
	FILE *l_file;
	BYTE *l_texture;

	BITMAPFILEHEADER fileheader;
	BITMAPINFOHEADER infoheader;
	RGBTRIPLE rgb;

	num_texture++;

    char filename[103];
    for(int i=0;i<ff.size();++i){
        filename[i]=ff[i];
    }
    filename[ff.size()]='\0';

	if ((l_file = fopen(filename, "rb")) == NULL)
	{
        cout<<"null\n";
		return (-1);
	}
    cout<<(int)infoheader.biWidth<<"\n";
    cout<<(int)infoheader.biHeight<<"\n";
	fread(&fileheader, sizeof(fileheader), 1, l_file);

	fseek(l_file, sizeof(fileheader), SEEK_SET);
	fread(&infoheader, sizeof(infoheader), 1, l_file);

	l_texture = (BYTE *)malloc(infoheader.biWidth * infoheader.biHeight * 4);
	memset(l_texture, 0, infoheader.biWidth * infoheader.biHeight * 4);
	for (i = 0; i < infoheader.biWidth * infoheader.biHeight; i++)
	{
		fread(&rgb, sizeof(rgb), 1, l_file);

		l_texture[j + 0] = rgb.rgbtRed;
		l_texture[j + 1] = rgb.rgbtGreen;
		l_texture[j + 2] = rgb.rgbtBlue;
		l_texture[j + 3] = 255;
		j += 4;
	}

	for(int k = 0;k<(int)sizeof(l_texture);++k){
        cout<<"l_texture["<<k<<"]: "<<(int)l_texture[k]<<"\n";
	}

	fclose(l_file);

	glBindTexture(GL_TEXTURE_2D, num_texture);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);

	// glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, infoheader.biWidth, infoheader.biHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, l_texture);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 4, infoheader.biWidth, infoheader.biHeight, GL_RGBA, GL_UNSIGNED_BYTE, l_texture);

	free(l_texture);

	return (num_texture);
}

void loadAllImages()
{
    printf("loading....\n");
	lava = loadBitmapImage("image/lava.bmp");
	sky = loadBitmapImage("image/sky.bmp");
	road = loadBitmapImage("image/road.bmp");
	pilar = loadBitmapImage("image/pilar.bmp");
	gameoverr = loadBitmapImage("image/gameoverr.bmp");

	furr = loadBitmapImage("image/furr.bmp");
	cout<<"loaded....\n";
}


void eyeright()
{
    //function for the right eye
    glPushMatrix();
    glTranslatef(.17,1.1,.75);     //Specify the coordinates for the right eye
    glRotatef(-45,0,0,1);
    glScalef(.9,.7,.7);            //Specify the size of the right eye
    glColor3f(1.0,1.0,1.0);       //Specify the color of the eye
    gluSphere(gluNewQuadric(),.3,100,100);
    glPopMatrix();
}
void eyeleft()
{
    glPushMatrix();
    glTranslatef(-.17,1.1,.75);     //Specify the position for the left eye
    glRotatef(45,0,0,1);
    glScalef(.9,.7,.7);
    glColor3f(1.0,1.0,1.0);
    gluSphere(gluNewQuadric(),.3,100,100);
    glPopMatrix();
}

void legleft()
{
    glPushMatrix();
    glTranslatef(.3,-.5,0);     //Specify the position for the left leg
    glRotatef(-90.0,1,0,0);
    glScalef(.8,.8,.8);
    gluCylinder(gluNewQuadric(),.5,.5,.5,30,6);
    glPopMatrix();
}

void legright()
{
    glPushMatrix();
    glTranslatef(-.3,-.5,0);     //Specify the position for the right leg
    glRotatef(-90.0,1,0,0);
    glScalef(.8,.8,.8);
    gluCylinder(gluNewQuadric(),.5,.5,.5,30,6);
    glPopMatrix();
}

void armleft()
{
    glPushMatrix();
    glTranslatef(-.82,0,.1);     //Specify the position for the left arm
    glRotatef(90,0,1,0);
    glRotatef(-50,1,0,0);
    gluCylinder(gluNewQuadric(),.15,.15,.48,30,6);
    glPopMatrix();
}

void armright()
{
    glPushMatrix();
    glTranslatef(.82,0,.1);      //Specify the position for the right arm
    glRotatef(90,0,1,0);
    glRotatef(-130,1,0,0);
    gluCylinder(gluNewQuadric(),.15,.15,.48,30,6);
    glPopMatrix();
}

void handleft()
{
    glPushMatrix();
    glTranslatef(.82,0,.1);     //Specify the position for the left hand
    glScalef(.4,.3,.3);
    gluSphere(gluNewQuadric(),.4,100,100);
    glPopMatrix();
}
void handright()
{
    glPushMatrix();
    glTranslatef(-.82,0,.1);    //Specify the position for the right hand
    glScalef(.4,.3,.3);
    gluSphere(gluNewQuadric(),.4,100,100);
    glPopMatrix();
}

void mouth()
{
    glPushMatrix();
    glTranslatef(0,.78,.74);
    glScalef(.4,.4,.1);
    glColor3f(0.0,0.0,0.0);
    gluSphere(gluNewQuadric(),.4,100,100);
    glPopMatrix();
}

void teeth()
{
    glPushMatrix();
    glColor3f(1.0,1.0,1.0);
    glTranslatef(-.08,.72,.76);
    glTranslatef(.055,0,.005 );
    glutSolidCube(.035);
    glTranslatef(.055,0,0 );
    glutSolidCube(.035);
    glPopMatrix();
}
void eyebrowleft()
{
    glPushMatrix();
    glTranslatef(-.3,1.5,.97);;
    glRotatef(90,0,1,0);
    glRotatef(45,1,0,0);
    glColor3f(0.0,0.0,0.0);
    gluCylinder(gluNewQuadric(),.05,.01,.3,4,6);
    glPopMatrix();
}

void eyebrowright()
{
    glPushMatrix();
    glTranslatef(.3,1.5,.97);
    glRotatef(270,0,1,0);
    glRotatef(45,1,0,0);
    gluCylinder(gluNewQuadric(),.05,.01,.3,4,6);
    glPopMatrix();
}

void neckring()
{
    glPushMatrix();
    glTranslatef(0,.5,0);
    glScalef(.59,.59,.59);
    glRotatef(90.0,1,0,0);
    glutSolidTorus(.1,1.0,20,20);
    glPopMatrix();
}


void head()
{
    glPushMatrix();
    glTranslatef(0,1.2,0);
    glScalef(.9 ,.9,.9 );
    glColor3f(1.0,1.8,1.6);
    gluSphere(gluNewQuadric(),.8,100,100);
    glPopMatrix();
}

void maintopball()
{
    glPushMatrix();
    glTranslatef(0,2.2,0);
    glScalef(.9,.9,.9);
    gluSphere(gluNewQuadric(),.18,100,100);
    glPopMatrix() ;
}

void hatring()
{
    glPushMatrix();
    glTranslatef(0,1.4,0);
    glScalef(.84,.84,.84);
    glRotatef(90.0,1,0,0);
    glutSolidTorus(.1,1.0,20,20);
    glPopMatrix();
}

void footleft()
{
    glPushMatrix();
    glTranslatef(-.3,-.5,0);
    glScalef(1.5,.3,1.5);
    glColor3f(0.0,0.0,0.0);
    gluSphere(gluNewQuadric(),.3,100,100);
    glPopMatrix();
}

void footright()
{
    glPushMatrix();
    glTranslatef(.3,-.5,0);
    glScalef(1.5,.3,1.5);
    glColor3f(0.0,0.0,0.0);
    gluSphere(gluNewQuadric(),.3,100,100);
    glPopMatrix();
}

void bellyCoatbottom()
{
    glPushMatrix();
    glTranslatef(0,-.2,0);
    glScalef(1,.7,1);
    glRotatef(90.0,1,0,0);
    gluDisk(gluNewQuadric(),0,.8,30,30);
    glPopMatrix();
}

void BellyCoat()
{
    glPushMatrix();
    glTranslatef(0,.5,0);
    glScalef(1,.7,1);
    glRotatef(90.0,1,0,0);
    gluCylinder(gluNewQuadric(),.6,.8,1,100,100);
    glPopMatrix();
}

void pupilleft()
{
    glPushMatrix();
    glTranslatef(-.17,1.1,.88);
    glScalef(.9,.9,.9);
    gluSphere(gluNewQuadric(),.1,100,100);
    glPopMatrix();
}

void pupilright()
{
    glPushMatrix();
    glTranslatef(.17,1.1,.88);
    glScalef(.9,.9,.9);
    gluSphere(gluNewQuadric(),.1,100,100);
    glPopMatrix();
}

void topbutton()
{
    glPushMatrix();
    glTranslatef(-.1,.4,.85);
    glScalef(1.9,1.9,1.9);
    gluSphere(gluNewQuadric(),.04,100,100);
    glPopMatrix();
}
void middlebutton()
{
    glPushMatrix()  ;
    glTranslatef(-.1,.15,.98);
    glScalef(1.9,1.9,1.9);
    gluSphere(gluNewQuadric(),.04,100,100);
    glPopMatrix();
}
void bottombutton()
{
    glPushMatrix();
    glTranslatef(-.1,-.1,.92);
    glScalef(1.9,1.9,1.9);
    glColor3f(0.0,0.0,0.0);
    gluSphere(gluNewQuadric(),.04,100,100);
    glPopMatrix();
}


void manush()
{

/*

	glColor3f(1.0f, 1.0f, 1.0f);

// Draw Body
	glTranslatef(0.0f ,0.75f, 0.0f);
	glutSolidSphere(0.75f,20,20);


// Draw Head
	glTranslatef(0.0f, 1.0f, 0.0f);
	glutSolidSphere(0.25f,20,20);

// Draw Eyes
	glPushMatrix();
	glColor3f(0.0f,0.0f,0.0f);
	glTranslatef(0.05f, 0.10f, 0.18f);
	glutSolidSphere(0.05f,10,10);
	glTranslatef(-0.1f, 0.0f, 0.0f);
	glutSolidSphere(0.05f,10,10);
	glPopMatrix();

// Draw Nose
	glColor3f(1.0f, 0.5f , 0.5f);
	glRotatef(0.0f,1.0f, 0.0f, 0.0f);
	glutSolidCone(0.08f,0.5f,10,2);
*/


    eyeright();
    eyeleft();
    eyebrowleft();
    eyebrowright();
    glColor3f(0.0,1.0,0.0);
    neckring();
    glColor3ub(50,40,60);
    legright();
    legleft();
    glColor3ub(255,90,0);
    armleft();
    armright();
    BellyCoat();
    bellyCoatbottom();
    glColor3ub(0,185,0);
    handleft();
    handright();
    mouth();
    teeth();
    glColor3ub(255,222,173);
    head();
    glColor3f(0.0,0.0,0.0);
    footleft();
    footright();
    topbutton();
    middlebutton();
    bottombutton();
    pupilleft();
    pupilright();
}

void skyy()
{
glEnable(GL_TEXTURE_2D);
		{
		    glColor3f(1,1,1);
			glBindTexture(GL_TEXTURE_2D, sky);

				GLUquadricObj *obj = gluNewQuadric();
				gluQuadricTexture(obj, GL_TRUE);
				glPushMatrix();
				glTranslatef(p,q,1000);
				glRotatef(180,0,0,1);
				gluSphere(obj, 5000, 20, 20);
				glPopMatrix();

/*
    glBegin(GL_QUADS);
				{
				    glTexCoord3f(0.0, 0.0, 0.0);
				    glVertex3f(-10000,10000,0);

				    glTexCoord3f(1.0, 0.0, 0.0);
				    glVertex3f(10000,10000,0);

				    glTexCoord3f(1.0, 1.0, 0.0);
				    glVertex3f(10000,10000,10000);

				    glTexCoord3f(0.0, 1.0, 0.0);
				    glVertex3f(-10000,10000,10000);
				}
				glEnd();*/
		}
}




void ground(double p1 , double p2)
{

glEnable(GL_TEXTURE_2D);
		{
		    glColor3f(1,1,1);
			glBindTexture(GL_TEXTURE_2D, lava);



    glBegin(GL_QUADS);
				{
				    glTexCoord3f(0.0, 0.0, 0.0);
				    glVertex3f(p1,p2,-100);

				    glTexCoord3f(1.0, 0.0, 0.0);
				    glVertex3f(1000,p2,-100);

				    glTexCoord3f(1.0, 1.0, 0.0);
				    glVertex3f(1000,1000,-100);

				    glTexCoord3f(0.0, 1.0, 0.0);
				    glVertex3f(p1,1000,-100);
				}
				glEnd();



		}


}


void river()
{
    glEnable(GL_TEXTURE_2D);
		{
		    glColor3f(1,1,1);
			glBindTexture(GL_TEXTURE_2D, lava);

 glBegin(GL_QUADS);
    {
         glTexCoord3f(0.0, 0.0, 0.0);
        glVertex3f(-10,0, 0);
         glTexCoord3f(1.0, 0.0, 0.0);
        glVertex3f(10,0, 0);
         glTexCoord3f(1.0, 1.0, 0.0);
        glVertex3f(10,10,0);
         glTexCoord3f(0.0, 1.0, 0.0);
        glVertex3f(-10,10,0);
    }
    glEnd();
		}
}

void wall()
{
    //glPushMatrix();

glEnable(GL_TEXTURE_2D);
		{
		    glColor3f(1,1,1);
			glBindTexture(GL_TEXTURE_2D, pilar);


    glBegin(GL_QUADS);
				{
				    glTexCoord3f(0.0, 0.0, 0.0);
				    glVertex3f(0,0,0);

				    glTexCoord3f(1.0, 0.0, 0.0);
				    glVertex3f(5,0,0);

				    glTexCoord3f(1.0, 1.0, 0.0);
				    glVertex3f(5,0,40);

				    glTexCoord3f(0.0, 1.0, 0.0);
				    glVertex3f(0,0,40);
				}
				glEnd();



		}
//glPopMatrix();

}

void pause()
{
    glPushMatrix();
    glTranslatef(-.03,0,0);

   glColor3f(1,0,0);
   glBegin(GL_QUADS);
				{

				    glVertex3f(p-.02,q+1,19.7);


				    glVertex3f(p-.12,q+1,19.7);


				    glVertex3f(p-.12,q+1,20.4);


				    glVertex3f(p-.02,q+1,20.4);
				}
				glEnd();

glPushMatrix();
glTranslatef(.2,0,0);
				glColor3f(1,0,0);
   glBegin(GL_QUADS);
				{

				  glVertex3f(p-.02,q+1,19.7);


				    glVertex3f(p-.12,q+1,19.7);


				    glVertex3f(p-.12,q+1,20.4);


				    glVertex3f(p-.02,q+1,20.4);
				}
				glEnd();
glPopMatrix();
glPopMatrix();

}


void roadtof(double lnt)
{
  //  glPushMatrix();

glEnable(GL_TEXTURE_2D);
		{
		    glColor3f(1,1,1);
			glBindTexture(GL_TEXTURE_2D, road);

			 glBegin(GL_QUADS);
    {
         glTexCoord3f(0.0, 0.0, 0.0);
        glVertex3f(-10,0, 0);
         glTexCoord3f(1.0, 0.0, 0.0);
        glVertex3f(10,0, 0);
         glTexCoord3f(1.0, 1.0, 0.0);
        glVertex3f(10,lnt,0);
         glTexCoord3f(0.0, 1.0, 0.0);
        glVertex3f(-10,lnt,0);
    }
    glEnd();
		}


//glPopMatrix();

}
void gameover()
{
    glEnable(GL_TEXTURE_2D);
		{
		    glColor3f(1,1,1);
			glBindTexture(GL_TEXTURE_2D, gameoverr);


    glBegin(GL_QUADS);
				{
				    glTexCoord3f(0.0, 0.0, 0.0);
				    glVertex3f(0,0,0);

				    glTexCoord3f(1.0, 0.0, 0.0);
				    glVertex3f(0,50,0);

				    glTexCoord3f(1.0, 1.0, 0.0);
				    glVertex3f(0,50,50);

				    glTexCoord3f(0.0, 1.0, 0.0);
				    glVertex3f(0,0,50);
				}
				glEnd();



		}

}

void objects( double ob)
{
double g;

for(g=250;g<ob;g+=900)//right wall
{

glPushMatrix();
    glTranslatef(2,g,0);
    wall();

glPopMatrix();
}


for(g=450;g<ob;g+=900)//mid wall
{

glPushMatrix();
    glTranslatef(-2,g,0);
    wall();

glPopMatrix();
}


for(g=100;g<ob;g+=900)//left wall
{

glPushMatrix();
    glTranslatef(-6,g,0);
    wall();

glPopMatrix();
}


glColor3f(0,0,0);
for(g=200;g<ob;g+=500)
{
    glPushMatrix();
glTranslatef(0,0,.1);
circle(0,g,2);
glPopMatrix();
}

glColor3f(0,0,1);
for(g=400;g<ob;g+=600)
{
    glPushMatrix();
glTranslatef(0,g,.1);
river();
glPopMatrix();
}

}

void display()
{
    //codes for Models, Camera

    //clear the display
    //color black
    glClearColor(0, 0, 0, 0);

    //clear buffers to preset values
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /***************************
    / set-up camera (view) here
    ****************************/

    //load the correct matrix -- MODEL-VIEW matrix
    //specify which matrix is the current matrix
    glMatrixMode(GL_MODELVIEW);

    //initialize the matrix
    //replace the current matrix with the identity matrix [Diagonals have 1, others have 0]
    glLoadIdentity();

    //now give three info
    //1. where is the camera (viewer)?
    //2. where is the camera looking?
    //3. Which direction is the camera's UP direction?


  if(h<-6)
    gluLookAt(-180,0,0,-200,0,0,0,0,1);
    else
         gluLookAt(p,q,r,p+m,q+s,r,0,0,1);

    //again select MODEL-VIEW
    glMatrixMode(GL_MODELVIEW);

    /**************************************************
    / Grid and axes Lines(You can remove them if you want)
    ***************************************************/

    // draw the three major AXES
   // drawAxis();

    //some grid lines along the field

// glutWireTorus(10,50,50,50);

//glutWireTeapot(50);
//GLUquadricObj* obj = gluNewQuadric();
//glTranslatef(t,s,m);
//gluCylinder(obj,10,10,10,10,10);



glPushMatrix();

	glColor3f(0.0,0.0,0.0);

	glTranslated(10,q+30,20);
	glScaled(.5,.5,0);
    	glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN,(int)'S');
	glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN,(int)'c');
	glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN,(int)'o');
	glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN,(int)'r');
	glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN,(int)'e');
	glColor3f(1.0,0.0,1.0);
	glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN,(int)':');
	glColor3f(0.0,0.0,0.0);
	glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN,(int)score);
	glPopMatrix();



glPushMatrix();
glTranslatef(-220,-30,-30);
glScalef(0,1.2,1.2);
gameover();
glPopMatrix();


roadtof(size);

glPushMatrix();
glTranslatef(-10,size+10,0);
glRotatef(-90,0,0,1);
roadtof(size/2);
glPopMatrix();

glPushMatrix();
glTranslatef((size/2),size,0);
roadtof(size/2);
glPopMatrix();


glPushMatrix();
glTranslatef(size+(size/2)-10,size+(size/2)+10,0);
glRotatef(-180,0,0,1);
roadtof(size/2);
glPopMatrix();



//objects
objects(size);


glPushMatrix();
glTranslatef(-10,size+10,0);
glRotatef(-90,0,0,1);
objects(size/2);
glPopMatrix();



glPushMatrix();
glTranslatef((size/2),size,0);
objects(size/2);
glPopMatrix();


glPushMatrix();
glTranslatef(size+(size/2)-10,size+(size/2)+10,0);
glRotatef(-180,0,0,1);
objects(size/2);
glPopMatrix();



//glPopMatrix();


glPushMatrix();
 //glColor3f(1, 1, 1);
 glTranslatef(p+(m*4.2),q+(s*4),h+2);
glRotatef(fall,1,0,0);
if(s==10)
glRotatef(180,0,1,0);

if(m==10)
glRotatef(90,0,1,0);
glScalef(1,2,3);
//glColor3f(1, 1, 1);
//glutSolidCube(2);
glEnable(GL_TEXTURE_2D);
		{
		    glColor3f(1,1,1);
			glBindTexture(GL_TEXTURE_2D, furr);

			manush();


		}


glPopMatrix();

double i,j;
for(j=-1000;j<15000;j+=1000)
for(i=-2000;i<20000;i+=1000)
ground(i,j);

if(fast==0)
    pause();


skyy();



    //ADD this line in the end --- if you use double buffer (i.e. GL_DOUBLE)
    glutSwapBuffers();
}

void keyBoardListener(unsigned char key,int x,int y)
{


int g;

if(key == 'p')
{
    if(fast>=.5)
    fast=0;
    else
        fast=1.5;

}

if(key =='w'&& fast!=0)
    fast+=.5;


            if(key == 'a' && h<=0 && fast!=0)
           {
               if(s==10)
                p-=.5;
                if(m==10)
                    q+=.5;

           }
        if(key == 'd' && h<=0 && fast!=0)
           {
            if(s==10)
            p+=.5;
            if(m==10)
            q-=.5;

           }


 if(key == 's')
    fast-=.5;
        /*   {
               if(m==10)
         p-=2;
         else if(s==10)
            q-=2;
            else if(m==-10)
                p+=2;
            else if(s==-10)
                q+=2;
           }*/
           if(key == ' ' && fast!=0)
            flag=1;


            if(key == 'q' && fast!=0)
           {
                if(s==10)
                {

                   q=q+40;
                   if(roadno!=11)
                    roadno++;
                    else
                        roadno=0;
                  m=-10;
                  s=0;
                }
                else if(m==10)
                {
                    p=p+40;
                    if(roadno!=11)
                    roadno++;
                    else
                        roadno=0;
                    m=0;
                    s=10;

                }
               else if(s==-10)
                {
                    m=10;
                    s=0;

                }
                else if(m==-10)
               {
                   s=-10;
                   m=0;
               }


           }
        if(key == 'e' && fast!=0)
           {



               if(s==10)
                {

                    q=q+40;

                     if(roadno!=11)
                    roadno++;
                    else
                        roadno=0;

                  m=10;
                  s=0;
                }
                else if(m==10)
                {
                    m=0;
                    s=-10;

                }
               else if(s==-10)
                {
                    m=-10;
                    s=0;

                }
                else if(m==-10)
               {
                   s=10;
                   m=0;
               }


           }






}

void specialKeyListener(int key, int x, int y)
{
    if (key == GLUT_KEY_UP)
    {
        vAngle+=angleSpeed;
    }
    else if (key == GLUT_KEY_DOWN)
    {
        vAngle-=angleSpeed;
    }
    else if (key == GLUT_KEY_LEFT)
    {
        hAngle-=angleSpeed;
    }
    else if (key == GLUT_KEY_RIGHT)
    {
        hAngle+=angleSpeed;
    }
    else if (key == GLUT_KEY_PAGE_UP)
    {
        if(R>=Rspeed)
        {
            R-=Rspeed;
        }
    }
    else if (key == GLUT_KEY_PAGE_DOWN)
    {
        R+=Rspeed;
    }
}

void animate()
{
double g;
if(fast>0 && h>-.8)
score++;
printf("Sccore = %.f\n",score);
if((p<-10 || p>10 || q>size) && roadno==0 && s==10)
{
    h-=.5;
}

else if(m==-10)
    h-=.5;

if((q<5000 || q>5020) && roadno==1 && m==10)
{
    h-=.5;
}

if((p<2490 || p>2510) && roadno==2 && s==10)
{
    h-=.5;
}

if((q<7500 || q>7520) && roadno==3 && m==10)
{
    h-=.5;
}

if((p<7500 || p>7520) && roadno==4 && s==-10)
{
    h-=.5;
}



for(g=250;g<size;g+=900) //right wall
if(q+40>g && q+40<g+2.1 && p>1 && p<7 )
{
     if(h>-1)
    h=-1;
    else
    h-=.5;

}

for(g=450;g<size;g+=900) //mid wall
if(q+40>g && q+40<g+2.1 && p>-2 && p<2 )
{
     if(h>-1)
    h=-1;
    else
    h-=.5;



}

for(g=100;g<size;g+=900) //left wall
if(q+40>g && q+40<g+2.1 && p>-7 && p<0 )
{
    if(h>-1)
    h=-1;
    else
    h-=.5;

}


for(g=200;g<size;g+=500) // circle
if(q+40>g && q+40 <g+6 && h<1 && p>-2 && p<2 )
{
    h-=.5;
}


for(g=400;g<size;g+=600)
if(q+40>g && q+40 <g+10 && h<1 ) //river
{
  //  h-=.5; //hihihi
}


    if(m==10 && h>=-.8 )
         p+=fast;
         else if(s==10 && h>=-.8 )
            q+=fast;
            else if(m==-10)
                p--;
            else if(s==-10)
                q--;




           if(h>=10)
            flag=2;

            if(flag ==1)
            h+=.8;
            else if(flag==2 )
           h-=.8;

            if(h<=0)
            flag=0;


            if(q>size && p > 500)
            {
             s=10;
             m=0;
             p=0;
             q=0;
            }

          // printf("%d %d hihi",h,flag);



    //codes for any changes in Models, Camera

    //camera will rotate at 0.0001 radians per frame.
    //cameraAngle += 0.0001;

    //codes for any changes in Models

    //this will call the display AGAIN
    glutPostRedisplay();

}

void init()
{
    //codes for initialization

    //angle in radian
    //cameraAngle = 0;
    R = 100.0;
    Rspeed = 3.0;

    vAngle = 0.0;
    hAngle = 0.0;
    angleSpeed = 0.05;

    //clear the screen
    glClearColor(0, 0, 0, 0);



    /************************
    / set-up projection here
    ************************/

    //load the PROJECTION matrix
    glMatrixMode(GL_PROJECTION);

    //initialize the matrix
    glLoadIdentity();

    /*
    gluPerspective() — set up a perspective projection matrix

    fovy -         Specifies the field of view angle, in degrees, in the y direction.
    aspect ratio - Specifies the aspect ratio that determines the field of view in the x direction. The aspect ratio is the ratio of x (width) to y (height).
    zNear -        Specifies the distance from the viewer to the near clipping plane (always positive).
    zFar  -        Specifies the distance from the viewer to the far clipping plane (always positive).
    */

    gluPerspective(70, 1, 0.1, 10000.0);

}


int main(int argc, char **argv)
{
    //initialize the GLUT library
    glutInit(&argc, argv);

    glutInitWindowSize(1000, 750);
    glutInitWindowPosition(0, 0);

    /*
    glutInitDisplayMode - inits display mode
    GLUT_DOUBLE - allows for display on the double buffer window
    GLUT_RGBA - shows color (Red, green, blue) and an alpha
    GLUT_DEPTH - allows for depth buffer
    */
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);

    glutCreateWindow("proj");

    //codes for initialization
    init();
loadAllImages();
    //enable Depth Testing
    glEnable(GL_DEPTH_TEST);

    //display callback function
    glutDisplayFunc(display);

    glutSpecialFunc(specialKeyListener);
    glutKeyboardFunc(keyBoardListener);

    //what you want to do in the idle time (when no drawing is occuring)
    glutIdleFunc(animate);

    //The main loop of OpenGL
    glutMainLoop();

    return 0;
}
