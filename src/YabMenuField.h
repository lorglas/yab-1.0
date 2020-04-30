#ifndef YABMENUFIELD_H
#define YABMENUFIELD_H

#include <MenuField.h>
#include "global.h"

class YabMenuField : public BMenuField
{
	public:
		YabMenuField(BRect frame,const char *name,const char *label,BMenu *menu,uint32 resize = B_FOLLOW_LEFT|B_FOLLOW_TOP,uint32 flags = B_WILL_DRAW | B_NAVIGABLE);
		#ifdef ZETA
		YabMenuField(BRect frame,const char *name,const char *label,BMenu *menu,bool fixed_size,uint32 resize = B_FOLLOW_LEFT|B_FOLLOW_TOP,uint32 flags = B_WILL_DRAW | B_NAVIGABLE);
		#endif
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
