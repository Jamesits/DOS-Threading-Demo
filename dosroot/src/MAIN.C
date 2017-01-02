#include "common.h"
#include "logo.h"
#include "event.h"
#include "file.h"
#include "menu.h"
#include "mouse.h"
#include "ui.h"
#include "han.h"
#include "pinyin.h"
#include "edit.h"
#include "music.h"
#include "keyboard.h"
#include "dialog.h"

void MainLoop(void);

int main(void)
{
    MainLoop();
    return 0;
}

void InitAllKeyBinding(void *n)
/* Initialize Keybindings */
{
    Event *func;
    
    func = ALLOC(sizeof(Event));
    InitEvent(func);
    RegEvent(func, &Exit);
    AddKeyBinding(n, KBState(ESC, NOMOD), func);
    
    func = ALLOC(sizeof(Event));
    InitEvent(func);
    RegEvent(func, &ClearGraph);
    RegEvent(func, &DrawLogo);
    RegEvent(func, &Exit);
    AddKeyBinding(n, KBState(F7, NOMOD), func);
    
    func = ALLOC(sizeof(Event));
    InitEvent(func);
    RegEvent(func, &OpenMenu0);
    AddKeyBinding(n, KBState(F1, NOMOD), func);
    
    func = ALLOC(sizeof(Event));
    InitEvent(func);
    RegEvent(func, &OpenMenu1);
    AddKeyBinding(n, KBState(F2, NOMOD), func);
    
    func = ALLOC(sizeof(Event));
    InitEvent(func);
    RegEvent(func, &OpenMenu2);
    AddKeyBinding(n, KBState(F3, NOMOD), func);
    
    func = ALLOC(sizeof(Event));
    InitEvent(func);
    RegEvent(func, &OpenMenu3);
    AddKeyBinding(n, KBState(F4, NOMOD), func);
    
    func = ALLOC(sizeof(Event));
    InitEvent(func);
    RegEvent(func, &OpenMenu4);
    AddKeyBinding(n, KBState(F5, NOMOD), func);
    
    func = ALLOC(sizeof(Event));
    InitEvent(func);
    RegEvent(func, &MenuUp);
    RegEvent(func, &CursorUp);
    AddKeyBinding(n, KBState(UP, NOMOD), func);
    
    func = ALLOC(sizeof(Event));
    InitEvent(func);
    RegEvent(func, &MenuDown);
    RegEvent(func, &CursorDown);
    AddKeyBinding(n, KBState(DOWN, NOMOD), func);
    
    func = ALLOC(sizeof(Event));
    InitEvent(func);
    RegEvent(func, &FormMenuLeft);
    RegEvent(func, &CursorLeft);
    AddKeyBinding(n, KBState(LEFT, NOMOD), func);
    
    func = ALLOC(sizeof(Event));
    InitEvent(func);
    RegEvent(func, &FormMenuRight);
    RegEvent(func, &CursorRight);
    AddKeyBinding(n, KBState(RIGHT, NOMOD), func);
    
    func = ALLOC(sizeof(Event));
    InitEvent(func);
    RegEvent(func, &IMSwitch);
    AddKeyBinding(n, KBState(SPACE, CTRL), func);
    
    func = ALLOC(sizeof(Event));
    InitEvent(func);
    RegEvent(func, &WidthSwitch);
    AddKeyBinding(n, KBState(SPACE, LEFTSHIFT), func);
    
    func = ALLOC(sizeof(Event));
    InitEvent(func);
    RegEvent(func, &PuncSwitch);
    AddKeyBinding(n, KBState('P', CTRL), func);
    
    func = ALLOC(sizeof(Event));
    InitEvent(func);
    RegEvent(func, &DrawOpenWindow);
    AddKeyBinding(n, KBState('O', CTRL), func);
    
    func = ALLOC(sizeof(Event));
    InitEvent(func);
    RegEvent(func, &DrawSaveWindow);
    AddKeyBinding(n, KBState('S', CTRL), func);
    
    func = ALLOC(sizeof(Event));
    InitEvent(func);
    RegEvent(func, &DrawFindWindow);
    AddKeyBinding(n, KBState('F', CTRL), func);
    
    func = ALLOC(sizeof(Event));
    InitEvent(func);
    RegEvent(func, &DrawReplaceWindow);
    AddKeyBinding(n, KBState('H', CTRL), func);
    
    func = ALLOC(sizeof(Event));
    InitEvent(func);
    RegEvent(func, &BackSpace);
    AddKeyBinding(n, KBState(BACKSPACE, NOMOD), func);
    
    func = ALLOC(sizeof(Event));
    InitEvent(func);
    RegEvent(func, &Delete);
    AddKeyBinding(n, KBState(DELETE, NOMOD), func);
    
    func = ALLOC(sizeof(Event));
    InitEvent(func);
    RegEvent(func, &EnterKey);
    AddKeyBinding(n, KBState(ENTER, NOMOD), func);
    
    func = ALLOC(sizeof(Event));
    InitEvent(func);
    RegEvent(func, &Home);
    AddKeyBinding(n, KBState(HOME, NOMOD), func);
    
    func = ALLOC(sizeof(Event));
    InitEvent(func);
    RegEvent(func, &CtrlHome);
    AddKeyBinding(n, KBState(HOME, CTRL), func);
    
    func = ALLOC(sizeof(Event));
    InitEvent(func);
    RegEvent(func, &End);
    AddKeyBinding(n, KBState(END, NOMOD), func);
    
    func = ALLOC(sizeof(Event));
    InitEvent(func);
    RegEvent(func, &CtrlEnd);
    AddKeyBinding(n, KBState(END, CTRL), func);
    
    func = ALLOC(sizeof(Event));
    InitEvent(func);
    RegEvent(func, &CheckEnterSubmit);
    AddKeyBinding(n, KBState(ENTER, NOMOD), func);
    
    func = ALLOC(sizeof(Event));
    InitEvent(func);
    RegEvent(func, &SwitchTextBox);
    AddKeyBinding(n, KBState(TAB, NOMOD), func);
    
    func = ALLOC(sizeof(Event));
    InitEvent(func);
    RegEvent(func, &CancelButton);
    AddKeyBinding(n, KBState('C', ALT), func);
    
    func = ALLOC(sizeof(Event));
    InitEvent(func);
    RegEvent(func, &OpenButton);
    AddKeyBinding(n, KBState('O', ALT), func);
}

void InitFormMenu(void *n)
/* Initialize form menus */
{
    FormMenu *formmenu;
    Menu *menu, *contextmenu;
    State *s;
    Event *func;
    s = (State *)n;
    formmenu = ALLOC(sizeof(FormMenu));
    InitFormMenuItem(formmenu);
    
    AddFormMenu(formmenu, "文件(F1)");
        menu = ALLOC(sizeof(Menu));
        InitMenuItem(menu);
        AddMenuToFormMenu(menu, formmenu);
        
        func = ALLOC(sizeof(Event));
        InitEvent(func);
        RegEvent(func, &NewFile);
        AddMenu(menu, 1, "新建(N)      Ctrl+N", func);
            
        func = ALLOC(sizeof(Event));
        InitEvent(func);
        RegEvent(func, &DrawOpenWindow);
        AddMenu(menu, 1, "打开(O)...   Ctrl+O", func);
        
        func = ALLOC(sizeof(Event));
        InitEvent(func);
        RegEvent(func, &DrawSaveWindow);
        AddMenu(menu, 1, "保存(S)      Ctrl+S", func);
        
        func = ALLOC(sizeof(Event));
        InitEvent(func);
        RegEvent(func, &DrawSaveAsWindow);
        AddMenu(menu, 1, "另存为...", func);
        
        func = ALLOC(sizeof(Event));
        InitEvent(func);
        RegEvent(func, &DoNothing);
        AddMenu(menu, 0, "-", func);
        
        func = ALLOC(sizeof(Event));
        InitEvent(func);
        RegEvent(func, &Exit);
        AddMenu(menu, 1, "退出(Q)      Esc", func);
        
    AddFormMenu(formmenu, "编辑(F2)");
        menu = ALLOC(sizeof(Menu));
        InitMenuItem(menu);
        AddMenuToFormMenu(menu, formmenu);
        
        func = ALLOC(sizeof(Event));
        InitEvent(func);
        RegEvent(func, &DoNothing);
        AddMenu(menu, 0, "撤销(U)      Ctrl+Z", func);
        
        func = ALLOC(sizeof(Event));
        InitEvent(func);
        RegEvent(func, &DoNothing);
        AddMenu(menu, 0, "-", func);
        
        func = ALLOC(sizeof(Event));
        InitEvent(func);
        RegEvent(func, &DoNothing);
        AddMenu(menu, 0, "剪切(T)      Ctrl+X", func);
        
        func = ALLOC(sizeof(Event));
        InitEvent(func);
        RegEvent(func, &DoNothing);
        AddMenu(menu, 0, "复制(C)      Ctrl+C", func);
        
        func = ALLOC(sizeof(Event));
        InitEvent(func);
        RegEvent(func, &DoNothing);
        AddMenu(menu, 0, "粘贴(P)      Ctrl+V", func);
        
        func = ALLOC(sizeof(Event));
        InitEvent(func);
        RegEvent(func, &DoNothing);
        AddMenu(menu, 0, "删除(L)      Del", func);
        
        func = ALLOC(sizeof(Event));
        InitEvent(func);
        RegEvent(func, &DoNothing);
        AddMenu(menu, 0, "-", func);
        
        func = ALLOC(sizeof(Event));
        InitEvent(func);
        RegEvent(func, &DrawFindWindow);
        AddMenu(menu, 1, "查找(F)...   Ctrl+F", func);
        
        func = ALLOC(sizeof(Event));
        InitEvent(func);
        RegEvent(func, &DoNothing);
        AddMenu(menu, 0, "查找下一个   F6", func);
        
        func = ALLOC(sizeof(Event));
        InitEvent(func);
        RegEvent(func, &DrawReplaceWindow);
        AddMenu(menu, 1, "替换(R)...   Ctrl+H", func);
        
        func = ALLOC(sizeof(Event));
        InitEvent(func);
        RegEvent(func, &DoNothing);
        AddMenu(menu, 0, "-", func);
        
        func = ALLOC(sizeof(Event));
        InitEvent(func);
        RegEvent(func, &DoNothing);
        AddMenu(menu, 1, "全选(A)      Ctrl+A", func);
        
    AddFormMenu(formmenu, "选项(F3)");
        menu = ALLOC(sizeof(Menu));
        InitMenuItem(menu);
        AddMenuToFormMenu(menu, formmenu);
        
        func = ALLOC(sizeof(Event));
        InitEvent(func);
        RegEvent(func, &ChangeDotted);
        AddMenu(menu, 3 - s -> dotted, "平滑拖动", func);
        
        func = ALLOC(sizeof(Event));
        InitEvent(func);
        RegEvent(func, &ChangeHighlight);
        AddMenu(menu, 2 + s -> highlight, "代码高亮", func);
        
        func = ALLOC(sizeof(Event));
        InitEvent(func);
        RegEvent(func, &DoNothing);
        AddMenu(menu, 5, "自动换行", func);
        
    /*AddFormMenu(formmenu, "格式(F3)");
        menu = ALLOC(sizeof(Menu));
        InitMenuItem(menu);
        AddMenuToFormMenu(menu, formmenu);
        
        func = ALLOC(sizeof(Event));
        InitEvent(func);
        RegEvent(func, &DoNothing);
        AddMenu(menu, 1, "字体(F)...", func);*/
    
    AddFormMenu(formmenu, "工具(F4)");
        menu = ALLOC(sizeof(Menu));
        InitMenuItem(menu);
        AddMenuToFormMenu(menu, formmenu);
        
        func = ALLOC(sizeof(Event));
        InitEvent(func);
        RegEvent(func, &RandomMusic);
        AddMenu(menu, 1, "音乐(M)...", func);
        
    AddFormMenu(formmenu, "帮助(F5)");
        menu = ALLOC(sizeof(Menu));
        InitMenuItem(menu);
        AddMenuToFormMenu(menu, formmenu);
        
        func = ALLOC(sizeof(Event));
        InitEvent(func);
        RegEvent(func, &ShowHelp);
        AddMenu(menu, 1, "帮助(H)...", func);
        
        func = ALLOC(sizeof(Event));
        InitEvent(func);
        RegEvent(func, &DoNothing);
        AddMenu(menu, 0, "-", func);
        
        func = ALLOC(sizeof(Event));
        InitEvent(func);
        RegEvent(func, &ClearGraph);
        RegEvent(func, &DrawLogo);
        RegEvent(func, &DrawMainWindow);
        RegEvent(func, &DrawFormMenu);
        RegEvent(func, &DrawMainTextBox);
        RegEvent(func, &DrawStatusBox);
        AddMenu(menu, 1, "关于(A)...", func);
    
    contextmenu = ALLOC(sizeof(Menu));
    InitMenuItem(contextmenu);
    
    func = ALLOC(sizeof(Event));
    InitEvent(func);
    RegEvent(func, &Exit);
    AddMenu(contextmenu, 1, "关闭(C)", func);
    
    s -> menu = formmenu;
    s -> contextmenu = contextmenu;
}

void InitStatus(void *n)
/* Initialize the main state */
{
    State *s;
    s = (State *)n;
    
    s -> isexit = 0;
    s -> isclearmenu = 0;
    s -> isdrag = 0;
    s -> ischildwindow = 0;
    s -> dotted = 1;
    s -> highlight = 0;
    s -> isedit = 1;
    s -> iscontextmenu = 0;
    s -> page = 0;
    s -> chinese = 0;
    s -> chipunc = 0;
    s -> fullwidth = 0;
    s -> filehead = NULL;
    s -> childhead = NULL;
    s -> iscursor = 0;
    s -> cursortime = -1;
    s -> currentcolumn = 1;
    s -> currentrow = 1;
    s -> pagemovecount = 0;
    s -> mousetype = 1;
    s -> isput = 0;
    s -> ispinyin = 0;
    s -> pinyinpage = 0;
    s -> sheng = 0;
    s -> yun = 0;
    s -> filename = (char *)ALLOC(20 * sizeof(char));
    
    srand(time(0));
}
    
void MainLoop(void)
/* The main loop, everything is here! */
{
    Event *OnLoad, *OnUnload, *OnMainLoop, *Redraw;
    /* The main loop events */
    
    State *s;
    
    s = (State *)ALLOC(sizeof(State));
    OnLoad = ALLOC(sizeof(Event));
    OnMainLoop = ALLOC(sizeof(Event));
    OnUnload = ALLOC(sizeof(Event));
    Redraw = ALLOC(sizeof(Event));

    InitEvent(OnLoad);
    InitEvent(OnMainLoop);
    InitEvent(OnUnload);
    InitEvent(Redraw);

    /* Add customed functions here to register events
     * Example:
     *     RegEvent(&OnLoad, &custom_function);        */
    
    RegEvent(OnLoad, &InitStatus);
    RegEvent(OnLoad, &InitGraph);
    RegEvent(OnLoad, &StartupMusic);
    RegEvent(OnLoad, &CalcDelay);
    RegEvent(OnLoad, &InitColor);
    RegEvent(OnLoad, &OpenHZK);
    RegEvent(OnLoad, &NewFile);
    RegEvent(OnLoad, &LoadKeyMap);
    RegEvent(OnLoad, &LoadKeyBinding);
    RegEvent(OnLoad, &InitAllKeyBinding);
    RegEvent(OnLoad, &DrawMainWindow);
    RegEvent(OnLoad, &DrawMainTextBox);
    RegEvent(OnLoad, &InitFormMenu);
    RegEvent(OnLoad, &DrawFormMenu);
    RegEvent(OnLoad, &DrawStatusBox);
    RegEvent(OnLoad, &LoadMouse);
    RegEvent(OnLoad, &FadingColor);
    
    RegEvent(OnMainLoop, &PlayMusic);
    RegEvent(OnMainLoop, &CheckKeyboard);
    RegEvent(OnMainLoop, &CheckKeyBinding);
    RegEvent(OnMainLoop, &CharInput);
    RegEvent(OnMainLoop, &PinyinInput);
    RegEvent(OnMainLoop, &PinyinShow);
    RegEvent(OnMainLoop, &RedrawMouse);
    RegEvent(OnMainLoop, &IsMoveOverMenu);
    RegEvent(OnMainLoop, &DrawMoveOverMenu);
    RegEvent(OnMainLoop, &ChildTitleContextMenu);
    RegEvent(OnMainLoop, &IsClickFormMenu);
    RegEvent(OnMainLoop, &IsMoveOverFormMenu);
    RegEvent(OnMainLoop, &DrawMoveOverFormMenu);
    RegEvent(OnMainLoop, &DrawClickFormMenu);
    RegEvent(OnMainLoop, &MoveChildWindow);
    RegEvent(OnMainLoop, &CheckChildButton);
    RegEvent(OnMainLoop, &CheckIMSwitch);
    RegEvent(OnMainLoop, &CheckStatus);
    RegEvent(OnMainLoop, &GetCurPos);
    RegEvent(OnMainLoop, &FlashCur);
    RegEvent(OnMainLoop, &MousetoCursor);
    RegEvent(OnMainLoop, &IsExit);
    
    RegEvent(OnUnload, &LogoutMusic);
    RegEvent(OnUnload, &CloseHZK);
    RegEvent(OnUnload, &FadingColor);

    //RegEvent(Redraw, &DrawMainWindow);
    RegEvent(Redraw, &DrawFormMenu);
    RegEvent(Redraw, &DrawMainTextBox);
    RegEvent(Redraw, &ClearMenuMoveOver);
    
    s -> redraw = Redraw;
    
    DoEvent(OnLoad, (void *)s);

    while(!s -> isexit)
        DoEvent(OnMainLoop, (void *)s);
    
    DoEvent(OnUnload, (void *)s);
    
    FreeEvent(OnLoad);
    FreeEvent(OnUnload);
    FreeEvent(OnMainLoop);
    FreeEvent(Redraw);
    FREEMEMRow(s -> filehead);
        
    closegraph();
    
    while(1)
        PlayMusic((void *)s);
}
