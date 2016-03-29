#ifndef MD2MODEL_H_
#define MD2MODEL_H_

#include <string>

#include "MD2AnimationList.h"
#include "MD2Types.h"
#include "../../Source/ThirdParty/glut.h"

using namespace std;

//!@brief Classe fa�ade exposant les fonctionnalit�s d'un mod�le MD2.
//!
//!	Notez que cette classe n'est qu'une fa�ade afin de regrouper toutes
//!	les fonctionnalit�s sous le m�me interface. Il est tr�s fortement 
//! sugg�r� de d�velopper une meilleure architecture derri�re la fa�ade.
class MD2Model
{
public:
	#define BASE_SPEED 150
	#define MD2_VERSION 8
	#define MD2_IDENT (('2'<<24) + ('P'<<16) + ('D'<<8) + 'I')

	vec3_t  m_kAnorms[162];
	float current_speed = 1.0f;

	md2_header_t    m_kHeader;
	md2_skin_t      *m_pSkins;
	md2_texCoord_t  *m_pTexCoords;
	md2_triangle_t  *m_pTriangles;
	md2_frame_t     *m_pFrames;
	int             *m_pGLcmds;
	float				alpha;
	float			frame_index;
	bool			next_frame = false;
	bool			previous_frame = false;
	int current_frame = 0;
	int overkill;
	int frames_for_animation = BASE_SPEED;
	int current_frame_animation = 1;

	GLfloat         m_fScale;
	GLuint          m_uiTexID;
	
	//!@brief Constructeur
	MD2Model();
	//!@brieft Destructeur
	~MD2Model();

	//!@brief Sert � charger le mod�le MD2.
	//!@param[in] ao_FileName Nom du fichier contenant le mod�le md2.
	void LoadModel(const string &ao_FileName);

	//!@brief Sert � charger une texture � associer au mod�le.
	//!@param[in] ao_FileName Nom du fichier contenant la texture.
	//!@warning ATTENTION : Le forum de texture � utiliser est PCX.
	void LoadTexture(const string &ao_FileName);

	//!@brief Lib�re les ressources allou�es lors du
	//!			chargement. (Textures + Mod�le)
	void FreeResources();

	//!@brief Ajoute une animation � la liste des animations
	//!			du mod�le.
	void AddAnimationData(const AnimationData& ao_AnimationData);
	
	//!@brief Active/d�sactive l'animation du mod�le 3D.
	//!@param[in] ab_PlayAnim Bool�an indiquant si l'animation doit jouer (true) ou non (false).
	void PlayAnimation(bool ab_PlayAnim);
	//!@brief Retourne si l'animation est entrain de jouer ou non.
	bool IsAnimationPlaying() const;

	//!@brief Change � la prochaine animation dans la liste d'animations.
	void NextAnimation();

	//!@brief Change � l'animation pr�c�dente dans la liste d'animations.
	void PreviousAnimation();

	//!@brief Configure la vitesse d'animation.
	//!@param[in] af_Speed multiplicateur de la vitesse d'animation.
	//!
	//!@note	La valeur af_Speed est un multiplicateur. Par exemple, une vitesse 
	//!			de 1 est la vitesse normale d'animation. Une vitesse de -1 jouera 
	//!			l'animation � l'envers et une vitesse de 0.5 la jouera � la moiti� de
	//!			sa vitesse normale.
	void SetAnimationSpeed(float af_Speed);

	//!@brief Retourne la vitesse d'animation
	float GetAnimationSpeed() const;

	//!@brief Effectuer l'animation et le rendu en fonction du temps.
	//!@param[in] af_DeltaT �cart de temps entre l'image pr�c�dente et l'image courante.
	void Render(float af_DeltaT);

protected:
};


#endif //MD2MODEL_H_
