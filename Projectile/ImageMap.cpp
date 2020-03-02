
#include <ImageMap.h>

#include <CarnegieMellonGraphics.h>

void ImageMap::LoadImages()
{
    const std::vector<std::string> images = { 
        "ColoradoSprings.jpg", 
		"GunBase1.jpg",
		"CanonCity.jpg",
		"FireExplosion.jpg",
		"Man1.jpg",
		"Man2.jpg",
		"Florence.jpg",
		"Pueblo.jpg"};
    for(auto n: images)
        mImages[n] = Image(n,Image::JPEG);
}

const Image& ImageMap::GetImage(const std::string& name)
{
    return mImages[name];
}
