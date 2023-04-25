#pragma once
#include "Component.h"
//#include "../Scene/LayerMask.h"
//#include "SpriteRenderer.h"

class KOA_API Camera : public Component
{
private:
	float m_AspectRation = 0;

	//Color backgroundColor;
	//LayerMask cullingMask;

public:
	Camera(Entity* owner);

	void SetRatio(float aspectRation);
	float GetAspectRation() const;
	
	//Matrix3x3f GetCameraMatrix() const;
};