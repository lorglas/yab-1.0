#include <Slider.h>
#include "YabSlider.h"

YabSlider::YabSlider(BRect frame,const char *name,const char *label,BMessage *message,int32 minValue,int32 maxValue,thumb_style thumbType = B_BLOCK_THUMB,uint32 resizingMode = B_FOLLOW_LEFT | B_FOLLOW_TOP,uint32 flags = B_NAVIGABLE | B_WILL_DRAW | B_FRAME_EVENTS)
	:BSlider(frame,name,label,message,minValue,maxValue,thumbType,resizingMode,flags)
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

YabSlider::YabSlider(BRect frame,const char *name,const char *label,BMessage *message,int32 minValue,int32 maxValue,orientation posture /*= B_HORIZONTAL*/,thumb_style thumbType = B_BLOCK_THUMB,uint32 resizingMode = B_FOLLOW_LEFT | B_FOLLOW_TOP,uint32 flags = B_NAVIGABLE | B_WILL_DRAW | B_FRAME_EVENTS)	
	:BSlider(frame,name,label,message,minValue,maxValue,posture,thumbType,resizingMode,flags)
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

void YabSlider::MouseDown(BPoint point)
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
	BSlider::MouseDown(point);
}


void YabSlider::MouseUp(BPoint point)
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
	BSlider::MouseUp(point);
}

void YabSlider::MouseMoved(BPoint point, uint32 transit, const BMessage *message)
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
	BSlider::MouseMoved(point, transit, message);
}
