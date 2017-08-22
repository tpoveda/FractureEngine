#include "../../../../include/Systems/Frac3DEngine/Layer0/F3D_FrameCounter.h"
#include "../../../../include/Systems/Frac3DEngine/_includesF3D.h"

F3D_FrameCounter::F3D_FrameCounter() :
numFrames(0.0f),
elapsedTime(0.0f),
fpsAsFloat(0.0f)
{
	fpsAsString[0] = '\0';
}

F3D_FrameCounter::~F3D_FrameCounter()
{
}

void F3D_FrameCounter::reset()
{
	numFrames = 0.0f;
	elapsedTime = 0.0f;
}

void F3D_FrameCounter::increaseFrames()
{
	numFrames += 1.0f;
}

bool F3D_FrameCounter::increaseElapsedTime(float deltaTime)
{
	elapsedTime += deltaTime;

	if (elapsedTime >= 1.0f)
	{
		return true;
	}
	return false;
}

float F3D_FrameCounter::getFPSAsFloat()
{
	if (elapsedTime >= 1.0f)
	{
		updateFPS();
		reset();
	}
	return fpsAsFloat;
}

const char* F3D_FrameCounter::getFPSAsString()
{
	if (elapsedTime >= 1.0f)
	{
		updateFPS();
		reset();
	}
	return fpsAsString;
}

void F3D_FrameCounter::updateFPS()
{
	if (elapsedTime != 0.0f)
	{
		fpsAsFloat = numFrames / elapsedTime;
		sprintf(fpsAsString, "FPS: %.2f", fpsAsFloat);
	}
}