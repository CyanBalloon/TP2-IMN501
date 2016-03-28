#include "MD2Model.h"
#include "../Foundation/RGBImage.h"
#include "../Foundation/PcxHandling.h"
#include <fstream>

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

void MD2Model::FreeResources(){}
void MD2Model::AddAnimationData(const AnimationData& ao_AnimationData){}

void MD2Model::PlayAnimation(bool ab_PlayAnim){}
bool MD2Model::IsAnimationPlaying() const{ return true;}

void MD2Model::NextAnimation(){}
void MD2Model::PreviousAnimation(){}

void MD2Model::SetAnimationSpeed(float af_Speed){}
float MD2Model::GetAnimationSpeed() const{ return 0.0f;}

void MD2Model::Render(float af_DeltaT) {
	// calcul de l'index maximum d'une frame du modèle
	int iMaxFrame = m_kHeader.num_frames - 1;
	float compteur = af_DeltaT;
	iMaxFrame / compteur;
	int iFrame = 1;
	// vérification de la validité de iFrame
	//if ((iFrame < 0) || (iFrame > iMaxFrame))
	//	return;


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
			md2_frame_t *pFrame = &m_pFrames[iFrame];
			md2_vertex_t *pVert = &pFrame->verts[m_pTriangles[i].vertex[k]];


			// [coordonnées de texture]
			GLfloat s = (GLfloat)m_pTexCoords[m_pTriangles[i].st[k]].s / m_kHeader.skinwidth;
			GLfloat t = (GLfloat)m_pTexCoords[m_pTriangles[i].st[k]].t / m_kHeader.skinheight;

			// application des coordonnées de texture
			glTexCoord2f(s, t);

			// [normale]
			glNormal3fv(m_kAnorms[pVert->normalIndex]);

			// [vertex]
			vec3_t v;

			// calcul de la position absolue du vertex et redimensionnement
			v[0] = (pFrame->scale[0] * pVert->v[0] + pFrame->translate[0]) * m_fScale;
			v[1] = (pFrame->scale[1] * pVert->v[1] + pFrame->translate[1]) * m_fScale;
			v[2] = (pFrame->scale[2] * pVert->v[2] + pFrame->translate[2]) * m_fScale;

			glVertex3fv(v);
		}
	}
	glEnd();
}

MD2Model::~MD2Model(){}
