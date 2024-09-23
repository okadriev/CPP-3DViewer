CC = g++

TEST_SRC = $(wildcard tests/*.cpp)
TEST_OBJ = $(patsubst %.cpp,%.o,$(TEST_SRC))
TEST_FILES = $(wildcard ) 																   ##ДОБАВИТЬ ФАЙЛЫ КОТОРЫЕ НУЖНО ПРОВЕРЯТЬ
TEST_FILES_OBJ = $(patsubst %.cpp,%.o,$(TEST_FILES))
TEST_EXEC = tests/test

# GIF_FLAGS = -lgif
# GTK_CAIRO_FLAGS = `pkg-config --cflags --libs gtk+-3.0 cairo`
GIF_FLAG = -lgif
GFLAG = -fprofile-arcs -ftest-coverage
TFLAG = -lcheck -lsubunit -lm
CFLAGS = -Wall -Wextra -Werror -std=c++17 -g

MAIN_SRC= $(wildcard 3D_Viewer_2.0.cpp )
MAIN_OBJ= $(patsubst %.cpp,%.o,$(MAIN_SRC))

VIEW_SRC= $(wildcard ./desktop/*.cpp )
VIEW_OBJ= $(patsubst %.cpp,%.o,$(VIEW_SRC))
VIEW_LIB = view.a

CNTRL_SRC= $(wildcard ./controller/*.cpp )
CNTRL_OBJ= $(patsubst %.cpp,%.o,$(CNTRL_SRC))
CNTRL_LIB = controller.a

MODEL_SRC = $(wildcard ./viewer/*/*.cpp )
MODEL_OBJ = $(SCREEN_SRC:.cpp=.o)
MODEL_LIB = model.a

BUILD_DIR = build
EXEC = desktop

all: install run

# $(VIEW_LIB): $(VIEW_OBJ)
# 	@ar rcs $(VIEW_LIB) $(VIEW_OBJ) 
# 	@ranlib $(VIEW_LIB)
# 	@rm -f $(VIEW_OBJ) 
# .PHONY: $(VIEW_LIB)

# $(CNTRL_LIB): $(CNTRL_OBJ)
# 	@ar rcs $(CNTRL_LIB) $(CNTRL_OBJ) 
# 	@ranlib $(CNTRL_LIB)
# 	@rm -f $(CNTRL_OBJ) 
# .PHONY: $(CNTRL_LIB)

# $(MODEL_LIB): $(MODEL_OBJ) 
# 	@ar rcs $(MODEL_LIB) $(MODEL_OBJ) 
# 	@ranlib $(MODEL_LIB)
# 	@rm -f $(MODEL_OBJ) 
# .PHONY: $(MODEL_LIB)

install:
	@clear
	@cd desktop && qmake desktop.pro -o Makefile.viewer
	@$(MAKE) -C desktop -f Makefile.viewer
	@mkdir $(BUILD_DIR)
	@mv desktop/desktop $(BUILD_DIR)
.PHONY: install

run: install
	@./$(BUILD_DIR)/$(EXEC)
.PHONY: run

uninstall:
	@rm -rf $(BUILD_DIR) ../setting.txt *.a
.PHONY: uninstall

reinstall: clean uninstall install

dvi: 
	# sudo apt-get install texlive-xetex
	# sudo apt-get install texlive-lang-cyrillic
	# sudo apt-get install doxygen
	@clear
	@cp docs/Doxyfile .
	@cp docs/README.md .
	@doxygen Doxyfile
	@cd latex && make
	@open latex/refman.pdf
	@rm -rf Doxyfile README.md latex/*.tex latex/*.tmp latex/*.aux latex/*.log latex/*.out latex/*.dot latex/*.sty latex/*.idx latex/*.toc latex/*.jpg latex/*.png latex/*.ilg latex/*.ind latex/Makefile
.PHONY: dvi

dist: install
	@clear
	@tar -cvzf breack_game.tgz $(BUILD_DIR)
.PHONY: dist

gcov_report: clean
	@clear 
	@$(CC) $(CFLAGS) -g -c  gtk/s21_parce.c -o s21_parce.o --coverage
	@$(CC) $(CFLAGS) -g -c   gtk/s21_matrix.c -o s21_matrix.o --coverage
	@$(CC) $(CFLAGS) $(GFLAG) -o gcov_r $(TEST_SRC) s21_parce.o s21_matrix.o $(TFLAG)
	@mkdir coverage_report
	@./gcov_r
	@python3 -m gcovr -r . --html --html-details -o coverage_report/index.html --exclude test
	@rm -f *.gcno *.gcda *.o gcov_r
	@rm -f */*/*.gcno */*/*.gcda
	@rm -f */*.gcno */*.gcda
.PHONY: gcov_report

leak_check: 
	@clear
	@valgrind --tool=memcheck --leak-check=yes ./$(TEST_EXEC)
.PHONY: leak_check

# cpp_check: 
# 	@clear
# 	@cppcheck --enable=all --suppress=missingIncludeSystem --language=c++ $(TEST_SRS) $(VIEW_SRC) $(MODEL_SRC) $(MAIN_SRC)
# .PHONY: cpp_check

# clang_check:
# 	@clear
# 	@cp ../materials/linters/.clang-format .
# 	@clang-format -n $(TEST_SRS) $(VIEW_SRC) $(MODEL_SRC) $(MAIN_SRC)
# .PHONY: clang_check

clean:
	@rm -f $(TEST_OBJ) $(TEST_EXEC)
	@rm -rf $(BUILD_DIR) latex html */*.o
	@rm -f $(VIEW_LIB) $(MODEL_LIB)
	@rm -rf coverage_report gcov_r Doxyfile README.md
	@rm -f desktop/Makefile.viewer desktop/.qmake.stash desktop/ui_mainwindow.h desktop/*.user desktop/moc*
.PHONY: clean

test: clean $(TEST_OBJ)
	@$(CC) $(TEST_OBJ) -o tests/test.exe -lcheck -lm -lrt -lpthread -lsubunit -g ##!!!!!!!!!!!!!
	@./tests/test.exe 

%.o: %.cpp
	@$(CC) $(CFLAGS) $(GIF_FLAG) -cpp $< -o $@