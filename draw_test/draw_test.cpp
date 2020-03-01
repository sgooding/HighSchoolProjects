#include <iostream>
#include <CarnegieMellonGraphics.h>
#include <GL/glut.h>


int main(int argn, char* argv[])
{
    //glutInit(&argn, argv);
    Window main(10,10,600,440,"draw_test");


    //std::cout << "any key to quit." << std::endl;
    main.waitForKeyboardEvent();
    //main.show();
    //// draw icon
    Image icon("scs.jpg",Image::JPEG);
    main.drawImage(icon,icon.getWidth(), 0);

    //// draw line
    Style pen(Color::BLACK, 5);
    main.drawLine(pen, 10, 10, 100, 100 );

    std::cout << "any key to quit." << std::endl;
    main.waitForKeyboardEvent();

    return 0;
}
