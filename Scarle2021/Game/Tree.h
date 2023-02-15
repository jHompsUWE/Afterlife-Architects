#ifndef _TREE_H_
#define _TREE_H_

//=================================================================
//An L-System (ish) tree
//=================================================================

#include "gameobject.h"
#include <list>
#include "Model.h"
#include <string>

using namespace std;
using namespace DirectX;

class TreeBit;

class Tree :public GameObject
{
	public:
	Tree(int _levels, int _perlevel, float _scale, Vector3 _shift, float _lean, string _bitFileName, ID3D11Device* _pd3dDevice, IEffectFactory* _EF);
	~Tree();

	virtual void Tick(GameData* _GD) override;
	virtual void Draw(DrawData* _DD) override; 

protected:
	list<TreeBit*> m_Tree;
};

#endif
