#include "MD2Model.h"
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
		file.read((char *)&m_pFrames[i].scale, sizeof(Vector3));
		file.read((char *)&m_pFrames[i].translate, sizeof(Vector3));
		file.read((char *)&m_pFrames[i].name, sizeof(char) * 16);
		file.read((char *)m_pFrames[i].verts, sizeof(md2_vertex_t) * m_kHeader.num_vertices);
	}

	// lecture des commandes opengl
	file.seekg(m_kHeader.offset_glcmds, std::ios::beg);
	file.read((char *)m_pGLcmds, sizeof(int) * m_kHeader.num_glcmds);

	// fermeture du fichier
	file.close();
}

void MD2Model::LoadTexture(const std::string &ao_FileName){}
void MD2Model::FreeResources(){}
void MD2Model::AddAnimationData(const AnimationData& ao_AnimationData){}

void MD2Model::PlayAnimation(bool ab_PlayAnim){}
bool MD2Model::IsAnimationPlaying() const{ return true;}

void MD2Model::NextAnimation(){}
void MD2Model::PreviousAnimation(){}

void MD2Model::SetAnimationSpeed(float af_Speed){}
float MD2Model::GetAnimationSpeed() const{ return 0.0f;}

void MD2Model::Render(float af_DeltaT){}

MD2Model::~MD2Model(){}
