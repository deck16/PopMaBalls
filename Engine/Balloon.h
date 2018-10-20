#pragma once

#include "Graphics.h"
#include "Colors.h"
#include "Vec2.h"
#include <random>
class Balloon
{
public:
	enum class State
	{
		Active,
		Missed,
		Popped
	};
public:
	Balloon() = default;
	Balloon(const Vec2& _pos, float _size, Color _c);
	void Draw(Graphics& gfx) const;
	void Update(float dt);
	void Pop();
	void Relocate(const Vec2& newpos);
	bool IsInsideBalloon(const Vec2& v) const;
	void Respawn(const Vec2& _pos, float _size, Color _c);
	State GetState() const;

	static constexpr float maxRadius = 30.0f;
	static constexpr int minRadius = 10.0f;
	static constexpr int colorLowerBound = 100;
private:
	static constexpr float inflateRate = 20.0f;
	bool isDeflating = false;
	Color c;
	float size;
	float r = 0.0f;
	Vec2 pos;
	bool isPopped = false;
	State state = State::Active;
};