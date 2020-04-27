#ifndef YABTABVIEWZETA_H
#define YABTABVIEWZETA_H

#include <experimental/TabView.h>
#include <interface/Control.h>
#include <interface/StackedViewManager.h>
#include <support/Vector.h>

class YabTabView : public BTabView
{
	public:
		YabTabView(BRect _frame, 
								         const BString& _name, 
								         uint32 _resize = B_FOLLOW_LEFT | B_FOLLOW_TOP, 
								         uint32 _flags = B_WILL_DRAW, 
								         BMessage* _message = NULL,
								         tab_orientation _orient = toTop);
		virtual void MouseMoved(BPoint point, uint32 transit, const BMessage *message);
		virtual void MouseUp(BPoint point);
		virtual void MouseDown(BPoint point);
		virtual void SelectionChanged(size_t _index);
		int FocusChanged;
		int OldTabView;
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
