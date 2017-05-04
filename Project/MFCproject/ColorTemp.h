#pragma once
class ColorTemp
{
public:
	ColorTemp(void);
	~ColorTemp(void);

public:
	int red;
	int green;
	int blue;
};

ColorTemp::ColorTemp()
{
	red = 0;
	green = 0;
	blue = 0;
}