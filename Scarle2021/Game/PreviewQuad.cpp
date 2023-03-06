#include "pch.h"
#include "PreviewQuad.h"

PreviewQuad::PreviewQuad(ID3D11Device* GD): VBQuad(GD, 1, 1)
{
}

PreviewQuad::~PreviewQuad()
{
}

void PreviewQuad::SetPos(Vector3 pos)
{
	m_pos = pos;
	UpdateWorldMatrix();
}

/// <summary>
/// Changes the color of the preview quad according to the ZoneType
/// </summary>
/// <param name="zone_type">the selected ZoneType</param>
void PreviewQuad::ChangePreviewQuadColor(ZoneType zone_type)
{
	switch (zone_type)
	{
	case Green:
		SetColor(Color(0, 1, 0, 0.5));
		break;

	case Yellow:
		SetColor(Color(1, 1, 0, 0.5));
		break;

	case Orange:
		SetColor(Color(1, 0.5, 0, 0.5));
		break;

	case Brown:
		SetColor(Color(0.36, 0.2, 0.1, 0.5));
		break;

	case Purple:
		SetColor(Color(0.9, 0, 0.9, 0.5));
		break;

	case Red:
		SetColor(Color(1, 0, 0, 0.5));
		break;

	case Blue:
		SetColor(Color(0.5, 0.5, 1, 0.5));
		break;

	case Void:
	case Structure:
		SetColor(Color(1, 1, 1, 0.5));
		break;
	}
}


/// <summary>
/// Resizes the preview quad to fit the given position
/// </summary>
/// <param name="start">Starting point of the quad</param>
/// <param name="end">End point of the quad</param>
void PreviewQuad::ResizePreviewQuad(Vector3 start, Vector3 end)
{
	int xDir = start.x < end.x ? 1 : -1;
	int zDir = start.z < end.z ? 1 : -1;

	int xCols = 1 + abs(start.x - end.x);
	int zCols = 1 + abs(start.z - end.z);

	Vector3 temp_pos = Vector3(start.x, 0.01f, start.z);

	if (xDir < 0)
	{
		temp_pos = temp_pos + Vector3(-xDir, 0, 0);
	}
	if (zDir < 0)
	{
		temp_pos = temp_pos + Vector3(0, 0, -zDir);
	}

	SetPos(temp_pos);
	SetScale(Vector3(xCols * xDir, 1, zCols * zDir));
	UpdateWorldMatrix();
}

void PreviewQuad::CreatePreviewQuadOfSize(Vector3 start, int size)
{
	Vector3 end = Vector3(start.x + size - 1.0f, 0, start.z + size - 1.0f);
	ResizePreviewQuad(start, end);
	UpdateWorldMatrix();
}

void PreviewQuad::ResetPreviewQuad()
{
	SetScale(Vector3::One);
	UpdateWorldMatrix();
}
