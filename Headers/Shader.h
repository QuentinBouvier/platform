#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <fstream>
#include <string>

#include "Global.h"

class Shader
{

public:

	//------------------------------------------------------//
	//														//
	//			Class constructors and destructor.			//
	//														//
	//------------------------------------------------------//
	Shader();

	//New Shader from shader file paths
	Shader(std::string vertexSource, std::string fragmentSource);

	//Copy constructor
	Shader(Shader const& shaderSourceCopy);

	~Shader();

	//------------------------------------------------------//
	//														//
	//					  Public Methods					//
	//														//
	//------------------------------------------------------//

	//Compile shaders and link them into a program. Gives ID to
	//each.
	bool load();

	//Compile a shader.
	bool compile(GLuint &shader, GLenum type, std::string const &sourceFile);

	//Send a mat4 as a uniform var to the shader.
	void sendMat4(std::string name, glm::mat4 matrix) const;

	//------------------------------------------------------//
	//														//
	//					Setters / Getters					//
	//														//
	//------------------------------------------------------//
	GLuint getProgramID() const;


private:

	GLuint m_vertexID;
	GLuint m_fragmentID;
	GLuint m_programID;

	std::string m_vertexSource;
	std::string m_fragmentSource;

};

#endif /* SHADER_H */