// #include "draw_scene.hpp"

// /// Camera parameters
// float angle_theta{45.0}; // Angle between x axis and viewpoint
// float angle_phy{30.0};	 // Angle between z axis and viewpoint
// float dist_zoom{30.0};	 // Distance between origin and viewpoint

// GLBI_Engine myEngine;
// GLBI_Set_Of_Points somePoints(3);
// GLBI_Convex_2D_Shape ground{3};
// GLBI_Texture solTexture;
// GLBI_Texture murTexture;

// void initScene()
// {
// 	std::vector<float> points{0.0, 0.0, 0.0};
// 	somePoints.initSet(points, 1.0, 1.0, 1.0);

// 	std::vector<float> baseCarre{-10.0, -10.0, 0.0,
// 								 10.0, -10.0, 0.0,
// 								 10.0, 10.0, 0.0,
// 								 -10.0, 10.0, 0.0};
// 	ground.initShape(baseCarre);
// 	ground.changeNature(GL_TRIANGLE_FAN);

// 	// === CHARGEMENT DE LA TEXTURE DU SOL ===
// 	int width, height, nbChannels;
// 	unsigned char *imageSol = stbi_load("../assets/images/mur.jpg", &width, &height, &nbChannels, 0);
// 	if (!imageSol)
// 	{
// 		std::cerr << "Erreur : mur.jpg non trouvée\n";
// 		exit(EXIT_FAILURE);
// 	}
// 	solTexture.createTexture();
// 	solTexture.attachTexture();
// 	solTexture.setParameters(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
// 	solTexture.loadImage(nbChannels, width, height, imageSol);
// 	solTexture.detachTexture();
// 	stbi_image_free(imageSol);

// 	// === CHARGEMENT DE LA TEXTURE DU MUR ===
// 	unsigned char *imageMur = stbi_load("../assets/images/sol.jpg", &width, &height, &nbChannels, 0);
// 	if (!imageMur)
// 	{
// 		std::cerr << "Erreur : sol.jpg non trouvée\n";
// 		exit(EXIT_FAILURE);
// 	}
// 	murTexture.createTexture();
// 	murTexture.attachTexture();
// 	murTexture.setParameters(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
// 	murTexture.loadImage(nbChannels, width, height, imageMur);
// 	murTexture.detachTexture();
// 	stbi_image_free(imageMur);
// }

// void drawScene()
// {
// 	glPointSize(10.0);

// 	somePoints.drawSet();

// 	myEngine.activateTexturing(true);
// 	solTexture.attachTexture();
// 	ground.drawShape();
// 	solTexture.detachTexture();
// }
