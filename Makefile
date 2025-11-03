CC      = cc
CFLAGS  = -std=c99 -pedantic -Werror -Wall -Wextra -Wvla -I./src
AR      = ar
ARFLAGS = rcs

.RECIPEPREFIX = >

SRC_DIR   = src
OBJ_DIR   = obj
TEST_DIR  = tests
LIB       = libfnmatch.a
TEST_BIN  = run-tests
SELFTEST  = selftest

SRCS = \
  $(SRC_DIR)/my_fnmatch.c \
  $(SRC_DIR)/match_core.c \
  $(SRC_DIR)/charset.c \
  $(SRC_DIR)/wildcards.c \
  $(SRC_DIR)/escape.c \
  $(SRC_DIR)/util.c

OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

TEST_SRCS := $(filter-out $(TEST_DIR)/selftest.c, $(wildcard $(TEST_DIR)/*.c))
TEST_OBJS = $(TEST_SRCS:$(TEST_DIR)/%.c=$(OBJ_DIR)/%.test.o)


CRIT_CFLAGS := $(shell pkg-config --cflags criterion 2>/dev/null)
CRIT_LIBS   := $(shell pkg-config --libs   criterion 2>/dev/null)

CFLAGS += $(CRIT_CFLAGS)
LDLIBS = $(CRIT_LIBS)

ifeq ($(LDLIBS),)
LDLIBS = -lcriterion -lpthread
endif

.PHONY: all build library tests check clean distclean selftest selfcheck coverage

all: build

build: $(LIB)

$(OBJ_DIR)/.mkdir:
> mkdir -p $(OBJ_DIR)
> touch $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)/.mkdir
> $(CC) $(CFLAGS) -c $< -o $@

$(LIB): $(OBJS)
> $(AR) $(ARFLAGS) $@ $^

library: build

$(OBJ_DIR)/%.test.o: $(TEST_DIR)/%.c | $(OBJ_DIR)/.mkdir
> $(CC) $(CFLAGS) -c $< -o $@

$(TEST_BIN): $(LIB) $(TEST_OBJS)
> $(CC) $(CFLAGS) $(TEST_OBJS) $(LIB) $(LDLIBS) -o $@

tests: $(TEST_BIN)

check: $(TEST_BIN)
> ./$(TEST_BIN)

selftest: $(LIB) $(OBJ_DIR)/.mkdir $(TEST_DIR)/selftest.c
> $(CC) $(CFLAGS) $(TEST_DIR)/selftest.c $(LIB) -o $(SELFTEST)

selfcheck: selftest
> ./$(SELFTEST)

coverage:
> $(MAKE) clean
> $(MAKE) CFLAGS="$(CFLAGS) -fprofile-arcs -ftest-coverage" LDFLAGS="--coverage" $(SELFTEST)
> ./$(SELFTEST)
> gcovr -r . --html --html-details -o coverage.html || true
> echo "=> Rapport: coverage.html"

clean:
> test -d $(OBJ_DIR) && rm -f $(OBJ_DIR)/*.o $(OBJ_DIR)/.mkdir || true
> rm -f $(TEST_BIN) $(SELFTEST)
> rm -f $(LIB)
> rmdir $(OBJ_DIR) 2>/dev/null || true

distclean: clean
> rm -f *.gcno *.gcda coverage.html 2>/dev/null || true

