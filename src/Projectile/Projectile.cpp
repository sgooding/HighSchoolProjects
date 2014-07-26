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

#include <iostream.h>
#include <sstream>
#include <math.h>

#include <CMUgraphics.h>
#include <APVECTOR.H>
#include <APSTRING.H>

using namespace std;

int iVelocity=75, initialHeight = 300;
double iAngle = (60*3.1415926535897932)/180;
string currentCity("ColoradoSprings.jpg");


// Function to wait for a mouse click and clear the screen
void WaitNClear(window &inputWindow);
void DrawActionWindow(window &actionWindow);
apvector <char> DisplayPrompt(window &promptWindow);
bool HandlePrompt (window &handleWindow , 
				   apvector<char> &handlePrompt ,
				   window &myWindow);
void DrawCities(window &instWindow, window &mywindow);
void ClearActionWindow(window &actionWindow);
void Instructions(window &handleWindow, window &myWindow);
int  ArrayToInteger (apvector<char> &Array,window &handleWindow);
void Calculation(window &actionWindow,window &myWindow);
void ClearPromptWindow(window &promptWindow);
void UpdateVariableState(window &actionWindow);
bool CheckTownLocation(window &actionWindow, int x2,int y2);
void DrawGun(window &actionWindow);
void DrawImage(window &actionWindow);
void RunningPeople(window &actionWindow);





int main(int argn, char* argv[])
{

 apvector <char> promptString;
 bool Quit;
    // Create a new window 600 by 440 in size
    window testWindow(600, 440, 5, 5);
	window myWindow(600,200,5,445);

    // Change the window title to something different
    testWindow.ChangeTitle("Projectiles");
  	
 testWindow.SetPen(BLACK);
 testWindow.SetFont(20, BOLD, SWISS);

    
    
	DrawActionWindow(testWindow);
	Instructions(testWindow,myWindow);
	UpdateVariableState(testWindow);

	DrawImage(testWindow);
	image baseImage("Gunbase1.jpg",JPEG);

	DrawGun(testWindow);
    


	testWindow.DrawImage(baseImage, 0, 300);


	
	do
	{
	promptString = DisplayPrompt(myWindow);
	Quit = HandlePrompt(testWindow,promptString,myWindow);
	//Calculation(testWindow);
	}while(!Quit);

	testWindow.DrawString(200,150,"HAVE A GREAT DAY :)");
	testWindow.DrawString(200,200,"click mouse anywhere to exit");
	
    return 0;
}

void WaitNClear(window &inputWindow)
{
 int iX, iY;
 
 	inputWindow.SetPen(BLACK);
	inputWindow.SetFont(16, BOLD, SWISS);
    inputWindow.DrawString(inputWindow.GetWidth()/2 - 100, inputWindow.GetHeight() - 25, "Click mouse to continue...");

    // Flush the mouse queue
    inputWindow.FlushMouseQueue();

    // Ignore return value since we don't care what type of click it was
    inputWindow.WaitMouseClick(iX, iY);

    // Set the brush and pen white so we can clear the background
    inputWindow.SetPen(WHITE, 0);    
    inputWindow.SetBrush(WHITE);
    
    // Draw a rectangle that covers the entire window
    inputWindow.DrawRectangle(0, 0, inputWindow.GetWidth(), inputWindow.GetHeight());
}

void DrawActionWindow(window &actionWindow)
{

	actionWindow.SetPen(BLACK);
	actionWindow.SetBrush(WHITE);
	actionWindow.DrawRectangle(0,0,actionWindow.GetWidth()-5,300);
}

apvector <char> DisplayPrompt(window &promptWindow)
{
	char keyPressed, prevChar;
	int x = 100, y = 30, strLength = 0, i =0;
	apvector<char> PromptString(0,0);

	promptWindow.FlushKeyQueue();
	promptWindow.SetPen(BLACK);
	promptWindow.SetBrush(BLACK);
	promptWindow.SetFont(20,BOLD, SWISS);
	keytype temp = ASCII;

	promptWindow.DrawString(0,y,"Sean $>");
	
	for(;temp != ESCAPE;)
	{ 
			temp = promptWindow.WaitKeyPress(keyPressed);

			//Return Key
			if((keyPressed == 13) && (PromptString.length() > 0))
			{
				promptWindow.SetPen(WHITE);
				promptWindow.SetBrush(WHITE);
				promptWindow.DrawRectangle(100,350,600,440,FILLED);
				promptWindow.SetPen(BLACK);
				//PromptString[strLength]
                stringstream ss; ss << PromptString[0];
				promptWindow.DrawString(5,5+x,ss.str());
				promptWindow.DrawInteger(10,10,PromptString.length());

				ClearPromptWindow(promptWindow);

				promptWindow.DrawString(0,0,"Working...");

				return PromptString;
			}
				
			if(temp!=ESCAPE)
			{
				if(temp == ARROW)
				{
					if(keyPressed == 4)
					{	
					
					if(x > 100)
						{x-=10;
						promptWindow.SetPen(WHITE);			
						promptWindow.SetBrush(WHITE);			
						promptWindow.DrawRectangle(x,y,x+20,y+20,FILLED);			
						promptWindow.SetPen(BLACK);
						promptWindow.DrawString(x,y,"_");
						PromptString.resize(PromptString.length()-1);

						}
					}

				}

				else{

					switch(keyPressed)
					{
			
						case ' ':
							promptWindow.SetPen(WHITE);
							promptWindow.SetBrush(WHITE);
							promptWindow.DrawRectangle(x-2,y+15,x+10,y+30,FILLED);
							promptWindow.SetPen(BLACK);
							x+=10;
							promptWindow.DrawString(x,y,"_");
							break;

						case 13:
							break;
			
						case 8:	
						if(x > 100)
						{x-=10;
						promptWindow.SetPen(WHITE);			
						promptWindow.SetBrush(WHITE);			
						promptWindow.DrawRectangle(x,y,x+20,y+20,FILLED);			
						promptWindow.SetPen(BLACK);
						promptWindow.DrawString(x,y,"_");
						PromptString.resize(PromptString.length()-1);

						}
							break;
						
						default:
							promptWindow.SetPen(WHITE);
							promptWindow.SetBrush(WHITE);
							promptWindow.DrawRectangle(x-2,y+15,x+10,y+30,FILLED);
							promptWindow.SetPen(BLACK);
							
							PromptString.resize(PromptString.length()+1);
							PromptString[PromptString.length()-1] = keyPressed;
							


                            stringstream ss; ss << keyPressed;
							promptWindow.DrawString(x,y,ss.str());	
							x+=10;
							promptWindow.DrawString(x,y,"_");
							break;
					}
				
				}
			
			}else promptWindow.DrawString(5,5,"Click on Window to Quit!");
			
			prevChar = keyPressed;

		
		

			
		
	}
	return 0;
}



bool HandlePrompt (window &handleWindow , apvector<char> &handlePrompt,
				   window &myWindow)
{
	apvector<char> right(5);
	char answer;

		
	//handleWindow.DrawInteger(5,5,handlePrompt[1]);


	
	if(handlePrompt[0] == 's')
	{
		DrawCities(handleWindow,myWindow);
		DrawImage(handleWindow);

		
	}


	if(handlePrompt[0] == 'v')
	{	
			//handleWindow.DrawString(0,0,"What the Hell");

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

	if(handlePrompt[0] == 't')
	{
	}

	if(handlePrompt[0] == 'c')
	{
		myWindow.DrawString(150,50,"Are you sure you want to clear screen? (y,n)");
		myWindow.WaitKeyPress(answer);
		handleWindow.DrawInteger(50,50,answer);
		
		if(answer == 'y')
			ClearActionWindow(handleWindow);


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
		
		handleWindow.DrawString(150,350,"Are you sure you want to quit? (y,n)");
		myWindow.WaitKeyPress(answer);
		//handleWindow.DrawCharacter(50,50,answer);
		if(answer == 'y')
		{
			handleWindow.SetWaitClose(false);
			return true;
		}
	}

	return false;

}

void DrawCities(window &instWindow, window &myWindow)
{	int bad = 0;

	char x;

	ClearActionWindow(instWindow);

	instWindow.DrawString(150,50,"(1) Canon City");
	instWindow.DrawString(150,70,"(2) Florence");
	instWindow.DrawString(150,90,"(3) Pueblo");
	instWindow.DrawString(150,110,"(4) Colorado Springs");

	instWindow.DrawString(100,200,"Select Your City");
	myWindow.WaitKeyPress(x);

	do{

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
		instWindow.DrawString(150,100,"Illegal Selection");
		bad = 1;
		break;
	}
	}
	while(bad == 1);

  

		
		
	ClearActionWindow(instWindow);

}

void ClearActionWindow(window &actionWindow)
{
	actionWindow.SetPen(BLACK);
	actionWindow.SetBrush(WHITE);
	actionWindow.DrawRectangle(0,0,actionWindow.GetWidth()-5,300);
}

void Instructions(window &handleWindow,window &myWindow)
{ char x;
image testImage;

handleWindow.StoreImage(testImage, 0, 0, (unsigned short)(handleWindow.GetWidth()), (unsigned short)(handleWindow.GetHeight()));

ClearActionWindow(handleWindow);

	handleWindow.DrawString(100,50,"The Commands Are:");
		handleWindow.DrawLine(100,70,270,70);
		handleWindow.DrawString(100,80,"(s) Select City");
		handleWindow.DrawString(100,100,"(v integer) Velocity and Value");
		handleWindow.DrawString(100,120,"(a angle) Angle and Angle in Degrees");
		handleWindow.DrawString(100,140,"(y integer) Vertical Height of Gun");
		handleWindow.DrawString(100,160,"(q) Quit");
		handleWindow.DrawString(100,180,"Example: v60 is a velocity of 60 m/s");

		handleWindow.DrawString(100,200,"press any key to quit...");
		myWindow.WaitKeyPress(x);
		ClearActionWindow(handleWindow);

handleWindow.DrawImage(testImage, 0, 0, (int)(testImage.GetWidth()), (int)(testImage.GetHeight()));

}

int ArrayToInteger (apvector<char> &Array,window &handleWindow)
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

void Calculation(window &actionWindow, window &myWindow)
{
	double x1=0,x2=0,y1=initialHeight,maxHeight = 0;
	int count = 0;
	bool destroyed;

	ClearActionWindow(actionWindow);

	double initialVelocity = iVelocity, vertVel, y2=0, horzVel;

	

    DrawGun(actionWindow);
	DrawImage(actionWindow);


	x1 = cos(iAngle)*30;
	y1 = y1-(sin(iAngle)*30);




	vertVel = -iVelocity*sin(iAngle);
//iVelocity *
	horzVel = iVelocity*cos(iAngle);

	cout<<iVelocity<<"   "<<vertVel;
	actionWindow.FlushMouseQueue();
	actionWindow.DrawInteger(200,300,vertVel);



	for(double time = 0; y2 <= 300; time+=.1)
	{
		Pause(100);

		//Vertical Velocity	
		vertVel = (vertVel + (9.8 * time));
		 

		//Vertical Displacement
		y2 = ((vertVel * time) + (.5 * -9.8 * time) + y1);
		
	//+ -y1
		//Horizontal Displacement
		x2 = (horzVel * time) + x1;

		//if(y2>=260)
		//{break;}

		actionWindow.SetPen(RED,5);
		actionWindow.DrawLine(x1,y1,x2,y2);

		if(maxHeight <  300 - y2)
			maxHeight = 300 - y2;

		//cout<<y2<<' ';
		x1 = x2;
		y1 = y2;

		//Check Town Location
		destroyed = CheckTownLocation(actionWindow,x2,y2);

		if(destroyed == true)
			break;

		count++;
		if(count == 1)
		{
		UpdateVariableState(actionWindow);
		actionWindow.DrawInteger(200,300,300 - y2);
		count = 0;
		}

	





	}

	actionWindow.DrawString(100,200,"BAM!");
	UpdateVariableState(actionWindow);

	if(!destroyed)
	{	RunningPeople(actionWindow); }

	actionWindow.DrawString(200,311,"HORIZONTAL DISTANCE = " );
	actionWindow.DrawDouble(440,311, x2);

	actionWindow.DrawString(200,333,"MAX HEIGHT = " );
	actionWindow.DrawDouble(440,333,maxHeight);

	ClearPromptWindow(myWindow);
	
	//CheckTownLocation(actionWindow,(int)x2, (int)y2);


	//actionWindow.DrawInteger(5,20,x);
//	actionWindow.DrawInteger(20,20,iVelocity);
//	actionWindow.DrawInteger(40,20,iAngle);

//	actionWindow.SetPen(BLACK);
//	actionWindow.DrawLine(0,20,x,20);
	


}

void ClearPromptWindow(window &promptWindow)
{
	/*
				promptWindow.SetPen(WHITE);
				promptWindow.SetBrush(WHITE);
				promptWindow.DrawRectangle(100,350,600,440,FILLED);
				promptWindow.SetPen(BLACK);
	*/
	promptWindow.SetPen(WHITE);
	promptWindow.SetBrush(WHITE);
	promptWindow.DrawRectangle(0,0,promptWindow.GetWidth(),promptWindow.GetHeight());
	promptWindow.SetPen(BLACK);
}

void UpdateVariableState(window &actionWindow)
{
	actionWindow.SetPen(WHITE);
	actionWindow.SetBrush(WHITE);
	actionWindow.DrawRectangle(0,300,actionWindow.GetWidth(),actionWindow.GetHeight());

	actionWindow.SetPen(BLACK);
	
	actionWindow.DrawString(0,311,"ANGLE = ");
	actionWindow.DrawDouble(100,311,((iAngle * 180)/3.1415926535897932));

	actionWindow.DrawString(0,333,"VELOCITY = ");
	actionWindow.DrawInteger(100,333,iVelocity);
}

bool CheckTownLocation(window &actionWindow,int x2,int y2)
{
		
	image testImage(currentCity, JPEG);
	image burnImage("FireExplosion.jpg",JPEG);
	actionWindow.SetPen(BLACK);


	if (((x2 >= 320) && (x2 <=320+testImage.GetWidth())) &&
		( (y2 >= (300 - testImage.GetHeight())) && (y2 <= 300))
		)

	{	
			actionWindow.SetBrush(WHITE);
			actionWindow.SetPen(WHITE);

				actionWindow.DrawRectangle(320, 300-((int)testImage.GetHeight()*.5),320+
								(int)(testImage.GetWidth() * .5), 300);

			for(double dscale = 0; dscale <=2; dscale=dscale + .1)
			{
			actionWindow.DrawImage(burnImage, 335-dscale*10, 300-((int)testImage.GetHeight()*.5)*dscale,
				(int)(testImage.GetWidth() * .5)*dscale, (int)(testImage.GetHeight() * .5)*dscale);
			
			Pause(100);
			
			//actionWindow.DrawRectangle(320, 300-((int)testImage.GetHeight()*.5)*dscale,320+
			//					(int)(testImage.GetWidth() * .5)*dscale, 300);

			//(int)(testImage.GetHeight() * .5)*dscale
			
			}
			return true;
	}
	else return false;
}

void DrawGun(window &actionWindow)
{
	double gunx,guny;

	gunx = cos(iAngle)*30;
	guny = sin(iAngle)*30;
	//Gun
	actionWindow.SetPen(BLACK,5);
	actionWindow.DrawLine(0,initialHeight,gunx,initialHeight-guny );
}

void DrawImage(window &actionWindow)
{
	    // Draw the image once
	image testImage(currentCity, JPEG);
    actionWindow.DrawImage(testImage, 320, 300-((int)testImage.GetHeight()*.5),
	(int)(testImage.GetWidth() * .5), (int)(testImage.GetHeight() * .5));

	actionWindow.SetPen(WHITE);
	actionWindow.SetBrush(WHITE);
}

void RunningPeople(window &actionWindow)
{


	image manImage("man1.jpg",JPEG);
	image man2Image("man2.jpg",JPEG);

	actionWindow.SetPen(WHITE);
	actionWindow.SetBrush(WHITE);


	
	for(int i = 0;i<=25;i++)
	{

		Pause(10);
		if(i%2 == 0)
		{
	actionWindow.DrawImage(manImage,360+(i*10), 299-((int)manImage.GetHeight()),
		(int)(manImage.GetWidth()), (int)(manImage.GetHeight()));
		}
		else{	
	actionWindow.DrawImage(man2Image,360+(i*10), 289-((int)manImage.GetHeight()),
		(int)(manImage.GetWidth()), (int)(manImage.GetHeight()));
		}

	Pause(100);


	actionWindow.DrawRectangle(360+(i*10), 289-((int)man2Image.GetHeight()),
		360+((int)man2Image.GetWidth()+(i*10)), 299);
	}

	actionWindow.SetPen(BLACK);
}






