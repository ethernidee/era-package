////////////////////////////////////////////////////////////////////////////////////
// (HD 3.0) HoMM3 GUI (Window Manager, Dialogs, Control Elements (DlgItems) )
// Author: Alexander Barinov (aka baratorch, aka Bara) e-mail: baratorch@yandex.ru
// Thanks: ZVS, GrayFace
////////////////////////////////////////////////////////////////////////////////////


#include "HoMM3_GUI.h"



////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////

void _Dlg_::SetItemsArrayListLength(int items_count)
{
 this->items_first = o_New(items_count*4);
 MemSet(this->items_first, 0, items_count*4);
 this->items_last = this->items_first;
 this->items_mem_end = this->items_first + items_count*4;
}

void _Dlg_::AddItemByZOrder(_DlgItem_* item, int z_order)
{
 int i = 0;
 int all_count = 0;
 int count = 0;

 for (_DlgItem_* itm = this->first_item; itm != NULL; itm = itm->next_item)
 {
  all_count++;
 }
 _DlgItem_** all_items = (_DlgItem_**)o_New(all_count * 4);
 for (_DlgItem_* itm = this->first_item; itm != NULL; itm = itm->next_item)
 {
  all_items[i++] = itm;
 }



 _DlgItem_** first = (_DlgItem_**)this->items_first;
 _DlgItem_** last = (_DlgItem_**)this->items_last;

 int sz = this->items_mem_end - this->items_first;
 this->items_first = o_New(sz+4);
 MemZero(this->items_first, sz+4);
 this->items_last = this->items_first;
 this->items_mem_end = this->items_first + sz+4;
 this->last_item = 0;
 this->first_item = 0;

 int z = z_order;
 for (_DlgItem_** p_itm = first; p_itm != last; p_itm++)
 {
  if (z == i)
  {
   this->AddItemToOwnArrayList(item);
   z = -2;
  }
  if (*p_itm)
  {
   this->AddItemToOwnArrayList(*p_itm);
   i++;
  }
 }
 count = i;
 if ((z == -1) || (z >= count))
 {
  this->AddItemToOwnArrayList(item);
 }

 for (i = 0; i < all_count; i++)
 {
  if (z_order == i)
  {
   this->AttachItem(item);
   z_order = -2;
  }
  this->AttachItem(all_items[i]);
 }
 if ((z_order == -1) || (z_order >= i))
 {
  this->AttachItem(item);
 }

 o_Delete(first);
 o_Delete(all_items);
}

////void _Dlg_::DetachItem(_DlgItem_* item)
////{
//// int all_count = 0;
//// int i;
////
//// for (_DlgItem_* itm = this->first_item; itm != NULL; itm = itm->next_item)
//// {
////  all_count++;
//// }
//// _DlgItem_** all_items = (_DlgItem_**)o_New(all_count * 4);
//// for (_DlgItem_* itm = this->first_item; itm != NULL; itm = itm->next_item)
//// {
////  all_items[i++] = itm;
//// }
//// for (i = 0; i < all_count; i++)
//// {
////  if (all_items[i] != item) this->AttachItem(all_items[i]);
//// }
////
//// o_Delete(all_items);
////}

void _Dlg_::RemoveItem(_DlgItem_* item)
{

 int i = 0;
 int all_count = 0;

 for (_DlgItem_* itm = this->first_item; itm != NULL; itm = itm->next_item)
 {
  all_count++;
 }
 _DlgItem_** all_items = (_DlgItem_**)o_New(all_count * 4);
 for (_DlgItem_* itm = this->first_item; itm != NULL; itm = itm->next_item)
 {
  all_items[i++] = itm;
 }

 _DlgItem_** first = (_DlgItem_**)this->items_first;
 _DlgItem_** last = (_DlgItem_**)this->items_last;

 int sz = this->items_mem_end - this->items_first;
 this->items_first = o_New(sz);
 MemZero(this->items_first, sz);
 this->items_last = this->items_first;
 this->items_mem_end = this->items_first + sz;
 this->last_item = 0;
 this->first_item = 0;

 for (_DlgItem_** p_itm = first; p_itm != last; p_itm++)
 {
  if ((*p_itm) && (*p_itm != item)) this->AddItemToOwnArrayList(*p_itm);
 }

 for (i = 0; i < all_count; i++)
 {
  if (all_items[i] != item) this->AttachItem(all_items[i]);
 }

 o_Delete(first);
 o_Delete(all_items);
}
void _Dlg_::SetItemZOrder(_DlgItem_* item, int z_order)
{
 RemoveItem(item);
 AddItemByZOrder(item, z_order); 
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////


void _DlgItem_::RedrawScreen() { o_WndMgr->RedrawScreenRect(parent->x + x, parent->y + y, width, height); }


//////////////////////////////////////////////////////////////////////////////////////////////////////////
_DlgStaticPcx16_* _DlgBlueBackground_::Create(int x, int y, int w, int h, int id)
{
 if ((w < 42) || (h < 42))
  return NULL;

 _Pcx16_* pcx16 = _Pcx16_::CreateNew("", w, h);
 if (pcx16 == NULL)return NULL;
 _Pcx8_* pcx8_fl = o_LoadPcx8("DlgBluBk.PCX");
 if (pcx8_fl == NULL) return NULL;
 _Def_* def_fr = o_LoadDef("DlgBluBo.def");
 if (def_fr == NULL) return NULL;

 int fi_ld = 2;
 int fi_rd = 3;
 int fi_d = 7;

 int x_, y_;

    y_ = 0;
    while (TRUE)
    {
        x_ = 0;
        while (TRUE)
        {
   pcx8_fl->DrawToPcx16(0,0,min(pcx8_fl->width, w - x_),min(pcx8_fl->height, h - y_), pcx16, x_, y_, FALSE);
            if (x_ + pcx8_fl->width >= pcx16->width)
                break;
            x_ += pcx8_fl->width;
        }
        if (y_ + pcx8_fl->height >= pcx16->height)
            break;
        y_ += pcx8_fl->height;
    }

    x_ = pcx16->width - 2 * def_fr->width;
    while (x_ > 0)
    {
  def_fr->groups[0]->frames[6]->DrawInterfaceToPcx16(pcx16, x_, 0, def_fr->palette16);//u
   def_fr->groups[0]->frames[fi_d]->DrawInterfaceToPcx16(pcx16, x_,pcx16->height - def_fr->height, def_fr->palette16);//d
        x_ -= def_fr->width;
    }
    y_ = pcx16->height - 2 * def_fr->height;
    while (y_ > 0)
    {
  def_fr->groups[0]->frames[4]->DrawInterfaceToPcx16(pcx16, 0, y_, def_fr->palette16);//l
  def_fr->groups[0]->frames[5]->DrawInterfaceToPcx16(pcx16, pcx16->width - def_fr->width,y_, def_fr->palette16);//r
        y_ -= def_fr->height;
    }
 def_fr->groups[0]->frames[0]->DrawInterfaceToPcx16(pcx16, 0,0, def_fr->palette16);//lu
 def_fr->groups[0]->frames[1]->DrawInterfaceToPcx16(pcx16, pcx16->width - def_fr->width, 0, def_fr->palette16);//ru
 def_fr->groups[0]->frames[fi_ld]->DrawInterfaceToPcx16(pcx16, 0, pcx16->height - def_fr->height, def_fr->palette16);//ld
 def_fr->groups[0]->frames[fi_rd]->DrawInterfaceToPcx16(pcx16, pcx16->width - def_fr->width,pcx16->height - def_fr->height, def_fr->palette16);//rd

 def_fr->DerefOrDestruct();
 pcx8_fl->DerefOrDestruct();

 _DlgStaticPcx16_* item = _DlgStaticPcx16_::Create(x, y, w, h, id, NULL, DIF_PCX);
 item->pcx16 = pcx16;
 return item;
}


_DlgStaticPcx16_* _DlgStdBackground_::Create(int x, int y, int w, int h, int id, _bool_ have_bottombar, int player_id)
{

 if ((w < 64) || (h < 64))
  return NULL;

 _Pcx16_* pcx16 = _Pcx16_::CreateNew("", w, h);
 if (pcx16 == NULL)return NULL;
 _Pcx8_* pcx8_fl = o_LoadPcx8("DiBoxBck.PCX");
 if (pcx8_fl == NULL) return NULL;
 _Def_* def_fr = o_LoadDef("dialgbox.def");
 if (def_fr == NULL) return NULL;

 _Palette16_ pal16;
 MemCopy(&pal16, def_fr->palette16, sizeof(_Palette16_));
 pal16.Colorize(player_id);

 int fi_ld = 2;
 int fi_rd = 3;
 int fi_d = 7;
 if (have_bottombar)
 {
  fi_ld = 8;
  fi_rd = 9;
  fi_d = 10;
 }

 int x_, y_;

    y_ = 0;
    while (TRUE)
    {
        x_ = 0;
        while (TRUE)
        {
   pcx8_fl->DrawToPcx16(0,0,min(pcx8_fl->width, w - x_),min(pcx8_fl->height, h - y_), pcx16, x_, y_, FALSE);
            if (x_ + pcx8_fl->width >= pcx16->width)
                break;
            x_ += pcx8_fl->width;
        }
        if (y_ + pcx8_fl->height >= pcx16->height)
            break;
        y_ += pcx8_fl->height;
    }

    x_ = pcx16->width - 2 * def_fr->width;
    while (x_ > 0)
    {
  def_fr->groups[0]->frames[6]->DrawInterfaceToPcx16(pcx16, x_, 0, &pal16);//u
   def_fr->groups[0]->frames[fi_d]->DrawInterfaceToPcx16(pcx16, x_,pcx16->height - def_fr->height, &pal16);//d
        x_ -= def_fr->width;
    }
    y_ = pcx16->height - 2 * def_fr->height;
    while (y_ > 0)
    {
  def_fr->groups[0]->frames[4]->DrawInterfaceToPcx16(pcx16, 0, y_, &pal16);//l
  def_fr->groups[0]->frames[5]->DrawInterfaceToPcx16(pcx16, pcx16->width - def_fr->width,y_, &pal16);//r
        y_ -= def_fr->height;
    }
 def_fr->groups[0]->frames[0]->DrawInterfaceToPcx16(pcx16, 0,0, &pal16);//lu
 def_fr->groups[0]->frames[1]->DrawInterfaceToPcx16(pcx16, pcx16->width - def_fr->width, 0, &pal16);//ru
 def_fr->groups[0]->frames[fi_ld]->DrawInterfaceToPcx16(pcx16, 0, pcx16->height - def_fr->height, &pal16);//ld
 def_fr->groups[0]->frames[fi_rd]->DrawInterfaceToPcx16(pcx16, pcx16->width - def_fr->width,pcx16->height - def_fr->height, &pal16);//rd

 def_fr->DerefOrDestruct();
 pcx8_fl->DerefOrDestruct();

 _DlgStaticPcx16_* item = _DlgStaticPcx16_::Create(x, y, w, h, id, NULL, DIF_PCX);
 item->pcx16 = pcx16;
 return item;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////
_ptr_ _CustomDlg_::v_table_funcs[15] = {
      0x41B040,//destroy
      0x5FF0A0,//show
      0x5FF220,//hide
      0x405610,//call process action
      0x49A230,//nullsub
      0x5FF5E0,//redraw
      0x5FFA20,// run
      0x5FFB30,//init items
      0x5FFBB0,//wtf?
      (_ptr_)_CustomDlg_::DlgProcBridge,
      0x5FFCA0, // on mouse move
      0x5FFD50, // on press button
      0x5FFE90, // on click - nullsub return 0
      0x4842C0, // nullsub return 0
      0x41B0F0 }; // close


_CustomDlg_* _CustomDlg_::Create(int x, int y, int width, int height, _dword_ flags, _func_CustomDlgProc dlg_proc)
{
 _CustomDlg_* dlg = (_CustomDlg_*)o_New(sizeof(_CustomDlg_));

 if (dlg != NULL) 
 {
  if (x == DLG_X_CENTER)
   x = (o_WndMgr->screen_pcx16->width - width) / 2;
  if (y == DLG_Y_CENTER)
   y = (o_WndMgr->screen_pcx16->height - height) / 2;
  CALL_6(_Dlg_*, __thiscall, 0x41AFA0, dlg, x, y, width, height, flags); //init
  dlg->dlg_proc = dlg_proc;
  dlg->v_table = v_table_funcs;
 }

 return dlg;
}

int __fastcall _CustomDlg_::DlgProcBridge(_CustomDlg_* this_, _dword_ not_used, _EventMsg_ *msg)
{
 if (this_->dlg_proc)
  return this_->dlg_proc(this_, msg);
 else
  return this_->DefProc(msg);
}

_Pcx8_* CreateSimpleFrame(int w_, int h_)
{
 int x = 0;
 int y = 0;
 _Pcx8_* pcx = _Pcx8_::CreateNew("", w_, h_);
 if (pcx == NULL) return NULL;

    _Pcx8_* pcx_fr_lu = o_LoadPcx8("hd_fr_lu.pcx");
    _Pcx8_* pcx_fr_ru = o_LoadPcx8("hd_fr_ru.pcx");
    _Pcx8_* pcx_fr_rd = o_LoadPcx8("hd_fr_rd.pcx");
    _Pcx8_* pcx_fr_ld = o_LoadPcx8("hd_fr_ld.pcx");
    _Pcx8_* pcx_fr_l = o_LoadPcx8("hd_fr_l.pcx");
    _Pcx8_* pcx_fr_r = o_LoadPcx8("hd_fr_r.pcx");
    _Pcx8_* pcx_fr_u = o_LoadPcx8("hd_fr_u.pcx");
    _Pcx8_* pcx_fr_d = o_LoadPcx8("hd_fr_d.pcx");


 pcx->SetPaletteFrom(pcx_fr_u);

        pcx->DrawPcx8(pcx_fr_lu, 0, 0);
        x = pcx_fr_lu->width;
        while (true)
        {
            pcx->DrawPcx8(pcx_fr_u,
                x, 0);
            if (x + pcx_fr_u->width >= w_)
                break;
            x += pcx_fr_u->width;
        }
        y = pcx_fr_lu->height;
        while (true)
        {
            pcx->DrawPcx8(pcx_fr_l,
                0, y);
            if (y + pcx_fr_l->height >= h_)
                break;
            y += pcx_fr_l->height;
        }
        pcx->DrawPcx8(pcx_fr_ru, w_ - pcx_fr_ru->width, 0);
        pcx->DrawPcx8(pcx_fr_ld, 0, h_ - pcx_fr_ld->height);
        x = pcx_fr_ld->width;
        while (true)
        {
            pcx->DrawPcx8(pcx_fr_d,
                x, h_ - pcx_fr_u->height);
            if (x + pcx_fr_d->width >= w_)
                break;
            x += pcx_fr_d->width;
        }
        y = pcx_fr_ru->height;
        while (true)
        {
            pcx->DrawPcx8(pcx_fr_r,
                w_ - pcx_fr_r->width, y);
            if (y + pcx_fr_r->height >= h_)
                break;
            y += pcx_fr_r->height;
        }
        pcx->DrawPcx8(pcx_fr_rd, w_ - pcx_fr_rd->width, h_ - pcx_fr_rd->height);
  pcx->FillRect(0, 4, 4, w_-8, h_-8);

  pcx_fr_l->DerefOrDestruct();
  pcx_fr_r->DerefOrDestruct();
  pcx_fr_u->DerefOrDestruct();
  pcx_fr_d->DerefOrDestruct();
  pcx_fr_lu->DerefOrDestruct();
  pcx_fr_ru->DerefOrDestruct();
  pcx_fr_ld->DerefOrDestruct();
  pcx_fr_rd->DerefOrDestruct();

 return pcx;
}
