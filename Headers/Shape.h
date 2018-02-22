#ifndef SHAPE_H
#define SHAPE_H

//------------------------------------------------------//
//	Shape is a pure virtual class that gives the basis	//
//	of a 3D shape display in the window.				//
//	Load method is pure virtual, display is universal.	//
//	Contains patterns for vertices, colors and texture	//
//	coord arrays to initialize into child classes		//
//------------------------------------------------------//

#include <cstring>

#include <SDL.h>
#include <GL/glew.h>

#include <glm/glm.hpp>

#include "Shader.h"
#include "Global.h"

class Shape
{
public:
	
	//------------------------------------------------------//
	//														//
	//			Class constructors and destructor.			//
	//														//
	//------------------------------------------------------//
	Shape();
	Shape(std::string const vertexSource, std::string const fragmentSource, int nbofvertices, Shape_type type);
	Shape(Shape const& source);
	virtual ~Shape();

	//------------------------------------------------------//
	//														//
	//					  Public Methods					//
	//														//
	//------------------------------------------------------//

	//Displays the shape
	void display(glm::mat4 projection, glm::mat4 modelview);

	//(Pure virtual) Loads data arrays and properties into the GPU
	virtual void load() = 0;

	//Update data arrays into the GPU
	//*data: pointer on the datas to upload
	//sizeb: size of the data
	//offset: position of the data in GPU the memory
	void updateVBO(void *data, int sizeb, int offset);


	virtual Size getSize() const = 0;

protected:

	Shader m_shader;

	float *m_vertices;
	float *m_colors;

	GLuint m_vboID;
	GLuint m_vaoID;

	int m_sizeofVerticesb;
	int m_sizeofColorsb;
	int m_nbofVertices;

	Shape_type m_shapeType;
};

#ifndef BUFFER_OFFSET

#define BUFFER_OFFSET(offset) ((char*)NULL + (offset)) //memory offset calculation macro

#endif /* BUFFER_OFFSET */

#endif /* SHAPE_H */