#pragma once
#include "VBQuad.h"
#include "ZoneType.h"

class PreviewQuad : public VBQuad
{
public:
	PreviewQuad(ID3D11Device* GD);
	~PreviewQuad();

	void ChangePreviewQuadColor(ZoneType zone_type);
	void ResizePreviewQuad(Vector3 start, Vector3 end);
	void CreatePreviewQuadOfSize(Vector3 start, int size);
	void ResetPreviewQuad();

protected:

private:

};

