#ifndef _UI_H
#define _UI_H

#define PART 8

#include "event.h"

struct _KeyboardState
{
    int key;
    int modifier;
};
typedef struct _KeyboardState KeyboardState;

struct _keybinding
{
    KeyboardState key;
    Event *event;
    struct _keybinding *next;
};
typedef struct _keybinding KeyBinding;

struct _RGB
{
    unsigned char b;
    unsigned char g;
    unsigned char r;
};
typedef struct _RGB RGB;

void DrawTextBox(int x1, int y1, int x2, int y2);

void DrawMainWindow(void *);
void IsExit(void *n);
void DrawMainTextBox(void *null);
void DrawStatusBox(void *null);

int RAvsRA(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4);

void SetColor(unsigned int n);
void FadingColor(void *null);
void InitColor(void *null);

void ChangeDotted(void *n);
void ChangeHighlight(void *n);

void CheckStatus(void *n);
void ShowHelp(void *n);
void OpenFile(void *n, char *f);
#endif
