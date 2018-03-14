
#include <GL/glut.h>
#include <GL/freeglut.h>
#include<iostream>
#include"final3.cpp"
#include<bits/stdc++.h>
using namespace std;

//int height, width;

//static int x_zoom=0;
//static int y_zoom=0;
//static int move_x=0;
//static int move_y=0;
//static int flag_get_eq=0;
//int coubt_x=0;
//int coubt_y=0;
int n;
float points[1000][2];


void init12D(float r, float g, float b)
{
	glClearColor(r, g, b, 0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(-height, height, -width, width); //co-ordinate of view-port
}
void display1(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);

	glScaled(1+x_zoom/70.0,1+y_zoom/70.0,0);
	glTranslated(move_x,move_y,0);

	/*Drawing the axes and blocks*/{
    	//x-axis
	    glBegin(GL_LINES);
	        glColor3f(1.0, 1.0, 1.0);
	        glVertex2i(-999999,0);
	        glVertex2i(999999,0);
	    glEnd();
	    //y-axis
	    glBegin(GL_LINES);
	        glColor3f(1.0, 1.0, 1.0);
	        glVertex2i(0,-999999);
	        glVertex2i(0,999999);
	    glEnd();

	    //m=inf lines lines along x-axis;
	    for(int i=-1000; i<=1000;i+=50){
	    	if(i==0)	
	    		continue;
	    	glBegin(GL_LINES);
		        glColor3f(0.2, 0.2 , 0.2);
		        glVertex2i(i,-999999);
		        glVertex2i(i,999999);
	    	glEnd();
	    }

	    //m=0 lines along the y-axis
	    for(int i=-1000; i<=1000;i+=50){
	    	if(i==0)	
	    		continue;
	    	glBegin(GL_LINES);
		        glColor3f(0.2, 0.2 , 0.2);
		        glVertex2i(-999999,i);
		        glVertex2i(999999,i);
	    	glEnd();
	    }
	}
	if(flag_get_eq==0){
		/*cout << "Enter the number of points: ";
		cin>>n;
		cout << "Enter the points: " << endl;
//		float points[n][2];
		for (int i = 0; i <= n - 1; i++){
			cin >> points[i][0];	
			cin >> points[i][1];
		}*/

		cout << "     -> Enter the number of points you want to enter :      |	";
		cin >> n;
		cout << " |_____________________________________________________________________________________________________________________________|\n";
		cout << " |                                                                                                                             |\n";
		cout << "                                 --------------------> X    |    Y <-----------------------                                     \n";
		cout << " |_____________________________________________________________________________________________________________________________|\n";
		cout << " |                                                                                                                             |\n";
		for (int i = 0; i < n ; ++i)
		{
			cout << "                                                      ";
			cin >> points[i][0] >> points[i][1];
			cout << " |_____________________________________________________________________________________________________________________________|\n";
			if (i!=n-1)
			{
			  cout << " |                                                                                                                             |\n";
			}
		}
		cout << endl << endl;

	}
	glColor3f(1.0, 0.0, 0.0);
	float width_graph = points[n-1][0] - points[0][0];
	glBegin(GL_LINES);
	glVertex2i(points[0][0], points[0][1]);
	glVertex2i(points[1][0], points[1][1]);
	glEnd();
	//towards +X;
	for (int j = 0; j <= 1000; j++){
		for (int i = 0; i <= n - 2; i++){
			glColor3f(1.0, 0.0, 0.0);
			glBegin(GL_LINES);
			glVertex2i((j + 1)*width_graph + points[i][0], points[i][1]);
			glVertex2i((j + 1)*width_graph + points[i+1][i], points[i+1][1]);
			glEnd();
		}
		if (j<1000){
			glColor3f(1.0, 1.0, 0.0);
			glBegin(GL_LINES);
			glVertex2i(j*width_graph + points[n-1][0], points[n-1][1]);
			glVertex2i((j + 1)*width_graph + points[0][0], points[0][1]);
			glEnd();
		}
	}

	//towards -x;
	for (int j = -1; j <= 1000; j++){
		for (int i = 0; i <= n - 2; i++){
			glColor3f(1.0, 0.0, 0.0);
			glBegin(GL_LINES);
			glVertex2i(points[i][0] - j*width_graph, points[i][1]);
			glVertex2i(points[i+1][0] - j*width_graph, points[i+1][1]);
			glEnd();
		}
		if (j<1000){
			glColor3f(1.0, 1.0, 0.0);
			glBegin(GL_LINES);
			glVertex2i(points[0][0] - j*width_graph, points[0][1]);
			glVertex2i(points[n-1][0] - (j + 1)*width_graph, points[n-1][1]);
			glEnd();
		}
	}
	glFlush();
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);

	glScaled(1+x_zoom/70.0,1+y_zoom/70.0,0);
	glTranslated(move_x,move_y,0);

	/*Drawing the axes and blocks*/{
    	//x-axis
	    glBegin(GL_LINES);
	        glColor3f(1.0, 1.0, 1.0);
	        glVertex2i(-999999,0);
	        glVertex2i(999999,0);
	    glEnd();
	    //y-axis
	    glBegin(GL_LINES);
	        glColor3f(1.0, 1.0, 1.0);
	        glVertex2i(0,-999999);
	        glVertex2i(0,999999);
	    glEnd();

	    //m=inf lines lines along x-axis;
	    for(int i=-1000; i<=1000;i+=50){
	    	if(i==0)
	    		continue;
	    	glBegin(GL_LINES);
		        glColor3f(0.2, 0.2 , 0.2);
		        glVertex2i(i,-999999);
		        glVertex2i(i,999999);
	    	glEnd();
	    }

	    //m=0 lines along the y-axis
	    for(int i=-1000; i<=1000;i+=50){
	    	if(i==0)
	    		continue;
	    	glBegin(GL_LINES);
		        glColor3f(0.2, 0.2 , 0.2);
		        glVertex2i(-999999,i);
		        glVertex2i(999999,i);
	    	glEnd();
	    }
	}

	if(flag_get_eq==0){
		/*cout << "Enter the number of points: ";
	//	int n;
		cin>>n;
		cout << "Enter the points: " << endl;
		
		for (int i = 0; i <= n - 1; i++){
			cin >> points[i][0];	
			cin >> points[i][1];
		}*/

		cout << "     -> Enter the number of points you want to enter :      |	";
		cin >> n;
		cout << " |_____________________________________________________________________________________________________________________________|\n";
		cout << " |                                                                                                                             |\n";
		cout << "                                 --------------------> X    |    Y <-----------------------                                     \n";
		cout << " |_____________________________________________________________________________________________________________________________|\n";
		cout << " |                                                                                                                             |\n";
		for (int i = 0; i < n; ++i)
		{
			cout << "                                                      ";
			cin >> points[i][0];
			cin >> points[i][1];
			cout << " |_____________________________________________________________________________________________________________________________|\n";
			if (i!=n-1)
			{
			  cout << " |                                                                                                                             |\n";
			}
		}
		cout << endl << endl;

	}
	glColor3f(1.0, 0.0, 1.0);

	glBegin(GL_LINES);
	glVertex2i(points[0][0], points[0][1]);
	glVertex2i(points[1][0], points[1][1]);
	glEnd();
	//glBegin(GL_POINTS);
	for (int i = 0; i <= n - 2; i++){
		glBegin(GL_LINES);
		glVertex2i(points[i][0], points[i][1]);
		glVertex2i(points[i+1][0], points[i+1][1]);
		glEnd();
	}
	//glEnd();
	
	glFlush();
}

/*void keyPressed(unsigned char key, int x, int y){
	/*Map*/

	/*Zoom-in Zoom-out x*/
	/*if(key=='w'){//zoom in
		x_zoom=1;
		y_zoom=0;
		move_y=0;
		move_x=0;
		glutPostRedisplay();
	}
	else if(key=='s'){//zoom out
		x_zoom=-1;
		y_zoom=0;
		move_y=0;
		move_x=0;
		glutPostRedisplay();
	}
	/*traversing x*/
	/*else if(key=='a'){//to +inf
		x_zoom=0;
		y_zoom=0;
		move_y=0;
		move_x=1;
		glutPostRedisplay();
	}
	else if(key=='d'){//to -inf
		x_zoom=0;
		y_zoom=0;
		move_y=0;
		move_x=-1;
		glutPostRedisplay();
	}

	/*Zoom-in Zoom out y*/
	/*else if(key=='p'){//zoom in
		x_zoom=0;
		y_zoom=1;
		move_y=0;
		move_x=0;
		glutPostRedisplay();
	}
	else if(key=='l'){//zoom out
		x_zoom=0;
		y_zoom=-1;
		move_y=0;
		move_x=0;
		glutPostRedisplay();
	}

	/*traversing y*/
	/*else if(key=='o'){//to +inf
		x_zoom=0;
		y_zoom=0;
		move_y=1;
		move_x=0;
		glutPostRedisplay();
	}
	else if(key=='k'){//to -inf
		x_zoom=0;
		y_zoom=0;
		move_y=-1;
		move_x=0;
		glutPostRedisplay();
	}
}*/

int main(int argc, char *argv[])
{
	/*cout << "Enter the width of the window: "; cin >> width;
	cout << "Enter the height of the window: "; cin >> height;

	cout << "GRAPH CALCULATOR" << endl;
	int choice;
	cout << "Want to repeat the pattern or not?" << endl << "1:no\t2:yes" << endl;
	cout << "CHOICE: ";
	cin >> choice;*/

	int a,c,d,e,f,g;
	string b;
	cout << "\n\n %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% ";
	cout << "\n %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% ";
	cout << "\n %%%%%                                                                                                                    %%%%% ";
	cout << "\n %%%%%                                  --> WELCOME TO THE GRAPH GENERATOR <--                                            %%%%% ";
	cout << "\n %%%%%                                                                                                                    %%%%% ";
	cout << "\n %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% ";
	cout << "\n %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% \n\n";
	
	cout << "  _____________________________________________________________________________________________________________________________  \n";
	cout << " |                                                                                                                             |\n";
	cout << "     -> Press 1 for simple pattern, Press 2 for repeated pattern and 3 to give the equation!                                    \n";
	cout << " |_____________________________________________________________________________________________________________________________|\n";
	cout << " |                                                                                                                             |\n";
	cout << "     -> Enter your choice :          |	";
	cin >> a;
	cout << " |_____________________________________________________________________________________________________________________________|\n";

	cout << " |                                                                                                                             |\n";
	cout << "     -> Enter the width :            |	";
	cin >> width;
	cout << " |_____________________________________________________________________________________________________________________________|\n";

	cout << " |                                                                                                                             |\n";
	cout << "     -> Enter the height :           |	";
	cin >> height;
	cout << " |_____________________________________________________________________________________________________________________________|\n";
	cout << " |                                                                                                                             |\n";


	/*if (a!=3)
	{
		cout << "     -> Enter the number of data you want to enter :        |	";
		cin >> c;
		cout << " |_____________________________________________________________________________________________________________________________|\n";
		cout << " |                                                                                                                             |\n";
		cout << "                                 --------------------> X    |    Y <-----------------------                                     \n";
		cout << " |_____________________________________________________________________________________________________________________________|\n";
		cout << " |                                                                                                                             |\n";
		for (int i = 0; i < c; ++i)
		{
			cout << "                                                      ";
			cin >> d >> e;
			cout << " |_____________________________________________________________________________________________________________________________|\n";
			if (i!=c-1)
			{
			  cout << " |                                                                                                                             |\n";
			}
		}
		cout << endl << endl;
	}
	else{
		cout << " |   -> Enter the eequation :        |	";
		cin >> b;
		cout << " |                                                                                                                             |\n";
		cout << " *******************************************************************************************************************************\n\n";
		
	}*/

	switch (a){
	case 1:
		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
		glutInitWindowSize(width, height);
		glutCreateWindow("Simple Pattern");
		glutKeyboardFunc(keyPressed);
		init12D(0.0, 0.0, 0.0);
		glutDisplayFunc(display);
		glutMainLoop();
	case 2:
		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
		glutInitWindowSize(width, height);
		glutCreateWindow("Simple Pattern");
		init12D(0.0, 0.0, 0.0);
		glutDisplayFunc(display1);
		glutKeyboardFunc(keyPressed);
		glutMainLoop();
	case 3:
	    glutInit(&argc,argv);
	    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
	    glutInitWindowSize (width, height);
	    glutCreateWindow ("Hello Graph");
	    glutKeyboardFunc(keyPressed);
	    glutMouseFunc(mouse);
	    init2D(0.0,0.0,0.0);
	    glutDisplayFunc(display2);
	    glutMainLoop();
	}
	return 0;
}