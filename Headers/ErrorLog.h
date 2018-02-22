//------------------------------------------------------//
//	this class provides a simple error log that can be	//
//	called to output the error strings throught			//
//	whatever stream you choose.							//
//	prefer uses of "cout" or "ofstream" for the moment	//
//														//
//	Errorlog will be used in all the program in order	//
//	to log every error at every moment, declared with a	//
//	singleton pattern									//
//														//
//	Due to Simpleton Pattern, the only acess to the		//
//	class is through the public method setStream().		//
//------------------------------------------------------//

#ifndef Errorlog_H
#define Errorlog_H

#include <iostream>
#include <string>
#include <fstream>

#include "Singleton.h"

class Errorlog : public Singleton<Errorlog>
{
	friend class Singleton < Errorlog > ;

private:

	//------------------------------------------------------//
	//														//
	//			Class constructor and destructor.			//
	//														//
	//------------------------------------------------------//

	Errorlog();
	~Errorlog();

public:

	//------------------------------------------------------//
	//														//
	//					Public Methods						//
	//														//
	//------------------------------------------------------//

	//------------------------------------------------------//
	//	Template overload for the logging output in			//
	//	m_stream. Variadic one recursively call itself 		//
	//	while there's still more than one argument, then 	//
	//	call the 1 arg in order to terminate the output 	//
	//	string.												//
	//------------------------------------------------------//
	template<typename T>
		void logError(T const& error) const;

	template<typename T, typename... Tx> 
		void logError(const T& error, const Tx&... errors) const;

	//------------------------------------------------------//
	//														//
	//					Setters / Getters					//
	//														//
	//------------------------------------------------------//

	//------------------------------------------------------//
	//	Simple setter for m_stream,							//
	//	1. directly sets a stream reference as the main		//
	//		output											//
	//	2. takes a file path & name to set it as a stream	//
	//		output											//
	//------------------------------------------------------//
	void setStream(std::ostream *stream);
	void setStream(std::string fileName);

private:
	
	//------------------------------------------------------//
	//														//
	//					 private Methods					//
	//														//
	//------------------------------------------------------//

	//------------------------------------------------------//
	//	sets a fileStream pointer to send into m_stream.	//
	//	If the file failed to open,	m_stream will be set as //
	//	std::cout as a default value						//
	//------------------------------------------------------//
	void loadFileStream();


	//------------------------------------------------------//
	//	output stream as a pointer is the only solution to	//
	//	grant a hotswap through a setter.					//
	//------------------------------------------------------//
	std::ostream *m_stream;
	std::ofstream *m_fileStream;
	std::string m_fileName;

};

template<typename T>
	void Errorlog::logError(T const& error) const
	{
		//Send error to the output stream
		*m_stream << error << std::endl;
	}

template<typename T, typename... Tx>
	void Errorlog::logError(const T& error, const Tx&... errors) const
	{
		//send error to the output stream
		*m_stream << error;
		//recursive call till there's more than one arg
		//the call 1arg overload
		logError(errors...);
	};



#endif /* Errorlog_H */