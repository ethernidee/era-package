#include "homm3.h"

_Fnt_* bigfont2;
_Fnt_* medfont2;
_Fnt_* smalfont2;

/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////

// глобальная переменная для функции изменения
// и запоминания параметров курсора мыши
int saveCursor[3];

void Y_Mouse_SetCursor(int type) // type: 0 = стандартный курсор, 1 = вернуть сохранённый курсор
{
    if (!type) { // сохранить данные о текущем курсоре и сделать стандартный курсор 
        saveCursor[2] = WOG_DisableMouse;
        WOG_DisableMouse = 0; // отключаем воговский блок изменения кадров курсора
        // запоминаем кадр курсора мыши
        saveCursor[0] = o_MouseMgr->Field<_int_>(+0x4C); // type
        saveCursor[1] = o_MouseMgr->Field<_int_>(+0x50); // frame
        b_MouseMgr_SetCursor(0,0);
        CALL_2(void*, __thiscall, 0x50D7B0, o_MouseMgr, 0);
    } else {  // вернуть сохранённый курсор
        b_MouseMgr_SetCursor(saveCursor[1], saveCursor[0]);
        WOG_DisableMouse = saveCursor[2];
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////

// Создаём стандартный задник с рамкой цвета игрока
int Set_DlgBackground_RK(_Dlg_* dlg, int status_bar, int color)
{
    //dlg->AddItem(_DlgStaticPcx8_::Create(0, 0, min(dlg->width,256), min(dlg->height,256), 0, "DiBoxBck.pcx"));
    
    int current_x, remaining_x, current_y, remaining_y, horizontal_row;

    current_x = 0;
    remaining_x = dlg->width;
    current_y = 0;
    remaining_y = dlg->height;
    horizontal_row = 0;

    if (remaining_x < 64 || remaining_y < 64)
        return 0;

    while (TRUE) {
        while (TRUE) { // do horizontal pass first
            if (remaining_x > 0) {
                dlg->AddItem(_DlgStaticPcx8_::Create(current_x, horizontal_row * 256, min(remaining_x, 256), min(remaining_y, 256), 0, "DiBoxBck.pcx"));
                current_x = current_x + 256;
                remaining_x = remaining_x - 256;
            }
            else break;
        }        
        current_x = 0;        // reset x position to 0
        remaining_x = dlg->width; // reset length of horizontal line
        remaining_y = remaining_y - 256; // update remaining y since we're done with horizontal pass
        horizontal_row = horizontal_row + 1;    // we might be working on a new row soon if condition below is met
        if (remaining_y <= 0)
            break;        // no more rows to add
    }

    int top_left = 0;
    int top_right = 1;
    int bottom_left = 2;
    int bottom_right = 3;
    int left_middle = 4;
    int right_middle = 5;
    int top_middle = 6;
    int bottom_middle = 7;

    if (status_bar) {
        bottom_left = 8;
        bottom_right = 9;
        bottom_middle = 10;
    }

    // add horizontal borders
    current_x = 0;
    remaining_x = dlg->width;
    while (remaining_x >= 64) {
        dlg->AddItem(_DlgStaticDef_::Create(current_x, 0, 0, "dialgbox.def", top_middle, 0, 0));
        dlg->AddItem(_DlgStaticDef_::Create(current_x, dlg->height - 64, 0, "dialgbox.def", bottom_middle, 0, 0));
        current_x += 64;
        remaining_x -= 64;
    }

    // add vertical borders (fixed!)
    current_y = 0;
    remaining_y = dlg->height;
    if (status_bar)
        remaining_y -= 26;
    while (remaining_y >= 64) {
        dlg->AddItem(_DlgStaticDef_::Create(0, current_y, 0, "dialgbox.def", left_middle, 0, 0));
        dlg->AddItem(_DlgStaticDef_::Create(dlg->width - 64, current_y, 0, "dialgbox.def", right_middle, 0, 0));
        current_y += 64;
        remaining_y -= 64;
    }

    if (status_bar){
        dlg->AddItem(_DlgStaticDef_::Create(0, dlg->height -26 -64, 0, "dialgbox.def", left_middle, 0, 0));
        dlg->AddItem(_DlgStaticDef_::Create(dlg->width - 64, dlg->height -26 -64, 0, "dialgbox.def", right_middle, 0, 0));
    }

    // add color this player
    if (color < 0 || color > 7){
        color = o_GameMgr->GetMeID();
    }
    CALL_5 (int, __thiscall, 0x5FF400, dlg, 512, 13, 0, color);

    // add four corners
    dlg->AddItem(_DlgStaticDef_::Create(0, 0, 0, "dialgbox.def", top_left, 0, 0));
    dlg->AddItem(_DlgStaticDef_::Create(0, dlg->height - 64, 0, "dialgbox.def", bottom_left, 0, 0));
    dlg->AddItem(_DlgStaticDef_::Create(dlg->width - 64, 0, 0, "dialgbox.def", top_right, 0, 0));
    dlg->AddItem(_DlgStaticDef_::Create(dlg->width - 64, dlg->height - 64, 0, "dialgbox.def", bottom_right, 0, 0));
    return 1;
}

// создание кастомного диалога: _CustomDlg_* dlg = _CustomDlg_Create(x, y, width, height, statusBar, color);
_CustomDlg_* CustomDlg_Create(int x, int y, int width, int height, int isStatusBar = false, int color = -1)
{
    _CustomDlg_* dlg = _CustomDlg_::Create(x, y, width, height, DF_SCREENSHOT | DF_SHADOW, NULL);
    if (color < 0 || color > 7) { color = o_GameMgr->GetMeID(); }
    Set_DlgBackground_RK(dlg, isStatusBar, color);
    return dlg;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////


void Set_DlgStdBackground(_CustomDlg_* dlg)
{
    CALL_5 (int, __thiscall, 0x48FA80, dlg, dlg->x, dlg->y, dlg->width, dlg->height);

    for (int i = (int)dlg->field_4C; i <= (int)dlg->field_50; ++i)
    {
        CALL_5 (int, __thiscall, 0x5FF400, dlg, 512, 13, i, o_GameMgr->GetMeID());
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////


int Dlg_SetBackgroundWithHDFrame(_Dlg_* dlg, int x, int y, int width, int height, int id, char* pcx8_name)
{
    int current_x, remaining_x, current_y, remaining_y, horizontal_row;

    current_x = x;
    remaining_x = width;
    current_y = y;
    remaining_y = height;
    horizontal_row = 0;

    if (remaining_x < 32 || remaining_y < 32)
        return 0;


    while (TRUE) {
        while (TRUE) { // do horizontal pass first
            if (remaining_x > x) {
                dlg->AddItem(_DlgStaticPcx8_::Create(current_x, y + horizontal_row * 256, min(remaining_x, 256), min(remaining_y, 256), id, pcx8_name));
                current_x = current_x + 256;
                remaining_x = remaining_x - 256;
            }
            else break;
        }        
        current_x = x;        // reset x position to 0
        remaining_x = width;  // reset length of horizontal line
        remaining_y = remaining_y - 256; // update remaining y since we're done with horizontal pass
        horizontal_row = horizontal_row + 1;    // we might be working on a new row soon if condition below is met
        if (remaining_y <= y)
            break;        // no more rows to add
    }
    
    // создаём рамкку HD
     _Pcx8_* frame = CreateSimpleFrame(width, height);
     _DlgStaticPcx8_* myPcx8 = _DlgStaticPcx8_::Create(x, y, width, height, id+1, pcx8_name );
     _Pcx8_* old = myPcx8->pcx8;
     myPcx8->pcx8 = frame;
     old->ref_count--;
     dlg->AddItem(myPcx8);

    return 1;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////


// показ сообщения по ПКМ c одним дефом
void b_MsgBoxAndDef(char* def_name, int def_frame, char* text)
{
    int str_len = strlen(text);
    int vx = str_len * 6;
    int vy = 16;

    while ( vx > (vy * 4) ) {
        vx = vx >> 1;   // делим на 2
        vy = vy * 2;    // умножаем на 2
    } 

    if (vx < 280) vx = 280;
    int lines = medfont2->GetLinesCountInText(text, vx);
    vy = (lines +1) *16;

    // if (vy < 100) vx = 320;
    if (vy > 220 || lines > 5) {
        vx = 440;
        lines = medfont2->GetLinesCountInText(text, vx);
        vy = (lines +1) *16;
    }

    if (vy < 20) vy = 20;   

    _Def_* def = _Def_::Load(def_name);
    int def_h = def->height;
    def->DerefOrDestruct(); 
    
    int y = vy +def_h +52;
    int x = vx +40;

    _CustomDlg_* dlg = _CustomDlg_::Create(-1, -1, x, y, DF_SCREENSHOT | DF_SHADOW, NULL);
    Set_DlgBackground_RK(dlg, 0, o_GameMgr->GetMeID());

    dlg->AddItem(_DlgStaticDef_::Create(0, 26, 1, def_name, def_frame, 0, 0x12)); 
    ((_DlgStaticDef_*)dlg->GetItem(1))->x = (dlg->width / 2) - (((_DlgStaticDef_*)dlg->GetItem(1))->width / 2); 

    dlg->AddItem(_DlgStaticText_::Create(18, 18 + def_h + 22 , dlg->width -36, dlg->height -18 -def_h -22, text, "medfont2.fnt", 1, 2, ALIGN_H_CENTER | ALIGN_V_TOP, 0)); 

    dlg->RMC_Show(); 
    dlg->Destroy(TRUE);
} 

// показ сообщения по ПКМ c одним pcx
void b_MsgBoxAndPcx8(char* text, char* pcx_name, int style)
{
    // вычисляем размеры текста
    int text_hi = o_Medfont_Fnt->height;
    int str_len = strlen(text);
    int tx = str_len * 6;
    int ty = text_hi;

    while ( tx > (ty * 4) ) {
        tx = tx >> 1;   // делим на 2
        ty = ty * 2;    // умножаем на 2
    } 

    if (tx < 280) tx = 280;
    int lines = o_Medfont_Fnt->GetLinesCountInText(text, tx);
    ty = (lines +1) *text_hi;

    if (ty > 220 || lines > 5) {
        tx = 440;
        lines = o_Medfont_Fnt->GetLinesCountInText(text, tx);
        ty = (lines +1) *text_hi;
    }

    if (ty < 20) ty = 20;

    int x = tx +40;
    int y = ty +60;
    if (style != 4 ) 
        y += 40;

    // вычисляем размеры картинки
    int pcx8_x = 0;
    int pcx8_y = 0;
    if (pcx_name) {
        _Pcx8_* pcx8 = o_LoadPcx8(pcx_name);
        pcx8_x = pcx8->width;
        pcx8_y = pcx8->height;
        pcx8->DerefOrDestruct();
        if (x < pcx8_x)
            x = (pcx8_x +40);

        y += (pcx8_y +20);
    }

    _CustomDlg_* dlg = _CustomDlg_::Create(-1, -1, x, y, DF_SCREENSHOT | DF_SHADOW, NULL);
    Set_DlgBackground_RK(dlg, 0, o_GameMgr->GetMeID());

    dlg->AddItem(_DlgStaticText_::Create(18, 26, x-40, ty, text, "medfont.fnt", 1, 2, ALIGN_H_CENTER | ALIGN_V_CENTER, 0)); 

    dlg->AddItem(_DlgStaticPcx8_::Create((x >> 1) - (pcx8_x >> 1), 44+ty, pcx8_x, pcx8_y, 5, pcx_name ));


    if ( style == 4 ) {
        dlg->RMC_Show(); 
    } else {
        int x_center = x >> 1; // вычисляем середину ширины диалога (x / 2)
        dlg->AddItem(_DlgStaticPcx8_::Create(x_center -33, y -51, DIID_OK_FRAME, "Box64x30.pcx"));
        dlg->AddItem(_DlgButton_::Create(x_center -32, y -50, 64, 30, DIID_OK, "iOkay.def", 0, 1, 1, 28, 2));

        Y_Mouse_SetCursor(0);
        dlg->Run(); 
        Y_Mouse_SetCursor(1);
    }

    dlg->Destroy(TRUE);
} 

/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////


// показ сообщений с большими размерами по ПКМ
// оно же используется для отображения всех описаний WoG опций
void b_MsgBoxBig(char* text, char style)
{
    int x, y;
    x = 400;
    int lines = medfont2->GetLinesCountInText(text, x -40);
    y = lines *16;

    if (y < 80) {
        y = 80;
    }

    if (lines > 30 ) { 
        x += 180; 
        lines = medfont2->GetLinesCountInText(text, x -40);
        y = lines *16;
    }

    y += 40;

    if (y > 580) { 
        y = 580;
        x += 200;
    } 

    _CustomDlg_* dlg = _CustomDlg_::Create(-1, -1, x, y, DF_SCREENSHOT | DF_SHADOW, NULL);
    Set_DlgBackground_RK(dlg, 0, o_GameMgr->GetMeID());

    dlg->AddItem(_DlgStaticText_::Create(20, 20, dlg->width -40, dlg->height -40, text, "medfont2.fnt", 1, 2, ALIGN_H_CENTER | ALIGN_V_CENTER, 0)); 

    dlg->RMC_Show(); 
    dlg->Destroy(TRUE);
}

/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////




/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////

int __stdcall Y_MsgBoxAndAnimatedDef_Proc(_CustomDlg_* dlg, _EventMsg_* msg)
{
    int r = dlg->DefProc(msg);

    //  делаем подвижность дефа   
    if (( (o_GetTime() - DrawingWaitTime) & 0x80000000) == 0) 
    {
        // _DlgStaticDef_* NPC_Def = (_DlgStaticDef_*)dlg->custom_data[0];
        CALL_1(_int_, __thiscall, 0x4EB140, (_DlgStaticDef_*)dlg->custom_data[0]); 
        dlg->Redraw(1);
        _dword_ t = o_GetTime() - DrawingWaitTime;
        if ((signed int)t < 100) t = 100;
        DrawingWaitTime += t;
    }

    return r;
}

// показ сообщения по ПКМ c одним дефом
void b_MsgBoxAndAnimatedDef(char* text, char* def_name)
{
    int str_len = strlen(text);
    int vx = str_len * 6;
    int vy = 16;

    while ( vx > (vy * 4) ) {
        vx = vx >> 1;   // делим на 2
        vy = vy * 2;    // умножаем на 2
    } 

    if (vx < 280) vx = 280;
    int lines = medfont2->GetLinesCountInText(text, vx);
    vy = (lines +1) *16;

    // if (vy < 100) vx = 320;
    if (vy > 220 || lines > 5) {
        vx = 440;
        lines = medfont2->GetLinesCountInText(text, vx);
        vy = (lines +1) *16;
    }

    if (vy < 20) vy = 20;

    _Def_* def = _Def_::Load(def_name);
    int def_h = def->height;
    def->DerefOrDestruct(); 
    
    int y = vy +def_h +94;
    int x = vx +40;

    _CustomDlg_* dlg = _CustomDlg_::Create(-1, -1, x, y, DF_SCREENSHOT | DF_SHADOW, Y_MsgBoxAndAnimatedDef_Proc);
    Set_DlgBackground_RK(dlg, 0, o_GameMgr->GetMeID());

    _DlgStaticDef_* animDef;
    dlg->AddItem(animDef = _DlgStaticDef_::Create(0, 26, 1, def_name, 0, 0, 0x12)); 
    animDef->x = (dlg->width / 2) - (animDef->width / 2); 
    dlg->custom_data[0] = (int)animDef;

    dlg->AddItem(_DlgStaticText_::Create(18, 18 + def_h + 22 , x-36, y-18 -def_h -22, text, "medfont2.fnt", 1, 2, ALIGN_H_CENTER | ALIGN_V_TOP, 0)); 

    int x_center = x >> 1; // вычисляем середину ширины диалога (x / 2)
    dlg->AddItem(_DlgStaticPcx8_::Create(x_center -33, y-57, DIID_OK_FRAME, "Box64x30.pcx"));
    dlg->AddItem(_DlgButton_::Create(x_center -32, y-56, 64, 30, DIID_OK, "iOkay.def", 0, 1, 1, 28, 2));

    Y_Mouse_SetCursor(0);
    dlg->Run();
    dlg->Destroy(TRUE);
    Y_Mouse_SetCursor(1);
} 

// *** end
