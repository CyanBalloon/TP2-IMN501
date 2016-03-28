#ifndef MD2_ANIMATION_LIST_H_
#define MD2_ANIMATION_LIST_H_

#include <string>
#include <vector>

using namespace std;

//!@brief Petite structure décrivant les propriétés d'une animation.
struct AnimationData
{
	string	mo_AnimationName;	//Le nom de l'animation
	float	mf_FrameBegin;		//L'image dans la séquences d'images du modèle où l'animation commence.
	float	mf_FrameEnd;		//L'image dans la séquence d'images du modèle où l'animation arrête.
	float	mf_FrameRate;		//Le nombre d'image par seconde de l'animation.
};

//!@brief Liste globale des animations.
//!
//! Cette liste d'animations est commune à tous les modèles 3D utilisés dans Quake 2.
//!	Puisque ce sont ces modèles que nous utilisons dans le cadre du TP, ces derniers
//! ont tous la même liste d'animation.
extern AnimationData gto_AnimationList[];

#endif //MD2_ANIMATION_LIST_H_
