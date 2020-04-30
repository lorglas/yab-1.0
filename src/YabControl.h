#ifndef YABCONTROL_H
#define YABCONTROL_H

#include <String.h>
#include <View.h>
#include <Control.h>

class YabControl : public BControl
{
	public:
		YabControl(BRect frame, const char *name, const char *label, BMessage *message, uint32 resizeMask, uint32 flags);
		//~YabControl();
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
};

#endif
