CC=gcc

LDFLAGS = -L/opt/homebrew/Cellar/check/0.15.2/lib -lcheck

CFLAGS=-Wall -Werror -Wextra -I/opt/homebrew/Cellar/check/0.15.2/include
GCOV_FLAGS=-fprofile-arcs -ftest-coverage -lgcov
CHECK_FLAGS=-lcheck -lm -lpthread 
ALL_FLAGS=$(CFLAGS) $(GCOV_FLAGS) $(CHECK_FLAGS) $(LDFLAGS)
SRCS =  s21_memchr.c \
		s21_memcmp.c \
		s21_memcpy.c \
		s21_memmove.c \
		s21_memset.c \
		s21_strcat.c \
		s21_strchr.c \
		s21_strcmp.c \
		s21_strncmp.c \
		s21_strcpy.c \
		s21_strcspn.c \
		s21_strerror.c \
		s21_strlen.c \
		s21_strncat.c \
		s21_strncpy.c \
		s21_strpbrk.c \
		s21_strrchr.c \
		s21_strspn.c \
		s21_strstr.c \
		s21_strtok.c \
		s21_to_upper.c \
		s21_to_lower.c \
		s21_insert.c \
		s21_trim.c \
		s21_sprintf.c
OBJS = $(SRCS:.c=.o) s21_string_tests.o
OBJST = $(SRCS:.c=.o) 
NAME = test
REPORT_NAME = report

all: s21_string.a
	make test
# %.o: %.c
# $(CC) $(CFLAGS) $(CHECK_FLAGS) -c $< -o $@
test: $(OBJS)
	$(CC) $(CFLAGS) $(CHECK_FLAGS) $(LDFLAGS) $(OBJS) -o $(NAME)
	make clean
clean_all:
	rm -rf $(OBJS)
	rm -rf *.o
	rm -rf *.gcno
	rm -rf *.gcda
	rm -rf *.info
	rm -rf *.a
	rm -rf $(REPORT_NAME)
	rm $(NAME)
clean:
	rm -rf $(OBJS)
	rm -rf *.o
	rm -rf *.gcno
	rm -rf *.gcda
	rm -rf *.info
s21_string.a: $(OBJST)
	ar rc s21_string.a $(OBJST)
	ranlib s21_string.a
gcov_report:
	$(CC) -o $(NAME) $(SRCS) s21_string_tests.c $(ALL_FLAGS)
	./$(NAME)
	lcov -t "gcov_report" -o s21_string_tests.info -c -d .
	genhtml -o $(REPORT_NAME) s21_string_tests.info
	rm $(NAME)
	make clean
