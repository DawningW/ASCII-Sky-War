#ifndef __GAME_H__
#define __GAME_H__

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "logger.h"
#include "resources.h"
#include "physics.h"
#include "input.h"
#include "renderer.h"
#include "webhelper.h"
#include "util.h"

void game_run();
void game_init();
void game_loop();
void game_exit();

#endif // !__GAME_H__
