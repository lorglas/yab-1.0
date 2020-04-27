//------------------------------------------------------------------------------
//      Copyright (c) 2001-2005, Haiku
//
//      Permission is hereby granted, free of charge, to any person obtaining a
//      copy of this software and associated documentation files (the "Software"),
//      to deal in the Software without restriction, including without limitation
//      the rights to use, copy, modify, merge, publish, distribute, sublicense,
//      and/or sell copies of the Software, and to permit persons to whom the
//      Software is furnished to do so, subject to the following conditions:
//
//      The above copyright notice and this permission notice shall be included in
//      all copies or substantial portions of the Software.
//
//      THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//      IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//      FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//      AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//      LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
//      FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
//      DEALINGS IN THE SOFTWARE.
//
//      File Name:              YabTabView.cpp
//      Author:                 Marc Flerackers (mflerackers@androme.be)
//				Modified by Jan Bungeroth (jan@be-logos.org)
//      Description:  YabTabView provides the framework for containing and
//                  managing groups of BView objects. Modified for *sane*
//		    view handling (they stay connected to the window).
//------------------------------------------------------------------------------   

#include <List.h>
#include <Rect.h>  
#include <String.h>
#include <View.h>  
#include <stdio.h>
#include "YabTabView.h"

#include "global.h"
#ifdef BUILD_HAIKUTAB

#define X_OFFSET 0.0f

YabTabView::YabTabView(BRect frame, const char* name, button_width width, uint32 resizingMode, uint32 flags)
	: BView(frame, name, resizingMode, flags)
{
        fTabList = new BList;
	fTabNames = new BList;

	// SetFont(be_bold_font);

	fTabWidthSetting = width;

        fSelection = 0;
        fFocus = -1;

        rgb_color color = ui_color(B_PANEL_BACKGROUND_COLOR);

        SetViewColor(color);
        SetLowColor(color);

        font_height fh;
        GetFontHeight(&fh);
        fTabHeight = fh.ascent + fh.descent + fh.leading + 10.0f;

        BRect bounds = Bounds();

        bounds.top += TabHeight();
        bounds.InsetBy(5.0f, 5.0f);

        fContainerView = new BView(bounds, "view container", B_FOLLOW_ALL,
                B_WILL_DRAW);

        fContainerView->SetViewColor(color);
        fContainerView->SetLowColor(color);

        AddChild(fContainerView);  
        FocusChanged = 1;
        OldTabView = 1;
}

YabTabView::~YabTabView()
{
	for(int i=0; i<CountTabs(); i++)
	{
		delete TabAt(i);
		delete fTabNames->RemoveItem(i);
	}

	delete fTabList;
	delete fTabNames;
}

void YabTabView::AddTab(BView *tabView, const char* label)
{
	if(tabView)
	{
               	tabView->Hide();
		fContainerView->AddChild(tabView);
		Invalidate();
              	if(CountTabs() == 0) tabView->Show();


		fTabList->AddItem(tabView);
		fTabNames->AddItem(new BString(label));
	}
}

BView* YabTabView::RemoveTab(int32 index)
{
	if(index < 0 || index >= CountTabs())
		return NULL;
	
	BView *tab = (BView*)fTabList->RemoveItem(index);
	delete fTabNames->RemoveItem(index);

        if (index <= fSelection && fSelection != 0)
                fSelection--;

        Select(fSelection);

        if (fFocus == CountTabs() - 1)
                SetFocusTab(fFocus, false);
        else
                SetFocusTab(fFocus, true);

        return tab; 	
}

int32 YabTabView::CountTabs() const
{
	return fTabList->CountItems();
}

int32 YabTabView::Selection() const
{
        return fSelection;
}  

void YabTabView::Select(int32 index)
{
        if (index < 0 || index >= CountTabs())
                index = Selection();

        BView *tab = TabAt(Selection());
        if (tab)
	{
		Invalidate();
		tab->Hide();
	}

        tab = TabAt(index);
        if (tab) 
	{
		Invalidate();
                tab->Show();
                fSelection = index;
                FocusChanged = index+1;
        }

}

void YabTabView::MakeFocus(bool focused)
{
        BView::MakeFocus(focused);

        SetFocusTab(Selection(), focused);
}    

int32 YabTabView::FocusTab() const
{
        return fFocus;
} 

void YabTabView::SetFocusTab(int32 tab, bool focused)
{
        if (tab >= CountTabs())
                return;

        if (focused) 
	{
                if (tab == fFocus)
		{
                        Invalidate(TabFrame(fFocus));
                        return;
		}

                if (fFocus != -1)
		{
                        // TabAt(fFocus)->MakeFocus(false);
                        Invalidate(TabFrame(fFocus));
                }
                if (tab != -1) 
		{
                        // TabAt(tab)->MakeFocus(true);
                        Invalidate(TabFrame(tab));
                }

                fFocus = tab;
        } 
	else if (fFocus != -1) 
	{
                // TabAt(fFocus)->MakeFocus(false);
                Invalidate(TabFrame(fFocus));
		fFocus = -1;
        }
}

BView* YabTabView::TabAt(int32 index)
{
	if(index < 0 || index >= CountTabs())
		return NULL;

	return (BView*)fTabList->ItemAt(index);
}     

const char* YabTabView::GetTabName(int32 index) const
{
	if(index < 0 || index >= CountTabs())
		return NULL; 

	return ((BString*)fTabNames->ItemAt(index))->String();
}

void YabTabView::KeyDown(const char *bytes, int32 numBytes)
{
        if (IsHidden())
                return;

        switch (bytes[0]) {
                case B_DOWN_ARROW:
                case B_LEFT_ARROW: {
                        int32 focus = fFocus - 1;
                        if (focus < 0)
                                focus = CountTabs() - 1;
                        SetFocusTab(focus, true);
                        FocusChanged = 1;
                        break;
                }

                case B_UP_ARROW:
                case B_RIGHT_ARROW: {
                        int32 focus = fFocus + 1;
                        if (focus >= CountTabs())
                                focus = 0;
                        SetFocusTab(focus, true);
                        FocusChanged = 1;
                        break;
                }

                case B_RETURN:
                case B_SPACE:
                        Select(FocusTab());
                        break;

                default:
                        BView::KeyDown(bytes, numBytes);
        }
}  

void YabTabView::MouseDown(BPoint point)
{
        if (point.y > fTabHeight)
                return;

        for (int32 i = 0; i < CountTabs(); i++) {
                if (TabFrame(i).Contains(point) && i != Selection()) {
                        Select(i);
			fFocus = -1;
                        return;
                }
        }

        BView::MouseDown(point);
}      

BRect YabTabView::TabFrame(int32 tab_index) const
{
        switch (fTabWidthSetting) {
                case B_WIDTH_FROM_LABEL:
                {
                        float x = X_OFFSET;
                        for (int32 i = 0; i < tab_index; i++)
			{
                                x += StringWidth(GetTabName(i)) + 20.0f;
			}

                        return BRect(x, 0.0f, x + StringWidth(GetTabName(tab_index)) + 20.0f, fTabHeight);
                }

                case B_WIDTH_FROM_WIDEST:
                {	
                        float width = 0.0f;

                        for (int32 i = 0; i < CountTabs(); i++) {
                                float tabWidth = StringWidth(GetTabName(i)) + 20.0f;

                                if (tabWidth > width)
                                        width = tabWidth;
                        }

                        return BRect(X_OFFSET + tab_index * width, 0.0f,
                                X_OFFSET + tab_index * width + width, fTabHeight);
                }

                case B_WIDTH_AS_USUAL:
                default:
                        return BRect(X_OFFSET + tab_index * 100.0f, 0.0f,
                                X_OFFSET + tab_index * 100.0f + 100.0f, fTabHeight);
        }
}  

void YabTabView::SetTabWidth(button_width width)
{
        fTabWidthSetting = width;

        Invalidate();
}  

button_width YabTabView::TabWidth() const
{
        return fTabWidthSetting;
}  

void YabTabView::SetTabHeight(float height)
{
        if (fTabHeight == height)
                return;

        fContainerView->MoveBy(0.0f, height - fTabHeight);
        fContainerView->ResizeBy(0.0f, height - fTabHeight);

        fTabHeight = height;

        Invalidate();
}


float YabTabView::TabHeight()
{
        return fTabHeight;
}


BView *YabTabView::ContainerView()
{
        return fContainerView;
}  

void YabTabView::Draw(BRect updateRect)
{
        DrawBox(DrawTabs());

        if (IsFocus() && fFocus != -1)
	{
		DrawFocusMark(TabFrame(fFocus), fFocus);
		// Invalidate(TabFrame(fFocus));
	}
}


BRect YabTabView::DrawTabs()
{
        for (int32 i = 0; i < CountTabs(); i++)
                DrawTab(TabFrame(i), i, i == fSelection ? B_TAB_FRONT : (i == 0) ? B_TAB_FIRST : B_TAB_ANY, i + 1 != fSelection);

        if (fSelection < CountTabs())
                return TabFrame(fSelection);

        return BRect();
}      

void YabTabView::DrawLabel(int32 current, BRect frame)
{
        const char *label = GetTabName(current);
        if (label == NULL)
                return;

        SetHighColor(0, 0, 0);
        float width = StringWidth(label);
        // TODO: remove offset
        float offset = frame.Height() / 2.0;
        DrawString(label, BPoint((frame.left + frame.right - width + offset) / 2.0, frame.bottom - 4.0f - 2.0f));
}


void YabTabView::DrawTab(BRect frame, int32 current, tab_position position, bool full)
{
        rgb_color no_tint = ui_color(B_PANEL_BACKGROUND_COLOR);
        rgb_color lightenmax = tint_color(no_tint, B_LIGHTEN_MAX_TINT);
        rgb_color darken2 = tint_color(no_tint, B_DARKEN_2_TINT);
        rgb_color darken3 = tint_color(no_tint, B_DARKEN_3_TINT);
        rgb_color darken4 = tint_color(no_tint, B_DARKEN_4_TINT);
        rgb_color darkenmax = tint_color(no_tint, B_DARKEN_MAX_TINT);

        SetHighColor(darkenmax);
        SetLowColor(no_tint);
        DrawLabel(current, frame);

        SetDrawingMode(B_OP_OVER);

        BeginLineArray(12); 

        int32 slopeWidth = (int32)ceilf(frame.Height() / 2.0);

        if (position != B_TAB_ANY) {
                // full height left side
                AddLine(BPoint(frame.left, frame.bottom),
                                           BPoint(frame.left + slopeWidth, frame.top), darken3);
                AddLine(BPoint(frame.left, frame.bottom + 1),
                                           BPoint(frame.left + slopeWidth, frame.top + 1), lightenmax);
        } else {
                // upper half of left side
                AddLine(BPoint(frame.left + slopeWidth / 2, frame.bottom - slopeWidth),
                                           BPoint(frame.left + slopeWidth, frame.top), darken3);
                AddLine(BPoint(frame.left + slopeWidth / 2 + 2, frame.bottom - slopeWidth - 1),
                                           BPoint(frame.left + slopeWidth, frame.top + 1), lightenmax);
        }

        // lines along the top
        AddLine(BPoint(frame.left + slopeWidth, frame.top),
                                   BPoint(frame.right, frame.top), darken3);
        AddLine(BPoint(frame.left + slopeWidth, frame.top + 1),
                                   BPoint(frame.right, frame.top + 1), lightenmax);

        if (full) {
                // full height right side
                AddLine(BPoint(frame.right, frame.top),
                                           BPoint(frame.right + slopeWidth + 2, frame.bottom), darken2);
                AddLine(BPoint(frame.right, frame.top + 1),
                                           BPoint(frame.right + slopeWidth + 1, frame.bottom), darken4);
        } else {
                // upper half of right side
                AddLine(BPoint(frame.right, frame.top),
                                           BPoint(frame.right + slopeWidth / 2 + 1,
                                                          frame.bottom - slopeWidth), darken2);
                AddLine(BPoint(frame.right, frame.top + 1),
                                           BPoint(frame.right + slopeWidth / 2,
                                                          frame.bottom - slopeWidth), darken4);
        }

        EndLineArray();
} 

void YabTabView::DrawFocusMark(BRect frame, int32 current)
{
        float width = StringWidth(GetTabName(current));

        SetHighColor(ui_color(B_KEYBOARD_NAVIGATION_COLOR));
        float offset = frame.Height() / 2.0;
        StrokeLine(BPoint((frame.left + frame.right - width + offset) / 2.0, frame.bottom - 3),
                                          BPoint((frame.left + frame.right + width + offset) / 2.0, frame.bottom
- 3));
	// Invalidate(frame);
}  

void YabTabView::DrawBox(BRect selTabRect)
{
        BRect rect = Bounds();
        BRect lastTabRect = TabFrame(CountTabs() - 1);

        rgb_color noTint = ui_color(B_PANEL_BACKGROUND_COLOR);
        rgb_color lightenMax = tint_color(noTint, B_LIGHTEN_MAX_TINT);
        rgb_color darken1 = tint_color(noTint, B_DARKEN_1_TINT);
        rgb_color darken2 = tint_color(noTint, B_DARKEN_2_TINT);
        rgb_color darken4 = tint_color(noTint, B_DARKEN_4_TINT);

        BeginLineArray(12);

        int32 offset = (int32)ceilf(selTabRect.Height() / 2.0);

        // outer lines
        AddLine(BPoint(rect.left, rect.bottom - 1),
                        BPoint(rect.left, selTabRect.bottom), darken2);
        if (selTabRect.left >= rect.left + 1)
                AddLine(BPoint(rect.left + 1, selTabRect.bottom),
                                BPoint(selTabRect.left, selTabRect.bottom), darken2);
        if (selTabRect.right + offset + 1 <= rect.right - 1)
                AddLine(BPoint(selTabRect.right + offset + 1, selTabRect.bottom),
                                BPoint(rect.right - 1, selTabRect.bottom), darken2);
        AddLine(BPoint(rect.right, selTabRect.bottom + 2),
                        BPoint(rect.right, rect.bottom), darken2);
        AddLine(BPoint(rect.right - 1, rect.bottom),
                        BPoint(rect.left + 2, rect.bottom), darken2);

        // inner lines
        rect.InsetBy(1, 1);
        selTabRect.bottom += 1;

        AddLine(BPoint(rect.left, rect.bottom - 2),
                        BPoint(rect.left, selTabRect.bottom), lightenMax);
        if (selTabRect.left >= rect.left + 1)
                AddLine(BPoint(rect.left + 1, selTabRect.bottom),
                                BPoint(selTabRect.left, selTabRect.bottom), lightenMax);
        if (selTabRect.right + offset + 1 <= rect.right - 2)  
		AddLine(BPoint(selTabRect.right + offset + 1, selTabRect.bottom),
                                BPoint(rect.right - 2, selTabRect.bottom), lightenMax);
        AddLine(BPoint(rect.right, selTabRect.bottom),
                        BPoint(rect.right, rect.bottom), darken4);
        AddLine(BPoint(rect.right - 1, rect.bottom),
                        BPoint(rect.left, rect.bottom), darken4);

        // soft inner bevel at right/bottom
        rect.right--;
        rect.bottom--;

        AddLine(BPoint(rect.right, selTabRect.bottom + 1),
                        BPoint(rect.right, rect.bottom), darken1);
        AddLine(BPoint(rect.right - 1, rect.bottom),
                        BPoint(rect.left + 1, rect.bottom), darken1);

        EndLineArray();
}

#endif
