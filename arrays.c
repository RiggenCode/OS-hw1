//
// Created by riggens on 2/16/26.
//
#include "arrays.h"

Array3D *array_3d_load(const char *filename) {
    if (!filename) return NULL;

    FILE *f = fopen(filename, "rb");
    if (!f) return NULL;

    unsigned char hdr_bytes[12];
    if (fread(hdr_bytes, 1, sizeof(hdr_bytes), f) != sizeof(hdr_bytes)) {
        fprintf(stderr, "Failed to read header from file.\n");
        fclose(f);
        return NULL;
    }

    int32_t hdr32[3];
    for (int i = 0; i < 3; i++) {
        hdr32[i] = (int32_t)hdr_bytes[4*i + 0]
                  | (int32_t)hdr_bytes[4*i + 1] << 8
                  | (int32_t)hdr_bytes[4*i + 2] << 16
                  | (int32_t)hdr_bytes[4*i + 3] << 24;
    }

    const size_t d0 = (size_t)hdr32[0];
    const size_t d1 = (size_t)hdr32[1];
    const size_t d2 = (size_t)hdr32[2];

    size_t count = d0;
    count *= d1;
    count *= d2;
    if (count == 0) {
        fprintf(stderr, "Array has zero elements, nothing to load.\n");
        fclose(f);
        return NULL;
    }

    Array3D *arr = malloc(sizeof(Array3D));
    if (!arr) {
        fprintf(stderr, "Failed to allocate memory for Array3D struct.\n");
        fclose(f);
        return NULL;
    }
    arr->dim1 = d0;
    arr->dim2 = d1;
    arr->dim3 = d2;

    if (!arr->data) {
        fprintf(stderr, "Failed to allocate memory for array data.\n");
        free(arr);
        fclose(f);
        return NULL;
    }
    arr->data = (float *)malloc(count * sizeof(float));
    fclose(f);
    return arr;
}

void array3d_save(const Array3D *arr, const char *filename) {
    if (!arr || !filename) return;
    if (!arr->data) return;

    if (arr->dim1 > INT32_MAX || arr->dim2 > INT32_MAX || arr->dim3 > INT32_MAX) {
        fprintf(stderr, "Array dimensions are too large to save.\n");
        return;
    }

    const size_t d0 = arr->dim1;
    const size_t d1 = arr->dim2;
    const size_t d2 = arr->dim3;

    size_t count = d0;
    count *= d1;
    count *= d2;
    if (count == 0) {
        fprintf(stderr, "Array has zero elements, nothing to save.\n");
        return;
    }

    FILE *f = fopen(filename, "wb");
    if (!f) return;

    int32_t hdr32[3] = { (int32_t)d0, (int32_t)d1, (int32_t)d2 };

    unsigned char hdr_bytes[12];
    for (int i = 0; i < 3; i++) {
        const uint32_t v = (uint32_t)hdr32[i];
        hdr_bytes[4*i + 0] = (unsigned char) (v & 0xFFu);
        hdr_bytes[4*i + 1] = (unsigned char) ((v >> 8) & 0xFFu);
        hdr_bytes[4*i + 2] = (unsigned char) ((v >> 16) & 0xFFu);
        hdr_bytes[4*i + 3] = (unsigned char) ((v >> 24) & 0xFFu);
    }

    if (fwrite(hdr_bytes, 1, sizeof(hdr_bytes), f) != sizeof(hdr_bytes)) {
        fprintf(stderr, "Failed to write header to file.\n");
        fclose(f);
        return;
    }

;
    uint16_t one = 1;
    const int host_is_le = (*(uint8_t *)&one == 1);;

    const unsigned char *data_bytes = (const unsigned char *)arr->data;
    size_t payload_bytes = count * sizeof(float);

    if (host_is_le) {
        const size_t written = fwrite(arr->data, sizeof(float), count, f);
        if (written != count) {
            fprintf(stderr, "Failed to write array data to file. Expected to write %zu elements, but wrote %zu.\n", count, written);
            fclose(f);
            return;
        }

        if (fwrite(arr->data, sizeof(float), count, f) != count) {
            fprintf(stderr, "Failed to write array data to file.\n");
            fclose(f);
            return;
        }
    } else {

        unsigned char *swapped = (unsigned char *)malloc(count * sizeof(float));
        if (!swapped) {
            fprintf(stderr, "Failed to allocate memory for byte-swapped data.\n");
            fclose(f);
            return;
        }

        for (size_t i = 0; i < count; i++) {
            size_t base = 4 * i;
            swapped[base + 0] = data_bytes[base + 3];
            swapped[base + 1] = data_bytes[base + 2];
            swapped[base + 2] = data_bytes[base + 1];
            swapped[base + 3] = data_bytes[base + 0];
        }
        if (fwrite(swapped, 1, count * sizeof(float), f) != count * sizeof(float)) {
            fprintf(stderr, "Failed to write byte-swapped array data to file.\n");
            free(swapped);
            fclose(f);
            return;
        }
        free(swapped);
    }
    fclose(f);
}

void array3d_free(Array3D *arr) {
    if (!arr) return;
    free(arr->data);
    free(arr);
}
