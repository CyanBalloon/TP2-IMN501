#ifndef MD2_TYPES_H_
#define MD2_TYPES_H_

#include "../Foundation/Vector3.h"

typedef struct {
	int ident;
	int version;
	int framesize;

	int skinwidth;
	int skinheight;

	int num_skins;
	int num_vertices;
	int num_st;
	int num_tris;
	int num_glcmds;
	int num_frames;

	int offset_skins;
	int offset_st;
	int offset_tris;
	int offset_frames;
	int offset_glcmds;
	int offset_end;
} md2_header_t;

typedef struct {
	unsigned char v[3];
	unsigned char normalIndex;
} md2_vertex_t;

typedef struct {
	unsigned short vertex[3];
	unsigned short st[3];
} md2_triangle_t;

typedef struct {
	short s;
	short t;
} md2_texCoord_t;

typedef struct {
	Vector3         scale;
	Vector3         translate;
	char            name[16];
	md2_vertex_t    *verts;
} md2_frame_t;

typedef struct {
	char    name[68];
} md2_skin_t;

#endif //MD2_TYPES_H_