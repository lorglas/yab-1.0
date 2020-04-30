#ifndef _ZETA_USING_EXPERIMENTAL_
#define _ZETA_USING_EXPERIMENTAL_ 1
#endif

#include "global.h"
#ifdef BUILD_ZETATAB

#include <Region.h>
#include <experimental/TabView.h>
#include "YabTabViewZeta.h"

YabTabView::YabTabView(BRect _frame,const BString& _name,uint32 _resize,uint32 _flags,BMessage* _message)
	:BTabView(_frame,_name,_resize,_flags,_message)
{
	FocusChanged = 1;	
	OldTabView=1;	
}

void YabTabView::SelectionChanged(size_t _index)
{
	FocusChanged = (int)_index+1;
	BTabView::SelectionChanged(_index);
}

#endif
