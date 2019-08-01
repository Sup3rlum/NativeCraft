#pragma once



inline unsigned long ncpair(int x, int y)
{
	return ((unsigned int)x) | ((unsigned long)y << 32);
}
inline void ncunpair(unsigned long u, int* x, int* y)
{
	*x = (int)((u << 32) >> 32);
	*y = (int)(u >> 32);
}