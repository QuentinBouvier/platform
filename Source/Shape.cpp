#include "..\Headers\Shape.h"

//Creating an errorlog instance for private use in other classes
extern Errorlog *errorlog;


//------------------------------------------------------//
//														//
//			Class constructors and destructor.			//
//														//
//------------------------------------------------------//
Shape::Shape():
m_shader(),
m_vertices(nullptr),
m_colors(nullptr),
m_vboID(0),
m_vaoID(0),
m_sizeofVerticesb(0),
m_sizeofColorsb(0),
m_nbofVertices(0),
m_shapeType(NO_TYPE)
{}

Shape::Shape(std::string const vertexSource, std::string const fragmentSource, int nbofvertices, Shape_type type) :
m_shader(vertexSource, fragmentSource),
m_vertices(nullptr),
m_colors(nullptr),
m_vboID(0),
m_vaoID(0),
m_sizeofVerticesb(nbofvertices * sizeof(float)),
m_sizeofColorsb(nbofvertices * sizeof(float)),
m_nbofVertices(nbofvertices),
m_shapeType(type)
{
	m_shader.load();
	m_vertices = new float[nbofvertices];
	m_colors = new float[nbofvertices];
}

Shape::Shape(Shape const& source):
m_shader(source.m_shader),
m_vertices(nullptr),
m_colors(nullptr),
m_vboID(0),
m_vaoID(0),
m_sizeofVerticesb(source.m_sizeofVerticesb),
m_sizeofColorsb(source.m_sizeofColorsb),
m_nbofVertices(source.m_nbofVertices),
m_shapeType(source.m_shapeType)
{
	m_shader.load();
	m_vertices = new float[m_nbofVertices];
	m_colors = new float[m_nbofVertices];

	for (int i(0); i < m_nbofVertices; i++)
	{
		m_vertices[i] = source.m_vertices[i];
		m_colors[i] = source.m_colors[i];
	}
}


Shape::~Shape()
{
	delete m_vertices;
	delete m_colors;
	glDeleteBuffers(1, &m_vboID);
	glDeleteVertexArrays(1, &m_vaoID);
}


//------------------------------------------------------//
//														//
//					  Public Methods					//
//														//
//------------------------------------------------------//
void Shape::display(glm::mat4 projection, glm::mat4 modelview)
{
	//Gathering matrices for a faster uniform sending to shader
	glm::mat4 projectionModelview = projection * modelview;

	//Activating shader
	glUseProgram(m_shader.getProgramID());

		//VAO binding to use VRAM ressources
		glBindVertexArray(m_vaoID);

			//Sending the matrices to the shader
			m_shader.sendMat4("matrices", projectionModelview);

			//Display
			glDrawArrays(GL_TRIANGLES, 0, m_nbofVertices / 3);

		glBindVertexArray(0);

	glUseProgram(0);
}

void Shape::updateVBO(void *datas, int sizeb, int offset)
{

	//retrieves and bind the VBO
	glBindBuffer(GL_ARRAY_BUFFER, m_vboID);

		//Gets a ptr to the VRAM space to write there
		void *VBOptr = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);

			if (VBOptr == NULL)
			{
				std::cout << "Error getting VBO" << std::endl;
				glBindBuffer(GL_ARRAY_BUFFER, 0);

				return;
			}

			//Overwrite old datas with new ones
			memcpy((char*) VBOptr + offset, datas, sizeb);

		//Destroys the ptr to the VRAM
		glUnmapBuffer(GL_ARRAY_BUFFER);
		VBOptr = 0;
	
	//Unbind VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}