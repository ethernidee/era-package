5FEFB0 ; int __thiscall Dlg_Construct(_Dlg_ *this, int x, int y, int sizeX, int sizeY, int flags)
5FF040 ; int __fastcall Dlg_Destroy(_Dlg_ *this)
5FF0A0 ; signed int __thiscall Dlg_Show(_Dlg_ *this, int zorder, int draw)
5FF220 ; int __thiscall Dlg_Hide(_Dlg_ *this, char a2)
5FF270 ; int __thiscall Dlg_InitDlgItem(_Dlg_ *this, _DlgItem_ *item, int zorder)
5FF320 ; void __thiscall Dlg_DetachDlgItem(_Dlg_ *this, _DlgItem_ *item)
5FF3A0 ; int __thiscall Dlg_Send_MouseMsg(_Dlg_ *dlg, _MouseStr_ *msg)
5FF400 ; int __thiscall Dlg_SendItemCommand(_Dlg_ *dlg, int cmdtype, int cmdsubtype, int itemind, int newparval)
5FF490 ; int __thiscall DlgItem_Send5Cmd2Item(int dlg, int it_id, int param)
5FF520 ; int __fastcall DlgItem_Send6Cmd2Item(void *dlg, int, int newparval, int itemind)
5FF5B0 ; int __fastcall Dlg_GetItem_byID(_Dlg_ *dlgpo, int, int ItemID)
5FF5E0 ; char __thiscall Dlg_Redraw(_Dlg_ *this, char a2, signed int a3, signed int a4)
5FF6C0 ; int __thiscall Dlg_LoadScreenPcx16(_Dlg_ *a1)
5FF9A0 ; _DlgItem_ *__thiscall Dlg_GetItemAtPosition(_Dlg_ *this, int Xabs, int Yasb)
5FFA20 ; int __thiscall Dlg_ShowAndRun(void *dlg, int a2)
5FFAC0 ; int __thiscall Dlg_CallProcessMsg(_MouseStr_ *a1)
5FFAD0 ; int __thiscall Dlg_DestructAllItems(_Dlg_ *this)
5FFC00 ; _Dlg_ *__thiscall DlgCustom_Create(_Dlg_ *this, int x, int y, int sizeX, int sizeY, int flags)
5FFCA0 ; char __thiscall Dlg_SetHintOnMouseMove(_Dlg_ *this, int Xabs, int Yasb)
5FFD50 ; char __thiscall Dlg_ShowMsgOnRightClick(_Dlg_ *this, int itemId)



H3DlgItem
{
	1. DlgEmptyStatic_Create(_DlgItem_ *this, __int16 PosX, __int16 PosY, __int16 SizeX, __int16 SizeY, __int16 ItemInd, __int16 Flags)
	2. DlgButton_Create
	3. DlgTextButton_Create
	4. DlgDef_BuildAndLoadDef
	5. BuildScrollBar
	6. DlgItem_BuildTextWithScrollBar
	7. DlgItem_BuildTextItem
}

_DlgItem_
_DlgText_

_DlgText_ *__thiscall Dlg_BuildTextBackPcx(_DWORD this, void *xpos, int ypos, int xsize, int ysize, int text, int font, char *PCXName, int color, int itemId, int align, int unused)


#pragma pack(push, 1)
struct _DlgStaticTextPcx8ed_
{
  _DlgStaticText_ staticText;
  _Pcx_ pcx8;
};
#pragma pack(pop)