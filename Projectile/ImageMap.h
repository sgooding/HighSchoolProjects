#ifndef _ImageMap_H
#define _ImageMap_H

#include <map>
#include <string>

#include <CarnegieMellonGraphics.h>

class ImageMap
{
    public:

        void LoadImages();

        const Image& GetImage(const std::string& name);

    private:
        std::map<std::string,Image> mImages;
};

#endif
