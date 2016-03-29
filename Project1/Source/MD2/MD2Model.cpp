#include "MD2Model.h"
#include "../Foundation/RGBImage.h"
#include "../Foundation/PcxHandling.h"
#include <fstream>
#include <iostream>

MD2Model::MD2Model(){}

void MD2Model::LoadModel(const string &ao_FileName) {
	fstream file;

	file.open(ao_FileName, std::ios::in | std::ios::binary);

	if (file.fail())
		throw exception("Problem loading the file");

	// lecture du header
	file.read((char *)&m_kHeader, sizeof(md2_header_t));

	// vérification de l'authenticité du modèle
	if ((m_kHeader.version != MD2_VERSION) || m_kHeader.ident != MD2_IDENT)
		throw exception("Model contains errors");

	// allocation de mémoire pour les données du modèle
	m_pSkins = new md2_skin_t[m_kHeader.num_skins];
	m_pTexCoords = new md2_texCoord_t[m_kHeader.num_st];
	m_pTriangles = new md2_triangle_t[m_kHeader.num_tris];
	m_pFrames = new md2_frame_t[m_kHeader.num_frames];
	m_pGLcmds = new int[m_kHeader.num_glcmds];

	// lecture des noms de skins
	file.seekg(m_kHeader.offset_skins, std::ios::beg);
	file.read((char *)m_pSkins, sizeof(char) * 68 * m_kHeader.num_skins);

	// lecture des coordonnées de texture
	file.seekg(m_kHeader.offset_st, std::ios::beg);
	file.read((char *)m_pTexCoords, sizeof(md2_texCoord_t) * m_kHeader.num_st);

	// lecture des triangles
	file.seekg(m_kHeader.offset_tris, std::ios::beg);
	file.read((char *)m_pTriangles, sizeof(md2_triangle_t) * m_kHeader.num_tris);

	// lecture des frames
	file.seekg(m_kHeader.offset_frames, std::ios::beg);

	for (int i = 0; i < m_kHeader.num_frames; i++)
	{
		// allocation de mémoire pour les vertices
		m_pFrames[i].verts = new md2_vertex_t[m_kHeader.num_vertices];

		// lecture des données de la frame
		file.read((char *)&m_pFrames[i].scale, sizeof(vec3_t));
		file.read((char *)&m_pFrames[i].translate, sizeof(vec3_t));
		file.read((char *)&m_pFrames[i].name, sizeof(char) * 16);
		file.read((char *)m_pFrames[i].verts, sizeof(md2_vertex_t) * m_kHeader.num_vertices);
	}

	// lecture des commandes opengl
	file.seekg(m_kHeader.offset_glcmds, std::ios::beg);
	file.read((char *)m_pGLcmds, sizeof(int) * m_kHeader.num_glcmds);

	// fermeture du fichier
	file.close();
}

void MD2Model::LoadTexture(const std::string &ao_FileName) {
	if (m_uiTexID != 0)
	{
		glDeleteTextures(1, &m_uiTexID);
	}

	glGenTextures(1, &m_uiTexID);

	RGBImage o_TmpImage;
	glBindTexture(GL_TEXTURE_2D, m_uiTexID);

	LoadPCX(ao_FileName, o_TmpImage);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, o_TmpImage.GetWidth(), o_TmpImage.GetHeight(), 0, GL_RGB, GL_FLOAT, o_TmpImage.GetRasterData());

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	glBindTexture(GL_TEXTURE_2D, NULL);
}

void MD2Model::FreeResources() {
	if (m_pSkins)
		delete[] m_pSkins;

	if (m_pTexCoords)
		delete[] m_pTexCoords;

	if (m_pTriangles)
		delete[] m_pTriangles;

	if (m_pFrames)
	{
		for (int i = 0; i < m_kHeader.num_frames; i++)
		{
			if (m_pFrames[i].verts)
				delete[] m_pFrames[i].verts;
		}

		delete[] m_pFrames;
	}
}

void MD2Model::AddAnimationData(const AnimationData& ao_AnimationData) {
	anim_v.push_back(ao_AnimationData);
}

void MD2Model::PlayAnimation(bool ab_PlayAnim) { animation_is_playing = ab_PlayAnim; }
bool MD2Model::IsAnimationPlaying() const { return animation_is_playing; }
void MD2Model::NextAnimation() { frame_index++; }
void MD2Model::PreviousAnimation() { frame_index--; }

void MD2Model::SetAnimationSpeed(float af_Speed) {
	current_speed = af_Speed;
	frames_for_animation = (current_speed == 0.0) ? 1 : BASE_SPEED / current_speed;
	animation_is_playing = true;
}

float MD2Model::GetAnimationSpeed() const { return current_speed; }

void MD2Model::Render(float af_DeltaT) {
	int iMaxFrame = anim_v.back().mf_FrameEnd;
	float alpha = float(current_frame_animation) / float(frames_for_animation);
	if (animation_is_playing)
	{
		frame_index = (alpha * iMaxFrame);
		current_frame_animation++;
	}

	if (current_frame_animation >= frames_for_animation) 
		current_frame_animation = 0;

	if (frame_index < 0)
		frame_index = iMaxFrame;

	if (frame_index > iMaxFrame)
		frame_index = 0;

	if (frame_index >= m_kHeader.num_frames - 1)
		return;

	// activation de la texture du modèle
	glBindTexture(GL_TEXTURE_2D, m_uiTexID);

	// dessin du modèle
	glBegin(GL_TRIANGLES);
	// dessine chaque triangle
	for (int i = 0; i < m_kHeader.num_tris; i++)
	{
		// dessigne chaque vertex du triangle
		for (int k = 0; k < 3; k++)
		{
			int frame_to_show = (frame_index >= iMaxFrame) ? frame_index - 1 : frame_index;
			md2_frame_t *pFrameA = &m_pFrames[int(frame_to_show)];
			md2_frame_t *pFrameB = &m_pFrames[int(frame_to_show+1)];

			md2_vertex_t *pVertA = &pFrameA->verts[m_pTriangles[i].vertex[k]];
			md2_vertex_t *pVertB = &pFrameB->verts[m_pTriangles[i].vertex[k]];

			// [coordonnées de texture]
			GLfloat s = (GLfloat)m_pTexCoords[m_pTriangles[i].st[k]].s / m_kHeader.skinwidth;
			GLfloat t = (GLfloat)m_pTexCoords[m_pTriangles[i].st[k]].t / m_kHeader.skinheight;

			// application des coordonnées de texture
			glTexCoord2f(s, t);

			// [normale]
			vec3_t normA, normB, n;

			memcpy(normA, m_kAnorms[pVertA->normalIndex], 3 * sizeof(float));
			memcpy(normB, m_kAnorms[pVertB->normalIndex], 3 * sizeof(float));

			// interpolation linéaire
			n[0] = normA[0] + alpha * (normB[0] - normA[0]);
			n[1] = normA[1] + alpha * (normB[1] - normA[1]);
			n[2] = normA[2] + alpha * (normB[2] - normA[2]);

			// spécification de la normale
			glNormal3fv(n);

			// [vertex]
			vec3_t vecA, vecB, v;

			// calcul de la position absolue des vertices
			vecA[0] = pFrameA->scale[0] * pVertA->v[0] + pFrameA->translate[0];
			vecA[1] = pFrameA->scale[1] * pVertA->v[1] + pFrameA->translate[1];
			vecA[2] = pFrameA->scale[2] * pVertA->v[2] + pFrameA->translate[2];

			vecB[0] = pFrameB->scale[0] * pVertB->v[0] + pFrameB->translate[0];
			vecB[1] = pFrameB->scale[1] * pVertB->v[1] + pFrameB->translate[1];
			vecB[2] = pFrameB->scale[2] * pVertB->v[2] + pFrameB->translate[2];

			// interpolation linéaire et redimensionnement
			v[0] = (vecA[0] + alpha * (vecB[0] - vecA[0]));
			v[1] = (vecA[1] + alpha * (vecB[1] - vecA[1]));
			v[2] = (vecA[2] + alpha * (vecB[2] - vecA[2]));

			// dessin du vertex
			glVertex3fv(v);
		}
	}
	glEnd();
}

MD2Model::~MD2Model(){}
