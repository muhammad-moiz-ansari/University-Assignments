#pragma once

class Rectangle
{
private:
	int length;
	int width;

public:
	Rectangle()
	{
		length = 0;
		width = 0;
	}
	void setLength(int l)
	{
		length = l;
	}
	void setWidth(int w)
	{
		width = w;
	}
	int getLength()
	{
		return length;
	}
	int getWidth()
	{
		return width;
	}
	int calArea()
	{
		return width * length;
	}
	int calPerimeter()
	{
		return 2 * (length + width);
	}
};
