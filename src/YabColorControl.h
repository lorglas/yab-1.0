#ifndef YABCOLORCONTROL_H
#define YABCOLORCONTROL_H

#include <ColorControl.h>

class YabColorControl : public BColorControl
{
	public:
		YabColorControl(BPoint start,color_control_layout layout,float cell_size,const char *name,BMessage *message = NULL,bool use_offscreen = false);
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
