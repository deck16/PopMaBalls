#include "FrameTimer.h"

FrameTimer::FrameTimer()
{
	last = std::chrono::steady_clock::now();
}

float FrameTimer::Mark()
{
	const auto old = last;
	last = std::chrono::steady_clock::now();
	std::chrono::duration<float>diff = last - old;
	return diff.count();
}
