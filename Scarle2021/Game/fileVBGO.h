#ifndef _FILE_VB_GO_H_
#define _FILE_VB_GO_H_
#include "VBGO.h"

//=================================================================
//create a VBGO using data from a file 
//format is a sort-of a simplified version of the obj format
//=================================================================

class FileVBGO : public VBGO
{
public:
	FileVBGO(std::string _fileName, ID3D11Device* _GD);
	virtual ~FileVBGO();

private:

	//data supplied by file tex coordinates or colours
	bool m_texCoords;
	bool m_colour;
};

#endif