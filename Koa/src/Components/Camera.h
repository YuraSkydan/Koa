#pragma once
#include "Component.h"
//#include "../Scene/LayerMask.h"
//#include "SpriteRenderer.h"

class KOA Camera : public Component
{
private:
	float m_AspectRation = 0;

	unsigned int m_Width = 0;
	unsigned int m_Heigth = 0;

public:
	float size = 1;
	//Color backgroundColor;
	//LayerMask cullingMask;

public:
	Camera(Entity* owner);

	void SetRatio(float aspectRation);

	float GetAspectRation() const { return m_AspectRation; }
	//Matrix3x3f GetCameraMatrix() const;

	//void Serialize(json& out) const override;
	//void Deserialize(json& in) override;
};