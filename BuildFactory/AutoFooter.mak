##
## GCC Options
##
GCC = gcc
GCC_OPT = $(DBG) $(OPT) -I. -I/boot/home/config/include/ $(INCNCURSES) -DHAVE_CONFIG -DUNIX
GPP = g++
GPP_OPT = $(DBG) $(OPT) -I. -DHAVE_CONFIG -DUNIX 

##
## Compile and link
##
yab: flex.o YabMain.o YabInterface.o YabWindow.o YabView.o $(FILEPANEL) $(FILEPANELLOOPER) YabList.o $(YABTEXT) $(BUBBLE) bison.o symbol.o function.o graphic.o io.o main.o $(CLV) $(CLVYAB) $(CLVCOLOR) $(YABSTACKVIEW) $(SPLITPANE) $(URLVIEW) $(HAIKUTAB) $(SPINNER) YabControl.o YabTextControl.o YabStringView.o YabButton.o YabPictureButton.o YabBitmapView.o YabOutlineListView.o YabListView.o YabMenuField.o YabPopUpMenu.o YabCheckBox.o YabColorControl.o YabRadioButton.o YabSlider.o YabScrollView.o $(ZETATAB)
	$(GPP) $(GPP_OPT) -o $(TARGET) flex.o YabMain.o YabInterface.o YabWindow.o YabView.o $(FILEPANEL) $(FILEPANELLOOPER) YabList.o $(YABTEXT) $(BUBBLE) bison.o symbol.o function.o graphic.o io.o main.o $(CLV) $(CLVYAB) $(CLVCOLOR) $(YABSTACKVIEW) $(SPLITPANE) $(URLVIEW) $(HAIKUTAB) $(SPINNER) $(LIBPATH) $(LIB) $(LIBGAME) $(LIBTRACKER) $(ZETALIB) $(LIBNCURSES) $(CALENDAR) YabControl.o YabTextControl.o YabStringView.o YabButton.o YabPictureButton.o YabBitmapView.o YabOutlineListView.o YabListView.o YabMenuField.o YabPopUpMenu.o YabCheckBox.o YabColorControl.o YabRadioButton.o YabSlider.o YabScrollView.o $(ZETATAB) -lz
YabMain.o: YabMain.cpp 
	$(GPP) $(GPP_OPT) -c YabMain.cpp -o YabMain.o
YabInterface.o: YabInterface.cpp YabInterface.h global.h YabMenu.h
	$(GPP) $(GPP_OPT) -c YabInterface.cpp -o YabInterface.o
YabWindow.o: YabWindow.cpp YabWindow.h
	$(GPP) $(GPP_OPT) -c YabWindow.cpp -o YabWindow.o
YabView.o: YabView.cpp YabView.h
	$(GPP) $(GPP_OPT) -c YabView.cpp -o YabView.o
$(BUBBLE): BubbleHelper.cpp BubbleHelper.h
	$(GPP) $(GPP_OPT) -c BubbleHelper.cpp -o BubbleHelper.o
$(FILEPANEL): YabFilePanel.cpp YabFilePanel.h
	$(GPP) $(GPP_OPT) -c YabFilePanel.cpp -o YabFilePanel.o
$(FILEPANELLOOPER): YabFilePanelLooper.cpp YabFilePanelLooper.h
	$(GPP) $(GPP_OPT) -c YabFilePanelLooper.cpp -o YabFilePanelLooper.o
YabList.o: YabList.cpp YabList.h
	$(GPP) $(GPP_OPT) -c YabList.cpp -o YabList.o
$(YABTEXT): YabText.cpp YabText.h
	$(GPP) $(GPP_OPT) -c YabText.cpp -o YabText.o
bison.o: bison.c yabasic.h config.h 
	$(GCC) $(GCC_OPT) -c bison.c -o bison.o
flex.o: flex.c bison.c yabasic.h config.h
	$(GCC) $(GCC_OPT) -c flex.c -o flex.o
function.o: function.c yabasic.h config.h
	$(GCC) $(GCC_OPT) -c function.c -o function.o
io.o: io.c yabasic.h config.h
	$(GCC) $(GCC_OPT) -c io.c -o io.o
graphic.o: graphic.c yabasic.h config.h
	$(GCC) $(GCC_OPT) -c graphic.c -o graphic.o
symbol.o: symbol.c yabasic.h config.h
	$(GCC) $(GCC_OPT) -c symbol.c -o symbol.o
main.o: main.c yabasic.h config.h
	$(GCC) $(GCC_OPT) -c main.c -o main.o
$(YABSTACKVIEW): YabStackView.cpp YabStackView.h
	$(GCC) $(GCC_OPT) -c YabStackView.cpp -o YabStackView.o
$(SPLITPANE): SplitPane.cpp SplitPane.h 
	$(GCC) $(GCC_OPT) -c SplitPane.cpp -o SplitPane.o
$(URLVIEW): URLView.cpp URLView.h
	$(GCC) $(GCC_OPT) -c URLView.cpp -o URLView.o
$(SPINNER): Spinner.cpp Spinner.h global.h
	$(GCC) $(GCC_OPT) -c Spinner.cpp -o Spinner.o
$(CLV): column/ColumnListView.cpp column/ColumnListView.h column/ObjectList.h 
	$(GCC) $(GCC_OPT) -c column/ColumnListView.cpp -o column/ColumnListView.o
$(CLVCOLOR): column/ColorTools.cpp column/ColorTools.h 
	$(GCC) $(GCC_OPT) -c column/ColorTools.cpp -o column/ColorTools.o
$(CLVYAB): column/YabColumnType.cpp column/YabColumnType.h
	$(GCC) $(GCC_OPT) -c column/YabColumnType.cpp -o column/YabColumnType.o
$(HAIKUTAB): YabTabView.cpp YabTabView.h
	$(GCC) $(GCC_OPT) -c YabTabView.cpp -o YabTabView.o

YabControl.o: YabControl.cpp YabControl.h
	$(GPP) $(GPP_OPT) -c YabControl.cpp -o YabControl.o
YabTabViewZeta.o: YabTabViewZeta.cpp YabTabViewZeta.h
	$(GPP) $(GPP_OPT) -c YabTabViewZeta.cpp -o YabTabViewZeta.o
YabSlider.o: YabSlider.cpp YabSlider.h
	$(GPP) $(GPP_OPT) -c YabSlider.cpp -o YabSlider.o
YabRadioButton.o: YabRadioButton.cpp YabRadioButton.h
	$(GPP) $(GPP_OPT) -c YabRadioButton.cpp -o YabRadioButton.o
YabColorControl.o: YabColorControl.cpp YabColorControl.h
	$(GPP) $(GPP_OPT) -c YabColorControl.cpp -o YabColorControl.o
YabCheckBox.o: YabCheckBox.cpp YabCheckBox.h
	$(GPP) $(GPP_OPT) -c YabCheckBox.cpp -o YabCheckBox.o
YabPopUpMenu.o: YabPopUpMenu.cpp YabPopUpMenu.h
	$(GPP) $(GPP_OPT) -c YabPopUpMenu.cpp -o YabPopUpMenu.o
YabMenuField.o: YabMenuField.cpp YabMenuField.h
	$(GPP) $(GPP_OPT) -c YabMenuField.cpp -o YabMenuField.o
YabListView.o: YabListView.cpp YabListView.h
	$(GPP) $(GPP_OPT) -c YabListView.cpp -o YabListView.o
YabOutlineListView.o: YabOutlineListView.cpp YabOutlineListView.h
	$(GPP) $(GPP_OPT) -c YabOutlineListView.cpp -o YabOutlineListView.o
YabScrollView.o: YabScrollView.cpp YabScrollView.h
	$(GPP) $(GPP_OPT) -c YabScrollView.cpp -o YabScrollView.o
YabTextControl.o: YabTextControl.cpp YabTextControl.h
	$(GPP) $(GPP_OPT) -c YabTextControl.cpp -o YabTextControl.o
YabStringView.o: YabStringView.cpp YabStringView.h 
	$(GPP) $(GPP_OPT) -c YabStringView.cpp -o YabStringView.o
YabButton.o: YabButton.cpp YabButton.h
	$(GPP) $(GPP_OPT) -c YabButton.cpp -o YabButton.o
YabPictureButton.o: YabPictureButton.cpp YabPictureButton.h
	$(GPP) $(GPP_OPT) -c YabPictureButton.cpp -o YabPictureButton.o
YabBitmapView.o: YabBitmapView.cpp YabBitmapView.h
	$(GPP) $(GPP_OPT) -c YabBitmapView.cpp -o YabBitmapView.o  

clean:
	rm -f core *.o column/*.o 
