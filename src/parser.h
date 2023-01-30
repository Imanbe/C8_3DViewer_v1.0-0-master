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

data_t Parsing(const char* filename);
void ParseVertex(char *line, double *array_of_cords, int *index_of_cords);
void ParseFaces(char *line, int *array_of_cords, int *index_of_cords);
void ParseVertFacCount(FILE *fpen, int* vertex_count, int *faces_count);
void PrintCords(int vertex_count, double *vertex_cords);
void PrintCords2(int faces_count, int *vertex_cords);

#endif  // SRC_PARSER_H
