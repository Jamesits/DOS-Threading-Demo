#include "common.h"
#include "keyboard.h"

void CheckKeyboard(void *n)
/* Read keyboard states and save it */
{
    State *s;
    s = (State *)n;
    if(bioskey(1))
    /* Key pressed, save it! */
    {
        s -> keyboard . key = bioskey(0);
        s -> keyboard . modifier = bioskey(2);
        s -> iskeyboard = 1;
    }
    else
    /* Use -1 as flag to implicate no key pressed */
    {
        s -> keyboard . key = -1;
        s -> keyboard . modifier = -1;
    }
}
    
void LoadKeyBinding(void *n)
/* Load-time initialization for key bindings */
{
    State *s;
    KeyBinding *kb;
    kb = ALLOC(sizeof(KeyBinding));
    s = (State *)n;
    InitKeyBinding(kb);
    s -> keybinding = kb;
}

void InitKeyBinding(KeyBinding *kb)
/* Initialize a key binding struct */
{
    kb -> event = ALLOC(sizeof(Event));
    InitEvent(kb -> event);
    kb -> key . key = -1;
    kb -> key . modifier = -1;
    kb -> next = NULL;
}

void AddKeyBinding(void *n, KeyboardState key, Event *event)
/* Add a key binding with an event */
{
    State *s;
    KeyBinding *kb, *kbtmp;
    s = (State *)n;
    kb = s -> keybinding;
    
    while(kb -> next != NULL)
    /* Go to the rear of the linked list */
        kb = kb -> next;
    
    if(kb -> key . key == -1)
    /* An empty item */
    {
        kb -> key . key = key . key;
        kb -> key . modifier = key . modifier;
        kb -> event = event;
    }
    else
    /* Create a new item to save it */
    {
        kbtmp = ALLOC(sizeof(KeyBinding));
        InitKeyBinding(kbtmp);
        kbtmp -> key . key = key . key;
        kbtmp -> key . modifier = key . modifier;
        kbtmp -> event = event;
        kb -> next = kbtmp;
    }
}

KeyboardState KBState(int key, int modifier)
/* Simply packaging a key binding into a KeyboardState struct */
{
    KeyboardState kb;
    kb . key = key;
    kb . modifier = modifier;
    return kb;
}

void CheckKeyBinding(void *n)
/* Check if matches a key binding */
{
    State *s;
    KeyBinding *kb;
    s = (State *)n;
    kb = s -> keybinding;
    while(kb -> event -> func != NULL)
    {
        if('A' <= kb -> key . key && kb -> key . key <= 'Z')
            kb -> key . key = s -> map . chs[kb -> key . key - 'A'];
        /* Fix for alphabets */
            
        if(((s -> keyboard . key & 0xFF00) == kb -> key . key) && (
            (kb -> key . modifier == NOMOD && 
			!(s -> keyboard . modifier & CTRL) && !(s -> keyboard . modifier & ALT))
            || (s -> keyboard . modifier & kb -> key . modifier)))
        /* Perfectly matched! */
            DoEvent(kb -> event, n);
            
        else if(s -> keyboard . key != -1)
        /* This is for debugging only */
            if(DEBUG)
                printf("%x|%x|%x\n", s -> keyboard . key & 0xFF00, 
                       s -> keyboard . key & 0xFF, s -> keyboard . modifier);
        if(kb -> next == NULL)
            break;
            
        kb = kb -> next;
    }
}

void LoadKeyMap(void *n)
/* Load A-Z Keymappings (Recorded manually by Felix Yan) */
{
    State *s;
    int chs[26]={0x1e00, 0x3000, 0x2e00, 0x2000, 0x1200, 0x2100, 0x2200, 0x2300, 0x1700,
                 0x2400, 0x2500, 0x2600, 0x3200, 0x3100, 0x1800, 0x1900, 0x1000, 0x1300,
                 0x1f00, 0x1400, 0x1600, 0x2f00, 0x1100, 0x2d00, 0x1500, 0x2c00};
    int num[10]={0x0b00, 0x0200, 0x0300, 0x0400, 0x0500, 0x0600, 0x0700, 0x0800, 0x0900,
                 0x0a00};
    int i;
    s = (State *)n;
    for(i = 0; i < 26; i ++)
        s -> map . chs[i] = chs[i];
    for(i = 0; i < 10; i ++)
        s -> nummap . num[i] = num[i];
    /* Save it to the main state */
}

void CheckChar(void *n, int key, int shift, int chipunc, int fullwidth, char *punc)
/* Check if a character should be inserted to text */
{
    State *s;
    s = (State *)n;
    if((s -> keyboard . key & 0xFF00) == key && (((s -> keyboard . modifier & LEFTSHIFT) ||
       (s -> keyboard . modifier & RIGHTSHIFT)) && shift || 
       !((s -> keyboard . modifier & LEFTSHIFT) || (s -> keyboard . modifier & RIGHTSHIFT)) && !shift) &&
       s -> chipunc == chipunc && s -> fullwidth == fullwidth
       && !(s -> keyboard . modifier & CTRL) && !(s -> keyboard . modifier & ALT))
    /* An ugly judgment to make sure key is correct */ 
    {
        Insert(n, punc);
        /* Insert the punc to text */
        
        s -> keyboard . key = -1;
        /* Clear the key */
    }
}

void CharInput(void *n)
/* Fetch & switch characters (Recorded manually by Felix Yan) */
{
    int i;
    
    char tmp[3] = {0};
    /* Temp string to save the characters that should be added to text */
    
    char lf[52] = {"£á£â£ã£ä£å£æ£ç£è£é£ê£ë£ì£í£î£ï£ð£ñ£ò£ó£ô£õ£ö£÷£ø£ù£ú"};
    char cf[52] = {"£Á£Â£Ã£Ä£Å£Æ£Ç£È£É£Ê£Ë£Ì£Í£Î£Ï£Ð£Ñ£Ò£Ó£Ô£Õ£Ö£×£Ø£Ù£Ú"};
    /* Lower-case and upper-case full-width letters */
    
    State *s;
    s = (State *)n;
    if(!s -> isedit || s -> ispinyin)
    /* Not editable or in pinyin input state */
		return;
        
    CheckChar(n, 0x3900, 0, 0, 1, "¡¡");
    CheckChar(n, 0x3900, 0, 1, 1, "¡¡");
    CheckChar(n, 0x3900, 0, 0, 0, " ");
    CheckChar(n, 0x3900, 0, 1, 0, " ");
    
    CheckChar(n, 0x200, 0, 0, 1, "£±");
    CheckChar(n, 0x200, 0, 1, 1, "£±");
    CheckChar(n, 0x200, 0, 0, 0, "1");
    CheckChar(n, 0x200, 0, 1, 0, "1");
    CheckChar(n, 0x200, 1, 0, 0, "!");
    CheckChar(n, 0x200, 1, 1, 0, "£¡");
    CheckChar(n, 0x200, 1, 1, 1, "£¡");
    CheckChar(n, 0x200, 1, 0, 1, "£¡");
    
    CheckChar(n, 0x300, 0, 0, 1, "£²");
    CheckChar(n, 0x300, 0, 1, 1, "£²");
    CheckChar(n, 0x300, 0, 0, 0, "2");
    CheckChar(n, 0x300, 0, 1, 0, "2");
    CheckChar(n, 0x300, 1, 0, 0, "@");
    CheckChar(n, 0x300, 1, 1, 0, "¡¤");
    CheckChar(n, 0x300, 1, 1, 1, "¡¤");
    CheckChar(n, 0x300, 1, 0, 1, "£À");
    
    CheckChar(n, 0x400, 0, 0, 1, "£³");
    CheckChar(n, 0x400, 0, 1, 1, "£³");
    CheckChar(n, 0x400, 0, 0, 0, "3");
    CheckChar(n, 0x400, 0, 1, 0, "3");
    CheckChar(n, 0x400, 1, 0, 0, "#");
    CheckChar(n, 0x400, 1, 1, 0, "#");
    CheckChar(n, 0x400, 1, 0, 1, "££");
    CheckChar(n, 0x400, 1, 1, 1, "££");
    
    CheckChar(n, 0x500, 0, 0, 1, "£´");
    CheckChar(n, 0x500, 0, 1, 1, "£´");
    CheckChar(n, 0x500, 0, 0, 0, "4");
    CheckChar(n, 0x500, 0, 1, 0, "4");
    CheckChar(n, 0x500, 1, 0, 0, "$");
    CheckChar(n, 0x500, 1, 1, 0, "£¤");
    CheckChar(n, 0x500, 1, 0, 1, "¡ç");
    CheckChar(n, 0x500, 1, 1, 1, "£¤");
    
    CheckChar(n, 0x600, 0, 0, 1, "£µ");
    CheckChar(n, 0x600, 0, 1, 1, "£µ");
    CheckChar(n, 0x600, 0, 0, 0, "5");
    CheckChar(n, 0x600, 0, 1, 0, "5");
    CheckChar(n, 0x600, 1, 0, 0, "%");
    CheckChar(n, 0x600, 1, 1, 0, "%");
    CheckChar(n, 0x600, 1, 0, 1, "£¥");
    CheckChar(n, 0x600, 1, 1, 1, "£¥");
    
    CheckChar(n, 0x700, 0, 0, 1, "£¶");
    CheckChar(n, 0x700, 0, 1, 1, "£¶");
    CheckChar(n, 0x700, 0, 0, 0, "6");
    CheckChar(n, 0x700, 0, 1, 0, "6");
    CheckChar(n, 0x700, 1, 0, 0, "^");
    CheckChar(n, 0x700, 1, 1, 0, "¡­¡­");
    CheckChar(n, 0x700, 1, 0, 1, "£Þ");
    CheckChar(n, 0x700, 1, 1, 1, "¡­¡­");
    
    CheckChar(n, 0x800, 0, 0, 1, "£·");
    CheckChar(n, 0x800, 0, 1, 1, "£·");
    CheckChar(n, 0x800, 0, 0, 0, "7");
    CheckChar(n, 0x800, 0, 1, 0, "7");
    CheckChar(n, 0x800, 1, 0, 0, "&");
    CheckChar(n, 0x800, 1, 1, 0, "&");
    CheckChar(n, 0x800, 1, 0, 1, "£¦");
    CheckChar(n, 0x800, 1, 1, 1, "£¦");
    
    CheckChar(n, 0x900, 0, 0, 1, "£¸");
    CheckChar(n, 0x900, 0, 1, 1, "£¸");
    CheckChar(n, 0x900, 0, 0, 0, "8");
    CheckChar(n, 0x900, 0, 1, 0, "8");
    CheckChar(n, 0x900, 1, 0, 0, "*");
    CheckChar(n, 0x900, 1, 1, 0, "*");
    CheckChar(n, 0x900, 1, 0, 1, "£ª");
    CheckChar(n, 0x900, 1, 1, 1, "£ª");
    
    CheckChar(n, 0xa00, 0, 0, 1, "£¹");
    CheckChar(n, 0xa00, 0, 1, 1, "£¹");
    CheckChar(n, 0xa00, 0, 0, 0, "9");
    CheckChar(n, 0xa00, 0, 1, 0, "9");
    CheckChar(n, 0xa00, 1, 0, 0, "(");
    CheckChar(n, 0xa00, 1, 1, 0, "£¨");
    CheckChar(n, 0xa00, 1, 0, 1, "£¨");
    CheckChar(n, 0xa00, 1, 1, 1, "£¨");
    
    CheckChar(n, 0xb00, 0, 0, 1, "£°");
    CheckChar(n, 0xb00, 0, 1, 1, "£°");
    CheckChar(n, 0xb00, 0, 0, 0, "0");
    CheckChar(n, 0xb00, 0, 1, 0, "0");
    CheckChar(n, 0xb00, 1, 0, 0, ")");
    CheckChar(n, 0xb00, 1, 1, 0, "£©");
    CheckChar(n, 0xb00, 1, 0, 1, "£©");
    CheckChar(n, 0xb00, 1, 1, 1, "£©");
    
    CheckChar(n, 0xc00, 0, 0, 0, "-");
    CheckChar(n, 0xc00, 0, 0, 1, "£­");
    CheckChar(n, 0xc00, 0, 1, 0, "-");
    CheckChar(n, 0xc00, 0, 1, 1, "£­");
    CheckChar(n, 0xc00, 1, 0, 0, "_");
    CheckChar(n, 0xc00, 1, 0, 1, "£ß");
    CheckChar(n, 0xc00, 1, 1, 0, "¡ª¡ª");
    CheckChar(n, 0xc00, 1, 1, 1, "¡ª¡ª");
    
    CheckChar(n, 0xd00, 0, 0, 0, "=");
    CheckChar(n, 0xd00, 0, 0, 1, "=");
    CheckChar(n, 0xd00, 0, 1, 0, "£½");
    CheckChar(n, 0xd00, 0, 1, 1, "£½");
    CheckChar(n, 0xd00, 1, 0, 0, "+");
    CheckChar(n, 0xd00, 1, 0, 1, "£«");
    CheckChar(n, 0xd00, 1, 1, 0, "+");
    CheckChar(n, 0xd00, 1, 1, 1, "£«");
    
    CheckChar(n, 0x2900, 0, 0, 0, "`");
    CheckChar(n, 0x2900, 0, 0, 1, "£à");
    CheckChar(n, 0x2900, 0, 1, 0, "`");
    CheckChar(n, 0x2900, 0, 1, 1, "£à");
    CheckChar(n, 0x2900, 1, 0, 0, "~");
    CheckChar(n, 0x2900, 1, 0, 1, "¡«");
    CheckChar(n, 0x2900, 1, 1, 0, "¡«");
    CheckChar(n, 0x2900, 1, 1, 1, "¡«");
    
    CheckChar(n, 0x1a00, 0, 0, 0, "[");
    CheckChar(n, 0x1a00, 0, 0, 1, "£Û");
    CheckChar(n, 0x1a00, 0, 1, 0, "£Û");
    CheckChar(n, 0x1a00, 0, 1, 1, "£Û");
    CheckChar(n, 0x1a00, 1, 0, 0, "{");
    CheckChar(n, 0x1a00, 1, 0, 1, "£û");
    CheckChar(n, 0x1a00, 1, 1, 0, "£û");
    CheckChar(n, 0x1a00, 1, 1, 1, "£û");
    
    CheckChar(n, 0x1b00, 0, 0, 0, "]");
    CheckChar(n, 0x1b00, 0, 0, 1, "£Ý");
    CheckChar(n, 0x1b00, 0, 1, 0, "£Ý");
    CheckChar(n, 0x1b00, 0, 1, 1, "£Ý");
    CheckChar(n, 0x1b00, 1, 0, 0, "}");
    CheckChar(n, 0x1b00, 1, 0, 1, "£ý");
    CheckChar(n, 0x1b00, 1, 1, 0, "£ý");
    CheckChar(n, 0x1b00, 1, 1, 1, "£ý");
    
    CheckChar(n, 0x2b00, 0, 0, 0, "\\");
    CheckChar(n, 0x2b00, 0, 0, 1, "£Ü");
    CheckChar(n, 0x2b00, 0, 1, 0, "¡¢");
    CheckChar(n, 0x2b00, 0, 1, 1, "¡¢");
    CheckChar(n, 0x2b00, 1, 0, 0, "|");
    CheckChar(n, 0x2b00, 1, 0, 1, "£ü");
    CheckChar(n, 0x2b00, 1, 1, 0, "|");
    CheckChar(n, 0x2b00, 1, 1, 1, "£ü");
    
    CheckChar(n, 0x2700, 0, 0, 0, ";");
    CheckChar(n, 0x2700, 0, 0, 1, "£»");
    CheckChar(n, 0x2700, 0, 1, 0, "£»");
    CheckChar(n, 0x2700, 0, 1, 1, "£»");
    CheckChar(n, 0x2700, 1, 0, 0, ":");
    CheckChar(n, 0x2700, 1, 0, 1, "£º");
    CheckChar(n, 0x2700, 1, 1, 0, "£º");
    CheckChar(n, 0x2700, 1, 1, 1, "£º");
    
    CheckChar(n, 0x2800, 0, 0, 0, "'");
    CheckChar(n, 0x2800, 0, 0, 1, "£§");
    CheckChar(n, 0x2800, 0, 1, 0, "£§");
    CheckChar(n, 0x2800, 0, 1, 1, "£§");
    CheckChar(n, 0x2800, 1, 0, 0, "\"");
    CheckChar(n, 0x2800, 1, 0, 1, "£¢");
    CheckChar(n, 0x2800, 1, 1, 0, "£¢");
    CheckChar(n, 0x2800, 1, 1, 1, "£¢");
    
    CheckChar(n, 0x3300, 0, 0, 0, ",");
    CheckChar(n, 0x3300, 0, 0, 1, "£¬");
    CheckChar(n, 0x3300, 0, 1, 0, "£¬");
    CheckChar(n, 0x3300, 0, 1, 1, "£¬");
    CheckChar(n, 0x3300, 1, 0, 0, "<");
    CheckChar(n, 0x3300, 1, 0, 1, "£¼");
    CheckChar(n, 0x3300, 1, 1, 0, "¡¶");
    CheckChar(n, 0x3300, 1, 1, 1, "¡¶");
    
    CheckChar(n, 0x3400, 0, 0, 0, ".");
    CheckChar(n, 0x3400, 0, 0, 1, "£®");
    tmp[0] = LeftChar(n);
    if('0' <= tmp[0] && tmp[0] <= '9')
        CheckChar(n, 0x3400, 0, 1, 0, ".");
    else
        CheckChar(n, 0x3400, 0, 1, 0, "¡£");
    CheckChar(n, 0x3400, 0, 1, 1, "¡£");
    CheckChar(n, 0x3400, 1, 0, 0, ">");
    CheckChar(n, 0x3400, 1, 0, 1, "£¾");
    CheckChar(n, 0x3400, 1, 1, 0, "¡·");
    CheckChar(n, 0x3400, 1, 1, 1, "¡·");
    
    CheckChar(n, 0x3500, 0, 0, 0, "/");
    CheckChar(n, 0x3500, 0, 0, 1, "£¯");
    CheckChar(n, 0x3500, 0, 1, 0, "¡¢");
    CheckChar(n, 0x3500, 0, 1, 1, "¡¢");
    CheckChar(n, 0x3500, 1, 0, 0, "?");
    CheckChar(n, 0x3500, 1, 0, 1, "£¿");
    CheckChar(n, 0x3500, 1, 1, 0, "£¿");
    CheckChar(n, 0x3500, 1, 1, 1, "£¿");
    
    for(i = 0; i < 26; i ++)
    /* Check letters */
    {
        tmp[1] = 0;
        
        if(!s -> chinese)
        {
            tmp[0] = 'a' + i;
            CheckChar(n, s -> map . chs[i], 0, 0, 0, tmp);
            CheckChar(n, s -> map . chs[i], 0, 1, 0, tmp);
            
            tmp[0] = lf[i * 2];
            tmp[1] = lf[i * 2 + 1];
            CheckChar(n, s -> map . chs[i], 0, 0, 1, tmp);
            CheckChar(n, s -> map . chs[i], 0, 1, 1, tmp);
        }
        
        tmp[1] = 0;
        
        tmp[0] = 'A' + i;
        CheckChar(n, s -> map . chs[i], 1, 0, 0, tmp);
        CheckChar(n, s -> map . chs[i], 1, 1, 0, tmp);
        
        tmp[0] = cf[i * 2];
        tmp[1] = cf[i * 2 + 1];
        CheckChar(n, s -> map . chs[i], 1, 0, 1, tmp);
        CheckChar(n, s -> map . chs[i], 1, 1, 1, tmp);
    }
}
