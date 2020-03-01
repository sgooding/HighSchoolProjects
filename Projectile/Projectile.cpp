/*
	Created By Sean Gooding 4/18/00
 ********PROJECTILES*********

  Input the velocity,angle, vertical positions,
  or city and lay seige 

  to change any of the above values type
  v90 for a velocity of 90 m/s
  a30 for an angle of 30 deg
  s to select a city
  h for help
  q for quit

  for some reason I can't get it to run on any other
  computers so if someone can get that to work I'd be 
  greatly appreciative

 */

using namespace std;

#include <iostream>
#include <sstream>
#include <math.h>
#include <unistd.h>
#include <GL/glut.h>

//#include <CMUgraphics.h>
#include <CarnegieMellonGraphics.h>
#include <apvector.h>
#include <apstring.h>

using namespace std;

class Projectile
{

	int iVelocity=75, initialHeight = 300;
	double iAngle = (60*3.1415926535897932)/180;
	std::string currentCity;
	Font gFont;



	// Function to wait for a mouse click and clear the screen
	//void WaitNClear(Window &inputWindow);
	//void DrawActionWindow(Window &actionWindow);
	//apvector <char> DisplayPrompt(Window &promptWindow);
	//bool HandlePrompt (Window &handleWindow ,
//			apvector<char> &handlePrompt ,
	//		Window &myWindow);
	//void DrawCities(Window &instWindow, Window &mywindow);
	//void ClearActionWindow(Window &actionWindow);
	//void Instructions(Window &handleWindow, Window &myWindow);
	//int  ArrayToInteger (apvector<char> &Array,Window &handleWindow);
	//void Calculation(Window &actionWindow,Window &myWindow);
	//void ClearPromptWindow(Window &promptWindow);
	//void UpdateVariableState(Window &actionWindow);
	//bool CheckTownLocation(Window &actionWindow, int x2,int y2);
	//void DrawGun(Window &actionWindow);
	//void DrawImage(Window &actionWindow);
	//void RunningPeople(Window &actionWindow);

	Image baseImage;
	Image gBurnImage;
	Image florence,springs, canon, pueblo, school;
	Image* gCurrentImage;

public:
	Projectile() :
		iVelocity(75),
		initialHeight(300),
		currentCity("ColoradoSprings.jpg"),
		gFont(Font::ROMAN,12),
		baseImage("GunBase1.jpg",Image::JPEG),
		canon("CanonCity.jpg",Image::JPEG),
		gBurnImage("FireExplosion.jpg",Image::JPEG),
		gManImage("Man1.jpg",Image::JPEG),
		gMan2Image("Man2.jpg",Image::JPEG),
		florence("Florence.jpg",Image::JPEG),
		springs("ColoradoSprings.jpg",Image::JPEG),
		pueblo("Pueblo.jpg",Image::JPEG),
		gCurrentImage(&canon)
	{

	}
	~Projectile()
	{
		exit(0);
	}

	void Run()
	{
		apvector <char> promptString;
		bool Quit;

		// Create a new window 600 by 440 in size
		Window testWindow(600, 440,"Projectile");
		testWindow.waitForKeyboardEvent();
		DrawActionWindow(testWindow);

		//Instructions(testWindow,myWindow);


		UpdateVariableState(testWindow);
		DrawImage(testWindow);
		DrawGun(testWindow);
		testWindow.drawImage(baseImage, 0, 300);

		do
		{
			promptString = DisplayPrompt(testWindow);
			Quit = HandlePrompt(testWindow,promptString,testWindow);
			std::cout << "Quit: " << Quit << std::endl;

		}while(!Quit);

		testWindow.drawText(Style::BLACK,gFont,200,150,"HAVE A GREAT DAY :)");
		testWindow.drawText(Style::BLACK,gFont,200,200,"click mouse anywhere to exit");
		testWindow.waitForKeyboardEvent();

	}
private:

	void WaitNClear(Window &inputWindow)
	{
		int iX, iY;


		//inputWindow.SetPen(BLACK);
		//inputWindow.SetFont(16, BOLD, SWISS);
		inputWindow.drawText(Style::BLACK, gFont, inputWindow.getWidth()/2 - 100, inputWindow.getHeight() - 25, "Click mouse to continue...");

		// Flush the mouse queue
		inputWindow.flushMouseQueue();

		// Ignore return value since we don't care what type of click it was
		inputWindow.waitForMouseEvent();
		iX = inputWindow.getMouseX();
		iY = inputWindow.getMouseY();

		// Set the brush and pen white so we can clear the background

		// Draw a rectangle that covers the entire window
		inputWindow.drawRectangleFilled(Style::WHITE,0, 0, inputWindow.getWidth(), inputWindow.getHeight());
	}

	void DrawActionWindow(Window &actionWindow)
	{
		Style pen(Color::BLACK,3);
		actionWindow.drawRectangleOutline(pen,3,3,actionWindow.getWidth()-5,300-3);
	}

	apvector <char> DisplayPrompt(Window &promptWindow)
		{
		char keyPressed, prevChar;
		int x = 100, y = 30, strLength = 0, i =0;
		apvector<char> PromptString(0,0);

		promptWindow.flushKeyboardQueue();

		promptWindow.drawText(Style::BLACK,gFont,0,y,"Sean $>");

		for(;;)
		{
			keyPressed = promptWindow.waitForKeyboardEvent().getValue();

			//Return Key
			if((keyPressed == 13) && (PromptString.length() > 0))
			{
				promptWindow.drawRectangleFilled(Style::WHITE,100,350,600,440);
				stringstream ss; ss << PromptString[0];
				promptWindow.drawText(Style::BLACK,gFont,5,5+x,ss.str());
				ClearPromptWindow(promptWindow);
				promptWindow.drawText(Style::BLACK,gFont,0,0,"Working...");
				return PromptString;
			}

			if(keyPressed != NamedKey::ESCAPE)
			{
				if( keyPressed == NamedKey::RIGHT_ARROW
						and keyPressed == 4
						and x > 100 )
				{
					x-=10;
					promptWindow.drawRectangleFilled(Style::WHITE,x,y,x+20,y+20);
					promptWindow.drawText(Style::BLACK,gFont,x,y,"_");
					PromptString.resize(PromptString.length()-1);
				}

				else
				{
					switch(keyPressed)
					{
					case ' ':
					{
						promptWindow.drawRectangleFilled(Style::WHITE,x-2,y+15,x+10,y+30);
						x+=10;
						promptWindow.drawText(Style::BLACK,gFont,x,y,"_");
						break;
					}
					case 13:
						break;

					case 8:
						if(x > 100)
						{
							x-=10;
							promptWindow.drawRectangleFilled(Style::WHITE,x,y,x+20,y+20);
							promptWindow.drawText(Style::BLACK,gFont,x,y,"_");
							PromptString.resize(PromptString.length()-1);
						}
						break;
					default:
					{
						promptWindow.drawRectangleFilled(Style::WHITE,x-2,y+15,x+10,y+30);
						PromptString.resize(PromptString.length()+1);
						PromptString[PromptString.length()-1] = keyPressed;
						stringstream ss; ss << keyPressed;
						promptWindow.drawText(Style::BLACK,gFont,x,y,ss.str());
						x+=10;
						promptWindow.drawText(Style::BLACK,gFont,x,y,"_");
					}
					}
				}
			}
			else
			{
				promptWindow.drawText(Style::BLACK,gFont,5,5,"Click on Window to Quit!");
			}

			prevChar = keyPressed;
		}

		return PromptString;
		}



	bool HandlePrompt ( Window &handleWindow ,
			apvector<char> &handlePrompt,
			Window &myWindow)
	{
		apvector<char> right(5);
		char answer;

		if(handlePrompt[0] == 's')
		{
			DrawCities(handleWindow,myWindow);
			DrawImage(handleWindow);
		}
		if(handlePrompt[0] == 'v')
		{
			iVelocity = ArrayToInteger(handlePrompt,handleWindow);
			UpdateVariableState(handleWindow);
			Calculation(handleWindow,myWindow);
		}

		if(handlePrompt[0] == 'h')
		{
			Instructions(handleWindow,myWindow);
		}

		if(handlePrompt[0] == 'a')
		{
			iAngle = ArrayToInteger(handlePrompt, handleWindow);
			iAngle = (iAngle*3.1415926535897932)/180;
			UpdateVariableState(handleWindow);
			ClearPromptWindow(myWindow);
			ClearActionWindow(handleWindow);
			DrawGun(handleWindow);
			DrawImage(handleWindow);
		}
		if(handlePrompt[0] == 'c')
		{
			myWindow.drawText(Style::BLACK,gFont,150,50,"Are you sure you want to clear screen? (y,n)");

			answer = myWindow.waitForKeyboardEvent().getValue();
			std::stringstream ss; ss << answer;
			handleWindow.drawText(Style::BLACK,gFont,50,50,ss.str());

			if(answer == 'y')
			{
				ClearActionWindow(handleWindow);
			}

			ClearPromptWindow(myWindow);
		}

		if(handlePrompt[0] == 'y')
		{
			initialHeight = ArrayToInteger(handlePrompt, handleWindow);
			initialHeight = 300 - initialHeight;
			UpdateVariableState(handleWindow);
			ClearPromptWindow(myWindow);
			ClearActionWindow(handleWindow);
			DrawImage(handleWindow);
			DrawGun(handleWindow);
		}



		if(handlePrompt[0] =='q')
		{
			handleWindow.drawText(Style::BLACK,gFont,150,350,"Are you sure you want to quit? (y,n)");
			answer = myWindow.waitForKeyboardEvent().getValue();

			if(answer == 'y')
			{
				return true;
			}
		}

		return false;

	}

	void DrawCities(Window &instWindow, Window &myWindow)
	{
		int bad = 0;

		char x;

		ClearActionWindow(instWindow);

		instWindow.drawText(Style::BLACK,gFont,150,50,"(1) Canon City");
		instWindow.drawText(Style::BLACK,gFont,150,70,"(2) Florence");
		instWindow.drawText(Style::BLACK,gFont,150,90,"(3) Pueblo");
		instWindow.drawText(Style::BLACK,gFont,150,110,"(4) Colorado Springs");

		instWindow.drawText(Style::BLACK,gFont,100,200,"Select Your City");
		x = myWindow.waitForKeyboardEvent().getValue();

		do
		{
			switch (x-48)
			{
			case 1:
				currentCity = "CanonCity.jpg";
				break;
			case 2:
				currentCity = "Florence.jpg";
				break;
			case 3:
				currentCity = "Pueblo.jpg";
				break;
			case 4:
				currentCity = "ColoradoSprings.jpg";
				break;
			default:
				instWindow.drawText(Style::BLACK,gFont,150,100,"Illegal Selection");
				bad = 1;
				break;
			}
		} while(bad == 1);

		ClearActionWindow(instWindow);

	}

	void ClearActionWindow(Window &actionWindow)
	{
		actionWindow.drawRectangleFilled(Style::WHITE,0,0,actionWindow.getWidth()-5,300);
	}


	void Instructions(Window &handleWindow,Window &myWindow)
	{
		char x;

		const int w(handleWindow.getWidth());
		const int h(handleWindow.getHeight());
		// not sure what this is for
		Image testImage( handleWindow.createImage(0, 0,w,h));

		ClearActionWindow(handleWindow);

		Style pen = Style(Color::BLACK,2);
		handleWindow.drawText(Style::BLACK,gFont,100,50,"The Commands Are:");
		handleWindow.drawLine(pen,100,70,270,70);
		handleWindow.drawText(Style::BLACK,gFont,100,80,"(s) Select City");
		handleWindow.drawText(Style::BLACK,gFont,100,100,"(v integer) Velocity and Value");
		handleWindow.drawText(Style::BLACK,gFont,100,120,"(a angle) Angle and Angle in Degrees");
		handleWindow.drawText(Style::BLACK,gFont,100,140,"(y integer) Vertical Height of Gun");
		handleWindow.drawText(Style::BLACK,gFont,100,160,"(q) Quit");
		handleWindow.drawText(Style::BLACK,gFont,100,180,"Example: v60 is a velocity of 60 m/s");

		handleWindow.drawText(Style::BLACK,gFont,100,200,"press any key to quit...");


		handleWindow.drawImage(canon, 50, 50);


		std::cout << "Wait for keyboard event" << std::endl;
		myWindow.waitForKeyboardEvent();
		std::cout << "Done." << std::endl;
		ClearActionWindow(handleWindow);

		std::cout << "Draw testImage: " << testImage << std::endl;
#if 0
		handleWindow.drawImage(testImage, 0, 0,
				Transform( (int)(testImage.getWidth()), (int)(testImage.getHeight())));
#else
		//handleWindow.drawImage(testImage, 10, 10);
#endif

	}

	int ArrayToInteger (apvector<char> &Array,Window &handleWindow)
	{
		int Exponent= Array.length()-2,Integer = 0;


		for(int i = 1; i<Array.length(); i++)
		{
			//handleWindow.DrawCharacter(10,10*i,Array[i]);
			Integer += (Array[i]-48)*(pow(10,Exponent));
			Exponent-=1;
		}

		//	handleWindow.DrawInteger(100,100,Integer);

		return Integer;
	}

	void Calculation(Window &actionWindow, Window &myWindow)
	{
		std::cout << "Calculation" << std::endl;
		double x1=0;
		double x2=0;
		double y1=initialHeight;
		double maxHeight = 0;
		int count = 0;
		bool destroyed(false);

		ClearActionWindow(actionWindow);

		double initialVelocity = iVelocity;
	    double vertVel;
	    double y2=y1;
	    double horzVel;

		std::cout << "Draw Gun" << std::endl;
		DrawGun(actionWindow);

		std::cout << "Draw Image" << std::endl;
		DrawImage(actionWindow);


		//x1 = cos(iAngle)*30;
		//y1 = y1-(sin(iAngle)*30);


		vertVel = -iVelocity*sin(iAngle);
		horzVel = iVelocity*cos(iAngle);

		cout<<iVelocity<<"   "<<vertVel;
		actionWindow.flushMouseQueue();

		//actionWindow.drawRectangleFilled(Style(Color::BLACK,1),250,400,300,500);
		//actionWindow.drawText(Style::BLACK,gFont,250,400,"Vert Velocity: " + Window::numberToString(vertVel));

		std::cout << "Initial: " << time << " : " << y2 << std::endl;
		double dt(0.1);
		for(double time = 0; time <= 20.0; time += dt)
		{
			usleep(100000);

			//Vertical Velocity
			vertVel += 9.8 * dt;

			//Vertical Displacement
			y2 = ((vertVel * dt) + (.5 * -9.8 * dt) + y1);

			//+ -y1
			//Horizontal Displacement
			x2 = (horzVel * dt) + x1;

			Style pen(Color::RED,3);
			actionWindow.drawLine(pen,x1,y1,x2,y2);
			std::cout << "T: " << time
					  << " (x1,y1): " << x1 << "," << y1
					  << " (x2,y2): " << x2 << "," << y2 << std::endl;

			if(maxHeight <  300 - y2)
			{
				maxHeight = 300 - y2;
			}

			x1 = x2;
			y1 = y2;

			//Check Town Location
			destroyed = CheckTownLocation(actionWindow,x2,y2);

			if(destroyed == true)
			{
				std::cout << "Town was destroyed!!" << std::endl;
				break;
			}

			count++;
			if(count == 1)
			{
				UpdateVariableState(actionWindow);
				actionWindow.drawRectangleFilled(Style(Color::WHITE,1),200,400,300,300);
				actionWindow.drawText(Style::BLACK,gFont,200,400,Window::numberToString(300 - y2));
				count = 0;
			}

			if((int)y2 > 300)
			{
				break;
			}

		}

		actionWindow.drawText(Style::BLACK,gFont,100,200,"BAM!");
		UpdateVariableState(actionWindow);

		if(!destroyed)
		{
			RunningPeople(actionWindow);
		}

		actionWindow.drawText(Style::BLACK,gFont,200,321,"HORIZONTAL DISTANCE = " );
		actionWindow.drawText(Style::BLACK,gFont,440,321, Window::numberToString(x2));

		actionWindow.drawText(Style::BLACK,gFont,200,353,"MAX HEIGHT = " );
		actionWindow.drawText(Style::BLACK,gFont,440,353,Window::numberToString(maxHeight));

		//ClearPromptWindow(myWindow);

	}

	void ClearPromptWindow(Window &promptWindow)
	{
		Style pen(Color::WHITE);
		promptWindow.drawRectangleFilled(pen,
				0,0,
				promptWindow.getWidth(),promptWindow.getHeight());
	}

	void UpdateVariableState(Window &actionWindow)
	{
		actionWindow.drawRectangleFilled(Style::WHITE,0,300,actionWindow.getWidth(),actionWindow.getHeight());

		actionWindow.drawText(Style::BLACK,gFont,0,311,"ANGLE = ");

		{
			std::stringstream ss; ss << ((iAngle * 180)/3.1415926535897932);
			actionWindow.drawText(Style::BLACK,gFont,100,311,ss.str());
		}

		actionWindow.drawText(Style::BLACK,gFont,0,333,"VELOCITY = ");
		{
			std::stringstream ss; ss << iVelocity;
			actionWindow.drawText(Style::BLACK,gFont,100,333,ss.str());
		}
	}



	bool CheckTownLocation(Window &actionWindow,int x2,int y2)
	{

		Image& testImage(*gCurrentImage);
		Image& burnImage(gBurnImage);

		if (((x2 >= 320) && (x2 <=320+testImage.getWidth())) &&
				( (y2 >= (300 - testImage.getHeight())) && (y2 <= 300))
		)

		{

			actionWindow.drawRectangleFilled(Style::WHITE,
					320, 300-((int)testImage.getHeight()*.5),320+
					(int)(testImage.getWidth() * .5), 300);

			int y_offset(0);
			for(double dscale = 0; dscale <= 1; dscale=dscale + .05)
			{
				double scale = 0.5+dscale;
				double x_center = 0.5*(burnImage.getWidth()*scale);
				double y_center = 0.5*(burnImage.getHeight()*scale);
				actionWindow.drawImage(burnImage,
						335-int(x_center), 250-int(y_center),
						Transform(scale,scale));
				usleep(100000);

			}
			return true;
		}
		else return false;
	}

	void DrawGun(Window &actionWindow)
	{
		double gunx(cos(iAngle)*30);
		double guny(sin(iAngle)*30);

		Style pen = Style(Color::BLACK,1);
		actionWindow.drawLine(pen,0,initialHeight,gunx,initialHeight-guny );
	}

	void DrawImage(Window &actionWindow)
	{
//		// Draw the image once
//		if(not Image::checkImage(currentCity, Image::JPEG))
//		{
//			std::cout << "ERROR: The " << currentCity << " image did not load correctly." << std::endl;
//		}
//
//		gCurrentImage = Image(currentCity, Image::JPEG);

		Transform scale(0.5,0.5);

		int x(320);


		if(currentCity == "ColoradoSprings.jpg")
		{
			int y(300-(int)springs.getHeight()*.5);
			actionWindow.drawImage(springs, x, y,scale);
			gCurrentImage = &springs;
		}
		else if(currentCity == "Pueblo.jpg")
		{
			int y(300-(int)pueblo.getHeight()*.5);
			actionWindow.drawImage(pueblo,x,y,scale);
			gCurrentImage = &pueblo;
		}
		else if(currentCity == "CanonCity.jpg")
		{
			int y(300-(int)canon.getHeight()*.5);
			actionWindow.drawImage(canon,x,y,scale);
			gCurrentImage = &canon;
		}
		else if(currentCity == "Florence.jpg")
		{
			int y(300-(int)florence.getHeight()*.5);
			actionWindow.drawImage(florence,x,y,scale);
			gCurrentImage = &florence;
		}
	}

	Image gManImage;
	Image gMan2Image;

	void RunningPeople(Window &actionWindow)
	{
		Image& manImage(gManImage);
		Image& man2Image(gMan2Image);//"Man2.jpg",Image::JPEG);

		for(int i = 0;i<=25;i++)
		{
			usleep(100000);
			Style pen(Color::WHITE,1);
			actionWindow.drawRectangleFilled(
					pen,
					360,
					289-((int)man2Image.getHeight()),
					360+((int)man2Image.getWidth()+(25*10)),
					299);

			if(i%2 == 0)
			{
				actionWindow.drawImage(manImage,
						360+(i*10),
						299-((int)manImage.getHeight()));
			}
			else
			{

				actionWindow.drawImage(man2Image,
						360+(i*10),
						289-((int)manImage.getHeight()));
			}

			usleep(100);



		}
	}
};


int main(int argn, char* argc[])
{
	Projectile app;
	app.Run();
	return 0;
}
