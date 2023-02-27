#pragma once
#include "VBQuad.h"
#include "ZoneType.h"

class PreviewQuad : public VBQuad
{
public:
	PreviewQuad(ID3D11Device* GD);
	~PreviewQuad();

	void StartPreviewQuad(ZoneType zone_type);
	void ResizePreviewQuad(Vector3 start, Vector3 end);
	void ResetPreviewQuad();

protected:

private:

};

