#ifndef SWO_INIT_H
#define SWO_INIT_H

#include <stdint.h>

void swoInit (uint32_t portMask, uint32_t cpuCoreFreqHz, uint32_t baudrate);

#endif