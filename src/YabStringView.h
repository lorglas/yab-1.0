#ifndef YABSTRINGVIEW_H
#define YABSTRINGVIEW_H

#include <interface/StringView.h>

class YabStringView : public BStringView
{
	public:
		YabStringView(BRect bounds,const char *name,const char *text,uint32 resizeFlags =B_FOLLOW_LEFT | B_FOLLOW_TOP,uint32 flags = B_WILL_DRAW);
		YabStringView(BRect bounds,const char *name,const char *text,uint32 truncation_mode,uint32 resizeFlags,uint32 flags);
		virtual void MouseMoved(BPoint pt, uint32 code, const BMessage *msg);
		virtual void MouseUp(BPoint pt);
		virtual void MouseDown(BPoint pt);
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
