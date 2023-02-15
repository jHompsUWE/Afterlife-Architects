#ifndef _DRAW_DATA_2D_H_
#define _DRAW_DATA_2D_H_

//=================================================================
//Data to be passed by game to all 2D Game Objects via Draw 
//=================================================================

#include "SpriteBatch.h"
#include "SpriteFont.h"

using namespace DirectX;
using namespace std;

struct DrawData2D
{
	//spritebatch stuff
	unique_ptr<SpriteBatch>	m_Sprites;
	unique_ptr<SpriteFont> m_Font;
};

#endif
