#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

// ============================================================
// FUNGSI UTAMA: apply_blur
// Parameter:
//   in     → array piksel gambar INPUT
//   out    → array piksel gambar OUTPUT (hasil blur)
//   w      → lebar gambar (width)
//   h      → tinggi gambar (height)
//   c      → jumlah channel (3=RGB, 1=Grayscale)
//   k_size → ukuran kernel (3=3x3, 5=5x5, dst)
// ============================================================
void apply_blur(unsigned char *in, unsigned char *out,
                int w, int h, int c, int k_size) {

    int r = k_size / 2;

    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            for (int ch = 0; ch < c; ch++) {

                float sum  = 0;
                int  count = 0;

                for (int ky = -r; ky <= r; ky++) {
                    for (int kx = -r; kx <= r; kx++) {

                        int py = y + ky;
                        int px = x + kx;

                        // Boundary check: pastikan tidak keluar batas gambar
                        if (px >= 0 && px < w && py >= 0 && py < h) {
                            sum += in[(py * w + px) * c + ch];
                            count++;
                        }
                    }
                }

                out[(y * w + x) * c + ch] = (unsigned char)(sum / count);
            }
        }
    }
}

// ============================================================
// MAIN
// Cara pakai: ./convolution <input.jpg> <output.jpg>
// ============================================================
int main(int argc, char *argv[]) {

    if (argc < 3) {
        printf("Cara pakai: %s <input> <output>\n", argv[0]);
        printf("Contoh   : %s foto.jpg hasil.jpg\n", argv[0]);
        return 1;
    }

    // Baca gambar input
    int w, h, c;
    unsigned char *img_in = stbi_load(argv[1], &w, &h, &c, 0);
    if (!img_in) {
        printf("ERROR: Gagal membaca gambar '%s'\n", argv[1]);
        return 1;
    }

    printf("File   : %s\n", argv[1]);
    printf("Ukuran : %d x %d piksel\n", w, h);
    printf("Channel: %d (%s)\n", c, c == 3 ? "RGB" : c == 4 ? "RGBA" : "Grayscale");

    // Alokasi memori untuk output
    unsigned char *img_out = (unsigned char *)malloc(w * h * c);
    if (!img_out) {
        printf("ERROR: Gagal alokasi memori\n");
        stbi_image_free(img_in);
        return 1;
    }

    // Terapkan blur (kernel 5×5)
    int k_size = 5;
    printf("Kernel : %d x %d\n", k_size, k_size);
    printf("Memproses...\n");

    apply_blur(img_in, img_out, w, h, c, k_size);

    // Simpan gambar output
    const char *out_path = argv[2];
    const char *ext = strrchr(out_path, '.');
    int berhasil = 0;

    if (ext && (strcmp(ext, ".jpg") == 0 || strcmp(ext, ".jpeg") == 0))
        berhasil = stbi_write_jpg(out_path, w, h, c, img_out, 90);
    else
        berhasil = stbi_write_png(out_path, w, h, c, img_out, w * c);

    if (berhasil)
        printf("Selesai! Disimpan ke: %s\n", out_path);
    else
        printf("ERROR: Gagal menyimpan gambar\n");

    // Bebaskan memori
    stbi_image_free(img_in);
    free(img_out);

    return 0;
}