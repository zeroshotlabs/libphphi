

PHP_CONFIG ?= php-config

CHECK_PHP_CONFIG = $(shell which $(PHP_CONFIG) > /dev/null 2>&1 || echo "Error")

ifeq ($(CHECK_PHP_CONFIG), Error)
$(error "php-config not found - Try PHP_CONFIG=/usr/path_to/php/bin/php-config make")
endif



# Get PHP configuration
## PHP_CONFIG := $(shell which php-config)
PHP_INCLUDE_DIRS := $(shell $(PHP_CONFIG) --includes)
PHP_LDFLAGS := $(shell $(PHP_CONFIG) --ldflags)
PHP_LIBS := $(shell $(PHP_CONFIG) --libs)

CC = gcc
AR = ar

EXT_DIR = ext
LIB_DIR = lib

# Combine PHP CFLAGS with your own
CFLAGS = -Wall -Wextra -fPIC -I./include $(PHP_INCLUDE_DIRS)

# Combine PHP LDFLAGS with your own
LDFLAGS = -shared $(PHP_LDFLAGS) $(PHP_LIBS)

SRCS = $(wildcard $(EXT_DIR)/*.c)
OBJS = $(patsubst $(EXT_DIR)/%.c,$(LIB_DIR)/%.o,$(SRCS))

.PHONY: all clean

all: $(LIB_DIR)/libphphi.so $(LIB_DIR)/libphphi.a

$(LIB_DIR)/libphphi.a: $(OBJS)
	$(AR) rcs $@ $^

$(LIB_DIR)/libphphi.so: $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^

$(LIB_DIR)/%.o: $(EXT_DIR)/%.c
	@mkdir -p $(LIB_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(LIB_DIR)/*.o $(LIB_DIR)/*.so $(LIB_DIR)/*.a






# ## include build.conf

# PHP_CONFIG ?= php-config

# CHECK_PHP_CONFIG = $(shell which $(PHP_CONFIG) > /dev/null 2>&1 || echo "Error")

# ifeq ($(CHECK_PHP_CONFIG), Error)
# $(error "php-config not found - Try PHP_CONFIG=/usr/path_to/php/bin/php-config make")
# endif


# # PHP_INCLUDE_DIR := $(shell $(PHP_CONFIG) --includes 2>/dev/null)
# PHP_INCLUDE_DIRS = $(shell $(PHP_CONFIG) --includes)




# CC = gcc
# AR = ar

# EXT_DIR = ext
# LIB_DIR = lib

# ## CFLAGS += -DLIB_PATH=\"$(LIB_PATH)\"
# CFLAGS = -Wall -Wextra -fPIC -I./include

# LDFLAGS = -shared

# SRCS = $(wildcard $(EXT_DIR)/*.c)
# OBJS = $(SRCS:.c=.o)

# .PHONY: all clean

# all: libphphi.so libphphi.a

# libphphi.a: $(OBJS)
# 	$(AR) rcs $(LIB_DIR)/$@ $^

# libphphi.so: $(OBJS)
# 	$(CC) $(LDFLAGS) -o $(LIB_DIR)/$@ $^

# %.o: %.c
# 	$(CC) $(CFLAGS) -c $< -o $(LIB_DIR)/$@

# clean:
# 	rm -f $(LIB_DIR)/*.o $(LIB_DIR)/*.so $(LIB_DIR)/*.a



# $(MODULE_NAME).a: $(OBJS) libphphi/libphphi.a
# 	$(CC) -static -o $@ $(OBJS) $(LDFLAGS)

# $(MODULE_NAME).so: $(OBJS) libphphi/libphphi.so
# 	$(CC) -shared -o $@ $(OBJS) $(LDFLAGS)



##	rm -f src/*.o libphphi.so libphphi.a

# .PHONY: all build shared static clean

# all: shared static

# shared: build libphphi.so

# static: build libphphi.a

# libphphi.so: $(OBJS)
# 	$(CC) $(LDFLAGS) -o $(LIB_DIR)/$@ $^

# libphphi.a: $(OBJS)
# 	$(AR) rcs $(LIB_DIR)/$@ $^

# $(LIB_DIR)/%.o: $(EXT_DIR)/%.c
# 	@mkdir -p $(LIB_DIR)
# 	$(CC) $(CFLAGS) -c $< -o $@

# show_build: $(OBJS)
# 	@echo -e "\n\nLIB USING PHP INC: $(PHP_INCLUDE_DIRS)"
# 	@echo -e "\n CFLAGS: $(CFLAGS)"
# 	@echo -e "\nLDFLAGS: $(LDFLAGS)"
# 	@echo -e "\n   OBJS: $(OBJS)"

# clean:
# 	rm -f $(LIB_DIR)/*.o $(LIB_DIR)/*.so $(LIB_DIR)/*.a

