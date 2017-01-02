#include "common.h"
#include "music.h"

void StartupMusic(void *n)
/* Play startup music */
{
    State *s;
    s = (State *)n;
    s -> curmusic = Startup;
}

void LogoutMusic(void *n)
/* Play logout music */
{
    State *s;
    s = (State *)n;
    s -> curmusic = Logout;
}

void RandomMusic(void *n)
/* Play a random music, except for startup music and logout music */
{
    State *s;
    s = (State *)n;
    s -> curmusic = 3 + rand() % 8;
    //s -> curmusic = LoveIsBlue;
}

void PlayMusic(void *n)
/* Music daemon, called in everything time of mainloop */
{
    static Music lastmusic = None;
    /* Saving last music for comparison */
    
    float delta = 1.059463;
    /* 2^(1/12), for calculating twelve-tone equal temperament frequencies */

    /* Startup Music */
    int startup[] =          {12,   8,    5,    0};
    /* Definition of every note */
    float startuptime[] = {0, 0.25, 0.25, 0.25, 0.25};
    /* Duration for every note */
    int startupnum = 4;
    /* Number of notes */
    int startupfreq = 1770;
    /* The highest frequency */
    int startuplen = 16;
    /* coefficient for duration */
    
    /* Laputa Theme */
    int laputa[] =          {7,    5,    4,    5,    4,    0,    5, 
                             12,   7,    9,    7,    4,    9, 
                             12,   12,   11,   12,   11,   4,   12,
                             4,    4,    5,    10,   10,   5,    5,
                             7,    5,    4,    5,    4,    0,    5,
                             12,   7,    9,    7,    4,    9, 
                             12,   11,   4,    5,    4,    2,    2,    0,    4,
                             4,    5,    7,    7,    5,    8,    7};
    float laputatime[] = {0, 0.25, 0.25, 0.75, 0.25, 0.5,  0.5,  1.25,
                             0.5,  0.75, 0.25, 0.5,  0.5,  1.25,
                             0.25, 0.25, 0.75, 0.25, 0.25, 0.75, 1.25,
                             0.25, 0.25, 0.75, 0.25, 0.5,  0.5,  1.5,
                             0.25, 0.25, 0.75, 0.25, 0.5,  0.5,  1.25,
                             0.5,  0.75, 0.25, 0.5,  0.5,  1.25,
                             0.5,  0.5,  0.25, 0.75, 0.5,  0.25, 0.5, 0.25, 1.25,
                             0.25, 0.25, 0.25, 0.25, 0.5,  0.5,  1};
    int laputanum = 56;
    int laputafreq = 1280;
    int laputalen = 14;
    
    /* Musicbox Dancer */
    int musicbox[] =          {/*24,   20,   17,   20,   12,   17,   20,   17,
                               24,   20,   17,   20,   12,   17,   20,   17,
                               24,   20,   17,   20,   12,   17,   20,   17,
                               24,   20,   17,   20,   12,   17,   20, */
                               12,   12,   12,   17,   12,   8,    12,   8,    5,
                               0,    1,    3,    5,
                               12,   12,   12,   5,    7,    10,   13,   
                               17,   13,   10,   7,    8,    12,   3,    5,
                               12,   12,   12,   17,   12,   8,    12,   8,    5,
                               0,    1,    3,    5,
                               12,   12,   12,   5,    7,    10,   13,
                               17,   13,   10,   13,   12,   17,   8,    12};
    float musicboxtime[] = {0, /*0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25,
                               0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25,
                               0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25,
                               0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.5,*/
                               0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.5,
                               0.25, 0.25, 0.25, 1,
                               0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25,
                               0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 1,
                               0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.5,
                               0.25, 0.25, 0.25, 1,
                               0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25,
                               0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 1
                               };
    int musicboxnum = 56/*87*/;
    int musicboxfreq = 1770;
    int musicboxlen = 10;
    
    /* love - MuRongXiaoXiao */
    int lovesale[] = {         7,    7,    12,   14,   12,
                               14,   14,   12,   14,   16,   14,
                               9,    9,    9,    12,   9,    9,    9,    12,
                               7,    12,   12,   14,   12,
                               7,    7,    12,   14,   12,
                               14,   14,   12,   14,   16,   14,
                               9,    9,    9,    12,   9,    9,    9,
                               12,   9,    5,    9,    9,    12,   7,
                               12,   7,    4,    4,    12,   7,    4,
                               5,    5,    7,    9,    14,
                               19,   14,   14,   19,   14,   12,   9,
                               12,   5,    5,    9,    12,
                               12,   7,    4,    4,    12,   7,    4,
                               0,    0,    2,    4,    2,
                               0,    0,    2,    4,    2,    2,    4,    5,
                               9,    12,   9,    7,    7};
    float lovesaletime[] = {0, 0.5,  0.5,  0.5,  0.5,  2,
                               0.5,  0.25, 0.25, 0.5,  0.5,  2,
                               0.5,  0.5,  0.5,  0.5,  0.5,  0.5,  0.5,  0.5,  
                               0.5,  0.5,  0.5,  0.5,  2,
                               0.5,  0.5,  0.5,  0.5,  2,
                               0.5,  0.25, 0.25, 0.5,  0.5,  2,
                               0.5,  0.5,  0.5,  0.5,  0.5,  0.5,  0.5,
                               0.25, 0.25, 0.5,  0.5,  0.5,  0.5,  2,
                               0.5,  0.5,  0.5,  0.5,  0.5,  0.5,  1,
                               0.5,  0.5,  0.5,  0.5,  2,
                               0.5,  0.5,  0.5,  0.5,  0.5,  0.5,  1,
                               0.5,  0.5,  0.5,  0.5,  2,
                               0.5,  0.5,  0.5,  0.5,  0.5,  0.5,  1,
                               0.5,  0.5,  0.5,  0.5,  2,
                               0.75, 0.25, 0.5,  0.5,  0.75, 0.25,  0.5,  0.5,
                               0.5,  0.5,  0.5,  0.5,  2};
    int lovesalenum = 98;
    int lovesalefreq = 1900;
    int lovesalelen = 8;
    
    /* Romeo and Juliet */
    int romeo[] = {         8,    5,    6,    13,   13,   10,   13,   8,
                            8,    10,   12,   10,   10,   12,   13,   15,
                            13,   15,   17,   15,   13,
                            8,    5,    6,    13,   13,   10,   13,   8,
                            8,    3,    3,    6,    13,   5,
                            6,    8,    10,   5,    6,    8,    10,   8};
    float romeotime[] = {0, 0.5,  0.5,  0.5,  1.5,  0.5,  0.5,  0.5,  1.5,
                            0.5,  0.5,  0.5,  1.5,  0.5,  0.5,  0.5,  1.5,
                            0.25, 0.25, 0.75, 0.25, 1.5,
                            0.5,  0.5,  0.5,  1.5,  0.5,  0.5,  0.5,  1.5,
                            1,    2,    1,    2,    1,    1.5,
                            0.5,  0.5,  0.5,  0.5,  0.5,  1,    1,    2};
    int romeonum = 43;
    int romeofreq = 1900;
    int romeolen = 8;
    
    int joy[] = {         3,    3,    2,    0,    0,    2,    3,    5,
                          7,    7,    5,    3,    3,    5,    5,
                          3,    3,    2,    0,    0,    2,    3,    5,
                          7,    7,    5,    3,    5,    7,    7,
                          5,    5,    3,    7,    5,    3,    2,    3,    7,
                          5,    3,    2,    3,    5,    7,    5,    12,
                          3,    3,    2,    0,    0,    2,    3,    5,
                          7,    7,    5,    3,    5,    7,    7};
    float joytime[] = {0, 1,    1,    1,    1,    1,    1,    1,    1,
                          1,    1,    1,    1,    1.5,  0.5,  2,
                          1,    1,    1,    1,    1,    1,    1,    1,
                          1,    1,    1,    1,    1.5,  0.5,  2,
                          1,    1,    1,    1,    1,    0.5,  0.5,  1,    1,
                          1,    0.5,  0.5,  1,    1,    1,    1,    1,
                          2,    1,    1,    1,    1,    1,    1,    1,
                          1,    1,    1,    1,    1.5,  0.5,  2};
    int joynum = 62;
    int joyfreq = 1500;
    int joylen = 6;
    
    int minuet[] =          {5,    12,   10,   8,    7,    5,    12,   12,
                             3,    7,    5,    3,    1,    0,    12,   12,
                             7,    5,    7,    8,    10,   8,
                             7,    8,    10,   12,   13,
                             12,   10,   8,    12,   8,    10,
                             5,    12,   10,   8,    7,    5,    12,   12,
                             3,    7,    5,    3,    1,    0,    12,   12,
                             7,    5,    7,    8,    10,   8,
                             7,    8,    10,   12,   10,
                             8,    10,   12,   13,   12};
    float minuettime[] = {0, 1,    0.5,  0.5,  0.5,  0.5,  1,    1,    1,
                             1,    0.5,  0.5,  0.5,  0.5,  1,    1,    1,
                             1,    0.5,  0.5,  0.5,  0.5,  1,
                             0.5,  0.5,  0.5,  0.5,  1,
                             0.5,  0.5,  0.5,  0.5,  1.5,  1,
                             1,    0.5,  0.5,  0.5,  0.5,  1,    1,    1,
                             1,    0.5,  0.5,  0.5,  0.5,  1,    1,    1,
                             1,    0.5,  0.5,  0.5,  0.5,  1,
                             0.5,  0.5,  0.5,  0.5,  1,
                             0.5,  0.5,  0.5,  0.5,  2};
    int minuetnum = 65;
    int minuetfreq = 1700;
    int minuetlen = 6;
    
    int turkey[] = {         13,   15,   16,   15,   12,
                             10,   12,   13,   12,   8,
                             7,    8,    9,    8,    1,    3,    4,    3,
                             1,    3,    4,    3,    0,
                             3,    0,    1,    3,    5,    3,    1,    3,
                             5,    3,    1,    3,    5,    6,    8,
                             8,    7,    5,    5,    3,    5,    7,    8,    10,
                             8,    7,    5,    5,    3,    5,    7,    8,    10,
                             12,   10,   8,    8,    7,    8,    10,   12,   13,
                             12,   10,   8,    8,    7,    8,    10,   12,   13,
                             13,   15,   16,   15,   12,
                             10,   12,   13,   12,   8,
                             7,    8,    9,    8,    1,    3,    4,    3,
                             1,    3,    4,    3,    0,
                             3,    1,    0,    1,    3,    4,    3,    8,
                             7,    10,   12, 
                             12,   13,   12,   13,   15,   13,   15};
    float turkeytime[] = {0, 0.25, 0.25, 0.25, 0.25, 1,
                             0.25, 0.25, 0.25, 0.25, 1,
                             0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25,
                             0.25, 0.25, 0.25, 0.25, 1,
                             0.5,  0.5,  0.5,  0.5,  0.5,  0.5,  0.5,  0.5,
                             0.5,  0.5,  0.5,  0.5,  0.5,  0.5,  1,
                             0.5,  0.5,  0.5,  0.5,  0.25, 0.25, 0.25, 0.25, 1,
                             0.5,  0.5,  0.5,  0.5,  0.25, 0.25, 0.25, 0.25, 1,
                             0.5,  0.5,  0.5,  0.5,  0.25, 0.25, 0.25, 0.25, 1,
                             0.5,  0.5,  0.5,  0.5,  0.25, 0.25, 0.25, 0.25, 1,
                             0.25, 0.25, 0.25, 0.25, 1,
                             0.25, 0.25, 0.25, 0.25, 1,
                             0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25,
                             0.25, 0.25, 0.25, 0.25, 1,
                             0.5,  0.5,  0.5,  0.5,  0.5,  0.5,  0.5,  0.5,
                             0.5,  0.5,  1,
                             0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 1};
    int turkeynum = 115;
    int turkeyfreq = 1600;
    int turkeylen = 9;
    
    int loveisblue[] =          {0,    2,    4,    5,    7,    9,
                                 7,    4,    5,    4,    7,    9,    7,    9,    12,
                                 0,    2,    4,    5,    7,    9,
                                 7,    4,    5,    4,    7,    8,    10,    8,    7};
    float loveisbluetime[] = {0, 1,    0.75, 0.25, 0.5,  0.5,  1,
                                 0.5,  0.25, 0.25, 0.75, 0.25, 0.25, 0.25, 0.5,  1,
                                 1,    0.75, 0.25, 0.5,  0.5,  1,
                                 0.5,  0.25, 0.25, 0.75, 0.25, 0.25, 0.25, 0.5,  1};
    int loveisbluenum = 30;
    int loveisbluefreq = 1800;
    int loveisbluelen = 12;
    
    /* Logout music - similar to the one of WinXP */
    int logout[] =          {0,    5,    12,   10};
    float logouttime[] = {0, 0.25, 0.25, 0.25, 0.25};
    int logoutnum = 4;
    int logoutfreq = 1770;
    int logoutlen = 16;
    
    /* Pointers to fetch current playing music */
    int *music;
    float *musictime;
    int musicnum;
    int maxfreq;
    int musiclen;
    
    // /* Login music - similar to the one of WinXP */
    //float start[9] = {0, 12, 5, 7, 0, 5};
    //float starttime[] = {0, 0.5, 0.25, 0.25, 0.7, 0.25, 0.5};
    
    int i;
    
    static int curnum;
    /* Saving current count of notes */
    
    State *s;
    static long t = -1;
    if(t == -1)
        t = biostime(0, 0);
    s = (State *)n;
    if(lastmusic != s -> curmusic)
        curnum = 0;
    lastmusic = s -> curmusic;
    
    switch(s -> curmusic)
    /* Judging current music and set the pointers */
    {
        case None:
            return;
        case Startup:
            music = startup;
            musictime = startuptime;
            musicnum = startupnum;
            maxfreq = startupfreq;
            musiclen = startuplen;
            break;
        case Laputa:
            music = laputa;
            musictime = laputatime;
            musicnum = laputanum;
            maxfreq = laputafreq;
            musiclen = laputalen;
            break;
        case Musicbox:
            music = musicbox;
            musictime = musicboxtime;
            musicnum = musicboxnum;
            maxfreq = musicboxfreq;
            musiclen = musicboxlen;
            break;
        case Lovesale:
            music = lovesale;
            musictime = lovesaletime;
            musicnum = lovesalenum;
            maxfreq = lovesalefreq;
            musiclen = lovesalelen;
            break;
        case Romeo:
            music = romeo;
            musictime = romeotime;
            musicnum = romeonum;
            maxfreq = romeofreq;
            musiclen = romeolen;
            break;
        case Joy:
            music = joy;
            musictime = joytime;
            musicnum = joynum;
            maxfreq = joyfreq;
            musiclen = joylen;
            break;
        case Minuet:
            music = minuet;
            musictime = minuettime;
            musicnum = minuetnum;
            maxfreq = minuetfreq;
            musiclen = minuetlen;
            break;
        case Turkey:
            music = turkey;
            musictime = turkeytime;
            musicnum = turkeynum;
            maxfreq = turkeyfreq;
            musiclen = turkeylen;
            break;
        case LoveIsBlue:
            music = loveisblue;
            musictime = loveisbluetime;
            musicnum = loveisbluenum;
            maxfreq = loveisbluefreq;
            musiclen = loveisbluelen;
            break;
        case Logout:
            music = logout;
            musictime = logouttime;
            musicnum = logoutnum;
            maxfreq = logoutfreq;
            musiclen = logoutlen;
            break;
    }
    
    if(biostime(0, 0) - t < musictime[curnum] * musiclen)
    /* Keep the last note if not finished */
        return;
    
    if(curnum >= musicnum)
    /* A song has completed! */
    {
        nosound();
        /* Mute the speaker */
        
        if(s -> curmusic == Logout)
        /* Shut down the program after logout music finished */
        {
            FREEMEM(s);
            exit(0);
        }
        
        s -> curmusic = None;
        return;
    }
    
    for(i = 0; i < music[curnum]; i ++)
    /* Calculating twelve-tone equal temperament frequencie */
        maxfreq /= delta;
    
    if(curnum > 0 && music[curnum] == music[curnum - 1])
    /* Add a short stop between two same notes */
    {
        nosound();
        delay(10);
    }
    
    sound((unsigned)maxfreq);
    /* Pronounce the note */
    
    curnum ++;
    /* Move to next note */
    
    t = biostime(0, 0);
    /* Save the current time */
}
