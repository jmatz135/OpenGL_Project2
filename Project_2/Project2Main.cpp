#include <iostream>
using namespace std;

#include <GL/glut.h>

void myDraw();
void keyboard( unsigned char, int, int);
void special( int, int, int );
void Menu();

float lowerRot = 0.0;
float upperRot = 0.0;
float handRot = 0.0;
float tx = 0.0;
float ty = 0.0;

void main( int argc, char *argv[] )
{
	// Print menu
	Menu();

  // Initialize window system
  glutInit( &argc, argv );
  glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
  glutInitWindowSize( 640, 480 );
  glutCreateWindow( "Robot arm" );

  // Projection
  glMatrixMode( GL_PROJECTION );
  glLoadIdentity();
  gluPerspective( 45.0, 1.333, 0.01, 10000.0 );

	// View transformation (move scene away from camera at origin)
  glMatrixMode( GL_MODELVIEW );
  glLoadIdentity();
  glTranslatef( 0, 0, -12 );

  // Hidden surface z-buffering
  glEnable( GL_DEPTH_TEST );

  // Callbacks
  glutDisplayFunc( myDraw );
  glutKeyboardFunc( keyboard );
	glutSpecialFunc( special );

	// Main loop
  glutMainLoop();
}

// Display callback
void myDraw()
{	
	// Clear the screen
	glClearColor( 0.0, 0.0, 0.0, 1.0);
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	// Save view translation matrix
	glPushMatrix();

	// Move entire arm
	glPushMatrix();
	glTranslatef( tx, ty, 0.0 );

	// Draw upper arm
	glRotatef( upperRot, 0, 0, 1 );		// rotate about pivot point
	glTranslatef( 1.0, 0, 0 );				// move to pivot point
	glPushMatrix();										// save current matrix
	glScalef( 2.0, 1.0, 1.0 );				// add scaling to matrix
	glColor3f( 1.0, 1.0, 1.0 );
	glutWireCube( 1.0 );
	glPopMatrix();										// discard effect of scaling, restore previous matrix	

	// Draw lower arm
	glTranslatef( 2, 0, 0 );					// move to end of upper arm
	glTranslatef( -1.0, 0, 0 );				// move back to origin
	glRotatef( lowerRot, 0, 0, 1 );		// rotate about pivot point
	glTranslatef( 1.0, 0, 0 );				// move to pivot point
	glPushMatrix();										// save current matrix, make copy
	glScalef( 2.0, 0.5, 1.0 );				// add scaling to matrix
	glColor3f( 1.0, 1.0, 0.0 );
	glutWireCube( 1.0 );
	glPopMatrix();										// discard effect of scaling, restore previous matrix

	// Draw hand
	glTranslatef( 1.5, 0, 0 );				// move to end of lower arm
	glRotatef( handRot, 1, 0, 0 );		// swivel (rotate around x axis)
	glPushMatrix();										// save current matrix, make copy
	glScalef( 1.0, 1.0, 0.5 );				// add scaling to matrix
	glColor3f( 1.0, 0.0, 0.0 );
	glutWireCube( 1.0 );
	glPopMatrix();										// discard effect of scaling, restore previous matrix

	// Discard entire arm movement
	glPopMatrix();

	// Restore view translation
	glPopMatrix();

	// Execute draw commands
	glutSwapBuffers();
}

// Keyboard callback
void keyboard( unsigned char key, int x, int y )
{
  // Process entries */
  switch( key )
    {
			case 'h':
				handRot += 1;
				break;
			case 'l':
				lowerRot += 1;
				lowerRot = float(int(lowerRot)%90);
				break;
			case 'u':
				upperRot += 1;
				break;
			case 'q':
				exit(1);
				break;
    }

  // Redraw the scene
  glutPostRedisplay();
}

// Special function callback
void special( int key, int x, int y )
{
  // Process entries */
  switch( key )
  {
		case GLUT_KEY_RIGHT:
			tx += 0.1;
			break;
		case GLUT_KEY_LEFT:
			tx -= 0.1;
			break;
		case GLUT_KEY_UP:
			ty += 0.1;
			break;
		case GLUT_KEY_DOWN:
			ty -= 0.1;
			break;
	}

	// Redraw the scene
  glutPostRedisplay();
}

void Menu()
{
	// Print menu to screen here
	cout << "Keyboard commands" << endl;
	cout << "-----------------" << endl;
	cout << "u - rotate upper arm" << endl;
	cout << "l - rotate lower arm" << endl;
	cout << "h - swivel hand" << endl;
	cout << "q - exit" << endl;
	cout << "right/left arrow - move entire arm in x" << endl;
	cout << "up/down arrow - move entire arm in y" << endl;
}