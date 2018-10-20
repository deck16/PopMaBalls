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
	class Particle
	{
	public:
		Particle() = default;
		Particle(const Vec2& _pos, const Vec2& _vel, float _size, Color _c);
		void MakeVisible();
		void Draw(Graphics& gfx) const;
		void Update(float dt);
		bool IsVisible() const;
		void Respawn(const Vec2& _pos, const Vec2& _vel, float _size, Color _c);
		void Relocate(const Vec2& _pos);
		void GenerateVel(std::mt19937& rng);
		Vec2 GetVel() const;
		static constexpr float sizeRatio = 0.1f;
	private:
		static constexpr float speed = 10.0f;
		bool isVisible = false;
		Vec2 pos;
		Vec2 vel;
		float size;
		Color c;
	};
public:
	Balloon() = default;
	Balloon(const Vec2& _pos, float _size, Color _c, std::mt19937& rng);
	void Draw(Graphics& gfx) const;
	void Update(float dt);
	void Pop();
	void Relocate(const Vec2& newpos);
	bool IsInsideBalloon(const Vec2& v) const;
	void Respawn(const Vec2& _pos, float _size, Color _c, std::mt19937& rng);
	State GetState() const;

	static constexpr float maxRadius = 50.0f;
	static constexpr float minRadius = 20.0f;
	static constexpr int colorLowerBound = 100;
private:
	static constexpr float inflateRate = 20.0f;
	static constexpr int nParticles = 20;
	bool isDeflating = false;
	Color c;
	float size;
	float r = 0.0f;
	Vec2 pos;
	bool isPopped = false;
	State state = State::Active;
	Particle particles[nParticles];
};