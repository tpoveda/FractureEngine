#ifndef F3D_FrameCounter_H
#define F3D_FrameCounter_H

class F3D_FrameCounter
{
public:
	F3D_FrameCounter();
	virtual ~F3D_FrameCounter();

	void reset();
	void increaseFrames();
	bool increaseElapsedTime(float deltaTime);
	float getFPSAsFloat();
	const char* getFPSAsString();

private:
	float numFrames;
	float elapsedTime;
	float fpsAsFloat;
	char fpsAsString[32];

	void updateFPS();
};

#endif