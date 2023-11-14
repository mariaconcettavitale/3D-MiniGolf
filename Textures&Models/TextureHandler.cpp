#include "TextureHandler.h"

#define STB_IMAGE_IMPLEMENTATION
#include <../stb/stb_image.h>
// Method that set the number of textures.
/*void TextureHandler::setTextures(int numTextures)
{
    
    this->numTextures = numTextures;


    GLuint* temp_texture_ids = new GLuint[this->numTextures];
    glGenTextures(this->numTextures, temp_texture_ids);

    this->texture_ids = temp_texture_ids;

}

*/
int TextureHandler::getTextureId()
{
    return this->texture_id;
}

void TextureHandler::setPath(string path)
{
    this->path = path;
}

//Method that load the textures 
void TextureHandler::loadTextures(bool skybox)
{
        TextureHandler texture;

        this->texture_ids = new GLuint[this->numTextures];
        glGenTextures(this->numTextures, texture_ids);
    
        
        texture.texture_id = texture_ids[0];
        stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
        texture.path = this->path;

        // Load the image using stb_image library.
        int width, height, numChannels;
        texture.textureData = stbi_load(texture.path.c_str(), &width, &height, &numChannels, 0);
        texture.width = width;
        texture.height = height;
        texture.numChannels = numChannels;
      
        if (texture.numChannels == 3)
            texture.type = GL_RGB;
        if (texture.numChannels == 4)
            texture.type = GL_RGBA;

        if (texture.textureData)
        {
            glBindTexture(GL_TEXTURE_2D, texture.texture_id);
            glTexImage2D(GL_TEXTURE_2D, 0, texture.type, texture.width, texture.height, 0, texture.type, GL_UNSIGNED_BYTE, texture.textureData);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            if (skybox)
            {
                glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
                glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
                //3d coordinate like z position
                glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
            }
            glBindTexture(GL_TEXTURE_2D, 0);

        }

        stbi_image_free(texture.textureData);
        textures.push_back(texture);
     


}
void TextureHandler::loadAnimation()
{

    for (int i = 0; i < 133; i++)
    {
       
        this->path = "../MiniGolf3D/textures/AnimationFrames/texture_(" + to_string(i + 1) + ").png";
        loadTextures(false);

    }
}

//method that loads the texture of the skybox
void TextureHandler::loadSkyBox()
{
   
    for (int i = 0; i < 6; i++)
    {

        this->path = "../MiniGolf3D/textures/SkyBox/box_(" + std::to_string(i + 1) + ").png";

        loadTextures(true);
    }
       /* TextureHandler texture;

        texture.texture_id = texture_ids[i];
        texture.path = std::string(this->path) + "box_(" + std::to_string(i + 1) + ").png";
        stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.

        // Load the texture using your preferred image loading stbi library 
        int width, height, numChannels;
        texture.textureData = stbi_load(texture.path.c_str(), &width, &height, &numChannels, 0);
        if (!texture.textureData) {
            printf("Error loading texture: %s\n", texture.path.c_str());
            exit(1);
        }

        texture.width = width;
        texture.height = height;
        texture.numChannels = numChannels;
     

        if (texture.numChannels == 3)
            texture.type = GL_RGB;
        if (texture.numChannels == 4)
            texture.type = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, texture.texture_id);
        glTexImage2D(GL_TEXTURE_2D, 0, texture.type, texture.width, texture.height, 0, texture.type, GL_UNSIGNED_BYTE, texture.textureData);

        // Set texture parameters (you may need to adjust these as needed).
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
 
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        //3d coordinate like z position
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

        stbi_image_free(texture.textureData);
        this->textures.push_back(texture);
    }*/

}