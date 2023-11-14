#pragma once
#ifndef __TextureHandler_h
#define __TextureHandler_h

/**
 * @class TextureHandler
 * @brief Manages texture handling and loading.
 *
 * This class is responsible for managing textures. It includes properties
 * for texture IDs, data, dimensions, channels, and other texture-related information. The class
 * provides methods for setting up textures, loading textures, and also handling skybox textures.
 *
 */

#include "../Libraries.h"

class TextureHandler
{
private:
    GLuint texture_id;
    unsigned char* textureData;
    string path;
    int width;
    int height;
    int numChannels;
    int numTextures;
    GLint type;
    GLuint* texture_ids;

public:
 
    TextureHandler() { numTextures = 1; };

    ~TextureHandler() { textures.clear(); };
    vector<TextureHandler> textures;
    int getTextureId();
   // void setTextures(int);
    void setPath(string);
    void loadTextures(bool);
    void loadAnimation();
    void loadSkyBox();
};
#endif
