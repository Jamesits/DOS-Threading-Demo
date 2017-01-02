#ifndef _LOGO_H
#define _LOGO_H

struct _Logo
/* Struct of a part of the whole logo, saving some points that the 
 * program will string them together with line. */
{
    int n;
    /* Number of the points */
    int *x, *y;
    /* X,Y coordinates for every point */
};
typedef struct _Logo Logo;

struct _Logos
/* Struct of the whole logo, saving pointers to each part of the logo.*/
{
    int n;
    /* Number of parts */
    Logo **logo;
    /* pointer to each logo */
};
typedef struct _Logos Logos;

Logos *GetLogoXY(void);
/* Function to read the logo from file and return a pointer to it. */

void DrawLogo(void *);
/* Draw out the Logo */

#endif
