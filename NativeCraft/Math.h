#pragma once



inline uint64_t ncpair(int32_t x, int32_t y)
{
	return ((uint64_t)x) | ((uint64_t)y << 32);
}
inline void ncunpair(uint64_t u, int* x, int* y)
{
	*x = (int)((u << 32) >> 32);
	*y = (int)(u >> 32);
}