#ifndef _MUSIC_H
#define _MUSIC_H

void PlayMusic(void *n);
/* Music daemon, called in everything time of mainloop */

void StartupMusic(void *n);
/* Play startup music */

void LogoutMusic(void *n);
/* Play logout music */

void RandomMusic(void *n);
/* Play a random music, except for startup music and logout music */

enum _Music
/* Enumerator of songs */
{
    None,
    Startup,
    Logout,
    Laputa,
    Musicbox,
    Lovesale,
    Romeo,
    Joy,
    Minuet,
    Turkey,
    LoveIsBlue
};
typedef enum _Music Music;

#endif
