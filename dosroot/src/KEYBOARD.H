#ifndef _KEYBOARD_H
#define _KEYBOARD_H

void CheckKeyboard(void *n);
/* Read keyboard states and save it */

void LoadKeyBinding(void *n);
/* Load-time initialization for key bindings */

void InitKeyBinding(KeyBinding *kb);
/* Initialize a key binding struct */

void AddKeyBinding(void *n, KeyboardState key, Event *event);
/* Add a key binding with an event */

KeyboardState KBState(int key, int modifier);
/* Simply packaging a key binding into a KeyboardState struct */

void CheckKeyBinding(void *n);
/* Check if matches a key binding */

void LoadKeyMap(void *n);
/* Load A-Z Keymappings (Recorded manually by Felix Yan) */

void CheckChar(void *n, int key, int shift, int chipunc, int fullwidth, char *punc);
/* Check if a character should be inserted to text */

void CharInput(void *n);
/* Fetch & switch characters (Recorded manually by Felix Yan) */

#endif
