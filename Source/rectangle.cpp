#include "..\Headers\rectangle.h"

//Creating an errorlog instance for private use in other classes
extern Errorlog *errorlog;

//------------------------------------------------------//
//														//
//			Class constructors and destructor.			//
//														//
//------------------------------------------------------//

Rectangle::Rectangle() :
Shape(),
m_size(0.0, 0.0, 0.0)
{
	//default is 0 sized white rectangle
	initVertices(0, 0);
	initColorsArray(1.0, 1.0, 1.0);
}

Rectangle::Rectangle(float width, float height, std::string const vertexShader, std::string const fragmentShader) :
Shape(vertexShader, fragmentShader, 108, BOX),
m_size(width, height, 0.0)
{
	initVertices(m_size.x, m_size.y);
	//Default rectangle color is white
	initColorsArray(1.0, 1.0, 1.0);
}

Rectangle::Rectangle(Rectangle const& source) :
Shape(source),
m_size(source.m_size.x, source.m_size.y, 0.0)
{}

Rectangle::Rectangle(float width, float height, std::string const vertexShader, std::string const fragmentShader, float R, float G, float B):
Shape(vertexShader, fragmentShader, 108, BOX),
m_size(width, height, 0.0)
{
	initVertices(m_size.x, m_size.y);
	initColorsArray(R, G, B);
}

Rectangle::~Rectangle()
{
}

//------------------------------------------------------//
//														//
//					  Public Methods					//
//														//
//------------------------------------------------------//

void Rectangle::load()
{

	//Destroys an old buffer object if it exists on that ID
	if (glIsBuffer(m_vboID) == GL_TRUE)
		glDeleteBuffers(1, &m_vboID);

	//Creating id and VBO
	glGenBuffers(1, &m_vboID);
	
	//binds the VBO to send data arrays in the VRAM
	glBindBuffer(GL_ARRAY_BUFFER, m_vboID);

		//Defines the size of the datas to be uploaded
		glBufferData(GL_ARRAY_BUFFER, m_sizeofVerticesb + m_sizeofColorsb, 0, GL_STATIC_DRAW);
		//Uploads datas
		glBufferSubData(GL_ARRAY_BUFFER, 0, m_sizeofVerticesb, m_vertices);
		glBufferSubData(GL_ARRAY_BUFFER, m_sizeofVerticesb, m_sizeofColorsb, m_colors);

	//Unbinds the VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//Checks if there's no VAO with this ID to destroy it
	if (glIsVertexArray(m_vaoID) == GL_TRUE)
		glDeleteVertexArrays(1, &m_vaoID);

	//Creates VAO ID
	glGenVertexArrays(1, &m_vaoID);

	//Binds the VAO to send drawing routines into the VRAM
	glBindVertexArray(m_vaoID);

		//Binds the VBO to query the uploaded datas
		glBindBuffer(GL_ARRAY_BUFFER, m_vboID);

			//uploads vertices and color arrays
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
			glEnableVertexAttribArray(0);

			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(m_sizeofVerticesb));
			glEnableVertexAttribArray(1);

		//unbind VBO
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	//Unbind VAO
	glBindVertexArray(0);
}

Size Rectangle::getSize() const
{
	return m_size;
}

//------------------------------------------------------//
//														//
//					  Private Methods					//
//														//
//------------------------------------------------------//

void Rectangle::initVertices(float width, float height)
{
	float x = width / 2;
	float y = height / 2;

	//		
	//	  G __ C	Face 1 : ABC / ADC
	//	  /  /|		Face 2 : EAD / EFD
	//	F/__/ |		Face 3 : FDC / FGC
	//	 |  |D|		Face 4 : EHG / EFG
	//	 |  | |		Face 5 : HBC / HGC
	//	 |  | |		Face 6 : ABH / AEH
	// H |  | |
	//	 |  | /B 	ABCD -> y =  0.0
	//	 |__|/		EFGH -> y = -0.0
	//	E   A

	float verticesTemp[] =
		{-x, -y, 0.0,	x, -y, 0.0,		x, y, 0.0,
		 -x, -y, 0.0,	-x, y, 0.0,		x, y, 0.0,		//Face 1 : ABC / ADC

		 -x, -y, -0.0,	-x, -y, 0.0,	-x, y, 0.0,
		 -x, -y, -0.0,	-x, y, -0.0,	-x, y, 0.0,		//Face 2 : EAD / EFD

		 -x, y, -0.0,	-x, y, 0.0,		x, y, 0.0,
		 -x, y, -0.0,	x, y, -0.0,		x, y, 0.0,		//Face 3 : FDC / FGC

		 -x, -y, -0.0,	x, -y, -0.0,	x, y, -0.0,
		 -x, -y, -0.0,	-x, y, -0.0,	x, y, -0.0,		//Face 4 : EHG / EFG

		 x, -y, -0.0,	x, -y, 0.0,		x, y, 0.0,
		 x, -y, -0.0,	x, y, -0.0,		x, y, 0.0,		//Face 5 : HBC / HGC

		 -x, -y, 0.0,	x, -y, 0.0,		x, -y, -0.0,
		 -x, -y, 0.0,	-x, -y, -0.0,	x, -y, -0.0};	//Face 6 : ABH / AEH

	for (int i(0); i < m_nbofVertices; i++)
		m_vertices[i] = verticesTemp[i];

}

void Rectangle::initColorsArray(float R, float G, float B)
{
	float colorsTemp[] =
		{R, G, B,	R, G, B,	R, G, B,
		R, G, B,	R, G, B,	R, G, B,

		R, G, B,	R, G, B,	R, G, B,
		R, G, B,	R, G, B,	R, G, B,

		R, G, B,	R, G, B,	R, G, B,
		R, G, B,	R, G, B,	R, G, B,

		R, G, B,	R, G, B,	R, G, B,
		R, G, B,	R, G, B,	R, G, B,

		R, G, B,	R, G, B,	R, G, B,
		R, G, B,	R, G, B,	R, G, B,

		R, G, B,	R, G, B,	R, G, B,
		R, G, B,	R, G, B,	R, G, B};

	for (int i(0); i < m_nbofVertices; i++)
		m_colors[i] = colorsTemp[i];

}