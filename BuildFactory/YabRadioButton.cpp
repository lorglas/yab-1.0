#include <Region.h>
#include <View.h>
#include <RadioButton.h>
#include "YabRadioButton.h"

YabRadioButton::YabRadioButton(BRect frame,const char *name,const char *label,BMessage *message,uint32 resizMask,uint32 flags)
	:BRadioButton(frame,name,label,message,resizMask,flags)
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

void YabRadioButton::MouseDown(BPoint point)
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
	BRadioButton::MouseDown(point);
}


void YabRadioButton::MouseUp(BPoint point)
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
	BRadioButton::MouseUp(point);
}

void YabRadioButton::MouseMoved(BPoint point, uint32 transit, const BMessage *message)
{
	BPoint ptCursor;
	uint32 uButtons = 0;
	GetMouse(&ptCursor, &uButtons, true); 

	mouseX = (int)ptCursor.x;
	mouseY = (int)ptCursor.y;
	if(uButtons & B_PRIMARY_MOUSE_BUTTON) mouseLButton = 1; else mouseLButton = 0;
	if(uButtons & B_SECONDARY_MOUSE_BUTTON) mouseRButton = 1; else mouseRButton = 0;
	if(uButtons & B_TERTIARY_MOUSE_BUTTON) mouseMButton = 1; else mouseMButton = 0;

	switch(transit)
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
	BRadioButton::MouseMoved(point, transit, message);
}
