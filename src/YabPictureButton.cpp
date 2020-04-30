#include <Region.h>
#include <View.h>
#include <PictureButton.h>
#include <stdio.h>
#include "YabPictureButton.h"

YabPictureButton::YabPictureButton(BRect frame,const char* name, BPicture *off, BPicture *on,BMessage *message, uint32 behavior = B_ONE_STATE_BUTTON,uint32 resizeMask =B_FOLLOW_LEFT | B_FOLLOW_TOP, uint32 flgs = B_WILL_DRAW | B_NAVIGABLE)
	:BPictureButton(frame,name,off,on,message,behavior,resizeMask,flgs)
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

void YabPictureButton::MouseDown(BPoint point)
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
	BPictureButton::MouseDown(point);
}


void YabPictureButton::MouseUp(BPoint point)
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
	BPictureButton::MouseUp(point);
}

void YabPictureButton::MouseMoved(BPoint point, uint32 transit, const BMessage *message)
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
	BPictureButton::MouseMoved(point, transit, message);
}
