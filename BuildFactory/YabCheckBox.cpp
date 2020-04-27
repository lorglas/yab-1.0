#include <CheckBox.h>
#include "YabCheckBox.h"

YabCheckBox::YabCheckBox(BRect frame,const char *name,const char *label,BMessage *message,uint32 resizeMask, uint32 flags)
	:BCheckBox(frame,name,label,message,resizeMask,flags)
{
	mouseMovedInfo = 1;
	mouseStateInfo = -1;
	prevMouseStateInfo = 0;
	mouseX = 0;
	mouseY = 0;
	mouseLButton = 0;
	mouseMButton = 0;
	mouseRButton = 0;		
}

void YabCheckBox::MouseDown(BPoint where)
{
	BPoint ptCursor;
	uint32 uButtons = 0;
	GetMouse(&ptCursor, &uButtons, false); 

	mouseX = (int)ptCursor.x;
	mouseY = (int)ptCursor.y;
	if(uButtons & B_PRIMARY_MOUSE_BUTTON) mouseLButton = 1; else mouseLButton = 0;
	if(uButtons & B_SECONDARY_MOUSE_BUTTON) mouseRButton = 1; else mouseRButton = 0;
	if(uButtons & B_TERTIARY_MOUSE_BUTTON) mouseMButton = 1; else mouseMButton = 0;
	mouseStateInfo = 4;
	BCheckBox::MouseDown(where);
}


void YabCheckBox::MouseUp(BPoint pt)
{
	BPoint ptCursor;
	uint32 uButtons = 0;
	GetMouse(&ptCursor, &uButtons, false); 

	mouseX = (int)ptCursor.x;
	mouseY = (int)ptCursor.y;
	if(uButtons & B_PRIMARY_MOUSE_BUTTON) mouseLButton = 1; else mouseLButton = 0;
	if(uButtons & B_SECONDARY_MOUSE_BUTTON) mouseRButton = 1; else mouseRButton = 0;
	if(uButtons & B_TERTIARY_MOUSE_BUTTON) mouseMButton = 1; else mouseMButton = 0;
	mouseStateInfo = 5;
	BCheckBox::MouseUp(pt);
}

void YabCheckBox::MouseMoved(BPoint pt, uint32 code, const BMessage *msg)
{
	BPoint ptCursor;
	uint32 uButtons = 0;
	GetMouse(&ptCursor, &uButtons, true); 

	mouseX = (int)ptCursor.x;
	mouseY = (int)ptCursor.y;
	if(uButtons & B_PRIMARY_MOUSE_BUTTON) mouseLButton = 1; else mouseLButton = 0;
	if(uButtons & B_SECONDARY_MOUSE_BUTTON) mouseRButton = 1; else mouseRButton = 0;
	if(uButtons & B_TERTIARY_MOUSE_BUTTON) mouseMButton = 1; else mouseMButton = 0;

	switch(code)
	{
		case B_INSIDE_VIEW:
			if(prevMouseStateInfo==1)
				mouseStateInfo = 0;
			else
				{
					mouseStateInfo = 1;
					prevMouseStateInfo = 1;
				}
			mouseMovedInfo = 0;
			break;		
		case B_ENTERED_VIEW:
			mouseStateInfo = 1;
			mouseMovedInfo = 0;
			break;
		case B_OUTSIDE_VIEW:
			mouseStateInfo = 2;
			mouseMovedInfo = 1;
			break;
		case B_EXITED_VIEW:
			mouseStateInfo = 3;
			mouseMovedInfo = 1;
			prevMouseStateInfo = 0;
			break;
	}
	BCheckBox::MouseMoved(pt, code, msg);
}
