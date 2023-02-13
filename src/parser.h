#ifndef SRC_PARSER_H

#define SRC_PARSER_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#define MEMORY_OK 0
#define MEMORY_ERROR 1

typedef struct METADATA {
    unsigned vertex_count;
    unsigned faces_count;
    unsigned memory_check;
} meta_t;

typedef struct DATA {
    double *vertex_cords;
    unsigned *faces_cords;
    meta_t meta_inf;
} data_t;


int Parsing(char* filename, data_t *obj);
void ParseVertex(char *line, data_t *obj, int *index_of_cords);
int ParseFaces(char *line, data_t *obj, int index_of_cords);
void ParseVertFacCount(char *filename, data_t *obj);
void PrintCords(data_t *obj);
void PrintCords2(data_t *obj);
void PrintIndexes(data_t *obj);
int s21_digit_supp(char ind);

#endif  // SRC_PARSER_H
