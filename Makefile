CC = gcc
CLINKER = $(CC)

.PHONY: all

all: split_multi_frame_xyz

.PHONY: split_multi_frame_xyz

split_multi_frame_xyz: split_multi_frame_xyz.exe

split_multi_frame_xyz.exe: split_multi_frame_xyz.o
	$(CLINKER) -o $@ $^


split_multi_frame_xyz.o: split_multi_frame_xyz.c
	$(CC) -o $@ -c $<

.PHONY: clean

clean: clean_tmp
	-del split_multi_frame_xyz.exe 1> NUL 2> NUL

.PHONY: clean_tmp

clean_tmp:
	-del split_multi_frame_xyz.o 1> NUL 2> NUL

