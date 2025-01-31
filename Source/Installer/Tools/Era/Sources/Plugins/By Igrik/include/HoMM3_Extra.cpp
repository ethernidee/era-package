#include "HoMM3_Extra.h"


_Pcx16_* pcx16_screen_off = NULL;
_bool_ screen_off = FALSE;

void e_SwapScreenOff()
{
	_Pcx16_* tmp;
	tmp = o_WndMgr->screen_pcx16;
	o_WndMgr->screen_pcx16 = pcx16_screen_off;
	pcx16_screen_off = tmp;
}

void e_SetScreenOff(_bool_ value, _bool_ use_off_drawn)
{
	_bool_ static last_use_off_drawn = 0;

	if (screen_off == value) return;

	screen_off = value;

	if (value)
	{
		if (!use_off_drawn)
		{
			if (!pcx16_screen_off)
				pcx16_screen_off = _Pcx16_::CreateNew("", o_WndMgr->screen_pcx16->width, o_WndMgr->screen_pcx16->height);
			e_SwapScreenOff();
		}

		last_use_off_drawn = use_off_drawn;
	}
	else
	{
		if (!last_use_off_drawn)
		{
			e_SwapScreenOff();
		}
	}
}

