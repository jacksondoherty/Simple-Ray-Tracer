
/*  The code provided is modified from the program "image.c" 
 *  appearing in _The OpenGL Programming Guide_ (red book).
 *  It demonstrates drawing pixels and shows the effect
 *  of glDrawPixels() and glCopyPixels().
 *
 *  There is no attempt to prevent you from drawing over the original
 *  image.
 *
 *  IMPORTANT: The window with the image must be the active window, i.e.,
 *  it must be clicked or the mouse must be over it, for input to occur.
 *  The result will be shown in the window you started the program from, 
 *  but don't make the mistake of typing in this window: it won't work.
 *
 */

#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <float.h>
#include <fstream>
#include <iostream>
#include <map>
#include <vector>
#include <math.h>
#include "Sphere.h"
#include "Triangle.h"
#include "Cuboid.h"
#include <ctime>
#include "Plane.h"
#include "PerspectCam.h"
#include "OrthoCam.h"
#include "Scene.h"
#include "Tracer.h"
using namespace std;


/* CS3258 SUPPLIED CODE */
#define	checkImageWidth 1024
#define	checkImageHeight 1024
GLubyte checkImage[checkImageHeight][checkImageWidth][3];

void dispatch(char line[]);

void standardErrorMsg(string commandName, int numArgs) {
	cout << "Error: ";
	cout << commandName;
	cout << " command accepts at least ";
	cout << numArgs;
	cout << " float parameters" << endl;
}

void argsIgnored(int numArgs) {
	cout << "Only first ";
	cout << numArgs;
	cout << " parameters accepted" << endl;
}

void specArgsErrorMsg(string commandName) {
	cout << "Error: ";
	cout << commandName;
	cout <<" command accepts 0 or 3 float specular paramaters" << endl;
}

void specArgsIgnored() {
	cout << "Only first three specular parameters accepted" << endl;
}

void colorValuesErrorMsg() {
	cout << "Error: color rgb values must be within range [0,1]" << endl;	
}

/* CS3258 SUPPLIED CODE */
void 
makeCheckImage(void)
{
   int i, j, c;
    
   for (i = 0; i < checkImageHeight; i++) {
      for (j = 0; j < checkImageWidth; j++) {
         c = ((((i&0x8)==0)^((j&0x8)==0)))*255;
         checkImage[i][j][0] = (GLubyte) c;
         checkImage[i][j][1] = (GLubyte) c;
         checkImage[i][j][2] = (GLubyte) c;
      }
   }
}

/* CS3258 SUPPLIED CODE */
void 
init(void)
{    
   glClearColor (0.0, 0.0, 0.0, 0.0);
   glShadeModel(GL_FLAT);
   makeCheckImage();
   glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
}

/* CS3258 SUPPLIED CODE */
void 
display(void)
{
   glClear(GL_COLOR_BUFFER_BIT);
   glRasterPos2i(0, 0);
   glDrawPixels(checkImageWidth, checkImageHeight, GL_RGB, 
                GL_UNSIGNED_BYTE, checkImage);
   glFlush();
}

/* CS3258 SUPPLIED CODE */
void 
reshape(int w, int h)
{
   glViewport(0, 0, (GLsizei) w, (GLsizei) h);
   //height = (GLint) h;
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluOrtho2D(0.0, (GLdouble) w, 0.0, (GLdouble) h);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

// Returns: FLT_MIN on error
float get_float(char* token, const char *delims) {
  if (token == NULL) {
    return FLT_MIN;
  }

	char* str_end;
	float flt = strtof(token, &str_end);
	if (*str_end != 0) {
		return FLT_MIN;
	}
	return flt;
}

vector<float> getFloatParams(int numParams, char* token, const char *delims, bool* errors) {
	vector<float> vect;
	for (int i = 0; i < numParams; i++) {
		token = strtok(NULL, delims);
		float flt = get_float(token, delims);
		if (flt == FLT_MIN) {
			*errors = true;
			return vect;
		}
		vect.push_back(flt);
	}

	return vect;
}

//	Set an orthographic camera looking down negative z axis
//	Left corner is 0,0,0 world space
void orthocamera(char* token, const char *delims) {
	bool errors = false;
	vector<float> params = getFloatParams(2, token, delims, &errors);
	if (errors) {
		standardErrorMsg("Orthocamera", 2);
		return;
	}

	token = strtok(NULL, delims);
	if (token != NULL) {
		argsIgnored(2);
	}

	int screenWidth = params[0];
	int screenLength = params[1];

	glutReshapeWindow(screenWidth, screenLength);

	OrthoCam *orthoCam = new OrthoCam(screenWidth, screenLength);

	Scene *scene = Scene::getInstance();
	scene->setCamera(orthoCam);
}

// Set and position a perspective camera
// Arguments: ex, ey, ez, gx, gy, gz, ux, uy, uz, s, au, av, bu, bv
void camera(char* token, const char *delims) {
	bool errors = false;
	vector<float> params = getFloatParams(14, token, delims, &errors);
	if (errors) {
		standardErrorMsg("Camera", 14);
		return;
	}

	token = strtok(NULL, delims);
	if (token != NULL) {
		argsIgnored(14);
	}

	Vec3f eyepoint(params[0], params[1], params[2]);
	Vec3f gazeDirection(params[3], params[4], params[5]);
	Vec3f upVector(params[6], params[7], params[8]);
	float distanceToScreen = params[9];
	int downDimension = params[10];
	int leftDimension = params[11];
	int upDimension = params[12];
	int rightDimension = params[13];

	int screenWidth = rightDimension - leftDimension;
	int screenLength = upDimension - downDimension;

	if (screenWidth<=0 || screenLength<=0) {
		cout << "Error: parameters must result in positive width and length dimensions" << endl;
		return;
	}

	glutReshapeWindow(screenWidth, screenLength);

	PerspectCam *pCam = new PerspectCam(
		eyepoint,
		gazeDirection,
		upVector,
		distanceToScreen,
		upDimension,
		downDimension,
		leftDimension,
		rightDimension);

	Scene *scene = Scene::getInstance();
	scene->setCamera(pCam);

	glutReshapeWindow(screenWidth, screenLength);
}

// Set scene background color
// Arguments: r, g, b
void background(char* token, const char *delims) {
	bool errors = false;
	vector<float> params = getFloatParams(3, token, delims, &errors);
	if (errors) {
		standardErrorMsg("Background", 3);
		return;
	}

	token = strtok(NULL, delims);
	if (token != NULL) {
		argsIgnored(3);
	}

	for (size_t i = 0; i < params.size(); i++) {
		if (params[i] < 0 || params[i] > 1) {
			colorValuesErrorMsg();
			return;
		}
	}

	Color bColor = Color(params[0], params[1], params[2]);

	Scene *scene = Scene::getInstance();
	scene->setBackgroundColor(bColor);
}

// Add sphere to scene
// Arguments: R, cx, cy, cz, ar, ag, ab, rr, rg, rb, sr, sg, sb
// Spec arguments optional
void sphere(char* token, const char *delims) {
	bool errors = false;
	vector<float> params = getFloatParams(10, token, delims, &errors);
	if (errors) {
		standardErrorMsg("Sphere", 10);
		return;
	}

	// spec arguments
	vector<float> specParams;
	token = strtok(NULL, delims);
	// ommitted defaults to zero which will signal diffuse color
	if (token == NULL) {
		specParams.push_back(0);
		specParams.push_back(0);
		specParams.push_back(0);
	} else {
		float flt = get_float(token, delims);
		if (flt == FLT_MIN) {
			specArgsErrorMsg("Sphere");
			return;
		}
		params.push_back(flt);

		bool specErrors = false;
		specParams = getFloatParams(2, token, delims, &specErrors);
		if (specErrors) {
			specArgsErrorMsg("Sphere");			
			return;
		}

		token = strtok(NULL, delims);
		if (token != NULL) {
			specArgsIgnored();
		}
	}

	for (size_t i = 0; i < specParams.size(); i++) {
		params.push_back(specParams[i]);
	}

	float radius = params[0];
	Vec3f center(params[1], params[2], params[3]);
	Color ambientColor(params[4], params[5], params[6]);
	Color reflectedColor(params[7], params[8], params[9]);
	Color specularColor(params[10], params[11], params[12]);
	Material m(ambientColor, reflectedColor, specularColor);

	SceneObject *s = new Sphere(radius, center, m);

	Scene *scene = Scene::getInstance();
	scene->addObject(s);
}

// Add triangle to scene
// Arguments: ux, uy, uz, vx, vy, vz, wx, wy, wz, ar, ag, ab, rr, rg, rb, 
//						sr, sg, sb
// Spec arguments optional
void triangle(char* token, const char *delims) {
	bool errors = false;
	vector<float> params = getFloatParams(15, token, delims, &errors);
	if (errors) {
		standardErrorMsg("Triangle", 15);
		return;
	}

	// spec arguments
	vector<float> specParams;
	token = strtok(NULL, delims);
	// ommitted defaults to zero which will signal diffuse color
	if (token == NULL) {
		specParams.push_back(0);
		specParams.push_back(0);
		specParams.push_back(0);
	} else {
		float flt = get_float(token, delims);
		if (flt == FLT_MIN) {
			specArgsErrorMsg("Triangle");
			return;
		}
		params.push_back(flt);

		bool specErrors = false;
		specParams = getFloatParams(2, token, delims, &specErrors);
		if (specErrors) {
			specArgsErrorMsg("Triangle");
			return;
		}

		token = strtok(NULL, delims);
		if (token != NULL) {
			specArgsIgnored();
		}
	}

	for (size_t i = 0; i < specParams.size(); i++) {
		params.push_back(specParams[i]);
	}

	Vec3f pt1(params[0], params[1], params[2]);
	Vec3f pt2(params[3], params[4], params[5]);
	Vec3f pt3(params[6], params[7], params[8]);
	Color ambientColor(params[9], params[10], params[11]);
	Color reflectedColor(params[12], params[13], params[14]);
	Color specularColor(params[15], params[16], params[17]);

	Material m(ambientColor, reflectedColor, specularColor);
	Triangle *t = new Triangle(pt1, pt2, pt3, m);

	Scene *scene = Scene::getInstance();
	scene->addObject(t);
}

// Add box (cuboid) to scene
// Arguments: ux, uy, uz, vx, vy, vz, ar, ag, ab, rr, rg, rb, sr, sg, sb
// Spec arguments optional
void box(char* token, const char *delims) {
	bool errors = false;
	vector<float> params = getFloatParams(12, token, delims, &errors);
	if (errors) {
		standardErrorMsg("Box", 12);
		return;
	}

	// spec arguments
	vector<float> specParams;
	token = strtok(NULL, delims);
	// ommitted defaults to zero which will signal diffuse color
	if (token == NULL) {
		specParams.push_back(0);
		specParams.push_back(0);
		specParams.push_back(0);
	} else {
		float flt = get_float(token, delims);
		if (flt == FLT_MIN) {
			specArgsErrorMsg("Box");
			return;
		}
		params.push_back(flt);

		bool specErrors = false;
		specParams = getFloatParams(2, token, delims, &specErrors);
		if (specErrors) {
			specArgsErrorMsg("Box");
			return;
		}

		token = strtok(NULL, delims);
		if (token != NULL) {
			specArgsIgnored();
		}
	}

	for (size_t i = 0; i < specParams.size(); i++) {
		params.push_back(specParams[i]);
	}

	Vec3f u(params[0], params[1], params[2]);
	Vec3f v(params[3], params[4], params[5]);

	Color ambientColor(params[6], params[7], params[8]);
	Color reflectedColor(params[9], params[10], params[11]);
	Color specularColor(params[12], params[13], params[14]);
	Material m(ambientColor, reflectedColor, specularColor);

	Cuboid *c = new Cuboid(u, v, m);

	Scene *scene = Scene::getInstance();
	scene->addObject(c);
}

// Add plane to scene
// Arguments: nx, ny, nz, px, py, pz, ar, ag, ag, rr, rg, rb, sr, sg, sb
// Spec aguments optional
void plane(char* token, const char *delims) {
	bool errors = false;
	vector<float> params = getFloatParams(12, token, delims, &errors);
	if (errors) {
		standardErrorMsg("Plane", 15);
		return;
	}

	// spec arguments
	vector<float> specParams;
	token = strtok(NULL, delims);
	// ommitted defaults to zero which will signal diffuse color
	if (token == NULL) {
		specParams.push_back(0);
		specParams.push_back(0);
		specParams.push_back(0);
	} else {
		float flt = get_float(token, delims);
		if (flt == FLT_MIN) {
			specArgsErrorMsg("Plane");
			return;
		}
		params.push_back(flt);

		bool specErrors = false;
		specParams = getFloatParams(2, token, delims, &specErrors);
		if (specErrors) {
			specArgsErrorMsg("Plane");
			return;
		}

		token = strtok(NULL, delims);
		if (token != NULL) {
			specArgsIgnored();
		}
	}

	for (size_t i = 0; i < specParams.size(); i++) {
		params.push_back(specParams[i]);
	}

	Vec3f normal(params[0], params[1], params[2]);
	Vec3f passingPoint(params[3], params[4], params[5]);
	Color ambientColor(params[6], params[7], params[8]);
	Color reflectedColor(params[9], params[10], params[11]);
	Color specularColor(params[12], params[13], params[14]);
	Material m(ambientColor, reflectedColor, specularColor);

	SceneObject *s = new Plane(normal, passingPoint, m);

	Scene *scene = Scene::getInstance();
	scene->addObject(s);
}

// Add a light to scene at infinity
// Arguments: lr, lg, lb, dx, dy, dz
void ilight(char* token, const char *delims) {
	bool errors = false;
	vector<float> params = getFloatParams(6, token, delims, &errors);
	if (errors) {
		standardErrorMsg("Ilight", 6);
		return;
	}

	token = strtok(NULL, delims);
	if (token != NULL) {
		argsIgnored(6);
	}

	for (int i = 0; i < 3; i++) {
		if (params[i] < 0 || params[i] > 1) {
			colorValuesErrorMsg();
			return;
		}
	}

	Color lightColor(params[0], params[1], params[2]);
	Vec3f direction(params[3], params[4], params[5]);

	Light *l = new Light(lightColor, direction);

	Scene *scene = Scene::getInstance();
	scene->addLight(l);
}

// clear screen and all lights and objects
void clear() {
	cout << "Clearing..." << endl;

	Scene *scene = Scene::getInstance();
	scene->clearObjects();
	scene->clearLights();

	glClear(GL_COLOR_BUFFER_BIT);
	glRasterPos2i(0,0);
	glFlush();
}

void trace() {
	cout << "Tracing..." << endl;
	int start = time(NULL);

	Scene *scene = Scene::getInstance();
	if (scene->getCamera() == NULL) {
		cout << "Error: no camera has been properly setup" << endl;
		return;
	}

	Tracer tracer(scene);
	tracer.trace();

	display();
	int end = time(NULL);
	int renderTime = end - start;
	cout << "Render Time: " << renderTime << " second(s)" << endl;
}

void test() {
	Scene *scene = Scene::getInstance();
	scene->printObjects();
	scene->printLights();
}

void read(char *token, const char *delims) {
	token = strtok(NULL, delims);
	if (token == NULL) {
		printf("Error: No file name supplied\n");
		return;
	} 

	printf("Attempting to open '%s'\n", token);

	FILE *file = fopen(token, "r");
	if (file == NULL) {
		printf("Error: Could not read file\n");
		return;
	}

	printf("Reading...\n");

	char* line = NULL;
	size_t len = 0;
	while (getline(&line, &len, file) != -1) {
		dispatch(line);
	}
	fclose(file);
}

// PRECOND: line is non-null
void dispatch(char line[]) {
	if (line[0] == '\0') return;

	// eliminate text after #
	char *ch = strchr(line, '#');
	if (ch != NULL) {
		*ch = '\0';
	}

	const char *delims = " ,\n";
	char* token = strtok(line, delims);

	// occurs with comments
	if (token == NULL) return;

  if (strcasecmp(token, "Orthocamera") == 0) {
  	orthocamera(token, delims);
  } else if (strcasecmp(token, "Camera") == 0) {
  	camera(token, delims);
  } else if (strcasecmp(token, "Background") == 0) {
  	background(token, delims);
  } else if (strcasecmp(token, "Sphere") == 0) {
  	sphere(token, delims);
  } else if (strcasecmp(token, "Triangle") == 0) {
  	triangle(token, delims);
  } else if (strcasecmp(token, "Box") == 0) {
  	box(token, delims);
  } else if (strcasecmp(token, "Ilight") == 0) {
  	ilight(token, delims);
  } else if (strcasecmp(token, "Clear") == 0) {
  	clear();
  } else if (strcasecmp(token, "Trace") == 0) {
  	trace();
  } else if (strcasecmp(token, "Test") == 0) {
  	test();
  } else if (strcasecmp(token, "Read") == 0) {
  	read(token, delims);
  } else if (strcasecmp(token, "Plane") == 0) {
  	plane(token, delims);
  } else {
		printf("Non-recognizable command\n");
	}
}

/* CS3258 SUPPLIED CODE */
void
main_loop(char line[])
{  
  if (line == NULL)
  {
    printf("Exiting...\n");
    exit(0);
  }
  else
  		dispatch(line);
   
  printf("CLI> ");
  fflush(stdout);

  return;
}

#define MAXLINE 1024

/*  ASCII Values for return, backspace, delete, escape and ctrl-d */
#define CR   13
#define BS    8
#define DEL 127
#define ESC  27
#define EOT   4

/* CS3258 SUPPLIED CODE */
void
read_next_command(unsigned char key, int x, int y)
{
   static char line[MAXLINE];
   static int count;
  
   if(count >= MAXLINE - 1)
   {
      printf("Error: Maximum line length exceeded. Discarded input.\n");
      count = 0;
      return;
   }

   putchar(key);
   fflush(stdout);  /* Immediate output (gratification) */
   
   if (key != CR && key != BS && key != DEL && key != ESC && key != EOT)
   {
      line[count]=key;
      count++;
   }
   else if (key == BS || key == DEL)
   {
      if(count == 0)
         return;
      
      fflush(stdout);
      count--;
   }
   else if (key == CR)
   {
      printf("\n");
      line[count] = '\0';
      count = 0;
      main_loop(line);
   }
   else if (key == ESC)
   {
      glutPostRedisplay();
   }
   else
   {
      printf("Exiting...\n");
      exit(0);
   }
}

/* CS3258 SUPPLIED CODE */
int 
main(int argc, char** argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(250, 250);
  glutInitWindowPosition(100, 100);
  glutCreateWindow(argv[0]);
  init();
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutKeyboardFunc(read_next_command);

  printf("CLI> ");
  fflush(stdout);

  glutMainLoop();
  return 0; 
}
