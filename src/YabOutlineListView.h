#ifndef YABOUTLINELISTVIEW_H
#define YABOUTLINELISTVIEW_H

#include <OutlineListView.h>

class YabOutlineListView : public BOutlineListView
{
	public:
		YabOutlineListView(BRect frame,const char * name,list_view_type type = B_SINGLE_SELECTION_LIST,uint32 resizeMask = B_FOLLOW_LEFT | B_FOLLOW_TOP,uint32 flags = B_WILL_DRAW | B_FRAME_EVENTS | B_NAVIGABLE);
		virtual void MouseMoved(BPoint pt, uint32 code, const BMessage *msg);
		virtual void MouseUp(BPoint where);
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
