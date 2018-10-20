/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"

Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	rng(rd()),
	cDist(Balloon::colorLowerBound, 255),
	rDist(Balloon::minRadius, Balloon::maxRadius),
	xDist(Balloon::maxRadius/0.5f, Graphics::ScreenWidth - Balloon::maxRadius/0.5f),
	yDist(Balloon::maxRadius/0.5f, Graphics::ScreenHeight - Balloon::maxRadius/0.5f),
	pDist(0.5f, 1.0f),
	popSnd(L"Sounds//pop.wav"),
	missSnd(L"Sounds//miss.wav")
{
	for (Balloon& b : balloons)
	{
		const float r = rDist(rng);
		const Vec2 pos = { xDist(rng), yDist(rng) };
		const Color c = { (unsigned char)cDist(rng) , (unsigned char)cDist(rng) , (unsigned char)cDist(rng) };
		const Vec2 pDir = { pDist(rng), pDist(rng) };
		b = { pos, r, c, rng };
	}
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	bool hit = false;
	const float dt = ft.Mark();
	while (!wnd.mouse.IsEmpty())
	{
		const Mouse::Event e = wnd.mouse.Read();
		if (e.GetType() == Mouse::Event::Type::LPress)
		{
			for (int i = 0; i < nBalloons; i++)
			{
				const Vec2 mpos = { (float)e.GetPosX(), (float)e.GetPosY() };
				if (balloons[i].IsInsideBalloon(mpos))
				{
					balloons[i].Pop();
					popSnd.Play();
					hit = true;
				}
				else if ((i == nBalloons-1) && !hit)
				{
					missSnd.Play();
				}
			}
		}
	}
	for (Balloon& b : balloons)
	{
		b.Update(dt);
		if (b.GetState() == Balloon::State::Missed)
		{
			b.Relocate({ xDist(rng), yDist(rng) });
		}
		else if (b.GetState() == Balloon::State::Popped)
		{
			counter += dt;
			if (counter > 0.2f)
			{
				counter = 0;
				b.Respawn({ xDist(rng), yDist(rng) }, rDist(rng),
					{ (unsigned char)cDist(rng), (unsigned char)cDist(rng),(unsigned char)cDist(rng) }, rng);
			}
		}
	}
}

void Game::ComposeFrame()
{
	for (Balloon& b : balloons)
	{
		b.Draw(gfx);
	}
}
