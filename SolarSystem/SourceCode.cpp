// This project is based on the skeleton project available at http://www.math.ucsd.edu/~sbuss/MathCG/OpenGLsoft/Solar/Solar.html

#include "Solar.h"   
#include <stdlib.h>
#include<math.h>
#include"glut.h"						

int flag=0;
static int val=1;
GLfloat pos[]={0.0,0.0,0.0,1.0};
GLfloat posl1[]={0.0,0.0,1000,1.0};
GLfloat specref[] = {1.f, 1.f, 1.f , 1.0f};
GLfloat ambient[]={.3,.3,.3,1.0};
GLfloat diffuse[]={1.0,1.0,1.0,1.0};
GLfloat emissionSun[]={1.0,1.0,1.0,1.0};

void handleMenu(int);
void MenuInit();
void drawsun();
void drawEarth();
void drawVenus();
void drawJupiter();
void drawSaturn();
void startScreen();

static GLenum spinMode = GL_TRUE;
static GLenum singleStep = GL_FALSE;

// These three variables control the animation's state and speed.
static float HourOfDay = 0.0;
static float DayOfYear = 0.0;
static float AnimateIncrement =24.0;							// Time step for animation (hours) for Earth
static float HourOfDayJ =0.0;
static float DayOfYearJ =0.0;
static float AnimateIncrementJ =9.9;
static float HourOfDayV =0.0;
static float DayOfYearV =0.0;
static float AnimateIncrementV =5832;
static float HourOfDayS =0.0;
static float DayOfYearS =0.0;
static float AnimateIncrementS =10.45;


void text(float x, float y,void *font,const char *string)		//User defined function to print a string on screen
{
	const char *c;
	glRasterPos2f(x, y);										//position on screen where text is to be rendered
 	for (c=string; *c != '\0'; c++) 
	{
        		glutBitmapCharacter(font, *c);
    }
} 

// glutKeyboardFunc is called below to set this function to handle
//all normal key presses.  
static void KeyPressFunc( unsigned char Key, int x, int y )
{
	switch ( Key ) {
	case 'R':
	case 'r':
		Key_r();
		break;
	case 's':
	case 'S':
		Key_s();
		break;
	case 13:
		flag=1;
		break;
	case 27:				// Escape key
		exit(1);
	}
}

// glutSpecialFunc is called below to set this function to handle
//all special key presses.  See glut.h for the names of
//special keys.
static void SpecialKeyFunc( int Key, int x, int y )
{
	switch ( Key ) {
	case GLUT_KEY_UP:		
		Key_up();
		break;
	case GLUT_KEY_DOWN:
		Key_down();
		break;
	}
}


static void Key_r(void)
{
	if ( singleStep ) {						// If ending single step mode
		singleStep = GL_FALSE;
		spinMode = GL_TRUE;					// Restart animation
	}
	else {
		spinMode = !spinMode;				// Toggle animation on and off.
	}
}

static void Key_s(void)
{
	singleStep = GL_TRUE;
	spinMode = GL_TRUE;
}

static void Key_up(void)
{
    AnimateIncrement *= 2.0;			// Double the animation time step
	AnimateIncrementJ *=2.0;
	AnimateIncrementV *=2.0;
	AnimateIncrementS *=2.0;

}

static void Key_down(void)
{
    AnimateIncrement /= 2.0;			// Halve the animation time step
	AnimateIncrementJ /= 2.0;
	AnimateIncrementV /=2.0;
	AnimateIncrementS /=2.0;

}

 void startScreen()
{
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();
		if(flag==0)
		{
			glTranslatef(0.0,0.0,-15.0);
			glColor3f(1.0,0.0,0.0);
			text(-3.0,7.0,(void *)8,"WELCOME!!!");

			glColor3f(0.0,0.0,1.0);
			text(-4.0,6.0,(void *)8,"SIMULATION OF SOLAR SYSTEM");
			text(-4.0,4.0,(void *)7,"INTERACTIONS:");
			text(-4.0,3.0,(void *)7,"S         : SINGLE STEP ANIMATION");
			text(-4.0,2.5,(void *)7,"R         : RESTART ANIMATION ");
			text(-4.0,2.0,(void *)7,"UP       : INCREASE ANIMATION SPEED");
			text(-4.0,1.5,(void *)7,"DOWN : DECREASE ANIMATION SPEED");
			text(-4.0,1.0,(void *)7,"ESC    : EXIT");
			text(-4.0,-0.5,(void *)8,"PRESS ENTER TO START THE SIMULATION");
			text(-4.0,-1.5,(void *)8,"RIGHT CLICK TO SELECT THE VIEW");
			text(5.0,-3.0,(void *)7,"BY:");
			text(5.0,-3.5,(void *)7,"BHUWAN - 1RE11CS022");
			text(5.0,-4.0,(void *)7,"BIBEK      - 1RE11CS120");

			glFlush();
			glutSwapBuffers();
			glutPostRedisplay();
		
			
		}
		
		if(flag==1)
		{
			Animate();
		}
}


// Animate() handles the animation and the redrawing of the graphics window contents.
static void Animate(void)
{
	    if (spinMode) {
		// Update the animation state
        HourOfDay += AnimateIncrement;
        DayOfYear += AnimateIncrement/24.0;
		
		HourOfDayJ +=AnimateIncrementJ;
		DayOfYearJ +=AnimateIncrementJ/9.9;
		
		HourOfDayV +=AnimateIncrementV;
		DayOfYearV +=AnimateIncrementV/5832;

		HourOfDayS +=AnimateIncrementS;
		DayOfYearS +=AnimateIncrementS/10.45;

        HourOfDay = HourOfDay - ((int)(HourOfDay/24))*24;
        DayOfYear = DayOfYear - ((int)(DayOfYear/365))*365;
	
		HourOfDayJ =HourOfDayJ -((int)(HourOfDayJ/9.9))*9.9;
		DayOfYearJ =DayOfYearJ -((int)(DayOfYearJ/4328.9))*4328.9;

		HourOfDayV =HourOfDayV -((int)(HourOfDayV/5832))*5832;
		DayOfYearV =DayOfYearV -((int)(DayOfYearV/224.7))*224.7;

		HourOfDayS =HourOfDayS -((int)(HourOfDayS/10.45))*10.45;
		DayOfYearS =DayOfYearS -((int)(DayOfYearS/10759))*10759;
	}
	
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	switch (val) //calling corresponding function depending on menu selection
	{
		case 1: 
			glTranslatef ( 3.0, 0.0, -15.0 );
			glRotatef( 20.0, 1.0, 0.0, 1.0 );
			break;
		case 2:
			glTranslatef ( 0.0, 0.0, -15.0 );
			glRotatef( 7.0, 1.0, 0.0, 0.0 );
			break;
		case 3:
			glTranslatef ( 0.0, 0.0, -18.0 );
			glRotatef( 90.0, 1.0, 0.0, 0.0 );
			break;
		}
		
	
	glPushAttrib(GL_LIGHTING_BIT);
	glPushMatrix();
	
	
	drawsun();
	
	
	glPopAttrib();
	glPopMatrix();
	
	glPushMatrix();
	glDisable(GL_LIGHT1);
	glEnable(GL_LIGHT0);					
	glLightfv(GL_LIGHT0,GL_POSITION,pos);
	
	drawEarth();
    
	glPopMatrix();
	glPushMatrix();
	
	drawJupiter();

	glPopMatrix();
	glPushMatrix();
	
	drawVenus();
	
	glPopMatrix();
	glPushMatrix();

	drawSaturn();

	glPopMatrix();
	
	// Flush the pipeline, and swap the buffers
    glFlush();
    glutSwapBuffers();
	
	

	if ( singleStep ) {
		spinMode = GL_FALSE;
	}

	glutPostRedisplay();		// Request a re-draw for animation purposes

		}

void drawsun()
{
	
	//Setup lighting
	glEnable(GL_LIGHT1);
	glLightfv(GL_LIGHT1, GL_SPECULAR, specref);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT1, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT1,GL_POSITION,posl1);

	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specref);
	glMateriali(GL_FRONT, GL_SHININESS, 0);
	glMaterialfv(GL_FRONT, GL_EMISSION, emissionSun);			//make sun glow
			
    glutSolidSphere( 1.2,30,30 );
	
}

void drawEarth()
{
	
	// First position the Earth around the sun
	//Use DayOfYear to determine its position
	glPushMatrix();
    glRotatef( 360.0*DayOfYear/365.0, 0.0, 1.0, 0.0 );
    glTranslatef( 4.0, 0.0, 0.0 );
    glPushMatrix();										// Save matrix state
	
	//Second, rotate the earth on its axis.
	//Use HourOfDay to determine its rotation.
	
	glRotatef( 360.0*HourOfDay/24.0, 0.0, 1.0, 0.0 );
	
	// Third, draw earth as a Solid sphere.
    glColor3f( 0.1, 0.3, 0.9 );
    glutSolidSphere( 0.4, 30, 30);
	

	glPopMatrix();
	
	glDisable(GL_LIGHT0);
	glColor3f(1.0,1.0,0.0);
	text(.5,.5,(void *)7,"Earth");
	glEnable(GL_LIGHT0);
	
	glRotatef( 360.0*12.0*DayOfYear/365.0, 0.0, 1.0, 0.0 );			//Draw moon
    glTranslatef( 0.55, 0.0, 0.0 );
    glColor3f( 0.75, 0.75, 0.75 );
    glutSolidSphere( 0.15, 20, 20 );
	

	glPopMatrix();
	glRotatef(90,1.0,0.0,0.0);										
	glColor3f(1.0,1.0,1.0);
	gluDisk(gluNewQuadric(),4.0,4.05,100,100);						//Draw orbit
	
}

void drawVenus()
{
	// First position it around the sun
	//	Use DayOfYearV to determine its position
    glPushMatrix();
	glRotatef( 360.0*DayOfYearV/(224.7), 0.0, 1.0, 0.0 );
    glTranslatef( 2.1, 0.0, 0.0);
	
	glPushMatrix();
	
	// Second, rotate Venus on its axis.
	//	Use HourOfDayV to determine its rotation.
	glRotatef( -360.0*HourOfDayV/(5823*243), 0.0, 1.0, 0.0 );
	
	// Third, draw Venus as a Solid sphere.
    glColor3f( 0.8, 0.9, 0.5 );
    glutSolidSphere( 0.38, 30, 30);

	glPopMatrix();
	glDisable(GL_LIGHT0);
	glColor3f(1.0,1.0,0.0);
	text(.35,.35,(void *)7,"Venus");
	glEnable(GL_LIGHT0);

	glPopMatrix();
	
	glRotatef(90,1.0,0.0,0.0);
	glColor3f(1.0,1.0,1.0);
	gluDisk(gluNewQuadric(),2.08,2.14,100,100);

}
void drawJupiter()
{
	// First position it around the sun
	//	Use DayOfYearJ to determine its position
    glPushMatrix();
	glRotatef( 360.0*DayOfYearJ/(4328.9), 0.0, 1.0, 0.0 );
    glTranslatef( 8.2, 0.0, 0.0);
	
	glPushMatrix();
	
	// rotate Jupiter on its axis.
	//	Use HourOfDayJ to determine its rotation.
	glRotatef( 360.0*2.42*HourOfDayJ/9.9, 0.0, 1.0, 0.0 );
	
	// draw Jupiter as a Solid sphere.
    glColor3f( 1.0, 0.1, 0.0);
    glutSolidSphere( 1.0, 30, 30);

	glPopMatrix();
	
	glDisable(GL_LIGHT0);
	glColor3f(0.5,1.0,0.0);
	text(1.2,1.2,(void *)7,"Jupiter");
	glEnable(GL_LIGHT0);	

	glPopMatrix();
	
	glRotatef(90,1.0,0.0,0.0);
	glColor3f(1.0,1.0,1.0);
	gluDisk(gluNewQuadric(),8.17,8.23,100,100);
	
}

void drawSaturn()
{

	// First position it around the sun
	//	Use DayOfYearS to determine its position
    glPushMatrix();
	glRotatef( 360.0*DayOfYearS/(10759), 0.0, 1.0, 0.0 );
    glTranslatef( 11.0, 0.0, 0.0);
	
	glPushMatrix();
	
	// rotate Saturn on its axis.
	//	Use HourOfDayS to determine its rotation.
	glRotatef( 360.0*2.3*HourOfDayS/10.45, 0.0, 1.0, 0.0 );
	
	// draw Saturn and its rings
    glColor3f( 1.0, 0.6, 0.25);
    gluSphere(gluNewQuadric(),.6,30,30);
	glRotatef(90,1.0,0.0,0.0);
	gluDisk(gluNewQuadric(), 0.9, 1.5, 32,32);

	glPopMatrix();
	
	glDisable(GL_LIGHT0);
	glColor3f(0.5,1.0,0.0);
	text(1.0,1.0,(void *)7,"Saturn");
	glEnable(GL_LIGHT0);
	
	glPopMatrix();
	
	glRotatef(90,1.0,0.0,0.0);
	glColor3f(1.0,1.0,1.0);
	gluDisk(gluNewQuadric(),10.98,11.03,100,100);
}


void MenuInit(void) //Initialize/create menu interface
{
	 glutCreateMenu(handleMenu);
	 glutAddMenuEntry("Oblique",1);
	 glutAddMenuEntry("Front",2);
	 glutAddMenuEntry("Top",3);

	 glutAttachMenu(GLUT_RIGHT_BUTTON); //Assigning mouse button to activate menu
}

void handleMenu(int value)
{
	if(value==4)
		exit(0);
	val=value;
}


void OpenGLInit(void)
{
    glShadeModel( GL_FLAT );
    glClearColor( 0.0, 0.0, 0.0, 0.0 );
    glClearDepth( 1.0 );
    glEnable( GL_DEPTH_TEST );
	
}

// ResizeWindow is called when the window is resized
static void ResizeWindow(int w, int h)
{
    float aspectRatio;
	h = (h == 0) ? 1 : h;
	w = (w == 0) ? 1 : w;
	glViewport( 0, 0, w, h );	// View port uses whole window
	aspectRatio = (float)w/(float)h;

	// Set up the projection view matrix (not very well!)
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluPerspective( 60.0, aspectRatio, 1.0, 50.0 );
	// Select the Modelview matrix
    glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
   
}


// Main routine
// Set up OpenGL, hook up callbacks, and start the main loop
int main( int argc, char** argv )
{
	// Need to double buffer for animation
	glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE| GLUT_RGB | GLUT_DEPTH );

	// Create and position the graphics window
    glutInitWindowPosition( 0, 0 );
    glutInitWindowSize( 600, 360 );
    glutCreateWindow( "Solar System Demo" );
	
	// Initialize OpenGL.
    OpenGLInit();
	MenuInit();

	// Set up callback functions for key presses
	glutKeyboardFunc( KeyPressFunc );
	glutSpecialFunc( SpecialKeyFunc );

	// Set up the callback function for resizing windows
    glutReshapeFunc( ResizeWindow );

	// Callback for graphics image redrawing
    glutDisplayFunc(startScreen);
	
	// Start the main loop.  glutMainLoop never returns.
	glutMainLoop();

    return(0);	
}
