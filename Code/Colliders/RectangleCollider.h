#pragma once

#include "Collider.h"
#include "../Vector2.h"
#include "../Entity.h"

namespace Monocle
{
	// Axis-Aligned Bounding Box
	class RectangleCollider : public Collider
	{
	public:
		float width;
		float height;
		RectangleCollider(float width, float height, Vector2 offset=Vector2::zero);
		ColliderType GetColliderType();
		bool IntersectsPoint(const Vector2& point);
		bool IntersectsLine(const Vector2& start, const Vector2& end);

		float GetRight(bool relativeToEntity = false);
		float GetLeft(bool relativeToEntity = false);
		float GetTop(bool relativeToEntity = false);
		float GetBottom(bool relativeToEntity = false);

		const Vector2& GetTopLeft(bool relativeToEntity = false);
		const Vector2& GetTopRight(bool relativeToEntity = false);
		const Vector2& GetBottomLeft(bool relativeToEntity = false);
		const Vector2& GetBottomRight(bool relativeToEntity = false);
	};
}