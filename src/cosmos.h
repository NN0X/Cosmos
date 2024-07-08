#ifndef COSMOS_H
#define COSMOS_H

#include "screen.h"
#include "vector.h"
#include "buffer.h"
#include "object.h"
#include "console.h"
#include "utility.h"
#include "defines.h"
#include "input.h"

extern Screen *cScreen;
extern Object *cObjects;
extern Timer *cTimer;
extern int cEXIT_KEY;
extern int cDEBUG;

void onStartup();
void onEachFrame();
void onShutdown();

#endif
