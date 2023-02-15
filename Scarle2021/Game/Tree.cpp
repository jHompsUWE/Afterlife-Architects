#include "pch.h"
#include "Tree.h"
#include "TreeBit.h"


Tree::Tree(int _levels, int _perLevel, float _scale, Vector3 _shift, float _lean, string _bitFileName, ID3D11Device* _pd3dDevice, IEffectFactory* _EF)
{
	//recursively create the tree
	new TreeBit(_levels,_perLevel,-1,_scale,_shift,_lean,_bitFileName,_pd3dDevice,_EF, nullptr, &m_Tree);
}

Tree::~Tree()
{
	//get rid of the tree parts here
	for (list<TreeBit *>::iterator it = m_Tree.begin(); it != m_Tree.end(); it++)
	{
		delete (*it);
	}

	m_Tree.clear();
}


void Tree::Tick(GameData* _GD)
{
	//update all tree parts
	for (list<TreeBit *>::iterator it = m_Tree.begin(); it != m_Tree.end(); it++)
	{
		(*it)->Tick(_GD);
	}
}

void Tree::Draw(DrawData* _DD)
{
	//draw all tree parts
	for (list<TreeBit *>::iterator it = m_Tree.begin(); it != m_Tree.end(); it++)
	{
		(*it)->Draw(_DD);
	}
}