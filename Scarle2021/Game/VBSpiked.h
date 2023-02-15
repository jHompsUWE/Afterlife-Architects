#ifndef _SPIKED_VB_H_
#define _SPIKED_VB_H_
#include "VBCube.h"

//=================================================================
//create a cube with a spike as a VBGO
//=================================================================

class VBSpike : public VBCube
{
public:
	VBSpike(){};

protected:
	virtual void Transform(WORD* _indices = nullptr) override
	{
		_indices;
		for (unsigned int i = 0; i<m_numPrims * 3; i++)
		{
			Vector3 vertPos = m_vertices[i].Pos;

			Matrix transform = Matrix::CreateTranslation(0.0f, 6.0f - sqrtf(vertPos.x*vertPos.x + vertPos.z*vertPos.z), 0.0f);

			Vector3 newPos = Vector3::Transform(vertPos, transform);
			
			m_vertices[i].Pos = newPos;
		}
	}

};



#endif