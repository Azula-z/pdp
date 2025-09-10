#include <stdlib.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

int main() {
    system("curl -o /tmp/imagen.jpg https://images7.memedroid.com/images/UPLOADED639/6684da908d1ca.jpeg");

    char *filename = "/tmp/imagen.jpg";

    int x, y, n;
    unsigned char *pxs = stbi_load(filename, &x, &y, &n, 0);

    for (int i = 0; i < y * x; i++) {

        unsigned int r = pxs[i * n + 0];
        unsigned int g = pxs[i * n + 1];
        unsigned int b = pxs[i * n + 2];
        
        unsigned char o = (unsigned char)(0.299 * r + 0.587 * g + 0.114 * b);

        pxs[i * n + 0] = o;
        pxs[i * n + 1] = o;
        pxs[i * n + 2] = o;
    }

    stbi_write_jpg("/tmp/imagen_bn.jpg", x, y, n, pxs, 5);
    stbi_image_free(pxs);

    system("gsettings set org.gnome.desktop.background picture-uri 'file:///tmp/imagen_bn.jpg'");

    return 0;
}
