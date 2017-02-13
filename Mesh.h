#ifndef SHADOW_MESH_H
#define SHADOW_MESH_H

#include <string.h>

#include <vector>
#include <algorithm>

#include <GL/freeglut.h>

struct PairOrder
{
    bool operator()(const std::pair<int, int>& lhs, const std::pair<int, int>& rhs)
    {
        return lhs.first < rhs.first;
    }
} po;

class Mesh {

public:
    std::vector<float> vertices;
    std::vector<float> normals;
    std::vector<float> textureUV;
    std::vector<std::vector<int> > vertexIndices;
    std::vector<std::vector<int> > normalIndices;
    std::vector<std::vector<int> > textureIndices;
    std::vector<int> materialIndices;
    int defaultMaterial;

    Mesh();

    GLfloat* getMaterial(int materialIndex);
    void sortByColorIndex();

    int materialStr2MaterialIndex(const char *materialStr);
    void render();
    void renderFixColor();
    void renderNormalColor();
    void read(const char *fileName);
};


#endif //SHADOW_MESH_H
