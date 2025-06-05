#pragma once
#include <glad/glad.h>
#include <string>

struct Texture
{
    Texture();
    ~Texture();

    bool loadFromFile(const std::string &path, bool flip = true);
    void attachTexture() const;
    void detachTexture() const;
    GLuint getID() const { return texID; }
    GLuint texID = 0;
};