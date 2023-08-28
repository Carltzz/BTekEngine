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
"layout (location = 2) in vec2 aTexCoord;\n"
"out vec2 TexCoord;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"   TexCoord = aTexCoord;\n"
"}\0";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"in vec2 TexCoord;\n"
"uniform vec4 customColor;\n"
"uniform sampler2D ourTexture;\n"
"void main()\n"
"{\n"
	"	//FragColor = vec4(TexCoord.x, TexCoord.y, 0.0f, 1.0f);\n"
	"	FragColor = texture(ourTexture, TexCoord);\n"
"}\0";

void BTekEngine::OpenGLApi::LoadCoreShaders() {
	shader = new Shader("DefaultShader");
	shader->SetVertexStage(vertexShaderSource);
	shader->SetPixelStage(fragmentShaderSource);
	bool success = shader->Compile();

	shader->Activate();
	int id = shader->AddShaderVariable(ShaderPrimitiveType::VEC4F, "customColor");
	Vector4<float> colour = { 1.0f, 1.0f, 0.0f, 1.0f };
	shader->UpdateShaderVariable(id, &colour, 0);

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
	glVertexAttribPointer((GLuint)desc.Attribute, desc.Components, GL_FLOAT, GL_FALSE, desc.Stride, (void*)(desc.Offset));
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
		BTekLogMessage(BTekEngine::LogLevel::ERR, "Failed to load shader stage:", src);
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

int BTekEngine::OpenGLApi::DefineShaderVariable(
	int shaderId,
	ShaderPrimitiveType type,
	const std::string& name,
	int size
) {
	GLuint location;
	if (type == ShaderPrimitiveType::STRUCT) {
		glGenBuffers(1, &location);
		glBindBuffer(GL_UNIFORM_BUFFER, location);
		glBufferData(GL_UNIFORM_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
		int uniformIndex = glGetUniformBlockIndex(shaderId, name.c_str());
		int bindingIndex;
		glGetActiveUniformBlockiv(shaderId, uniformIndex, GL_UNIFORM_BLOCK_BINDING, &bindingIndex);
		glUniformBlockBinding(shaderId, uniformIndex, bindingIndex);
		glBindBufferBase(GL_UNIFORM_BUFFER, bindingIndex, location);
	} else {
		location = glGetUniformLocation(shaderId, name.c_str());
	}
	return location;
}

void BTekEngine::OpenGLApi::UpdateShaderVariable(
	int shaderId,
	ShaderPrimitiveType type,
	int location,
	void* data,
	int dstOffset,
	int size) {
	switch (type) {
		case ShaderPrimitiveType::FLOAT: glUniform1f(location, *static_cast<float*>(data));
		case ShaderPrimitiveType::VEC2F: {
			float* vec2 = static_cast<float*>(data);
			glUniform2f(location, vec2[0], vec2[1]);
		}
		case ShaderPrimitiveType::VEC3F: {
			float* vec3 = static_cast<float*>(data);
			glUniform3f(location, vec3[0], vec3[1], vec3[2]);
		}
		case ShaderPrimitiveType::VEC4F: {
			float* vec4 = static_cast<float*>(data);
			glUniform4f(location, vec4[0], vec4[1], vec4[2], vec4[3]);
		}

		case ShaderPrimitiveType::INT: glUniform1i(location, *static_cast<int*>(data));
		case ShaderPrimitiveType::VEC2I: {
			int* vec2 = static_cast<int*>(data);
			glUniform2i(location, vec2[0], vec2[1]);
		}
		case ShaderPrimitiveType::VEC3I: {
			int* vec3 = static_cast<int*>(data);
			glUniform3i(location, vec3[0], vec3[1], vec3[2]);
		}
		case ShaderPrimitiveType::VEC4I: {
			int* vec4 = static_cast<int*>(data);
			glUniform4i(location, vec4[0], vec4[1], vec4[2], vec4[3]);
		}

		case ShaderPrimitiveType::UINT: glUniform1ui(location, *static_cast<int*>(data));
		case ShaderPrimitiveType::VEC2UI: {
			int* vec2 = static_cast<int*>(data);
			glUniform2i(location, vec2[0], vec2[1]);
		}
		case ShaderPrimitiveType::VEC3UI: {
			int* vec3 = static_cast<int*>(data);
			glUniform3i(location, vec3[0], vec3[1], vec3[2]);
		}
		case ShaderPrimitiveType::VEC4UI: {
			int* vec4 = static_cast<int*>(data);
			glUniform4i(location, vec4[0], vec4[1], vec4[2], vec4[3]);
		}
	}

	if (type == ShaderPrimitiveType::STRUCT) {
		glBindBuffer(GL_UNIFORM_BUFFER, location);
		glBufferSubData(GL_UNIFORM_BUFFER, dstOffset, size, data);
	} else {
		ShaderPrimitiveType basePrimitive = type > ShaderPrimitiveType::MAT4X4F ? 
			(ShaderPrimitiveType)((int)type - (int)ShaderPrimitiveType::PFLOAT) : 
			type;
		int count = size / GfxGetShaderPrimitiveSize(basePrimitive);
		switch (type) {
		case ShaderPrimitiveType::MAT2X2F: glUniformMatrix2fv(location, count, GL_FALSE, static_cast<float*>(data));
		case ShaderPrimitiveType::MAT2X3F: glUniformMatrix2x3fv(location, count, GL_FALSE, static_cast<float*>(data));
		case ShaderPrimitiveType::MAT2X4F: glUniformMatrix2x4fv(location, count, GL_FALSE, static_cast<float*>(data));
		case ShaderPrimitiveType::MAT3X2F: glUniformMatrix3x2fv(location, count, GL_FALSE, static_cast<float*>(data));
		case ShaderPrimitiveType::MAT3X3F: glUniformMatrix3fv(location, count, GL_FALSE, static_cast<float*>(data));
		case ShaderPrimitiveType::MAT3X4F: glUniformMatrix3x4fv(location, count, GL_FALSE, static_cast<float*>(data));
		case ShaderPrimitiveType::MAT4X2F: glUniformMatrix4x2fv(location, count, GL_FALSE, static_cast<float*>(data));
		case ShaderPrimitiveType::MAT4X3F: glUniformMatrix4x3fv(location, count, GL_FALSE, static_cast<float*>(data));
		case ShaderPrimitiveType::MAT4X4F: glUniformMatrix4fv(location, count, GL_FALSE, static_cast<float*>(data));
		case ShaderPrimitiveType::PFLOAT: glUniform1fv(location, count, static_cast<float*>(data)); return;
		case ShaderPrimitiveType::PVEC2F: glUniform2fv(location, count, static_cast<float*>(data)); return;
		case ShaderPrimitiveType::PVEC3F: glUniform3fv(location, count, static_cast<float*>(data)); return;
		case ShaderPrimitiveType::PVEC4F: glUniform4fv(location, count, static_cast<float*>(data)); return;
		case ShaderPrimitiveType::PINT: glUniform1iv(location, count, static_cast<int*>(data)); return;
		case ShaderPrimitiveType::PVEC2I: glUniform2iv(location, count, static_cast<int*>(data)); return;
		case ShaderPrimitiveType::PVEC3I: glUniform3iv(location, count, static_cast<int*>(data)); return;
		case ShaderPrimitiveType::PVEC4I: glUniform4iv(location, count, static_cast<int*>(data)); return;
		case ShaderPrimitiveType::PUINT: glUniform1uiv(location, count, static_cast<unsigned int*>(data)); return;
		case ShaderPrimitiveType::PVEC2UI: glUniform2uiv(location, count, static_cast<unsigned int*>(data)); return;
		case ShaderPrimitiveType::PVEC3UI: glUniform3uiv(location, count, static_cast<unsigned int*>(data)); return;
		case ShaderPrimitiveType::PVEC4UI: glUniform4uiv(location, count, static_cast<unsigned int*>(data)); return;
		}
	}
}

void BTekEngine::OpenGLApi::DeleteShaderVariable(
	ShaderPrimitiveType type,
	int id
) {
	GLuint glId = id;
	if (type == ShaderPrimitiveType::STRUCT) {
		glDeleteBuffers(1, &glId);
	}
}

int BTekEngine::OpenGLApi::CreateTexture2D(int width, int height) {
	GLuint id;
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	return id;
}

void BTekEngine::OpenGLApi::SetTexture2DPixels(int textureId, int sx, int sy, int width, int height, void* data) {
	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexSubImage2D(GL_TEXTURE_2D, 0, sx, sy, width, height, GL_RGBA, GL_UNSIGNED_BYTE, data);
}

void BTekEngine::OpenGLApi::ActivateTexture2D(int textureId) {
	glBindTexture(GL_TEXTURE_2D, textureId);
}

void BTekEngine::OpenGLApi::DeleteTexture2D(int textureId) {
	GLuint id;
	glDeleteTextures(1, &id);
}

void BTekEngine::OpenGLApi::CleanUp() {
	glUseProgram(0);

}