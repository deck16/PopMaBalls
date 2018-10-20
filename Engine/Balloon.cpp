#include "Balloon.h"

Balloon::Balloon(const Vec2& _pos, float _size, Color _c, std::mt19937& rng)
	:
	pos(_pos),
	size(_size),
	c(_c)
{
	float dir = 0.0f;
	for (Balloon::Particle& p : particles)
	{
		p.GenerateVel(rng);
		p = Balloon::Particle(pos, p.GetVel(), size*Balloon::Particle::sizeRatio, _c);
	}
}

void Balloon::Draw(Graphics & gfx) const
{
	if (!isPopped)
	{
		gfx.FillCircle(pos, r, c);
	}
	for (const Balloon::Particle& p : particles)
	{
		p.Draw(gfx);
	}

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
	else
	{
		state = State::Popped;
		for (Balloon::Particle& p : particles)
		{
			p.MakeVisible();
			p.Update(dt);
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
	for (Balloon::Particle& p : particles)
	{
		p.Relocate(newpos);
	}
	state = State::Active;
}

bool Balloon::IsInsideBalloon(const Vec2 & v) const
{
	return (v - pos).GetLength() <= r;
}

void Balloon::Respawn(const Vec2 & _pos, float _size, Color _c, std::mt19937& rng)
{
	pos = _pos;
	size = _size;
	c = _c;
	state = State::Active;
	isPopped = false; 
	for (Balloon::Particle& p : particles)
	{	
		p.GenerateVel(rng);
		p.Respawn(_pos, p.GetVel(), _size*Balloon::Particle::sizeRatio, _c );
	}
}

Balloon::State Balloon::GetState() const
{
	return state;
}

Balloon::Particle::Particle(const Vec2 & _pos, const Vec2 & _vel, float _size, Color _c)
	:
	pos(_pos),
	vel(_vel),
	size(_size),
	c(_c)
{
}

void Balloon::Particle::MakeVisible()
{
	isVisible = true;
}

void Balloon::Particle::Draw(Graphics & gfx) const
{
	if (isVisible)
	{
		gfx.DrawRect(pos, size, size, c);
	}
}

void Balloon::Particle::Update(float dt)
{
	if (isVisible)
	{
		pos += vel * dt;
	}
}

bool Balloon::Particle::IsVisible() const
{
	return isVisible;
}

void Balloon::Particle::Relocate(const Vec2 & _pos)
{
	pos = _pos;
}

void Balloon::Particle::GenerateVel(std::mt19937 & rng)
{
	std::uniform_real_distribution<float>xdist(-speed, speed);
	std::uniform_real_distribution<float>ydist(-speed, speed);
	vel = { xdist(rng), ydist(rng) };
}

Vec2 Balloon::Particle::GetVel() const
{
	return vel;
}

void Balloon::Particle::Respawn(const Vec2& _pos, const Vec2& _vel, float _size, Color _c)
{
	pos = _pos;
	size = _size;
	c = _c;
	vel = _vel;
}
