#include "FONT.h"
#include "gui.h"

extern const GUI_FONT GUI_FontRoboto27B;

const unsigned char goodbye[] = "TR";

const GUI_FONT_SHOW F_ENGLISH[] =
	{
		{66, 140, 0, 0xffff, &GUI_FontRoboto27B, (unsigned short *)&goodbye, sizeof(goodbye), 0, 0}, //0
		{66, 140, 0, 0xffff, &GUI_FontRoboto27B, (unsigned short *)&goodbye, sizeof(goodbye), 0, 0}, //1
};
