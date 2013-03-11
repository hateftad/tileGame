#ifndef DEBUGDRAWER_H
#define DEBUGDRAWER_H

#include "ModelAsset.h"
#include <vector>
#include <Box2D/Box2d.h>


class DebugDrawer : public b2Draw
{
public:
	struct verts
	{
		float32 x;
		float32 y;
	};
	DebugDrawer(Graphics* graphics);
	void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color);
	void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) {}
	void DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color) {}
	void DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color) {}
	void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color) {}
	void DrawTransform(const b2Transform& xf) {}

	void Draw(int32 vertexCount);
	void CreateVerts(const b2Vec2* vertices, int32 vertexCount, int size);
private:

	ModelAsset* m_assets;
	verts m_vertices[4];
};


#endif