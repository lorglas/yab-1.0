#ifndef YABPICTUREBUTTON_H
#define YABPICTUREBUTTON_H

#include <PictureButton.h>

class YabPictureButton : public BPictureButton
{
	public:
		YabPictureButton(BRect frame,const char* name, BPicture *off, BPicture *on,BMessage *message, uint32 behavior = B_ONE_STATE_BUTTON,uint32 resizeMask =B_FOLLOW_LEFT | B_FOLLOW_TOP, uint32 flgs = B_WILL_DRAW | B_NAVIGABLE);		
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
