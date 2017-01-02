void OutPutMain(void *n);
void OutPutXY(void *n);
/*put out a txt in a rectangle*/
void PageDown(void *n);
/* move page down by one row */

void PageUp(void *n);
/* move page up by one row */

void BackSpace(void *n);
/*del the NO.N char in Row M*/

void Delete(void *n);
/*del the NO.N + 1 char in Row M*/

void HZInsert(void *n);
/*insert the NO.N char in Row M*/

void DrawCur(void *n);
/*draw a cursor in the txt*/

void ClrCur(void *n);
/*clear the cursor at last position*/

void FlashCur(void *n);
/*move the cursor by keyboard*/

void CursorUp(void *n);

void CursorDown(void *n);

void CursorLeft(void *n);

void CursorRight(void *n);

void GetCurPos(void *n);
/* get cursor position by row and column */

void MousetoCursor(void *n);
/* left click mouse and then move the cursor to the current position */

void RowCount(void *n);
/* caculate the total row of the txt */

//void LineFeed(void *n);
/* put the last char to the next row */

void Insert(void *n,char *hz);
/* insert a hanzi in front of the cursor */

void EnterKey(void *n);
/* add the function of pressing Enter Key */


void ChosenArea(void *n);
/* chose a string and color it BLUE */


int LeftHZ(void *n);
/* there is a HZ on the left side of the cursor */

int RightHZ(void *n);
/* there is a HZ on the right side of the cursor */

void InitChildhead(void *n);
void InitChildhead2(void *n);
/* init childhead */

void FreeChildhead(void *n);
void FreeChildhead2(void *n);
/* free childhead */

char *GetChildText(void *n);
char *GetChildText2(void *n);

char LeftChar(void *n);

int UpHZ(void *n);
/* judge the HZ above the cursor */
int FindUpHZPosition(void *n);
/* calculate the HZ positon in the front row */
int DownHZ(void *n);
/* there is a HZ on the top side of the cursor */
int FindDownHZPosition(void *n);
/* calculate the HZ positon in the next row */


void Home(void *n);
/* put the cursor in the first of the currentrow */
void CtrlHome(void *n);
/* put the cursor in the first of the firstrow */
void End(void *n);
/* put the cursor in the end of the currentrow */
void CtrlEnd(void *n);
/* put the cursor in the end of the currentrow */
