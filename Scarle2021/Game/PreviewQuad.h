#pragma once
#include "VBQuad.h"
#include "ZoneType.h"
#include "NewEventManager.h"

class PreviewQuad : public VBQuad
{
public:
	PreviewQuad(ID3D11Device* GD);
	~PreviewQuad();

	void SetPos(Vector3 pos);

	void ChangePreviewQuadColor(ZoneType zone_type);
	void ResizePreviewQuad(Vector3 start, Vector3 end);
	void CreatePreviewQuadOfSize(Vector3 start, int size);
	void ResetPreviewQuad();

protected:

private:
	const char click_sound_1[32] = "Click";
};

