/************************************************************************
* @author yffei
*
************************************************************************/
#define GLUT_DISABLE_ATEXIT_HACK  
#include<gl/glew.h>
#include<gl/GLUT.H>  
#include<gl/GLU.H>  
#include<gl/GL.H>  
#include<stdio.h>
#include<math.h>  
#include<string>
#include<iostream>
#include<istream>
#include<fstream>

const char* pVSFileName = "base.vs";
const char* pFSFileName = "base.fs";
const char* ShaderDir   = "shader/";

const GLfloat factor = 0.1f;
void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_TRIANGLES);
	glVertex3f(-0.75f, 0.5f, 0.0f);
	glVertex3f(0.75f, 0.5f, 0.0f);
	glVertex3f(0.0f, -0.5f, 0.0f);
	glEnd();

	glutSwapBuffers();
}

bool ReadFile(const char* pFileName, std::string& outFile)
{
	using namespace std;

	string  wholeDir(ShaderDir); 
	wholeDir += pFileName;
	ifstream f(wholeDir.c_str());

	bool ret = false;

	if (f.is_open()) {
		string line;
		while (getline(f, line)) {
			outFile.append(line);
			outFile.append("\n");
		}

		f.close();

		ret = true;
	}

	return ret;
}


void CompileShader()
{
	using namespace std;
	GLuint ShaderProgram = glCreateProgram();

	if (ShaderProgram == 0) {
		fprintf(stderr, "Error creating shader program\n");
	}
	string vs, fs;

	/*if (!ReadFile(pVSFileName, vs)) {
		exit(1);
	};

	if (!ReadFile(pFSFileName, fs)) {
		exit(1);
	};*/
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(600, 600);
	glutCreateWindow("OpenGL FrameWork");

	glutDisplayFunc(&RenderScene);

	// Must be done after glut is initialized!
	GLenum res = glewInit();
	if (res != GLEW_OK) {
		fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
		return 1;
	}

	CompileShader();

	glutMainLoop();
	return 0;
}