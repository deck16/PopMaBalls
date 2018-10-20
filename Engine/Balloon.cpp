#include "Balloon.h"

Balloon::Balloon(const Vec2& _pos, float _size, Color _c)
	:
	pos(_pos),
	size(_size),
	c(_c)
{
}

void Balloon::Draw(Graphics & gfx) const
{
	if (!isPopped)
		gfx.FillCircle(pos, r, c);
}

void Balloon::Update(float dt)
{
	if (!isPopped)
	{
		if (!isDeflating)
		{
			r += dt * inflateRate;
			if (r >= size)
			{
				isDeflating = true;
			}
		}
		else
		{
			r -= dt * inflateRate;
			if (r <= 0.0f)
			{
				isDeflating = false;
				state = State::Missed;
			}
		}
	}
}

void Balloon::Pop()
{
	isPopped = true;
}

void Balloon::Relocate(const Vec2 & newpos)
{
	pos = newpos;
	state = State::Active;
}

bool Balloon::IsInsideBalloon(const Vec2 & v) const
{
	return (v - pos).GetLength() == r;
}

void Balloon::Respawn(const Vec2 & _pos, float _size, Color _c)
{
	pos = _pos;
	size = _size;
	c = _c;
}

Balloon::State Balloon::GetState() const
{
	return state;
}
