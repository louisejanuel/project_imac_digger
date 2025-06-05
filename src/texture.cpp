// #include "stb_image_implementation.hpp"
// #include "texture.hpp"


// Charge une image et crée une texture OpenGL
// GLuint chargerTexture(const char* filename) {
//     int width, height, channels;
//     unsigned char* data = stbi_load(filename, &width, &height, &channels, 4);
//     if (!data) {
//         std::cerr << "Erreur chargement image : " << filename << std::endl;
//         return 0;
//     }
//     GLuint texture;
//     glGenTextures(1, &texture);
//     glBindTexture(GL_TEXTURE_2D, texture);
//     glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//     stbi_image_free(data);
//     return texture;
// }

// void drawCaseTexture(float xpos, float ypos, float cellWidth, float cellHeight, GLuint texture) {
//     glEnable(GL_TEXTURE_2D);
//     glBindTexture(GL_TEXTURE_2D, texture);
//     glColor3f(1,1,1); // pour ne pas teinter la texture
//     glBegin(GL_QUADS);
//     glTexCoord2f(0,0); glVertex2f(xpos, ypos);
//     glTexCoord2f(1,0); glVertex2f(xpos + cellWidth, ypos);
//     glTexCoord2f(1,1); glVertex2f(xpos + cellWidth, ypos + cellHeight);
//     glTexCoord2f(0,1); glVertex2f(xpos, ypos + cellHeight);
//     glEnd();
//     glDisable(GL_TEXTURE_2D);
// }

// void drawCarte(const GLBI_Map& map, GLuint tex_mur, GLuint tex_vide, GLuint tex_gemme, GLuint tex_ennemi, GLuint tex_piege) {
//     auto& carte = map.grid;
//     int largeur = map.width;
//     int hauteur = map.height;
    

//     float cellWidth = 2.0f / largeur;
//     float cellHeight = 2.0f / hauteur;

//     for (int y = 0; y < hauteur; ++y) {
//         for (int x = 0; x < largeur; ++x) {
//             int val = carte[y][x];

//             float xpos = -1.0f + x * cellWidth;
//             float ypos = -1.0f + y * cellHeight;

//             // Cases vides (blanc) ou murs (noir)
//             // if (val == 1) glColor3f(0.0f, 0.0f, 0.0f); // mur noir
//             // else glColor3f(1.0f, 1.0f, 1.0f); // vide blanc

//             // glBegin(GL_QUADS);
//             // glVertex2f(xpos, ypos);
//             // glVertex2f(xpos + cellWidth, ypos);
//             // glVertex2f(xpos + cellWidth, ypos + cellHeight);
//             // glVertex2f(xpos, ypos + cellHeight);
//             // glEnd();

//             // // piège (petit carré bleu)
//             // if (val == 2) {
//             //     glColor3f(0.0f, 0.0f, 1.0f);
//             //     float margin = 0.2f;
//             //     glBegin(GL_QUADS);
//             //     glVertex2f(xpos + cellWidth * margin, ypos + cellHeight * margin);
//             //     glVertex2f(xpos + cellWidth * (1 - margin), ypos + cellHeight * margin);
//             //     glVertex2f(xpos + cellWidth * (1 - margin), ypos + cellHeight * (1 - margin));
//             //     glVertex2f(xpos + cellWidth * margin, ypos + cellHeight * (1 - margin));
//             //     glEnd();
//             // }

//             // // Ennemi (petit carré rouge)
//             // if (val == 4) {
//             //     glColor3f(1.0f, 0.0f, 0.0f);
//             //     float margin = 0.2f;
//             //     glBegin(GL_QUADS);
//             //     glVertex2f(xpos + cellWidth * margin, ypos + cellHeight * margin);
//             //     glVertex2f(xpos + cellWidth * (1 - margin), ypos + cellHeight * margin);
//             //     glVertex2f(xpos + cellWidth * (1 - margin), ypos + cellHeight * (1 - margin));
//             //     glVertex2f(xpos + cellWidth * margin, ypos + cellHeight * (1 - margin));
//             //     glEnd();
//             // }
//             // if (val == 3) { // Gemme (petit carré jaune)
//             //     glColor3f(1.0f, 1.0f, 0.0f);
//             //     float margin = 0.2f;
//             //     glBegin(GL_QUADS);
//             //     glVertex2f(xpos + cellWidth * margin, ypos + cellHeight * margin);
//             //     glVertex2f(xpos + cellWidth * (1 - margin), ypos + cellHeight * margin);
//             //     glVertex2f(xpos + cellWidth * (1 - margin), ypos + cellHeight * (1 - margin));
//             //     glVertex2f(xpos + cellWidth * margin, ypos + cellHeight * (1 - margin));
//             //     glEnd();
//             // }
//             if (val == 3) drawCaseTexture(xpos, ypos, cellWidth, cellHeight, tex_mur);//mur
//             else if (val == 4) { //piege
//                 float margin = 0.2;
//                 drawCaseTexture(xpos + cellWidth * margin,
//                     ypos + cellHeight * margin,
//                     cellWidth * (1 - 2 * margin),
//                     cellHeight * (1 - 2 * margin),
//                     tex_piege);
//             }
//             else if (val == 2) { //objet
//                 float margin = 0.2;
//                 drawCaseTexture(xpos + cellWidth * margin,
//                     ypos + cellHeight * margin,
//                     cellWidth * (1 - 2 * margin),
//                     cellHeight * (1 - 2 * margin),
//                     tex_gemme);
//             }
//             // else if (val == 4) { //ennemi
//             //     float margin = 0.2;
//             //     drawCaseTexture(xpos + cellWidth * margin,
//             //         ypos + cellHeight * margin,
//             //         cellWidth * (1 - 2 * margin),
//             //         cellHeight * (1 - 2 * margin),
//             //         tex_ennemi);
//             // }
//             else drawCaseTexture(xpos, ypos, cellWidth, cellHeight, tex_vide);//vide
//         }
//     }
// }


// // Initialisation des buffers et VAO du perso
// void initTexturePerso(){
//     carre.setNbElt(4);
//     // Attrib location 0 pour position, 2 floats
//     carre.addOneBuffer(0, 2, coordCoins, "position", true);
//     // Attrib location 2 pour UV, 2 floats
//     carre.addOneBuffer(2, 2, uvs, "uvs", true);
//     carre.createVAO();
// 	carre.changeType(GL_TRIANGLE_FAN);

//     loadTexturePerso(texturePerso);
// }

// // Initialisation des buffers et VAO des blocs 
// void initTextureBackground(){
//     tileShape.setNbElt(4);
//     // Attrib location 0 pour position, 2 floats
//     tileShape.addOneBuffer(0, 2, tileCoords, "position", true);
//     // Attrib location 2 pour UV, 2 floats
//     tileShape.addOneBuffer(2, 2, uvs, "uvs", true);
//     tileShape.createVAO();
// 	tileShape.changeType(GL_TRIANGLE_FAN);

//     loadTextureFond(textureFond);
//     loadTextureObjet(textureObjet);
//     loadTexturePiege(texturePiege);
// }


// Fonction générique de chargement de texture à partir d'un fichier
// void loadTexture(const char* filename, GLBI_Texture& texture){
// 	int width{};
// 	int height{};
// 	int nbChan{3};
// 	stbi_set_flip_vertically_on_load(true);
// 	unsigned char *data = stbi_load(filename, &width, &height, &nbChan, 0);
//     if(data){
		
// 		myEngine.activateTexturing(true);
//         texture.createTexture();
// 		texture.attachTexture();
// 		texture.setParameters(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
// 		texture.loadImage(width, height, nbChan, data);
// 		stbi_image_free(data);
//         texture.detachTexture();
		
//     }
// 	else{
// 		std::cout<<"image non chargée !!!"<< std::endl;
// 	}
// }


// void loadTexturePerso(GLBI_Texture& texture){
//     loadTexture("../assets/images/souris.png", texture);
// }

// void loadTextureFond(GLBI_Texture& texture){
//     loadTexture("../assets/images/sol.jpg", texture);
// }

// void loadTextureObjet(GLBI_Texture& texture){
//     loadTexture("../assets/images/fromage.png", texture);
// }

// void loadTexturePiege(GLBI_Texture& texture){
//     loadTexture("../assets/images/trou.png", texture);
// }