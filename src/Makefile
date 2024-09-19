all: clean install run
# clear && cd desktop && rm -rf build && mkdir build && cd build && cmake .. && cmake --build . && ./viewer -platform xcb && cd ../..

install:
# убрать "DEFINES+=" если будут не нужны
	@cd desktop && qmake "DEFINES+=" desktop.pro -o Makefile.viewer 
	@$(MAKE) -C desktop -f Makefile.viewer 
	@mv desktop/desktop 3Dviewer

run:
	@./3Dviewer

uninstall:
	@rm -rf 3Dviewer

clean:
	@rm -rf build-* 
	@rm -rf desktop/.qmake* desktop/*.user desktop/moc_* desktop/*.o
	@rm -rf desktop/Makefile* desktop/ui_mainwindow.h

# для гиф: