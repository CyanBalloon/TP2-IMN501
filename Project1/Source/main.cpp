#include <vector>
#include <iostream>

#include "ApplicationSettings.h"
#include "Camera/CameraMouse.h"
#include "MD2/MD2AnimationList.h"
#include "MD2/MD2Model.h"
#include "ThirdParty/glut.h"

using namespace std;

void InitDisplay(int* apu32_ArgCount, char** apc_ArgVal);
void InitScene();
void WelcomeMessage();

void DrawFrameCallback();
void MouseMotionCallback(int as32_X, int as32_Y);
void MouseButtonCallback(int as32_Button, int as32_State, int as32_X, int as32_Y);
void FrameExpireCallback(int as32_Value);
void KeyboardCallback(unsigned char ac_Key,int as32_X, int as32_Y);
void SpecialKeyboardCallback(int as32_Key, int as32_X, int as32_Y);

CameraMouse go_MouseCam;

MD2Model go_MD2Model1;
MD2Model go_MD2Model2;

int main(int aps32_ArgCount, char** apc_ArgVal)
{
	WelcomeMessage();

	InitDisplay(&aps32_ArgCount, apc_ArgVal);
	InitScene();

	glutMainLoop();
	return 0;
}

void WelcomeMessage()
{
	cout << "TP2 du cours IMN501 - Animation et chargement d'un modèle complexe" << endl;
	cout << "------------------------------------------------------------------" << endl << endl;
	cout << "Controle de la camera:" << endl;
	cout << "Bouton gauche -> rotation" << endl;
	cout << "Bouton droit -> zoom" << endl << endl;
	cout << "Touches:" << endl << endl;
	cout << "Q -> Quitter" << endl;
	cout << "F1 -> Rendu triangles pleins" << endl;
	cout << "F2 -> Rendu fil de fer" << endl;
	cout << "F3 -> Rendu points" << endl;
	cout << "Fleche Haut -> Augmenter la vitesse d'animation" << endl;
	cout << "Fleche Bas -> Diminuer la vitesse d'animation" << endl;
	cout << "Fleche Gauche -> Animation precedente" << endl;
	cout << "Fleche Droite -> Animation Suivante" << endl << endl;
	cout << "1 -> Modele DrFreakenStein" << endl;
	cout << "2 -> Modele Chevalier et Dragon" << endl;
	cout << "3 -> Modele Han Solo" << endl;
	cout << "4 -> Modele Chevalier Ange" << endl;
}

void InitDisplay(int* apu32_ArgCount, char** apc_ArgVal)
{
	glutInit(apu32_ArgCount,apc_ArgVal);
	glutInitWindowPosition(WINDOW_POSY,WINDOW_POSX);
	glutInitWindowSize(WINDOW_WIDTH,WINDOW_HEIGHT);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);

	glutCreateWindow(WINDOW_NAME);

	glutDisplayFunc(DrawFrameCallback);
	glutMouseFunc(	MouseButtonCallback);
	glutMotionFunc(	MouseMotionCallback);
	glutTimerFunc(FRAME_DURATION_MS,FrameExpireCallback,1);
	glutKeyboardFunc(KeyboardCallback);
	glutSpecialFunc(SpecialKeyboardCallback);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(67.5f,(float)WINDOW_WIDTH/(float)WINDOW_HEIGHT,0.1,100.0);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);

	glEnable(GL_NORMALIZE);

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
}

void InitScene()
{
	for(int i = 0; i < 20; ++i)
	{
		go_MD2Model1.AddAnimationData(gto_AnimationList[i]);
		go_MD2Model2.AddAnimationData(gto_AnimationList[i]);
	}

	//Dr FreakenStein
	//////////////////////////////////////////////////////////////////////////
	go_MD2Model1.LoadModel("Resources/DrFreak/tris.md2");
	go_MD2Model1.LoadTexture("Resources/DrFreak/drfreak.pcx");
	go_MD2Model2.LoadModel("Resources/DrFreak/weapon.md2");
	go_MD2Model2.LoadTexture("Resources/DrFreak/weapon.pcx");
}	

void DrawFrameCallback()
{
	float tf_Black[4] = {0,0,0,0};
	float tf_White[4] = {1,1,1,1};

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
	glClearColor(0.0, 0.0, 0.0, 0.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	go_MouseCam.RefreshCamera(0);
	
	float tf_LightPos1[] = {-5,5,5,1};
	glLightfv(GL_LIGHT0,GL_POSITION,tf_LightPos1);
	glLightf(GL_LIGHT0,GL_SPOT_CUTOFF,180.0f);

	float tf_LightPos2[] = {5,3,5,1};
	float tf_LightDiff2[] = {1.0f,1.0f,1.0,1};
	glLightfv(GL_LIGHT1,GL_POSITION,tf_LightPos2);
	glLightf(GL_LIGHT1,GL_SPOT_CUTOFF,180.0f);
	glLightfv(GL_LIGHT1,GL_DIFFUSE,tf_LightDiff2);

	glMaterialfv(GL_FRONT,GL_AMBIENT,tf_White);
	glMaterialfv(GL_FRONT,GL_EMISSION,tf_Black);
	glMaterialfv(GL_FRONT,GL_DIFFUSE,tf_White);
	glMaterialfv(GL_FRONT,GL_SPECULAR,tf_Black);

	glPushMatrix();

	glScalef(0.10f,0.10f,0.10f);
	glRotatef( -90.0, 1.0, 0.0, 0.0 );
	glRotatef( -90.0, 0.0, 0.0, 1.0 );

	go_MD2Model1.Render(1/FPS);
	go_MD2Model2.Render(1/FPS);

	glPopMatrix();

	glutSwapBuffers();
}

void MouseMotionCallback(int as32_X, int as32_Y)
{
	go_MouseCam.RefreshPosition(as32_X,as32_Y);
}

void MouseButtonCallback(int as32_Button, int as32_State, int as32_X, int as32_Y)
{
	go_MouseCam.RefreshState(as32_Button,as32_State,as32_X,as32_Y);
}

void FrameExpireCallback(int as32_Value)
{
	glutTimerFunc(FRAME_DURATION_MS,FrameExpireCallback,1);
	glutPostRedisplay();
}

void KeyboardCallback(unsigned char ac_Key,int as32_X, int as32_Y)
{
	switch(ac_Key)
	{
	case 'q' :
		go_MD2Model1.FreeResources();
		go_MD2Model2.FreeResources();
		exit(0);
		break;
	case '1' :
		go_MD2Model1.FreeResources();
		go_MD2Model2.FreeResources();
		go_MD2Model1.LoadModel("Resources/DrFreak/tris.md2");
		go_MD2Model1.LoadTexture("Resources/DrFreak/drfreak.pcx");
		go_MD2Model2.LoadModel("Resources/DrFreak/weapon.md2");
		go_MD2Model2.LoadTexture("Resources/DrFreak/weapon.pcx");
		break;

	case '2' :
		go_MD2Model1.FreeResources();
		go_MD2Model2.FreeResources();
		go_MD2Model1.LoadModel("Resources/DragonKnight/tris.md2");
		go_MD2Model1.LoadTexture("Resources/DragonKnight/dragon_armour.pcx");
		go_MD2Model2.LoadModel("Resources/DragonKnight/weapon.md2");
		go_MD2Model2.LoadTexture("Resources/DragonKnight/weapon.pcx");
		break;

	case '3' :
		go_MD2Model1.FreeResources();
		go_MD2Model2.FreeResources();
		go_MD2Model1.LoadModel("Resources/HanSolo/tris.md2");
		go_MD2Model1.LoadTexture("Resources/HanSolo/solo_anh.pcx");
		go_MD2Model2.LoadModel("Resources/HanSolo/weapon.md2");
		go_MD2Model2.LoadTexture("Resources/HanSolo/weapon.pcx");
		break;

	case '4' :
		go_MD2Model1.FreeResources();
		go_MD2Model2.FreeResources();
		go_MD2Model1.LoadModel("Resources/ForgottenOne/tris.md2");
		go_MD2Model1.LoadTexture("Resources/ForgottenOne/ForgottenOne.pcx");
		go_MD2Model2.LoadModel("Resources/ForgottenOne/weapon.md2");
		go_MD2Model2.LoadTexture("Resources/ForgottenOne/weapon.pcx");
		break;

	case ' ' :
		go_MD2Model1.PlayAnimation(!go_MD2Model1.IsAnimationPlaying());
		go_MD2Model2.PlayAnimation(!go_MD2Model2.IsAnimationPlaying());
		break;
	}
}

void SpecialKeyboardCallback(int as32_Key, int as32_X, int as32_Y)
{
	switch(as32_Key)
	{
	case GLUT_KEY_F1 :
		glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
		break;

	case GLUT_KEY_F2:
		glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
		break;

	case GLUT_KEY_F3:
		glPolygonMode( GL_FRONT_AND_BACK, GL_POINT );
		break;

	case GLUT_KEY_LEFT:
		go_MD2Model1.PreviousAnimation();
		go_MD2Model2.PreviousAnimation();
		break;

	case GLUT_KEY_RIGHT:
		go_MD2Model1.NextAnimation();
		go_MD2Model2.NextAnimation();
		break;

	case GLUT_KEY_UP :
		go_MD2Model1.SetAnimationSpeed(go_MD2Model1.GetAnimationSpeed() + 0.2f);
		go_MD2Model2.SetAnimationSpeed(go_MD2Model2.GetAnimationSpeed() + 0.2f);
		break;

	case GLUT_KEY_DOWN:
		go_MD2Model1.SetAnimationSpeed(go_MD2Model1.GetAnimationSpeed() - 0.2f);
		go_MD2Model2.SetAnimationSpeed(go_MD2Model2.GetAnimationSpeed() - 0.2f);
		break;
	}
}


