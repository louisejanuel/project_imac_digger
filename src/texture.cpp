#include "stb_image_implementation.hpp"
#include "texture.hpp"

// Initialisation des buffers et VAO du perso
void initTexturePerso(){
    carre.setNbElt(4);
    // Attrib location 0 pour position, 2 floats
    carre.addOneBuffer(0, 2, coordCoins, "position", true);
    // Attrib location 2 pour UV, 2 floats
    carre.addOneBuffer(2, 2, uvs, "uvs", true);
    carre.createVAO();
	carre.changeType(GL_TRIANGLE_FAN);

    loadTexturePerso(texturePerso);
}

// Initialisation des buffers et VAO des blocs 
void initTextureBackground(){
    tileShape.setNbElt(4);
    // Attrib location 0 pour position, 2 floats
    tileShape.addOneBuffer(0, 2, tileCoords, "position", true);
    // Attrib location 2 pour UV, 2 floats
    tileShape.addOneBuffer(2, 2, uvs, "uvs", true);
    tileShape.createVAO();
	tileShape.changeType(GL_TRIANGLE_FAN);

    loadTextureFond(textureFond);
    loadTextureObjet(textureObjet);
    loadTexturePiege(texturePiege);
}


// Fonction générique de chargement de texture à partir d'un fichier
void loadTexture(const char* filename, GLBI_Texture& texture){
	int width{};
	int height{};
	int nbChan{3};
	stbi_set_flip_vertically_on_load(true);
	unsigned char *data = stbi_load(filename, &width, &height, &nbChan, 0);
    if(data){
		
		myEngine.activateTexturing(true);
        texture.createTexture();
		texture.attachTexture();
		texture.setParameters(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		texture.loadImage(width, height, nbChan, data);
		stbi_image_free(data);
        texture.detachTexture();
		
    }
	else{
		std::cout<<"image non chargée !!!"<< std::endl;
	}
}


void loadTexturePerso(GLBI_Texture& texture){
    loadTexture("../assets/images/souris.png", texture);
}

void loadTextureFond(GLBI_Texture& texture){
    loadTexture("../assets/images/sol.jpg", texture);
}

void loadTextureObjet(GLBI_Texture& texture){
    loadTexture("../assets/images/fromage.png", texture);
}

void loadTexturePiege(GLBI_Texture& texture){
    loadTexture("../assets/images/trou.png", texture);
}