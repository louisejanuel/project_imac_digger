#define STB_IMAGE_IMPLEMENTATION
#include "texture.hpp"
#include "stb_image_implementation.hpp"
#include "utils.hpp"

Texture::Texture() {}

Texture::~Texture() {
    if (texID) glDeleteTextures(1, &texID);
}

bool Texture::loadFromFile(const std::string& path, bool flip) {
    if (texID) glDeleteTextures(1, &texID);

    stbi_set_flip_vertically_on_load(flip);
    int w, h, c;
    unsigned char* data = stbi_load(path.c_str(), &w, &h, &c, 0);
    if (!data) {
        std::cerr << "[Texture] Erreur chargement : " << path << " (" << stbi_failure_reason() << ")\n";
        texID = 0;
        return false;
    }
    glGenTextures(1, &texID);
    glBindTexture(GL_TEXTURE_2D, texID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    GLenum format = (c == 4) ? GL_RGBA : GL_RGB;
    glTexImage2D(GL_TEXTURE_2D, 0, format, w, h, 0, format, GL_UNSIGNED_BYTE, data);
    glBindTexture(GL_TEXTURE_2D, 0);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    stbi_image_free(data);
    return true;
}

void Texture::attachTexture() const {
    glBindTexture(GL_TEXTURE_2D, texID);
    glEnable(GL_TEXTURE_2D);
}

void Texture::detachTexture() const {
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);
}