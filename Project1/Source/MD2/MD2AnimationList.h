#ifndef MD2_ANIMATION_LIST_H_
#define MD2_ANIMATION_LIST_H_

#include <string>
#include <vector>

using namespace std;

//!@brief Petite structure d�crivant les propri�t�s d'une animation.
struct AnimationData
{
	string	mo_AnimationName;	//Le nom de l'animation
	float	mf_FrameBegin;		//L'image dans la s�quences d'images du mod�le o� l'animation commence.
	float	mf_FrameEnd;		//L'image dans la s�quence d'images du mod�le o� l'animation arr�te.
	float	mf_FrameRate;		//Le nombre d'image par seconde de l'animation.
};

//!@brief Liste globale des animations.
//!
//! Cette liste d'animations est commune � tous les mod�les 3D utilis�s dans Quake 2.
//!	Puisque ce sont ces mod�les que nous utilisons dans le cadre du TP, ces derniers
//! ont tous la m�me liste d'animation.
extern AnimationData gto_AnimationList[];

#endif //MD2_ANIMATION_LIST_H_
