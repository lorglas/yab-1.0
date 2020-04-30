#ifndef YABTEXTCONTROL_H
#define YABTEXTCONTROL_H

#include <TextControl.h>

class YabTextControl : public BTextControl
{
	public:
		YabTextControl(BRect frame,const char *name,const char *label,const char *initial_text,BMessage *message,uint32 rmask = B_FOLLOW_LEFT | B_FOLLOW_TOP,uint32 flags = B_WILL_DRAW | B_NAVIGABLE); 
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
