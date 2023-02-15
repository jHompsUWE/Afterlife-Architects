#ifndef _VBSNAIL_H_
#define _VBSNAIL_H_

//=================================================================
//create a snail shell from a base line shape read in from a txt file
//=================================================================

#include "VBGO.h"
#include <string>

struct GameData;

class VBSnail : public VBGO
{
public:
	VBSnail( ID3D11Device* _GD, std::string _filename, int _sections, float _scale, float _rot, float _step, Color _col1, Color _col2 );
	virtual ~VBSnail(){};

	virtual void Tick(GameData* _GD) override;

protected:
};

#endif