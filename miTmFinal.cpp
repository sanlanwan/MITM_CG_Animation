#include <iostream>
#include <time.h>
#include <math.h>

// Apple Specific Compatibility Issues
#ifdef __APPLE__
#include "GLUT/glut.h"
#else
#include "GL/glut.h"
#endif

void display();
void displayUsermitm();
void displayMitmserver();
void drawServer(int, int);
void pipeLine(int, int, float);
void pipeLine(int, int, float, int);

// Define the value of PI, upto 12 decimal places
#define PI 3.141592653589

void drawText(float x, float y, char *s)
{
	glRasterPos2f(x, y);
	for (int i = 0; s[i] != '\0'; i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, s[i]);
}
float xpos = 370, xposMitm = 70, yposMitm = -150, xposMitm2 = 215, yposMitm2 = -215;
float r, g, b;
GLfloat colors[3][3] = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
GLfloat color[3];
// ID to detect which scene the story is in.
int SCENE_ID;

// Variables for Animator Faders
GLfloat title_fade,
	intro_next_text_appear,
	kg_chap_fade, kg_title_fade,
	kg_soon_fade, kg_subtitle_1_appear,
	hs_chap_fade, hs_title_fade,
	hs_subtitle_1_appear,
	eng_chap_fade, eng_title_fade,
	ec_subtitle_1_fade,
	epilogue_para1_fade, epilogue_para2_fade, epilogue_para3_fade, epilogue_para4_fade, epilogue_para5_fade, epilogue_para6_fade,
	moral_para1_fade, moral_para2_fade, moral_para3_fade, moral_para4_fade;

// Variables for Translation Animators
GLfloat trans_x_chap1, trans_x_title1,
	trans_x_chap2, trans_y_title2,
	trans_subtitle_1_done, trans_subtitle_2_done,
	trans_x_chap3, trans_x_title3,
	trans_x_chap4, trans_x_title4,
	trans_x_sb1 = -630, trans_y_sb1 = -50, trans_x_sb2 = -1630, trans_y_sb2 = -50,
	trans_x_chap5, trans_x_title5,
	trans_x_chap6, trans_x_title6;

// Variables for Turn-based Switching
bool sun_moved_half, sun_has_set, stars_are_made,
	chapter_1_done, chapter_2_done, chapter_3_done, chapter_4_done, chapter_5_done;

// Variables for Random Star Generation
int star_alpha, no_of_stars, stars_array[40][2];

// Function to Create Delay
void delay(float secs)
{
	float end = clock() / CLOCKS_PER_SEC + secs;
	while ((clock() / CLOCKS_PER_SEC) < end)
		;
}

// Function to Print Text
void print(char *string,
		   GLfloat r, GLfloat g, GLfloat b, GLfloat a,
		   GLint x, GLint y,
		   GLfloat w, GLfloat h,
		   GLfloat strokeSize)
{
	glPushMatrix();

	glColor4f(r, g, b, a);
	glTranslatef(x, y, 0);
	glScalef(w, h, 0);

	glPointSize(strokeSize);
	glLineWidth(strokeSize);

	while (*string)
		glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, *string++);

	glPopMatrix();

	glLineWidth(1);
	glPointSize(1);
}

/*
* Titles Scene
*/
void displayIntro()
{
	// Background
	glClearColor(6.0, 6.0, 6.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	// Story Title
	print("The Demonstration of",
		  1, 0, 0, title_fade, 400, 600, .3, .3, 2);

	print("MAN",
		  1, 0, 0, title_fade, 575, 480, 1, 1, 10);

	print("IN",
		  1, 0, 0, title_fade, 655, 405, .6, .6, 8);

	print("THE",
		  1, 0, 0, title_fade, 700, 365, .2, .2, 6);

	print("MIDDLE",
		  1, 0, 0, title_fade, 670, 310, .2, .4, 4);

	print("ATTACK",
		  1, 0, 0, title_fade, 665, 270, .2, .2, 4);

	print("by Shiva Amartya Narayana(1BI17CS105)",
		  0, 0, 0, title_fade, 790, 250, .15, .15, 1);
	print(" Pranav B(1BI17CS112)",
		  0, 0, 0, title_fade, 820, 225, .15, .15, 1);

	print("Press N to continue...",
		  0, 1, 0, intro_next_text_appear, 560, 10, .09, .09, 1);
}

/*
* MITM Title Screen
*/
void mitmIntroscene()
{
	// Background
	glClearColor(0.05, 0.05, 0.05, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	// Story Title
	print("INTRODUCTION",
		  1, 1, 1, kg_chap_fade, 300 + trans_x_chap1, 400, .2, .2, 2);
	print("What is Man-in-the-middle attack?",
		  1, 1, 1, kg_title_fade, 300 + trans_x_title1, 350, .15, .3, 2);
}

/*
* About MITM
*/
void aboutMitm()
{
	// Background
	glClearColor(0.05, 0.05, 0.05, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	// Summary Title
	print("About",
		  1, 1, 1, 1, 75, 650, .3, .3, 1.5);

	// Summary Text
	print("A man-in-the-middle attack requires three players. There’s the victim,",
		  1, 1, 1, epilogue_para1_fade, 75, 575, .125, .125, 1.25);
	print("the entity with which the victim is trying to communicate,",
		  1, 1, 1, epilogue_para2_fade, 75, 525, .125, .125, 1.25);
	print("and the “man in the middle,” who’s intercepting the victim’s communications.",
		  1, 1, 1, epilogue_para3_fade, 75, 475, .125, .125, 1.25);
	print("Critical to the scenario is that the victim isn’t aware of the man in the middle.",
		  1, 1, 1, epilogue_para4_fade, 75, 425, .125, .125, 1.25);
}

/*
*	Title of Nomral Sim
*/
void usimTitlescene()
{
	// Background
	glClearColor(0.05, 0.05, 0.05, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	// Story Title
	print("SIMULATION",
		  1, 1, 1, hs_chap_fade, 300 + trans_x_chap3, 400, .2, .2, 2);
	print("USER PERFORMING A FINANCIAL TRANSACTION",
		  1, 1, 1, hs_title_fade, 400 - trans_x_title3, 350, .15, .3, 2);
}

/*
*	Title of MiTm Sim
*/
// MITM Title
void simmitmTitlescene()
{
	// Background
	glClearColor(0.05, 0.05, 0.05, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	// Story Title
	print("SIMULATION",
		  1, 1, 1, hs_chap_fade, 300 + trans_x_chap3, 400, .2, .2, 2);
	print("BANKING TRANSACTION PERFORMED WITH MITM",
		  1, 1, 1, hs_title_fade, 400 - trans_x_title3, 350, .15, .3, 2);
}

// How to protect?
void protect()
{
	// Background
	glClearColor(0.05, 0.05, 0.05, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	// Summary Title
	print("How to protect from MITM?",
		  1, 1, 1, 1, 75, 650, .2, .2, 1.5);

	// Summary Text
	print("1. Limit your sensitive activity on public networks or use a VPN connection on public networks.",
		  1, 1, 1, epilogue_para1_fade, 75, 575, .125, .125, 1.25);
	print("    A VPN will add an extra layer of security.",
		  1, 1, 1, epilogue_para2_fade, 75, 525, .125, .125, 1.25);

	print("2. Keep your operating system and your browser always up to date. ",
		  1, 1, 1, epilogue_para3_fade, 75, 475, .125, .125, 1.25);
	print("   This way, the attackers will not be able to use exploits to install malware on your computer.",
		  1, 1, 1, epilogue_para4_fade, 75, 425, .125, .125, 1.25);

	print("3. Monitor the devices connected to your network.",
		  1, 1, 1, epilogue_para5_fade, 75, 375, .125, .125, 1.25);

	print("THE END",
		  1, 1, 1, epilogue_para5_fade, 275, 250, 1.125, 1.125, 3.00);

	print("Press 'q' to exit.",
		  1, 1, 1, epilogue_para5_fade, 275, 225, .125, .125, 1.25);
}

//drawComp.cpp

// Function to draw Packets
void packet(int xpos, int ypos)
{
	glPushMatrix();
	glTranslatef(xpos, ypos, 0);
	glBegin(GL_QUADS);
	glVertex2f(0, 0);
	glVertex2f(0, 30);
	glVertex2f(30, 30);
	glVertex2f(30, 0);
	glEnd();
	glPopMatrix();
}

// Function to draw mitmPackets
void packetMitm(int xpos, int ypos)
{
	glPushMatrix();
	glTranslatef(xpos, ypos, 0);
	glRotatef(-45, 0, 0, 1);
	glBegin(GL_QUADS);
	glVertex2f(0, 0);
	glVertex2f(0, 30);
	glVertex2f(30, 30);
	glVertex2f(30, 0);
	glEnd();
	glPopMatrix();
}

// Function to draw mitmPacketscust
void packetMitmcust(int xpos, int ypos)
{
	glPushMatrix();
	glTranslatef(xpos, ypos, 0);
	glRotatef(45, 0, 0, 1);
	glBegin(GL_QUADS);
	glVertex2f(0, 0);
	glVertex2f(0, 30);
	glVertex2f(30, 30);
	glVertex2f(30, 0);
	glEnd();
	glPopMatrix();
}

// Function to draw Packet Header
void packetHeader(int xpos, int ypos)
{
	glPushMatrix();
	glTranslatef(xpos, ypos, 0);
	glBegin(GL_QUADS);
	glVertex2f(0, 0);
	glVertex2f(200, 0);
	glVertex2f(200, 220);
	glVertex2f(0, 220);
	glEnd();
	glPopMatrix();
}

//Function to alternate packets color
void changeColor(int value)
{
	int i = rand() % 3;
	color[0] = colors[i][0];
	color[1] = colors[i][1];
	color[2] = colors[i][2];
	glutTimerFunc(500, changeColor, 0);
}

void drawCircle(GLfloat x, GLfloat y,
				GLfloat r, GLfloat g, GLfloat b,
				GLfloat sx, GLfloat sy,
				GLfloat radius)
{
	glPushMatrix();

	glTranslatef(x, y, 0);
	glScalef(sx, sy, 0);

	glBegin(GL_POLYGON);
	glColor3ub(r, g, b);
	for (GLfloat i = 0; i < 360; i += 5)
		glVertex2f(radius * sin(i * PI / 180), radius * cos(i * PI / 180));
	glEnd();

	glPopMatrix();
}

void idle()
{
	if (xpos <= 1000)
	{

		xpos += 5;
	}
	else
		xpos = 370;
	glutPostRedisplay();
}

void idleMitm()
{
	if (xposMitm <= 220 && yposMitm <= 300)
	{

		xposMitm += 1;
		yposMitm -= 1;
	}
	else
	{
		xposMitm = 70;
		yposMitm = -150;
	}
	glutPostRedisplay();
}

void idleMitmcust()
{
	if (xposMitm2 <= 350 && yposMitm2 <= 430)
	{

		xposMitm2 += 1;
		yposMitm2 += 1;
	}
	else
	{
		xposMitm2 = 215;
		yposMitm2 = -215;
	}
	glutPostRedisplay();
}

// Function to Draw Comp
void display()
{
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	glPushMatrix();
	glTranslatef(0, -200, 0);
	drawServer(100, 300);
	drawText(210, 420, "USER");
	drawServer(1000, 300);
	drawText(1105, 420, "SERVER");
	pipeLine(180, 490, 0);
	glColor3f(1, 1, 1);
	packetHeader(xpos - 80, 600);
	glColor3f(1, 0, 0);
	drawText(xpos - 70, 800, "FROM: User A");
	drawText(xpos - 70, 750, "TO: User B");
	drawText(xpos - 70, 700, "HTTP Body: Amount=500");
	glColor3fv(color);
	packet(xpos, 500);
	packet(xpos - 40, 500);
	packet(xpos - 80, 500);
	glFlush();
	glPopMatrix();
}

void displayUsermitm()
{
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1, 0, 0);
	glPushMatrix();
	glTranslatef(0, 100, 0);
	glPushMatrix();
	glTranslatef(-100, 0, 0);
	pipeLine(0, 500, -45, 400);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(390, -355, 0);
	pipeLine(600, 0, 45, 400);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0, -100, 0);
	drawServer(100, 300);
	drawText(210, 420, "USER");
	drawServer(1000, 300);
	drawText(1105, 420, "SERVER");
	pipeLine(180, 490, 0);
	drawServer(550, -50);
	drawText(630, 80, "MIDDLE-MAN");
	glColor3fv(color);
	glPopMatrix();
	glColor3f(1, 1, 1);
	glPushMatrix();
	glTranslatef(0, -150, 0);
	glColor3f(1, 0, 0);
	glPopMatrix();
	glColor3f(1, 1, 1);
	glPushMatrix();
	glTranslatef(xposMitm, yposMitm, 0);
	packetHeader(0, 200);
	packetMitm(300, 400);
	packetMitm(300 - 40, 400 + 40);
	packetMitm(300 - 80, 400 + 80);
	glColor3f(1, 0, 0);
	drawText(10, 380, "FROM:User A");
	drawText(10, 330, "TO:User B");
	drawText(10, 270, "HTTP Body:Amount=500");
	glPopMatrix();
	glPopMatrix();
	glFlush();
}

void displayMitmserver()
{
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1, 0, 0);
	glPushMatrix();
	glTranslatef(0, 100, 0);
	glPushMatrix();
	glTranslatef(-100, 0, 0);
	pipeLine(0, 500, -45, 400);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(390, -355, 0);
	pipeLine(600, 0, 45, 400);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0, -100, 0);
	drawServer(100, 300);
	drawText(210, 420, "USER");
	drawServer(1000, 300);
	drawText(1105, 420, "SERVER");
	pipeLine(180, 490, 0);
	drawServer(550, -50);
	drawText(630, 80, "MIDDLE-MAN");
	glColor3fv(color);
	glPopMatrix();
	glColor3f(1, 1, 1);
	glPushMatrix();
	glTranslatef(0, -150, 0);
	glColor3f(1, 0, 0);
	glPopMatrix();
	glColor3f(1, 1, 1);
	glPushMatrix();
	glTranslatef(xposMitm2, yposMitm2, 0);
	packetHeader(650, 100);
	packetMitmcust(700, 400);
	packetMitmcust(700 - 40, 400 - 40);
	packetMitmcust(700 - 80, 400 - 80);
	glColor3f(1, 0, 0);
	drawText(660, 280, "FROM: User A");
	drawText(660, 230, "TO: User D");
	drawText(660, 170, "HTTP Body: Amount=50000");
	glPopMatrix();
	glPopMatrix();
	glFlush();
}

void pipeLine(int xpos, int ypos, float angle)
{
	glPushMatrix();
	glTranslatef(xpos, ypos, 0);
	glRotatef(angle, 0, 0, 1);
	glBegin(GL_QUADS);
	glVertex2f(90, 0);
	glVertex2f(90, 50);
	glVertex2f(900, 50);
	glVertex2f(900, 0);
	glEnd();
	glPopMatrix();
}

void pipeLine(int xpos, int ypos, float angle, int length)
{
	glPushMatrix();
	glRotatef(angle, 0, 0, 1);
	glTranslatef(xpos, ypos, 0);
	glBegin(GL_QUADS);
	glVertex2f(0, 0);
	glVertex2f(0, 50);
	glVertex2f(0 + length, 50);
	glVertex2f(0 + length, 0);
	glEnd();
	glPopMatrix();
}

void drawServer(int xpos, int ypos)
{
	glPushMatrix();
	glTranslatef(xpos, ypos, 0);

	glBegin(GL_POLYGON);
	glColor3f(1.0, 0.0, 1.0);
	glVertex2i(100, 150);
	glVertex2i(100, 250);
	glVertex2i(150, 250);
	glVertex2i(150, 150);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(1.0, 1.0, 1.0);
	glVertex2i(100, 216);
	glVertex2i(100, 208);
	glVertex2i(140, 208);
	glVertex2i(140, 216);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(1.0, 1.0, 1.0);
	glVertex2i(100, 236);
	glVertex2i(100, 220);
	glVertex2i(140, 220);
	glVertex2i(140, 236);
	glEnd();

	//PowerButton
	drawCircle(125, 170,
			   223, 189, 31, // Goldish Yellow
			   1, 1,
			   5);

	glPopMatrix();
}

void simScenesub()
{
	print("User A is transferring Rs.500 to User B",
		  1, 1, 1, 600, 380, 30, .14, .14, 1);
}

void simmitmScenesub()
{
	print("Middle man is connected to User A's network. ",
		  1, 1, 1, 600, 100, 50, .14, .14, 1);
	print("He modified the User A's request as shown and packet reaches the necessary server.", 1, 1, 1, 600, 100, 30, .14, .14, 1);
}

//finish

// Function to Render Scene
void renderScene()
{
	// Switch to know which scene is playing
	switch (SCENE_ID)
	{
	case 0:
		displayIntro();
		break;
	case 1:
		mitmIntroscene();
		break;
	case 2:
		aboutMitm();
		break;
	case 3:
		usimTitlescene();
		break;
	case 4:
		display();
		glutIdleFunc(idle);
		glutTimerFunc(500, changeColor, 0);
		simScenesub();
		break;
	case 5:
		simmitmTitlescene();
		break;
	case 6:
		displayUsermitm();
		glutIdleFunc(idleMitm);
		simmitmScenesub();
		break;
	case 7:
		displayMitmserver();
		glutIdleFunc(idleMitmcust);
		simmitmScenesub();
		break;
	case 8:
		protect();
		break;
	default:
		break;
	}

	// glFush sends it to the Display Buffer
	glFlush();
}

// Function to Handle Mouse Clicks
void mouseClick(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		std::cout << x << "\t" << 800 - y << "\n";
}

// Animator Updation Function
void update(int)
{
	// Introduction
	if (SCENE_ID == 0)
	{
		if (title_fade < 1)
			title_fade += .003;
		else
			intro_next_text_appear = 1;
	}

	// MITM Intro
	if (SCENE_ID == 1)
	{
		if (trans_x_chap1 < 100)
			trans_x_chap1 += 1;

		if (trans_x_title1 < 100)
			trans_x_title1 += 1;

		if (kg_chap_fade < 1)
			kg_chap_fade += .025;

		if (kg_title_fade < 1)
			kg_title_fade += .025;
	}

	// MITM Title Screen
	if (SCENE_ID == 2)
	{
		if (kg_soon_fade < 1)
			kg_soon_fade += .025;
		else
			kg_subtitle_1_appear = 1;
	}

	// About MITM
	if (SCENE_ID == 3)
	{
		if (trans_x_chap3 < 100)
			trans_x_chap3 += 1;

		if (trans_x_title3 < 100)
			trans_x_title3 += 1;

		if (hs_chap_fade < 1)
			hs_chap_fade += .01;

		if (hs_title_fade < 1)
			hs_title_fade += .01;
	}

	// Find out
	if (SCENE_ID == 5)
	{
		if (trans_x_chap3 < 100)
			trans_x_chap3 += 1;

		if (trans_x_title3 < 100)
			trans_x_title3 += 1;

		if (hs_chap_fade < 1)
			hs_chap_fade += .01;

		if (hs_title_fade < 1)
			hs_title_fade += .01;
	}

	// About MITM
	if (SCENE_ID == 2)
	{
		if (epilogue_para1_fade < 1)
			epilogue_para1_fade += .02;
		else if (epilogue_para2_fade < 1)
			epilogue_para2_fade += .02;
		else if (epilogue_para3_fade < 1)
			epilogue_para3_fade += .02;
		else if (epilogue_para4_fade < 1)
			epilogue_para4_fade += .02;
		else if (epilogue_para5_fade < 1)
			epilogue_para5_fade += .02;
	}

	// PROTECT
	if (SCENE_ID == 8)
	{
		if (epilogue_para1_fade < 1)
			epilogue_para1_fade += .02;
		else if (epilogue_para2_fade < 1)
			epilogue_para2_fade += .02;
		else if (epilogue_para3_fade < 1)
			epilogue_para3_fade += .02;
		else if (epilogue_para4_fade < 1)
			epilogue_para4_fade += .02;
		else if (epilogue_para5_fade < 1)
			epilogue_para5_fade += .02;
	}

	// Recalls the Display Function
	glutPostRedisplay();

	// Creates a Timer of 25ms
	glutTimerFunc(25, update, 0);
}

// Keyboard Action
void keyPress(unsigned char key, int x, int y)
{
	switch (key)
	{
		// Go to Previous Scene
	case 'b':
	case 'B':
		if (SCENE_ID == 0)
			break;
		SCENE_ID--;
		break;
		// Go to Next Scene
	case 'n':
	case 'N':
		if (SCENE_ID == 8)
			break;
		SCENE_ID++;
		break;
		// Quit Story
	case 'q':
	case 'Q':
		exit(0);
		break;
	default:
		break;
	}

	glutPostRedisplay();
}

// Function to Initialize Screen
void initializeScreen()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 1400, 0, 800);
}

// Main Function
int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(1400, 800);
	glutCreateWindow("Man in the Middle");

	// Enables Transparency
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	// Enable Smoothening
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

	// Display Function
	glutDisplayFunc(renderScene);

	// Input Functions
	glutKeyboardFunc(keyPress);
	glutMouseFunc(mouseClick);

	initializeScreen();

	// Timer Function
	// every 25 milliseconds, update function is called
	glutTimerFunc(25, update, 0);

	glutMainLoop();

	return 0;
}