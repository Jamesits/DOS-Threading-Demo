char Lowercase(char ch);
int NotNameChar(char ch);
int IsNumber(char ch);

void OutTextxy(void *n, int x, int y, char *p, int color);
/* Output a normal string that may include any character including Chinese */

void OpenHZK(void *n);
/* Open the HZK file on the program loading progress */

void CloseHZK(void *n);
/* Close the HZK file when closing program */
