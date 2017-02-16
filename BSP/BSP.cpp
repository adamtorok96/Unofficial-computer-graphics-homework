#include <new>
#include "BSP.h"

bool BSP::BSP::read(const char *filename) {

    FILE *f = fopen(filename, "r");

    if( !f ) {
        fclose(f);

        return false;
    }

    if( fread(&header, sizeof(Header), 1, f) != 1 || !isValidHeaderMagic() ) {
        fclose(f);

        return false;
    }

    if( !readLump<Texture>(f, LUMP_TEXTURES, textures) ) {
        printf("Failed to read lump: %d\n", LUMP_TEXTURES);
    }

    if( !readLump<Face>(f, LUMP_FACES, faces) ) {
        printf("lump read error\n");
    }

    if( !readLump<Vertex>(f, LUMP_VERTEXES, vertices) ) {
        printf("lump read error\n");
    }

    if( !readLump<LeafFace>(f, LUMP_LEAFFACES, leafFaces) ) {
        printf("lump read error\n");
    }

    if( !readLump<MeshVert>(f, LUMP_MESHVERTS, meshVerts) ) {
        printf("lump read error\n");
    }

    fclose(f);

    return true;
}

bool BSP::BSP::isValidHeaderMagic() {
    return header.magic[0] == 'I' && header.magic[1] == 'B' && header.magic[2] == 'S' && header.magic[3] == 'P';
}

template <typename Lump>
bool BSP::BSP::readLump(FILE *f, unsigned int lump, Lump *address) {

    if( lump > NUM_LUMPS )
        return false;

    size_t count = header.lumps[lump].length / sizeof(Lump);

    if( count == 0 ) {
        return true;
    }

    fseek(f, header.lumps[lump].offset, SEEK_SET);

    try {
        address = new Lump[count];
    } catch (std::bad_alloc &e) {
        return false;
    }

    return fread(address, sizeof(Lump), count, f) == count;
}

BSP::BSP::~BSP() {
    delete[] textures;
}

void BSP::BSP::drawFace(int i) {
    Face *face = &faces[i];


    glScalef(0.01f, 0.01f, 0.01f);

    glVertexPointer(3, GL_FLOAT, sizeof(Vertex), &(vertices[face->vertex].position));
    glEnableClientState(GL_VERTEX_ARRAY);

    // If we want to render the textures
    /*
    if(g_bTextures)
    {

        // Set the current pass as the first texture (For multi-texturing)
        glActiveTextureARB(GL_TEXTURE0_ARB);

        // Since we are using vertex arrays, we need to tell OpenGL which texture
        // coordinates to use for each texture pass.  We switch our current texture
        // to the first one, then set our texture coordinates.
        glClientActiveTextureARB(GL_TEXTURE0_ARB);
        glTexCoordPointer(2, GL_FLOAT, sizeof(tBSPVertex), &(m_pVerts[pFace->startVertIndex].vTextureCoord));

        // Set our vertex array client states for allowing texture coordinates
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);

        // Turn on texture arrays for the first pass
        glClientActiveTextureARB(GL_TEXTURE0_ARB);

        // To enable each texture pass, we want to turn on the texture coord array
        // state for each pass.  This needs to be done since we are using vertex arrays.

        // Turn on texture mapping and bind the face's texture map
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,  m_textures[pFace->textureID]);
    }
*/
    /*
    if(g_bLightmaps)
    {


/////// * /////////// * /////////// * NEW * /////// * /////////// * /////////// *

        // Set the current pass as the second lightmap texture_
        glActiveTextureARB(GL_TEXTURE1_ARB);

        // Turn on texture arrays for the second lightmap pass
        glClientActiveTextureARB(GL_TEXTURE1_ARB);
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);

        // Next, we need to specify the UV coordinates for our lightmaps.  This is done
        // by switching to the second texture and giving OpenGL our lightmap array.
        glClientActiveTextureARB(GL_TEXTURE1_ARB);
        glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), &(vertices[face->vertex].color));

/////// * /////////// * /////////// * NEW * /////// * /////////// * /////////// *


        // Turn on texture mapping and bind the face's lightmap over the texture
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,  m_lightmaps[pFace->lightmapID]);
    }
     */

    // Render our current face to the screen with vertex arrays
    glDrawElements(GL_TRIANGLES, face->n_meshverts, GL_UNSIGNED_INT, &(meshVerts[face->meshvert]));
}

void BSP::BSP::render() {

    for(int i = 0; i < sizeof(faces) / sizeof(Face); i++) {
        drawFace(i);
    }

}
