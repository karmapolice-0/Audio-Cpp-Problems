#pragma once

#ifndef __MODINV_H__
#define __MODINV_H__

#include <cstdint>

uint16_t mod_inv(uint16_t a, uint16_t m);
uint16_t egcd(uint16_t a, uint16_t b, int* x, int* y);

#endif