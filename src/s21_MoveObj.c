#include "s21_MoveObj.h"

/**********************************************************************/
/*                                                                    */
/*                  Functions to move/rotate model                    */
/*                                                                    */
/**********************************************************************/


void s21_scale(data_t *obj, double scale) {
    if (scale != 0.0) {
        for (unsigned i = 0; i < obj->meta_inf.vertex_count; i++) {
            obj->vertex_cords[i] *= scale;
        }
    }

}

void s21_moveOX(data_t *obj, double value) {
    if (value != 0.0) {
        for (unsigned i = 0; i < obj->meta_inf.vertex_count; i += 3) {
            obj->vertex_cords[i] += value;
        }
    }
}

void s21_moveOY(data_t *obj, double value) {
    if (value != 0.0) {
        for (unsigned i = 1; i < obj->meta_inf.vertex_count; i += 3) {
            obj->vertex_cords[i] += value;
        }
    }
}

void s21_moveOZ(data_t *obj, double value) {
    if (value != 0.0) {
        for (unsigned i = 2; i < obj->meta_inf.vertex_count; i += 3) {
            obj->vertex_cords[i] += value;
        }
    }
}
