#include"shaderClass.h"

std::string get_file_contents(const char* filename)
{
	std::ifstream in(filename, std::ios::binary);
	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	throw(errno);
}

Shader::Shader(const char* vertexFile, const char* fragmentFile)
{
	std::string vertexCode = get_file_contents(vertexFile);
	std::string fragmentCode = get_file_contents(fragmentFile);

	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);		//create vertex shader and assign vertexShader as reference
	glShaderSource(vertexShader, 1, &vertexSource, NULL);		//attach vertex shader source to vertex shader object
	glCompileShader(vertexShader);		//compile vertex shader into machine code

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);		//create fragment shader and assign fragmentShader as reference
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);		//attach fragment shader source to fragment shader object
	glCompileShader(fragmentShader);	//compile fragment shader into machine code

	ID = glCreateProgram();	//create shader program object and assign shaderProgram as reference
	glAttachShader(ID, vertexShader);	//attach shaders to shader program
	glAttachShader(ID, fragmentShader);	//^
	glLinkProgram(ID);	//link all shaders together in shader program

	glDeleteShader(vertexShader);	//delete shader objects as they have already been linked
	glDeleteShader(fragmentShader);	//^
}

void Shader::Activate()
{
	glUseProgram(ID);
}

void Shader::Delete()
{
	glDeleteProgram(ID);
}