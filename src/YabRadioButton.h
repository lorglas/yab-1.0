#ifndef YABRADIOBUTTON_H
#define YABRADIOBUTTON_H

#include <RadioButton.h>

class YabRadioButton : public BRadioButton
{
	public:
		YabRadioButton(BRect frame,const char *name,const char *label,BMessage *message,uint32 resizMask = B_FOLLOW_LEFT | B_FOLLOW_TOP,uint32 flags = B_WILL_DRAW | B_NAVIGABLE);
		virtual void MouseMoved(BPoint point, uint32 transit, const BMessage *message);
		virtual void MouseUp(BPoint point);
		virtual void MouseDown(BPoint point);
		int mouseMovedInfo;
		int mouseStateInfo;
		int mouseX;
		int mouseY;
		uint mouseLButton;
		uint mouseMButton;
		uint mouseRButton;
	private:
		int prevMouseStateInfo;
};

#endif



