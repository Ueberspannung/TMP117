#include "Wire.h"
#include "TMP117.h"

TMP117 sensor(0x4F);

void setup(void)
{
	Wire.begin();
	Wire.setClock(100000);
}


void loop(void)
{
}
