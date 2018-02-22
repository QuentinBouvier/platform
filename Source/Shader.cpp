#include "../Headers/Shader.h"

//Creating an errorlog instance for private use in other classes
extern Errorlog *errorlog;


//------------------------------------------------------//
//														//
//			Class constructors and destructor.			//
//														//
//------------------------------------------------------//

Shader::Shader():
m_vertexID(0),
m_fragmentID(0),
m_programID(0),
m_vertexSource(),
m_fragmentSource()
{}


Shader::Shader(std::string vertexSource, std::string fragmentSource):
m_vertexID(0),
m_fragmentID(0),
m_programID(0),
m_vertexSource(vertexSource),
m_fragmentSource(fragmentSource)
{}

Shader::Shader(Shader const& shaderSourceCopy)
{
	m_fragmentSource = shaderSourceCopy.m_fragmentSource;
	m_vertexSource = shaderSourceCopy.m_vertexSource;

	load();
}

Shader::~Shader()
{
	glDeleteShader(m_vertexID);
	glDeleteShader(m_fragmentID);
	glDeleteProgram(m_programID);
}

//------------------------------------------------------//
//														//
//					  Public Methods					//
//														//
//------------------------------------------------------//

bool Shader::load()
{

	//Deleting an old shader on that ID

	if (glIsShader(m_vertexID) == GL_TRUE)
		glDeleteShader(m_vertexID);

	if (glIsShader(m_fragmentID) == GL_TRUE)
		glDeleteShader(m_fragmentID);

	if (glIsProgram(m_programID) == GL_TRUE)
		glDeleteProgram(m_programID);

	//Vertex Shader compiling
	if (!compile(m_vertexID, GL_VERTEX_SHADER, m_vertexSource))
		return false;
	//Fragment Shader compiling
	if (!compile(m_fragmentID, GL_FRAGMENT_SHADER, m_fragmentSource))
		return false;

	//creating ID for program
	m_programID = glCreateProgram();

	//Attaching shaders to program
	glAttachShader(m_programID, m_vertexID);
	glAttachShader(m_programID, m_fragmentID);

	//Attrib shader input locations: 0 vertex coord, 1 colors, 2 texture coord
	glBindAttribLocation(m_programID, 0, "in_Vertex");
	glBindAttribLocation(m_programID, 1, "in_Color");
	glBindAttribLocation(m_programID, 2, "in_TexCoord0");

	//Link shaders into program
	glLinkProgram(m_programID);

	//Link troubleshouting

	GLint linkError(0);
	glGetProgramiv(m_programID, GL_LINK_STATUS, &linkError);

	if (linkError != GL_TRUE)
	{

		//Query error code size
		GLint errorSize(0);
		glGetProgramiv(m_programID, GL_INFO_LOG_LENGTH, &errorSize);

		//Error logging into C string
		char *error = new char[errorSize + 1];

		glGetShaderInfoLog(m_programID, errorSize, &errorSize, error);
		error[errorSize] = '\0';

		//Error display
		errorlog->logError("Program failed to link ", 
						  m_vertexSource, 
						  " and ", 
						  m_fragmentSource, 
						  " with message :");
		errorlog->logError(error);

		//Memory release
		delete[] error;
		glDeleteProgram(m_programID);


		return false;
	}
	else
		return true;
}

bool Shader::compile(GLuint &shader, GLenum type, std::string const &sourceFile)
{

	//Create shader ID
	shader = glCreateShader(type);

	//Troubleshout shader creation problem
	if (shader == 0)
	{
		errorlog->logError("Error: \"", type, "\" is not a valid Shader type");
		return false;
	}

	//Reading stream for shader source code
	std::ifstream file(sourceFile.c_str());

	//Troubleshouting file opening error
	if (!file)
	{
		errorlog->logError("Error: Unable to find", sourceFile);
		glDeleteShader(shader);

		return false;
	}

	//Reading recipients for shader source code
	std::string line;
	std::string sourceCode;

	while (getline(file, line))
		sourceCode += line + '\n';

	file.close();

	//Convert string into C char* string for copilation
	const GLchar* sourceCodeString = sourceCode.c_str();

	glShaderSource(shader, 1, &sourceCodeString, 0);

	//Compilation
	glCompileShader(shader);

	//Compilation error troubleshouting
	GLint compilationError(0);

	glGetShaderiv(shader, GL_COMPILE_STATUS, &compilationError); //Compilation status

	if (compilationError = !GL_TRUE)
	{
		//Query error string size
		GLint errorSize(0);
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &errorSize);

		char *error = new char[errorSize + 1];

		glGetShaderInfoLog(shader, errorSize, &errorSize, error);
		error[errorSize] = '\0';

		//Error display
		errorlog->logError(sourceFile.c_str(), "Failed to compile with error : ");
		errorlog->logError(error);

		//Memory cleaning
		delete[] error;
		glDeleteShader(shader);

		return false;
	}
	else
		return true;
}

void Shader::sendMat4(std::string name, glm::mat4 matrix) const
{
	int location = glGetUniformLocation(getProgramID(), name.c_str());

	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

//------------------------------------------------------//
//														//
//					Setters / Getters					//
//														//
//------------------------------------------------------//

GLuint Shader::getProgramID() const
{
	return m_programID;
}