#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Shape.h"

class Rectangle :
	public Shape
{
public:

	//------------------------------------------------------//
	//														//
	//			Class constructors and destructor.			//
	//														//
	//------------------------------------------------------//
	Rectangle();
	
	//Simple constructor
	Rectangle(float width, float height, std::string const vertexShader, std::string const fragmentShader);
	
	//Simple constructor with color.
	Rectangle(float width, float height, std::string const vertexShader, std::string const fragmentShader, float R, float G, float B);

	//Copy constructor
	Rectangle(Rectangle const& source);
	
	virtual ~Rectangle();

	//------------------------------------------------------//
	//														//
	//					  Public Methods					//
	//														//
	//------------------------------------------------------//

	//(Shape pure virtual) loads data arrays and properties into the VRAM
	virtual void load();

	virtual Size getSize() const;

private:

	//------------------------------------------------------//
	//														//
	//					  Private Methods					//
	//														//
	//------------------------------------------------------//

	//Private: Method to fill the vertices array
	void initVertices(float width, float height);

	//Private: Method to fill the colors array
	void initColorsArray(float R, float G, float B);


	//------------------------------------------------------//
	//														//
	//						 Members						//
	//														//
	//------------------------------------------------------//

	Size m_size;

};

#endif /* RECTANGLE_H */