#ifndef YABSCROLLVIEW_H
#define YABSCROLLVIEW_H

#include <ScrollView.h>

class YabScrollView : public BScrollView
{
	public:
		YabScrollView(const char *name,BView *target,uint32 resizeMask = B_FOLLOW_LEFT | B_FOLLOW_TOP,uint32 flags = 0,bool horizontal = false,bool vertical = false, border_style border = B_FANCY_BORDER);
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
