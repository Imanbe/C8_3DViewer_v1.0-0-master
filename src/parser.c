#include "parser.h"

data_t Parsing(const char* filename) {
    FILE* fpen = fopen(filename, "r");

    data_t data_v_f;
    int vertex_count = 0, faces_count = 0;
    double* vertex_cords = NULL;
    int* faces_cords = NULL;
    int index_faces_cords = 0, index_vertex_cords = 0;
    char line[32];


    if (fpen != NULL) {

        ParseVertFacCount(fpen, &vertex_count, &faces_count);
        
        if (vertex_count > 0 && faces_count > 0) {
            vertex_cords = calloc(vertex_count*3, sizeof(double));
            faces_cords = calloc(faces_count*3, sizeof(int));
        }

        
        // Добавляем всё в массив
        fpen = fopen(filename, "r");
        while (fgets(line, 100, fpen) != NULL) {
            if (line[0] == 'v') {
                ParseVertex(line, vertex_cords, &index_vertex_cords);
            } else if (line[0] == 'f') {
                ParseFaces(line, faces_cords, &index_faces_cords);
            }

            memset(line,0,strlen(line));
        }

        printf("--%d--%d--\n", vertex_count, faces_count);
        PrintCords(vertex_count, vertex_cords);
        PrintCords2(faces_count, faces_cords);

    } else {
        perror("fopen() ");
    }

    data_v_f.vertex_count = vertex_count;
    data_v_f.faces_count = faces_count;
    data_v_f.vertex_cords = vertex_cords;
    data_v_f.faces_cords = faces_cords;

    return data_v_f;
}


void ParseVertex(char *line, double *array_of_cords, int *index_of_cords) {
    double digital;
    for (size_t i = 0; i < strlen(line); i++) {
        if (line[i] == ' ') {
            i += 1;
            const char *dig_start = &line[i];
            while (strchr(line, ' ') == NULL) {
                i += 1;
            }
            char *dig_end = &line[i];
            digital = strtod(dig_start, &dig_end);
            array_of_cords[*index_of_cords] = digital;
            *index_of_cords += 1;
        }
    }
}

void ParseFaces(char *line, int *array_of_cords, int *index_of_cords) {
    double digital;
    for (size_t i = 0; i < strlen(line); i++) {
        if (line[i] == ' ') {
            i += 1;
            const char *dig_start = &line[i];
            while (strchr(line, '/') == NULL) {
                i += 1;
            }
            char *dig_end = &line[i];
            digital = strtod(dig_start, &dig_end);
            array_of_cords[*index_of_cords] = digital;
            *index_of_cords += 1;
        }
    }
}

void ParseVertFacCount(FILE *fpen, int* vertex_count, int *faces_count) {
    char c;
    char bel_c;

    c = fgetc(fpen);
    bel_c = fgetc(fpen);

    while ((bel_c != EOF)) {
        if (c == 'v' && bel_c == ' ') {
            *vertex_count += 1;
        } else if (c == 'f') {
            while (bel_c != '\n' && bel_c != EOF) {
                if (bel_c == ' ') {
                    *faces_count += 1;
                }
                bel_c = fgetc(fpen);
            }
        }
        c = bel_c;
        bel_c = fgetc(fpen);
    }        
}

void PrintCords(int vertex_count, double *vertex_cords) {
    int j = 1;
    for (int i = 0; i < vertex_count * 3; i++) {
        printf("%lf ", vertex_cords[i]);
        if (j % 3 == 0) {
            printf("\n");
        }
        j++;
    }
}

void PrintCords2(int faces_count, int *vertex_cords) {
    int j = 1;
    for (int i = 0; i < faces_count; i++) {
        printf("%d ", vertex_cords[i]);
        if (j % 3 == 0) {
            printf("\n");
        }
        j++;
    }
}
