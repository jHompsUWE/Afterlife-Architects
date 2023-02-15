#include "pch.h"
#include "TreeBit.h"
#include "GameData.h"

TreeBit::TreeBit(int _levels, int _perLevel, int _ofLevel, float _scale, Vector3 _shift, float _lean, string _bitFileName, ID3D11Device* _pd3dDevice, IEffectFactory* _EF, TreeBit* _parent, list<TreeBit*>* _tree) :CMOGO(_bitFileName, _pd3dDevice, _EF)
{
	m_parent = _parent;

	//the trunk just sits there
	if (_ofLevel >= 0 )
	{
		m_yaw = XM_2PI *  (float)_ofLevel / (float)_perLevel; //equally spread the branches around the trunk/parent
		m_pitch = _lean; //leaning the branches out by this angle
		m_pos = _shift;  //move this far up the trunk/parent
		m_scale = _scale*Vector3::One; //scale me down by this much relative to my trunk/parent
	}
	
	_tree->push_back(this);
	
	if (_levels >1)
	{
		for (int i = 0; i < _perLevel; i++)
		{
			//recursively create my children
			new TreeBit(_levels - 1, _perLevel, i, _scale, _shift, _lean, _bitFileName, _pd3dDevice, _EF, this, _tree);
		}
	}
	
}

TreeBit::~TreeBit()
{
}


void TreeBit::Tick(GameData* _GD)
{
	CMOGO::Tick(_GD);
	if (m_parent)
	{
		//as should all be ticked in generational order
		//this should pick up all the previous generations of the parenting
		m_worldMat = m_worldMat * m_parent->m_worldMat;
	}
	
}