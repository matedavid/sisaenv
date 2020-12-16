#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>

void decimal_to_base(uint16_t number, int base, uint8_t *binary);
uint8_t base_to_decimal(uint8_t *content, int size, int base);

#endif
