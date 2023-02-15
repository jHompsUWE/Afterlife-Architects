#ifndef _TREE_BIT_H_
#define _TREE_BIT_H_

//=================================================================
//A component of the L-System (ish) tree
//=================================================================

#include "CMOGO.h"
#include <list>

using namespace std;

class TreeBit :public CMOGO
{
public:
	TreeBit(int _levels, int _perLevel, int _ofLevel, float _scale, Vector3 _shift, float _lean, string _bitFileName, ID3D11Device* _pd3dDevice, IEffectFactory* _EF, TreeBit* _parent, list<TreeBit*>* _tree);
	~TreeBit();

	virtual void Tick(GameData* _GD) override;

protected:

	TreeBit* m_parent;		//my parent part in the tree

};

#endif