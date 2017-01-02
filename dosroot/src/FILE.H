Row *ReadFile(void *n, char *filename, Event *readerr);
/* Read all content from a file, and format all the data to a struct */

void NewFile(void *n);
/* open a new file */

void ShowFile(void *row);

void ReadErr(void *filename);
