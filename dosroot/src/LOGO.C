#include "common.h"
#include "logo.h"

Logos *GetLogoXY(void)
/* Function to read the logo from file and return a pointer to it. */
{
    Logos *a;
    Logo *b;
    /* Temporary variables to save logo parts */
    
    int i, j;
    FILE *fp;
    fp = fopen("logo.txt", "r");
    /* Open logo.txt for read */
    
    a = ALLOC(sizeof(Logos));
    /* Allocate memory to the temporary logo variable */
    
    fscanf(fp, "%d", &a -> n);
    /* Read parts of the logo from file */
    
    a -> logo = (Logo **)ALLOC(a -> n * sizeof(Logo *));
    /* Allocate memory to the pointer array of logo parts */
    
    for(i = 0; i < a -> n; i++)
    {
        b = ALLOC(sizeof(Logo));
        /* Allocate memory for every part of the logo */
        
        fscanf(fp, "%d", &b -> n);
        /* Read the number of pointer for a part */
        
        b -> x = (int *)ALLOC(b -> n * sizeof(int));
        b -> y = (int *)ALLOC(b -> n * sizeof(int));
        /* Dynamic Allocate array to save the coordinates */
        
        for(j = 0; j < b -> n; j++)
            fscanf(fp, "%d%d", &b -> x[j], &b -> y[j]);
            /* Read each coordinates from file */
        
        a -> logo[i] = b;
        /* Give the pointer back to the whole logo pointer */
    }
    fclose(fp);
    return a;
}

void DrawLogo(void *n)
/* Draw out the Logo */
{
    int midx, midy;
    /* Saving the center of the screen */
    
    int dx, dy;
    /* Saving current X,Y coordinates */
    
    int dnx, dny;
    /* Saving the delta X,Y for putpixel operations */
    
    int c, lc = -1;
    /* Saving random color and the last one, to make sure no same color
     * is used between next door letters */
    
    int i, j, tx, ty;
    Logos *a;
    a = GetLogoXY();
    /* Get Logo Using GetLogoXY() */
    
    DoNothing(n);
    
    midx = getmaxx() / 2;
    midy = getmaxy() / 2;
    /* Get the center of the screen */
    
    for(i = 200; i>0; i-=20)
    /* Draw some circles */
    {
        SetColor(15);
        circle(midx, midy, i);
        /* Draw a circle */
        
        delay(50);
        SetColor(0);
        circle(midx, midy, i);
        /* Set color to black and erase the circle */
    }
    
    for(i = 0; i < a -> n; i++)
    /* Draw each part of the logo */
    {
        SetColor(15);
        for(j = 1; j < a -> logo[i] -> n; j++)
        /* String the points to lines */
        {
            dx = a -> logo[i] -> x[j-1];
            dy = a -> logo[i] -> y[j-1];
            /* Current location is at last point */
            
            for(; dx != a -> logo[i] -> x[j] || 
                  dy != a -> logo[i] -> y[j]; )
            /* If not reached, just draw another pixel */
            {
                putpixel(dx, dy, 15);
                delay(3);
                dnx = dny = 1;
                if((dx != a -> logo[i] -> x[j]) && 
                   (dy != a -> logo[i] -> y[j]))
                /* Wordaround for non 1:1 scaling */
                {
                    tx = dx - a -> logo[i] -> x[j];
                    ty = dy - a -> logo[i] -> y[j];
                    /* Calculate the difference */
                    
                    tx = tx > 0 ? tx: -tx;
                    ty = ty > 0 ? ty: -ty;
                    /* Force it to positive */
                    
                    if(tx > ty)
                        dnx++;
                    else if(ty > tx)
                        dny++;
                    /* A simple workaround that supports 1:2 and 2:1
                     * scaling ... */
                }
                if(dx != a -> logo[i] -> x[j])
                    dx += (dx < a -> logo[i] -> x[j] ? dnx: -dnx);
                if(dy != a -> logo[i] -> y[j])
                    dy += (dy < a -> logo[i] -> y[j] ? dny: -dny);
                /* Plus the delta into current location */
            }
        }
        do
        {
            c = rand() % 6 + 1;
        } while(c == lc);
        /* Generate a different color from the last letter */
        
        lc = c;
        /* Save the color for next time comparison */
        
        if(a -> logo[i] -> n < 5)
            c = 0;
        /* Workaround for the triangle in letter "A" */
        
        setfillstyle(1, c);
        floodfill((a -> logo[i] -> x[0] + a -> logo[i] -> x[1]) / 2 + 1,
                  (a -> logo[i] -> y[0] + a -> logo[i] -> y[1]) / 2, 15);
        /* Floodfill in the pixel right to the first line of the
         * letter. */
    }
    
    /* Keep the image until a keyboard hit */
    
    for(i = 0; i < a -> n; i++)
    {
        FREEMEM(a -> logo[i] -> x);
        FREEMEM(a -> logo[i] -> y);
        FREEMEM(a -> logo[i]);
    }
    FREEMEM(a -> logo);
    FREEMEM(a);
    /* Release all memory that used */
}
