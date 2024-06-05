CC = gcc
CFLAGS = -Wall -Werror -Wextra
C11 = -std=c11

CPP = cppcheck --enable=all --suppress=missingIncludeSystem

MAIN = main.c

BUILD_BRICKS = build

CFILES_BACK_LIB = $(shell find brickgame -name '*.c')
OBJS_BACK_LIB = $(CFILES_BACK_LIB:%.c=%.o)

CFILES_GUI_LIB = $(shell find gui -name '*.c')
OBJS_GUI_LIB = $(CFILES_GUI_LIB:%.c=%.o)

CFILES_TEST_LIB = $(shell find tests -name '*.c')
OBJS_TEST_LIB = $(CFILES_TEST_LIB:%.c=%.o)

CHECK_LIBS = -lcheck  -lm -lncurses

all: s21_bricks

install: s21_bricks.a gui_lib
	$(CC) $(CFLAGS) $(C11) main.c $(OBJS_BACK_LIB) $(OBJS_GUI_LIB) -o ../s21_bricks $(CHECK_LIBS)

s21_bricks: s21_bricks.a gui_lib final

$(OBJS_BACK_LIB): %.o: %.c
		$(CC) $(CFLAGS) $(C11) -c $< -o $@

$(OBJS_GUI_LIB): %.o: %.c
		$(CC) $(CFLAGS) $(C11) -c $< -o $@

$(OBJS_TEST_LIB): %.o: %.c
		$(CC) $(CFLAGS) $(C11) -c $< -o $@

s21_bricks.a: $(OBJS_BACK_LIB)

gui_lib: $(OBJS_GUI_LIB)

test_lib: $(OBJS_TEST_LIB)

final:
		$(CC) $(CFLAGS) $(C11) main.c $(OBJS_BACK_LIB) $(OBJS_GUI_LIB) -o s21_bricks $(CHECK_LIBS)
		rm -rf $(OBJS_GUI_LIB)
		rm -rf $(OBJS_BACK_LIB)

test: s21_bricks.a gui_lib test_lib
		$(CC) $(CFLAGS) $(C11) $(OBJS_BACK_LIB) $(OBJS_GUI_LIB) $(OBJS_TEST_LIB) -o s21_bricks_tests $(CHECK_LIBS) 
		rm -rf $(OBJS_GUI_LIB)
		rm -rf $(OBJS_BACK_LIB)
		rm -rf $(OBJS_TEST_LIB)

debug_test:
		$(CC) -g -o debug_test $(CFILES_BACK_LIB) $(CFILES_GUI_LIB) $(CFILES_TEST_LIB) $(CHECK_LIBS) 
		rm -rf $(OBJS_GUI_LIB)
		rm -rf $(OBJS_BACK_LIB)
		rm -rf $(OBJS_TEST_LIB)

debug_out: s21_bricks.a gui_lib
	gcc -g -o deb_bricks main.c $(CFILES_BACK_LIB) $(CFILES_GUI_LIB) $(CHECK_LIBS)
		rm -rf $(OBJS_GUI_LIB)
		rm -rf $(OBJS_BACK_LIB)
		rm -rf s21_bricks.a gui_bricks.a

gcov_report:
		$(CC) --coverage $(CFLAGS) $(CFILES_BACK_LIB) $(CFILES_GUI_LIB) $(CFILES_TEST_LIB) -o test -lcheck  -lm -lncurses
		./test
		lcov -t "test" -o test.info -c -d ./
		genhtml -o report test.info

gcovr_report: clean
	rm -rf report/
	mkdir report/
	$(CC) --coverage $(CFLAGS) $(CFLAGS) $(CFILES_BACK_LIB) $(CFILES_GUI_LIB) $(CFILES_TEST_LIB) -o test -lcheck -lm -lncurses
	./test
	python3 -m gcovr  --root . --html-medium-threshold 50 --html-high-threshold 80 --exclude tests/ --html --html-details  -o report/coverage_report.html

dvi:
	# cp ../documentation/README.md .
	cp ../documentation/Doxyfile .
	doxygen Doxyfile
	cd latex && xelatex refman.tex
	open latex/refman.pdf
	rm -rf Doxyfile README.md refman.log texput.log

cppcheck:
		$(CPP) $(CFILES)

clang_check:
		find -name "*.c" -o -name "*.h" | xargs clang-format -n

dist:
	tar -cvzf BricksGame-1.tar.gz s21_bricks README.md

clean:
		rm -f s21_bricks $(OBJS_BACK_LIB) $(OBJS_GUI_LIB) $(OBJS_TEST_LIB) build/main.o $(MY_LIB)
		rm -rf *.gcda *.info *.gcno
		rm -rf *.out report/* test
		rm -rf s21_bricks_tests
		rm -rf deb_bricks debug_test
		rm -rf latex/ BricksGame-1.tar.gz BricksGame-1/
		rm -rf Doxyfile README.md refman.log texput.log

uninstall: clean
	rm -rf ../s21_bricks

rebuild: clean s21_bricks