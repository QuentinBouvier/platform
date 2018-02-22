#include "..\Headers\Errorlog.h"

//------------------------------------------------------//
//														//
//				Constructor / Destructor				//
//														//
//------------------------------------------------------//
Errorlog::Errorlog():
m_fileName(""),
m_stream(0),
m_fileStream(0)
{
}

Errorlog::~Errorlog()
{
	//clears dynamic ptrs if it hasn't been done yet
	if (m_fileStream != NULL)
		delete m_fileStream;
}

//------------------------------------------------------//
//														//
//					Setters / Getters					//
//														//
//------------------------------------------------------//

void Errorlog::setStream(std::ostream *stream)
{
	//clears file writing stream as it's only for program internal streams
	m_fileName = "";
	if (m_fileStream != NULL)
	{
		delete m_fileStream;
		m_fileStream = 0;
	}
	m_stream = stream;
}

void Errorlog::setStream(std::string fileName)
{
	m_fileName = fileName;
	loadFileStream();
}



//------------------------------------------------------//
//														//
//					Private Methods						//
//														//
//------------------------------------------------------//

void Errorlog::loadFileStream()
{
	//sets an output write in file stream
	m_fileStream = new std::ofstream(m_fileName);
	if (*m_fileStream)
	{
		m_stream = m_fileStream;
	}
	//set cout as default output stream if the filestream is broken
	else
	{
		m_stream = &std::cout;
		delete m_fileStream;
		m_fileStream = 0;
		logError("Error: Unable to load log file. Switch to default output stream");
	}
}