#pragma once

#include <stdbool.h>

void backlight_init();
void backlight_revert();

void backlight_dim();
void backlight_brighten();

bool backlight_upd();
