#ifndef YABCHECKBOX_H
#define YABCHECKBOX_H

#include <CheckBox.h>

class YabCheckBox : public BCheckBox
{
	public:
		YabCheckBox(BRect frame,const char *name,const char *label,BMessage *message,uint32 resizeMask = B_FOLLOW_LEFT | B_FOLLOW_TOP, uint32 flags = B_WILL_DRAW | B_NAVIGABLE);
		virtual void MouseMoved(BPoint pt, uint32 code, const BMessage *msg);
		virtual void MouseUp(BPoint pt);
		virtual void MouseDown(BPoint where);
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
