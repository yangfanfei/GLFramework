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
#include "vertor.h"
#include "mvp.h"

#define WINDOW_WIDTH  1024
#define WINDOW_HEIGHT 768

struct Vertex
{
	FFVector3f v3Pos;
	FFVector2f v2Tex;

	Vertex() {}

	Vertex(FFVector3f pos, FFVector2f tex)
	{
		v3Pos = pos;
		v2Tex = tex;
	}
};


const char* pVSFileName = "base.vs";
const char* pFSFileName = "base.fs";
const char* ShaderDir   = "..//shader/";

GLuint			VBO;
GLuint			IBO;
GLuint			gMVPLocation;
FFPersProjInfo	gPersProjInfo;
FFCamera*		pCam = NULL;

void RenderScene(void)
{
	pCam->OnRender();

	glClear(GL_COLOR_BUFFER_BIT);

	FFMvp p;
	p.SetCamera(*pCam);
	p.SetPerspectiveProj(gPersProjInfo);

	glUniformMatrix4fv(gMVPLocation, 1, GL_TRUE, (const GLfloat*)p.GetWVPTrans());

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

	glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);

	glDisableVertexAttribArray(0);

	glutSwapBuffers();
}

bool ReadFile(const char* pFileName, std::string& outFile)
{
	using namespace std;

	string  wholeDir(ShaderDir); 
	wholeDir += pFileName;
	ifstream f(wholeDir, std::ios::in);

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

static void AddShader(GLuint ShaderProgram, const char* pShaderText, GLenum ShaderType)
{
	GLuint ShaderObj = glCreateShader(ShaderType);

	if (ShaderObj == 0) {
		fprintf(stderr, "Error creating shader type %d\n", ShaderType);
		exit(0);
	}

	const GLchar* p[1];
	p[0] = pShaderText;
	GLint Lengths[1];
	Lengths[0] = strlen(pShaderText);
	glShaderSource(ShaderObj, 1, p, Lengths);
	glCompileShader(ShaderObj);
	GLint success;
	glGetShaderiv(ShaderObj, GL_COMPILE_STATUS, &success);
	if (!success) {
		GLchar InfoLog[1024];
		glGetShaderInfoLog(ShaderObj, 1024, NULL, InfoLog);
		fprintf(stderr, "Error compiling shader type %d: '%s'\n", ShaderType, InfoLog);
		exit(1);
	}

	glAttachShader(ShaderProgram, ShaderObj);
}

void CompileShader()
{
	using namespace std;
	GLuint ShaderProgram = glCreateProgram();

	if (ShaderProgram == 0) {
		fprintf(stderr, "Error creating shader program\n");
	}
	string vs, fs;

	if (!ReadFile(pVSFileName, vs)) {
		exit(1);
	};

	if (!ReadFile(pFSFileName, fs)) {
		exit(1);
	};

	AddShader(ShaderProgram, vs.c_str(), GL_VERTEX_SHADER);
	AddShader(ShaderProgram, fs.c_str(), GL_FRAGMENT_SHADER);

	GLint Success = 0;
	GLchar ErrorLog[1024] = { 0 };

	glLinkProgram(ShaderProgram);
	glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &Success);
	if (Success == 0) {
		glGetProgramInfoLog(ShaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
		fprintf(stderr, "Error linking shader program: '%s'\n", ErrorLog);
		exit(1);
	}

	glValidateProgram(ShaderProgram);
	glGetProgramiv(ShaderProgram, GL_VALIDATE_STATUS, &Success);
	if (!Success) {
		glGetProgramInfoLog(ShaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
		fprintf(stderr, "Invalid shader program: '%s'\n", ErrorLog);
		exit(1);
	}

	glUseProgram(ShaderProgram);

	gMVPLocation = glGetUniformLocation(ShaderProgram, "gMVP");
}

void CreateVBuffer()
{
	Vertex v[4] = { Vertex(FFVector3f(-1.0f, -1.0f, 0.5773f),  FFVector2f(0.0f, 0.0f)),
					Vertex(FFVector3f(0.0f, -1.0f, -1.15475f), FFVector2f(0.5f, 0.0f)),
					Vertex(FFVector3f(1.0f, -1.0f, 0.5773f),   FFVector2f(1.0f, 0.0f)),
					Vertex(FFVector3f(0.0f, 1.0f, 0.0f),       FFVector2f(0.5f, 1.0f)) };

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(v), v, GL_STATIC_DRAW);
}

void CreateIdxBuffer()
{
	unsigned int Indices[] = {	0, 3, 1,
								1, 3, 2,
								2, 3, 0,
								0, 1, 2 };

	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow("OpenGL FrameWork");

	FFVector3f pos(0.0f, 1.0f, 1.0f);
	FFVector3f target(0.0f, -1.0f, -1.0f);
	FFVector3f up(1.0f, 0.0f, 0.0f);

	pCam = new FFCamera(WINDOW_WIDTH, WINDOW_HEIGHT, pos, target, up);

	glutDisplayFunc(&RenderScene);

	// Must be done after glut is initialized!
	GLenum res = glewInit();
	if (res != GLEW_OK) {
		fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
		return 1;
	}

	gPersProjInfo.fFOV = 90.0f;
	gPersProjInfo.fHeight = WINDOW_HEIGHT;
	gPersProjInfo.fWidth = WINDOW_WIDTH;
	gPersProjInfo.fZNear = 1.0f;
	gPersProjInfo.fZFar = 100.0f;

	CreateVBuffer();

	CreateIdxBuffer();

	CompileShader();

	glutMainLoop();
	return 0;
}