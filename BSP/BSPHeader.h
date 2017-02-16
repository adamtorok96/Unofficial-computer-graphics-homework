//
// Created by edems on 2017.02.16..
//

#ifndef SHADOW_BSPHEADER_H
#define SHADOW_BSPHEADER_H

#define NUM_LUMPS 10

struct {
    int	ident;
    int	version;
    //lump_t	lumps[NUM_LUMPS];
    int	mapRevision;
};

#endif //SHADOW_BSPHEADER_H
