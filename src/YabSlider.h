#ifndef YABSLIDER_H
#define YABSLIDER_H

#include <Slider.h>

class YabSlider : public BSlider
{
	public:
		YabSlider(BRect frame,const char *name,const char *label,BMessage *message,int32 minValue,int32 maxValue,thumb_style thumbType = B_BLOCK_THUMB,uint32 resizingMode = B_FOLLOW_LEFT | B_FOLLOW_TOP,uint32 flags = B_NAVIGABLE | B_WILL_DRAW | B_FRAME_EVENTS);
		YabSlider(BRect frame,const char *name,const char *label,BMessage *message,int32 minValue,int32 maxValue,orientation posture /*= B_HORIZONTAL*/,thumb_style thumbType = B_BLOCK_THUMB,uint32 resizingMode = B_FOLLOW_LEFT | B_FOLLOW_TOP,uint32 flags = B_NAVIGABLE | B_WILL_DRAW | B_FRAME_EVENTS);
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
