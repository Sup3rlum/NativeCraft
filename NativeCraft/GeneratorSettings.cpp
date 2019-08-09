#include "GeneratorSettings.h"

GeneratorSettings::GeneratorSettings()
{
	srand(time(NULL));

	Seed = rand();
}
GeneratorSettings::GeneratorSettings(uint32_t _seed)
{
	Seed = _seed;
}