#ifndef _SPIRAL_H_
#define _SPIRAL_H_
#include "VBCube.h"
#include <fstream>
//=================================================================
//create a twisted cube VBGO
//=================================================================

class VBSpiral : public VBCube
{
public:
	VBSpiral(){};
protected:
	virtual void Transform(WORD* indices = nullptr) override
	{
		for (UINT i = 0; i<m_numPrims * 3; i++)
		{
			Vector3 vertPos = m_vertices[i].Pos;

			Matrix rotMat = Matrix::CreateFromYawPitchRoll(XM_PI*(vertPos.y + 5.0f) / 20.0f, 0.0f, 0.0f);
			
			Vector3 newPos = Vector3::Transform(vertPos, rotMat);

			m_vertices[i].Pos = newPos;
		}

		if (indices && false)
		{
			//spits out an obj of the model produced
			std::ofstream output;
			output.open("test.obj");
			output << "g TEST\n\n";
			for (UINT i = 0; i < m_numPrims * 3; i++)
			{
				output << "v " << m_vertices[i].Pos.x << " " << m_vertices[i].Pos.y << " " << m_vertices[i].Pos.z << "\n";
			}
			int count = 1;
			output << "\n";
			for (unsigned int i = 0; i < m_numPrims; i++)
			{
				output << "f " << count << " " << count+1 << " " << count+2 << "\n";
				count += 3;
			}
			output.close();
		}
	}
};

#endif