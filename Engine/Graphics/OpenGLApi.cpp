#include "OpenGLApi.h"
#include "Engine.h"
#include "Util/Logger.h"
#include "Shader.h"
#include <map>

#ifdef _WIN32
#include <Windows.h>
#include <GL/glew.h>
#else
#endif

BTekEngine::Shader* shader;

const std::map<BTekEngine::ShaderType, GLenum> shader_enums = {
	{ BTekEngine::ShaderType::Vertex, GL_VERTEX_SHADER },
	{ BTekEngine::ShaderType::Hull, GL_TESS_CONTROL_SHADER },
	{ BTekEngine::ShaderType::Domain, GL_TESS_EVALUATION_SHADER },
	{ BTekEngine::ShaderType::Geometry, GL_GEOMETRY_SHADER },
	{ BTekEngine::ShaderType::Pixel, GL_FRAGMENT_SHADER },
	{ BTekEngine::ShaderType::Compute, GL_COMPUTE_SHADER }
};

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

void BTekEngine::OpenGLApi::LoadCoreShaders() {
	shader = new Shader("DefaultShader");
	shader->SetVertexStage(vertexShaderSource);
	shader->SetPixelStage(fragmentShaderSource);
	bool success = shader->Compile();
	shader->Activate();

	if (success) BTekLogMessage(BTekEngine::LogLevel::INFO, "Finished loading shaders.");
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

int BTekEngine::OpenGLApi::CreateShader() {
	return glCreateProgram();
}

int BTekEngine::OpenGLApi::CreateShaderStage(ShaderType shaderType) {
	return glCreateShader(shader_enums.at(shaderType));
}

bool BTekEngine::OpenGLApi::CompileShaderStage(int id, const char* src) {
	glShaderSource(id, 1, &src, NULL);
	glCompileShader(id);

	char infoLog[512];
	int success;

	glGetShaderiv(id, GL_COMPILE_STATUS, &success);

	if (!success) {
		glGetShaderInfoLog(id, 512, NULL, infoLog);
		BTekLogMessage(BTekEngine::LogLevel::ERR, "Failed to load fragment shader id:", id);
		BTekLogMessage(BTekEngine::LogLevel::ERR, infoLog);
	}

	return success;
}

void compileShader_attachShader(int programId, int shaderId) {
	if (shaderId != -1) glAttachShader(programId, shaderId);
}

bool BTekEngine::OpenGLApi::CompileShader(int shaderId, ShaderDescriptor desc) {
	compileShader_attachShader(shaderId, desc.VertexShader);
	compileShader_attachShader(shaderId, desc.HullShader);
	compileShader_attachShader(shaderId, desc.DomainShader);
	compileShader_attachShader(shaderId, desc.GeometryShader);
	compileShader_attachShader(shaderId, desc.PixelShader);
	compileShader_attachShader(shaderId, desc.ComputeShader);

	glLinkProgram(shaderId);

	char infoLog[512];
	int success;
	glGetProgramiv(shaderId, GL_LINK_STATUS, &success);

	if (!success) {
		glGetProgramInfoLog(shaderId, 512, NULL, infoLog);
		BTekLogMessage(BTekEngine::LogLevel::ERR, "Failed to link default shader program: ", shaderId);
		BTekLogMessage(BTekEngine::LogLevel::ERR, infoLog);
	}

	return success;
}

void BTekEngine::OpenGLApi::ActivateShader(int id) {
	glUseProgram(id);
}

void BTekEngine::OpenGLApi::DeleteShaderStage(int id) {
	glDeleteShader(id);
}

void BTekEngine::OpenGLApi::DeleteShader(int id) {
	glDeleteShader(id);
}

void BTekEngine::OpenGLApi::CleanUp() {
	glUseProgram(0);
}