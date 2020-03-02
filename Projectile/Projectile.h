#ifndef _Projectile_H_
#define _Projectile_H_

#include <iostream>
#include <sstream>
#include <math.h>
#include <unistd.h>
#include <GL/glut.h>

#include <CarnegieMellonGraphics.h>
#include <ImageMap.h>

#include <apvector.h>
#include <apstring.h>


inline double DEG2RAD(const double& DEG) 
{ 
    return DEG*M_PI/180.0; 
}

class Projectile
{

public:

	Projectile();

	~Projectile();

	void Run();

private:
	
	apvector <char> DisplayPrompt();
    
	bool HandlePrompt ( Window &handleWindow ,
			apvector<char> &handlePrompt,
			Window &myWindow);

	void DrawCities(Window &instWindow, Window &myWindow);

	void ClearActionWindow();
	
	void Instructions();

	int ArrayToInteger(apvector<char> &Array);
	
	void Calculation(Window &actionWindow, Window &myWindow);

	void ClearPromptWindow();
	
	void UpdateVariableState();
	
	bool CheckTownLocation(Window &actionWindow,int x2,int y2);

	void DrawGun(Window &actionWindow);

	void DrawCity(Window &actionWindow);

	void RunningPeople(Window &actionWindow);
	
	void DrawFinalResults();

    Window testWindow;
    Window helpWindow;

	int iVelocity;
    int initialHeight;
	int iAngleDeg;
	std::string currentCity;
	Font gFont;

    ImageMap mImageMap;

    double mFinalX;
    double mMaxHeight;



};
#endif
