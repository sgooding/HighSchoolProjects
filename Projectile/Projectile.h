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

#include <map>


inline double DEG2RAD(const double& DEG) 
{ 
    return DEG*M_PI/180.0; 
}

class Projectile
{
    Window testWindow;
    Window helpWindow;

	int iVelocity;
    int initialHeight;
	double iAngle;
	std::string currentCity;
	Font gFont;

    ImageMap mImageMap;

public:

	Projectile();

	~Projectile();

	void Run();

private:

	void DrawActionWindow();
	
	apvector <char> DisplayPrompt();
    
	bool HandlePrompt ( Window &handleWindow ,
			apvector<char> &handlePrompt,
			Window &myWindow);

	void DrawCities(Window &instWindow, Window &myWindow);

	void ClearActionWindow(Window &actionWindow);
	
	void Instructions();

	int ArrayToInteger(apvector<char> &Array);
	
	void Calculation(Window &actionWindow, Window &myWindow);

	void ClearPromptWindow();
	
	void UpdateVariableState();
	
	bool CheckTownLocation(Window &actionWindow,int x2,int y2);

	void DrawGun(Window &actionWindow);

	void DrawCity(Window &actionWindow);

	void RunningPeople(Window &actionWindow);
	
};
#endif
