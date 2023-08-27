#include "OpenGLApi.h"
#include "Engine.h"
#include "Util/Logger.h"

#ifdef _WIN32
#include <Windows.h>
#include <GL/glew.h>
#else
#endif

void BTekEngine::OpenGLApi::DrawRectangle(Vector3<double> Start, Vector3<double> End) {
	float sx = (float)Start.X;
	float sy = (float)Start.Y;
	float ex = (float)End.X;
	float ey = (float)End.Y;
	
	glBegin(GL_QUADS);
	glVertex3f(sx, sy, 0);
	glVertex3f(sx, ey, 0);
	glVertex3f(ex, ey, 0);
	glVertex3f(ex, sy, 0);
	glEnd();
}

void BTekEngine::OpenGLApi::PrepareRender() {
	ClearBuffers();
}

void BTekEngine::OpenGLApi::SetViewport(double x, double y, double width, double height) {
	glViewport((GLint)x, (GLint)y, (GLsizei)width, (GLsizei)height);
}

void BTekEngine::OpenGLApi::SetClearColor(Color3<double> colour) {
	SetClearColor(colour.R, colour.G, colour.B);
}

void BTekEngine::OpenGLApi::SetClearColor(double r, double g, double b) {
	glClearColor((float)r, (float)g, (float)b, 1.0f);
}

void BTekEngine::OpenGLApi::ClearBuffers() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void BTekEngine::OpenGLApi::FinishRender() {
	
}

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
	"	FragColor = vec4(0.0f, 0.0f, 1.0f, 1.0f);\n"
"}\0";

unsigned int defaultVertexShader;
unsigned int defaultFragmentShader;
unsigned int defaultShaderProgram;

void BTekEngine::OpenGLApi::LoadCoreShaders() {
	defaultVertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(defaultVertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(defaultVertexShader);

	int success;
	char infoLog[512];
	glGetShaderiv(defaultVertexShader, GL_COMPILE_STATUS, &success);

	if (!success) {
		glGetShaderInfoLog(defaultVertexShader, 512, NULL, infoLog);
		BTekLogMessage(BTekEngine::LogLevel::CRITICAL, "Failed to load default vertex shader.");
		BTekLogMessage(BTekEngine::LogLevel::CRITICAL, infoLog);
	}

	defaultFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(defaultFragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(defaultFragmentShader);
	
	glGetShaderiv(defaultFragmentShader, GL_COMPILE_STATUS, &success);

	if (!success) {
		glGetShaderInfoLog(defaultFragmentShader, 512, NULL, infoLog);
		BTekLogMessage(BTekEngine::LogLevel::CRITICAL, "Failed to load default fragment shader.");
		BTekLogMessage(BTekEngine::LogLevel::CRITICAL, infoLog);
	}

	defaultShaderProgram = glCreateProgram();
	glAttachShader(defaultShaderProgram, defaultVertexShader);
	glAttachShader(defaultShaderProgram, defaultFragmentShader);
	glLinkProgram(defaultShaderProgram);

	glGetProgramiv(defaultShaderProgram, GL_LINK_STATUS, &success);

	if (!success) {
		glGetProgramInfoLog(defaultShaderProgram, 512, NULL, infoLog);
		BTekLogMessage(BTekEngine::LogLevel::CRITICAL, "Failed to link default shader program.");
		BTekLogMessage(BTekEngine::LogLevel::CRITICAL, infoLog);
	}

	glUseProgram(defaultShaderProgram);

	glDeleteShader(defaultVertexShader);
	glDeleteShader(defaultFragmentShader);

	BTekLogMessage(BTekEngine::LogLevel::INFO, "Finished loading shaders.");
}

int BTekEngine::OpenGLApi::AllocateMesh() {
	GLuint vao;
	glGenVertexArrays(1, &vao);
	return vao;
}

void BTekEngine::OpenGLApi::SetMeshAttribute(int meshId, MeshAttribDescriptor desc) {
	glBindVertexArray(meshId);
	glBindBuffer(GL_ARRAY_BUFFER, (GLuint)desc.BufferId);
	glVertexAttribPointer((GLuint)desc.Attribute, desc.Size, GL_FLOAT, GL_FALSE, desc.Stride * 4, 0);
	glEnableVertexAttribArray((GLuint)desc.Attribute);
}

void BTekEngine::OpenGLApi::DrawMesh(int meshId, int startIndex, int count) {
	glBindVertexArray(meshId);
	glDrawArrays(GL_TRIANGLES, startIndex, count);
}

void BTekEngine::OpenGLApi::DrawIndexedMesh(int meshId, int indexBufferId, int startIndex, int count) {
	glBindVertexArray(meshId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferId);
	glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, (void*)startIndex);
}

void BTekEngine::OpenGLApi::DeallocateMesh(int meshId) {
	GLuint glId = (GLuint)meshId;
	glDeleteVertexArrays(1, &glId);
}

int BTekEngine::OpenGLApi::CreateVertexBuffer(int sizeInBytes, void* data) {
	GLuint id = 0; glGenBuffers(1, &id);
	glBindBuffer(GL_ARRAY_BUFFER, id);
	glBufferData(GL_ARRAY_BUFFER, sizeInBytes, data, GL_STATIC_DRAW);
	return id;
}

void BTekEngine::OpenGLApi::DeleteVertexBuffer(int id) {
	GLuint glId = (GLuint)id;
	glDeleteBuffers(1, &glId);
}

int BTekEngine::OpenGLApi::CreateIndexBuffer(int sizeInBytes, void* data) {
	GLuint id = 0; glGenBuffers(1, &id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeInBytes, data, GL_STATIC_DRAW);
	return id;
}

// This is identical to deleting a vertex buffer, but for clarity purposes
// it has been re-implemented
void BTekEngine::OpenGLApi::DeleteIndexBuffer(int id) {
	GLuint glId = (GLuint)id;
	glDeleteBuffers(1, &glId);
}

void BTekEngine::OpenGLApi::CleanUp() {
	glUseProgram(0);
	glDeleteProgram(defaultShaderProgram);
}