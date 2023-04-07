#include "Transform.h"

Transform::Transform(Entity* owner)
	: Component(owner), m_Scale(1.0f), m_TransformMatrix(1.0f)
{ }

void Transform::SetPosition(const Vector3f& position)
{
	m_Position = position;
}

void Transform::SetEulerAngles(const Vector3f& angles)
{
	m_EulerAngles = angles;
}

void Transform::SetScale(const Vector3f& scale)
{
	m_Scale = scale;
}

const Vector3f& Transform::GetPosition() const
{
	return m_Position;
}

const Vector3f& Transform::GetEulerAngles() const
{
	return m_EulerAngles;
}

const Vector3f& Transform::GetScale() const
{
	return m_Scale;
}

const Matrix4x4f& Transform::GetTransformMatrix()
{
	//if(m_IsDirty)
	{
		m_TransformMatrix = Matrix4x4f(1.0f);
		m_TransformMatrix = MatrixTransform::Translate(m_TransformMatrix, m_Position);
		m_TransformMatrix = MatrixTransform::Scale(m_TransformMatrix, m_Scale);
		m_TransformMatrix = MatrixTransform::Rotate(m_TransformMatrix, m_EulerAngles);

		//Matrix2x2f test1;
		//Matrix2x2f test2;

		//auto test3 = test1 + test2;
	}

	return m_TransformMatrix;
}