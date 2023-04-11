#pragma once
#include <vector>
#include "Component.h"
#include "../Math/MatrixTransform.h"

enum class KOA_API Space { Self, World };

class KOA_API Transform : public Component
{
private:
	Vector3f m_Position;
	Vector3f m_EulerAngles;
	Vector3f m_Scale;

	Transform* m_Parent = nullptr;
	std::vector<Transform*> m_Childs;

	Matrix4x4f m_TransformMatrix;

public:
	Transform(Entity* owner);

	void SetPosition(const Vector3f& position);
	void SetEulerAngles(const Vector3f& angles);
	void SetScale(const Vector3f& scale);

	const Vector3f& GetPosition() const;
	const Vector3f& GetEulerAngles() const;
	const Vector3f& GetScale() const;

	const Matrix4x4f& GetTransformMatrix();

	~Transform() override = default;
};