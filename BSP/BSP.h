#ifndef SHADOW_BSP_H
#define SHADOW_BSP_H

#include <cstdio>

#include <GL/gl.h>

#include "BSPStructs.h"

namespace BSP {

    class BSP {
        Header header;

        Texture * textures;
        Face * faces;
        Vertex * vertices;
        LeafFace * leafFaces;
        MeshVert * meshVerts;

        bool isValidHeaderMagic();

        template <typename Lump>
        bool readLump(FILE *f, unsigned int lump, Lump *addr);

        void drawFace(int i);

    public:

        ~BSP();

        bool read(const char *filename);

        void render();
    };

}

#endif //SHADOW_BSP_H
