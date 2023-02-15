#ifndef _MARCHCUBES_H_
#define _MARCHCUBES_H_
#include "VBGO.h"

//=================================================================
//create a VBGO for the isosurface of a given function using the marching cubes
//it was a bit of hack for 3D printing project
//=================================================================


class VBMarchCubes : public VBGO
{
public:
	VBMarchCubes() {};
	virtual ~VBMarchCubes() {};

	//initialise the Veretx and Index buffers for this function
	void init(Vector3 _size, float _isolevel, Vector3 _scale, Vector3 _origin, ID3D11Device* _GD);
	void init(Vector3 _min,Vector3 _max,Vector3 _size, float _isoLevel, ID3D11Device* _GD); //2

	void Tick(GameData* _GD) override;

protected:
	float function(Vector3 _pos);
};

#endif
