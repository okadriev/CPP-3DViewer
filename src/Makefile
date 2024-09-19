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
CFLAGS = -Wall -Wextra -Werror -std=c17 -g

MAIN_SRC= $(wildcard 3D_Viewer_2.0.cpp )
MAIN_OBJ= $(patsubst %.c,%.o,$(MAIN_SRC))

DSK_SRC= $(wildcard ./desktop/*.cpp )
DSK_OBJ= $(patsubst %.c,%.o,$(DSK_SRC))
DSK_LIB = desktop.a

VWR_SRC = $(wildcard ./viewer/*/*.cpp )
VWR_OBJ = $(SCREEN_SRC:.cpp=.o)
VWR_LIB = viewer.a

BUILD_DIR = build 																					 ##### ДОБАВИТЬ В QMAKE ЧТОБЫ УСТАНАВЛИВАЛОСЬ СЮДА
EXEC = 3D_Viewer_2.0 																				 #### ДОБАВИТЬ В QMAKE ЧТОБЫ УСТАНАВЛИВАЛОСЬ СЮДА

all: install run

$(DSK_LIB): $(DSK_OBJ)
	@ar rcs $(DSK_LIB) $(DSK_OBJ) $(DSK_OBJ)
	@ranlib $(DSK_LIB)
	@rm -f $(DSK_OBJ) 
.PHONY: $(DSK_LIB)

$(VWR_LIB): $(VWR_OBJ) 
	@ar rcs $(VWR_LIB) $(VWR_OBJ) $(VWR_OBJ)
	@ranlib $(VWR_LIB)
	@rm -f $(VWR_OBJ) 
.PHONY: $(VWR_LIB)

install: clear clean $(DSK_LIB) $(VWR_LIB)
	@cd desktop && qmake && make        #####ПУСТЬ QMAKE СОБИРАЕТ ИЗ БИБЛИОТЕК VIEWER.A И DESKTOP.A И MAIN.C
	@./$(BUILD_DIR)/$(EXEC) $(PARAM)
.PHONY: install

run: install
	@./$(BUILD_DIR)/$(EXEC) $(PARAM)
.PHONY: run

uninstall:
	@rm -rf $(BUILD_DIR)
.PHONY: uninstall

dvi: clear
	# sudo apt-get install texlive-xetex
	# sudo apt-get install texlive-lang-cyrillic
	# sudo apt-get install doxygen
	@cp docs/Doxyfile .
	@cp docs/README.md .
	@doxygen Doxyfile
	@cd latex && make
	@open latex/refman.pdf
	@rm -rf Doxyfile README.md latex/*.tex latex/*.tmp latex/*.aux latex/*.log latex/*.out latex/*.dot latex/*.sty latex/*.idx latex/*.toc latex/*.jpg latex/*.png latex/*.ilg latex/*.ind latex/Makefile
.PHONY: dvi

dist: install
	@tar -cvzf breack_game.tgz $(BUILD_DIR)
.PHONY: dist

gcov_report: clear clean
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

leak_check: clear
	@valgrind --tool=memcheck --leak-check=yes ./$(TEST_EXEC)
.PHONY: leak_check

cpp_check: clear
	@cppcheck --enable=all --suppress=missingIncludeSystem --language=c++ $(TEST_SRS) $(DSK_SRC) $(VWR_SRC) $(MAIN_SRC)
.PHONY: cpp_check

clang_check: clear
	@cp ../materials/linters/.clang-format .
	@clang-format -n $(TEST_SRS) $(DSK_SRC) $(VWR_SRC) $(MAIN_SRC)
.PHONY: clang_check

clear:
	clear
.PHONY: clear

clean:
	@rm -f $(TEST_OBJ) $(TEST_EXEC)
	@rm -rf $(BUILD_DIR) latex html
	@rm -f $(DSK_LIB) $(VWR_LIB)
	@rm -rf coverage_report gcov_r Doxyfile README.md
.PHONY: clean

test: clean $(TEST_OBJ)
	@$(CC) $(TEST_OBJ) -o tests/test.exe -lcheck -lm -lrt -lpthread -lsubunit -g ##!!!!!!!!!!!!!
	@./tests/test.exe 

%.o: %.cpp
	@$(CC) $(CFLAGS) $(GIF_FLAG) -cpp $< -o $@

