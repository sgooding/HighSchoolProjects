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

#include <Projectile.h>

using namespace std;

Projectile::Projectile() :
    testWindow(600, 440,"Projectile"),
    helpWindow(600, 440,"help"),
    iVelocity(75),
    initialHeight(300),
    iAngle(DEG2RAD(60.0)),
    currentCity("ColoradoSprings.jpg"),
    gFont(Font::ROMAN,10)
{
    mImageMap.LoadImages();
}

Projectile::~Projectile()
{
    exit(0);
}

void Projectile::Run()
{
    apvector <char> promptString;

    DrawActionWindow();
    Instructions();

    UpdateVariableState();
    DrawCity(testWindow);
    DrawGun(testWindow);

    bool quit(false);
    while(not quit)
    {
        promptString = DisplayPrompt();
        quit = HandlePrompt(testWindow,promptString,testWindow);
    }

    testWindow.drawText(Style::BLACK,gFont,200,150,"HAVE A GREAT DAY :)");
    testWindow.drawText(Style::BLACK,gFont,200,200,"Hit <ENTER> Quit");
    testWindow.waitForKeyboardEvent();

}

//private:

void Projectile::DrawActionWindow()
{
    testWindow.drawRectangleFilled(Style::WHITE,0,0,testWindow.getWidth(),300);
    Style pen(Color::BLACK,3);
    testWindow.drawRectangleOutline(pen,3,3,testWindow.getWidth()-5,300-3);
}

apvector <char> Projectile::DisplayPrompt()
{
    char keyPressed, prevChar;
    int x = 100, y = 30, strLength = 0, i =0;
    apvector<char> PromptString(0,0);

    testWindow.flushKeyboardQueue();

    testWindow.drawText(Style::BLACK,gFont,0,y,"Sean $>");

    for(;;)
    {
        keyPressed = testWindow.waitForKeyboardEvent().getValue();

        //Return Key
        if((keyPressed == 13) && (PromptString.length() > 0))
        {
            testWindow.drawRectangleFilled(Style::WHITE,100,350,600,440);
            stringstream ss; ss << PromptString[0];
            testWindow.drawText(Style::BLACK,gFont,5,5+x,ss.str());
            ClearPromptWindow();
            testWindow.drawText(Style::BLACK,gFont,0,0,"Working...");
            return PromptString;
        }

        if(keyPressed != NamedKey::ESCAPE)
        {
            if( keyPressed == NamedKey::RIGHT_ARROW
                    and keyPressed == 4
                    and x > 100 )
            {
                x-=10;
                testWindow.drawRectangleFilled(Style::WHITE,x,y,x+20,y+20);
                testWindow.drawText(Style::BLACK,gFont,x,y,"_");
                PromptString.resize(PromptString.length()-1);
            }

            else
            {
                switch(keyPressed)
                {
                    case ' ':
                        {
                            testWindow.drawRectangleFilled(Style::WHITE,x-2,y+15,x+10,y+30);
                            x+=10;
                            testWindow.drawText(Style::BLACK,gFont,x,y,"_");
                            break;
                        }
                    case 13:
                        break;

                    case 8:
                        if(x > 100)
                        {
                            x-=10;
                            testWindow.drawRectangleFilled(Style::WHITE,x,y,x+20,y+20);
                            testWindow.drawText(Style::BLACK,gFont,x,y,"_");
                            PromptString.resize(PromptString.length()-1);
                        }
                        break;
                    default:
                        {
                            testWindow.drawRectangleFilled(Style::WHITE,x-2,y+15,x+10,y+30);
                            PromptString.resize(PromptString.length()+1);
                            PromptString[PromptString.length()-1] = keyPressed;
                            stringstream ss; ss << keyPressed;
                            testWindow.drawText(Style::BLACK,gFont,x,y,ss.str());
                            x+=10;
                            testWindow.drawText(Style::BLACK,gFont,x,y,"_");
                        }
                }
            }
        }
        else
        {
            testWindow.drawText(Style::BLACK,gFont,5,5,"Click on Window to Quit!");
        }

        prevChar = keyPressed;
    }

    return PromptString;
}



bool Projectile::HandlePrompt ( Window &handleWindow ,
        apvector<char> &handlePrompt,
        Window &myWindow)
{
    apvector<char> right(5);
    char answer;

    if(handlePrompt[0] == 's')
    {
        DrawCities(handleWindow,myWindow);
        DrawCity(handleWindow);
    }
    if(handlePrompt[0] == 'v')
    {
        iVelocity = ArrayToInteger(handlePrompt);
        UpdateVariableState();
        Calculation(handleWindow,myWindow);
    }

    if(handlePrompt[0] == 'h')
    {
        Instructions();
    }

    if(handlePrompt[0] == 'a')
    {
        iAngle = ArrayToInteger(handlePrompt);
        iAngle = DEG2RAD(iAngle);
        UpdateVariableState();
        ClearPromptWindow();
        ClearActionWindow(handleWindow);
        DrawGun(handleWindow);
        DrawCity(handleWindow);
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

        ClearPromptWindow();
    }

    if(handlePrompt[0] == 'y')
    {
        initialHeight = ArrayToInteger(handlePrompt);
        initialHeight = 300 - initialHeight;
        UpdateVariableState();
        ClearPromptWindow();
        ClearActionWindow(handleWindow);
        DrawCity(handleWindow);
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

void Projectile::DrawCities(Window &instWindow, Window &myWindow)
{
    int bad = 0;

    char x;

    ClearActionWindow(instWindow);

    instWindow.drawText(Style::BLACK,gFont,150,50, "(1) Canon City");
    instWindow.drawText(Style::BLACK,gFont,150,70, "(2) Florence");
    instWindow.drawText(Style::BLACK,gFont,150,90, "(3) Pueblo");
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

void Projectile::ClearActionWindow(Window &actionWindow)
{
    actionWindow.drawRectangleFilled(Style::WHITE,0,0,actionWindow.getWidth(),300);
    actionWindow.drawRectangleOutline(Style::BLACK,0,0,actionWindow.getWidth(),300);
}


void Projectile::Instructions()
{
    helpWindow.show();
    helpWindow.drawRectangleFilled(Style(Color::WHITE),0,0,helpWindow.getWidth(),helpWindow.getHeight());
    Style pen = Style(Color::BLACK,2);
    helpWindow.drawText(Style::BLACK,gFont,100,50,"The Commands Are:");
    helpWindow.drawLine(pen,100,70,270,70);
    helpWindow.drawText(Style::BLACK,gFont,100,80,"(s) Select City");
    helpWindow.drawText(Style::BLACK,gFont,100,100,"(v integer) Velocity and Value");
    helpWindow.drawText(Style::BLACK,gFont,100,120,"(a angle) Angle and Angle in Degrees");
    helpWindow.drawText(Style::BLACK,gFont,100,140,"(y integer) Vertical Height of Gun");
    helpWindow.drawText(Style::BLACK,gFont,100,160,"(q) Quit");
    helpWindow.drawText(Style::BLACK,gFont,100,180,"Example: v60 is a velocity of 60 m/s");
    helpWindow.drawText(Style::BLACK,gFont,100,200,"press any key to quit...");
    helpWindow.drawImage(mImageMap.GetImage("CanonCity.jpg"), 50, 50);
    helpWindow.waitForKeyboardEvent();
    helpWindow.hide();
}

int Projectile::ArrayToInteger(apvector<char> &Array)
{
    int Exponent= Array.length()-2,Integer = 0;

    for(int i = 1; i<Array.length(); i++)
    {
        Integer += (Array[i]-48)*(pow(10,Exponent));
        Exponent-=1;
    }
    return Integer;
}

void Projectile::Calculation(Window &actionWindow, Window &myWindow)
{
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
    DrawCity(actionWindow);


    vertVel = -iVelocity*sin(iAngle);
    horzVel = iVelocity*cos(iAngle);

    actionWindow.flushMouseQueue();

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
            UpdateVariableState();
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
    UpdateVariableState();

    if(!destroyed)
    {
        RunningPeople(actionWindow);
    }

    actionWindow.drawText(Style::BLACK,gFont,200,321,"HORIZONTAL DISTANCE = " );
    actionWindow.drawText(Style::BLACK,gFont,440,321, Window::numberToString(x2));

    actionWindow.drawText(Style::BLACK,gFont,200,353,"MAX HEIGHT = " );
    actionWindow.drawText(Style::BLACK,gFont,440,353,Window::numberToString(maxHeight));
}

void Projectile::ClearPromptWindow()
{
    Style pen(Color::WHITE);
    testWindow.drawRectangleFilled(pen,
            0,0,
            testWindow.getWidth(),testWindow.getHeight());
}

void Projectile::UpdateVariableState()
{
    testWindow.drawRectangleFilled(Style::WHITE,0,300,testWindow.getWidth(),testWindow.getHeight());
    testWindow.drawText(Style::BLACK,gFont,0,311,"ANGLE = ");
    {
        std::stringstream ss; ss << ((iAngle * 180)/3.1415926535897932);
        testWindow.drawText(Style::BLACK,gFont,100,311,ss.str());
    }

    testWindow.drawText(Style::BLACK,gFont,0,333,"VELOCITY = ");
    {
        std::stringstream ss; ss << iVelocity;
        testWindow.drawText(Style::BLACK,gFont,100,333,ss.str());
    }
}

bool Projectile::CheckTownLocation(Window &actionWindow,int x2,int y2)
{
    const Image& testImage(mImageMap.GetImage(currentCity));
    const Image& burnImage(mImageMap.GetImage("FireExplosion.jpg"));

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

void Projectile::DrawGun(Window &actionWindow)
{
    double gun_length(30);
    double gunx(cos(iAngle)*gun_length);
    double guny(sin(iAngle)*gun_length);

    Style pen = Style(Color::BLACK,3);
    actionWindow.drawLine(pen,0,initialHeight,gunx,initialHeight-guny );
}

void Projectile::DrawCity(Window &actionWindow)
{
    Transform scale(0.5,0.5);
    int x(320);
    int y(300-(int)mImageMap.GetImage(currentCity).getHeight()*.5);

    actionWindow.drawImage(mImageMap.GetImage(currentCity), x, y,scale);
}


void Projectile::RunningPeople(Window &actionWindow)
{
    const Image& manImage(mImageMap.GetImage("Man1.jpg"));
    const Image& man2Image(mImageMap.GetImage("Man2.jpg"));

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

