
include build.conf

.PHONY: all build shared static clean

all: shared static

build: $(OBJS)
	@echo -e "\n\nLIB USING PHP INC: $(PHP_INCLUDE_DIRS)"
	@echo -e "\n CFLAGS: $(CFLAGS)"
	@echo -e "\nLDFLAGS: $(LDFLAGS)"
	@echo -e "\n   OBJS: $(OBJS)"

shared: build libphphi.so

static: build libphphi.a

libphphi.so: $(OBJS)
	$(CC) $(LDFLAGS) -o $(LIB_DIR)/$@ $^ -ldl -lrt

libphphi.a: $(OBJS)
	$(AR) rcs $(LIB_DIR)/$@ $^

$(LIB_DIR)/%.o: $(EXT_DIR)/%.c
	@mkdir -p $(LIB_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(LIB_DIR)/*.o $(LIB_DIR)/*.so $(LIB_DIR)/*.a

