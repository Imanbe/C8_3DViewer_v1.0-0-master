#ifndef SRC_PARSER_H

#define SRC_PARSER_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

typedef struct DATA {
    double vertex_count;
    int faces_count;
    double *vertex_cords;
    int *faces_cords;
} data_t;

int Parsing(const char* filename, data_t *obj);
void ParseVertex(char *line, data_t *obj, int *index_of_cords);
int ParseFaces(char *line, data_t *obj, int index_of_cords);
void ParseVertFacCount(FILE *fpen, data_t *obj);
void PrintCords(data_t *obj);
void PrintCords2(data_t *obj);
int s21_digit_supp(char ind);

#endif  // SRC_PARSER_H
