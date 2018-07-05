#ifndef WIN_PROPERTIES_H
#define WIN_PROPERTIES_H
#pragma once
class WindowProperties
{
public:
	static int x, y, w, h;
public:
	WindowProperties();
	~WindowProperties();
	static void SetSize(int w, int h);
};
#endif
