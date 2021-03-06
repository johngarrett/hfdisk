//
// partition_map.h - partition map routines
//
// Written by Eryk Vershen (eryk@apple.com)
//

/*
 * Copyright 1996 by Apple Computer, Inc.
 *              All Rights Reserved 
 *  
 * Permission to use, copy, modify, and distribute this software and 
 * its documentation for any purpose and without fee is hereby granted, 
 * provided that the above copyright notice appears in all copies and 
 * that both the copyright notice and this permission notice appear in 
 * supporting documentation. 
 *  
 * APPLE COMPUTER DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE 
 * INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS 
 * FOR A PARTICULAR PURPOSE. 
 *  
 * IN NO EVENT SHALL APPLE COMPUTER BE LIABLE FOR ANY SPECIAL, INDIRECT, OR 
 * CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM 
 * LOSS OF USE, DATA OR PROFITS, WHETHER IN ACTION OF CONTRACT, 
 * NEGLIGENCE, OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION 
 * WITH THE USE OR PERFORMANCE OF THIS SOFTWARE. 
 */
#ifndef partition_map_h
#define partition_map_h
#include "dpme.h"
#include <stdint.h>

struct partition_map_header {
    int fd;
    char *name;
    struct partition_map * disk_order;
    struct partition_map * base_order;
    Block0 *misc;
    int writeable;
    int changed;
    int regular_file;
    int blocks_in_map;
    int maximum_in_map;
    uint32_t media_size;
};
typedef struct partition_map_header partition_map_header;

struct partition_map {
    struct partition_map * next_on_disk;
    struct partition_map * prev_on_disk;
    struct partition_map * next_by_base;
    struct partition_map * prev_by_base;
    long disk_address;
    struct partition_map_header * the_map;
    DPME *data;
};
typedef struct partition_map partition_map;


//
// Global Constants
//
extern const char * kFreeType;
extern const char * kMapType;
extern const char * kUnixType;
extern const char * kBootstrapType;
extern const char * kBootstrapName;

extern const char * kFreeName;


//
// Forward declarations
//
int add_partition_to_map(const char *name, const char *dptype, uint32_t base, uint32_t length, partition_map_header *map);
void close_partition_map(partition_map_header *map);
void delete_partition_from_map(partition_map *entry);
partition_map* find_entry_by_disk_address(long index, partition_map_header *map);
partition_map* find_entry_by_sector(uint32_t lba, partition_map_header *map);
partition_map_header* init_partition_map(char *name, partition_map_header* oldmap);
void move_entry_in_map(long old_index, long index, partition_map_header *map);
partition_map_header* open_partition_map(char *name, int *valid_file);
void resize_map(long new_size, partition_map_header *map);
void write_partition_map(partition_map_header *map);
uint32_t find_free_space(partition_map_header *map);

#endif
