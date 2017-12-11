/* Class for storing information about for example the dimensions of the world. Contains also coefficients for transoforming between meters and pixels. */

#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include <iostream>

class Settings {
    public:
        Settings(const size_t sw, const size_t sh, const float ww, const float wh) :
           screenWidth(sw), screenHeight(sh), worldWidth(ww), worldHeight(wh),
           metersToPixels(sw/ww), pixelsToMeters(ww/sw), tileWidth(sw/ww), tileHeight(sh/wh) { }
        const size_t screenWidth;
        const size_t screenHeight;
        const float worldWidth;
        const float worldHeight;
        const float metersToPixels;
        const float pixelsToMeters;
        const float tileWidth;
        const float tileHeight;
};

#endif
