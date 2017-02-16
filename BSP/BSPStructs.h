#ifndef SHADOW_BSP_STRUCTS_H
#define SHADOW_BSP_STRUCTS_H

#include "../Vector.h"

namespace BSP {

    #define NUM_LUMPS 17
    #define LUMP_ENTITIES 0
    #define LUMP_TEXTURES 1
    #define LUMP_PLANES 2
    #define LUMP_NODES 3
    #define LUMP_LEAFS 4
    #define LUMP_LEAFFACES 5
    #define LUMP_LEAFBRUSHES 6
    #define LUMP_MODELS 7
    #define LUMP_BRUSHES	8
    #define LUMP_BRUSHSIDES 9
    #define LUMP_VERTEXES 10
    #define LUMP_MESHVERTS 11
    #define LUMP_EFFECTS 12
    #define LUMP_FACES 13
    #define LUMP_LIGHTMAPS 14
    #define LUMP_LIGHTVOLS 15
    #define LUMP_VISDATA 16

    struct LumpData {
        int offset;
        int length;
    };

    struct Header {
        char magic[4];
        int version;
        LumpData lumps[NUM_LUMPS];
        int mapRevision;
    };

    class Lump {
    public:
       // virtual void print() = 0;
    };

    class Texture : public Lump {
        char name[64];
        int flags;
        int contents;

    public:
        void print() {
            printf("Texture\n");
            printf("\tName: %s\n", name);
            printf("\tFlags: %X\n", flags);
            printf("\tContents: %d\n", contents);
        }
    };

    class Node : public Lump {
    public:
        int plane;
        int children[2];
        int mins[3];
        int maxs;
    };

    class Leaf : public Lump {
    public:
        int cluster;
        int area;
        int mins[3];
        int maxs[3];
        int leafface;
        int n_leaffaces;
        int leafbrush;
        int n_leafbrushes;
    };

    class LeafFace : public Lump {
    public:
        int face;
    };

    class LeafBrush : public Lump {
    public:
        int brush;
    };

    class Brush : public Lump {
    public:
        int brushside;
        int n_brushsides;
        int texture;
    };

    class BrushSide : public Lump {
    public:
        int plane;
        int texture;
    };

    class Vertex : public Lump {
    public:
        Vector3f position;
        float texcoord[2][2];
        Vector3f normal;
        unsigned char color[4];
    };

    class MeshVert : public Lump {
    public:
        int offset;
    };

    class Face : public Lump {
    public:
        int texture;
        int effect;
        int type;
        int vertex;
        int n_vertexes;
        int meshvert;
        int n_meshverts;
        int lm_index;
        int lm_start[2];
        int lm_size[2];
        Vector3f lm_origin;
        float lm_vecs[2][3];
        Vector3f normal;
        int size[2];

        void print() {
            printf("Face\n");
            printf("\tVertices: %d\n", n_vertexes);
        }
    };

    class Lightmap : public Lump {
    public:
        unsigned char map[128][128][3];
    };

    class Lightvol : public Lump {
    public:
        Vector3uc ambient;
        Vector3uc directional;
        unsigned char dir[2];
    };
}
#endif //SHADOW_BSPHEADER_H
