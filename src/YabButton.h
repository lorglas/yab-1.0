#ifndef YABBUTTON_H
#define YABBUTTON_H

#include <Button.h>

class YabButton : public BButton
{
	public:
		YabButton(BRect frame,const char *name,const char *label, BMessage *message,uint32 resizeMask = B_FOLLOW_LEFT | B_FOLLOW_TOP, uint32 flags = B_WILL_DRAW | B_NAVIGABLE); 		
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
