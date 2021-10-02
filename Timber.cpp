// Include important C++ libraries here
#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <sstream>
#include <SFML/Audio.hpp>


using namespace sf;
//declaramos funciones
void updateBranches(int seed);
const int NUM_BRANCHES = 6;

Sprite branches[NUM_BRANCHES];

//Donde esta el jugador/rama?
// izquierda o derecha
enum class side { LEFT, RIGHT, NONE };
side branchPositions[NUM_BRANCHES];


int main()
{
	//vamo a crear un objeto modo de video o video mode
	VideoMode vm(960, 540);
	// ahora vamos a crear la ventana con ese objeto
	//RenderWindow window(vm, "Timber!!!", Style::Fullscreen);
	RenderWindow window(vm, "Timber!!!");
	View view(sf::FloatRect(0, 0, 1920, 1080));
	window.setView(view);
	// Create a texture to hold a graphic on the GPU
	Texture textureBackground;
	// Load a graphic into the texture
	textureBackground.loadFromFile("graphics/background.png");
	// Create a sprite
	Sprite spriteBackground;
	// Attach the texture to the sprite
	spriteBackground.setTexture(textureBackground);
	// Set the spriteBackground to cover the screen
	spriteBackground.setPosition(0, 0);
	// vamo a crear el arbolito
	Texture textureTree;
	textureTree.loadFromFile("graphics/tree.png");
	Sprite spriteTree;
	spriteTree.setTexture(textureTree);
	spriteTree.setPosition(810,0);

	//agregamo mas arbolitos de fondo
	Texture textureTree2;
	textureTree2.loadFromFile("graphics/tree2.png");
	Sprite spriteTree2;
	spriteTree2.setTexture(textureTree2);
	Sprite spriteTree3;
	spriteTree3.setTexture(textureTree2);
	Sprite spriteTree4;
	spriteTree4.setTexture(textureTree2);
	Sprite spriteTree5;
	spriteTree5.setTexture(textureTree2);
	Sprite spriteTree6;
	spriteTree6.setTexture(textureTree2);

	spriteTree2.setPosition(-20, -100);
	spriteTree3.setPosition(300, -20);
	spriteTree4.setPosition(1300, -75);
	spriteTree5.setPosition(1700, -200);
	spriteTree6.setPosition(1900, -15);

	//vamo a crear una abejita bb
	Texture textureBee;
	textureBee.loadFromFile("graphics/bee.png");
	Sprite spriteBee;
	spriteBee.setTexture(textureBee);
	spriteBee.setPosition(0,800);
	// se ta moviendo la abejita?
	bool beeActive = false;

	//que tan rapido puede volar la abeja en pixeles por segundo
	float beeSpeed = 0.0f;


	//vamo a poner unas nubesitas
	Texture textureCloud;
	textureCloud.loadFromFile("graphics/cloud.png");

	//hacemos las nubes con un arreglo
	const int NUM_CLOUDS = 6;
	Sprite clouds[NUM_CLOUDS];
	int cloudSpeeds[NUM_CLOUDS];
	bool cloudsActive[NUM_CLOUDS];

	for (int i = 0; i < NUM_CLOUDS; i++)
	{
		clouds[i].setTexture(textureCloud);
		clouds[i].setPosition(-300, i * 150);
		cloudsActive[i] = false;
		cloudSpeeds[i] = 0;

	}
	/*
		Sprite spriteCloud1;
		Sprite spriteCloud2;
		Sprite spriteCloud3;
		spriteCloud1.setTexture(textureCloud);
		spriteCloud2.setTexture(textureCloud);
		spriteCloud3.setTexture(textureCloud);
		spriteCloud1.setPosition(0,0);
		spriteCloud2.setPosition(0,250);
		spriteCloud3.setPosition(0,500);
		bool cloud1Active = false;
		bool cloud2Active = false;
		bool cloud3Active = false;
		float cloud1Speed = 0.0f;
		float cloud2Speed = 0.0f;
		float cloud3Speed = 0.0f;
	*/
	// 3 nuevos sprites con la misma textura pai
	
	//la variable de tiempo
	Clock clock;

	//barra de tiempo
	RectangleShape timeBar;
	float timeBarStartWidth = 400;
	float timeBarHeight = 80;
	timeBar.setSize(Vector2f(timeBarStartWidth,timeBarHeight));
	timeBar.setFillColor(Color::Green);
	timeBar.setPosition((1920 / 2) - timeBarStartWidth / 2, 980);

	Time gameTimeTotal;
	float timeRemaining = 6.0f;
	float timeBarWidthPerSecond = timeBarStartWidth / timeRemaining;

	//variable para pausar el juego
	bool paused = true;

	// variable para los puntos
	int score = 0;

	sf::Text messageText;
	sf::Text scoreText;
	sf::Text fpsText;
	sf::Text creditos;
	//elegimos a fuente
	Font font;
	font.loadFromFile("fonts/KOMIKAP_.ttf");

	// le aplicamos la fuente a nuestro mensaje
	messageText.setFont(font);
	scoreText.setFont(font);
	fpsText.setFont(font);
	creditos.setFont(font);

	//le ponemos texto al fps
	fpsText.setFillColor(Color::Red);
	//fpsText.setColor(Color::White);
	fpsText.setCharacterSize(50);
	fpsText.setPosition(1200, 50);

	//asignamos el mensaje actual
	messageText.setString("Presiona Enter para empezar!");
	scoreText.setString("Puntos = 0");


	//le ponemos cuan grande va a ser ese mensaje
	messageText.setCharacterSize(75);
	creditos.setCharacterSize(25);
	scoreText.setCharacterSize(100);

	//le damos color al mensaje
	creditos.setFillColor(Color::Red);
	messageText.setFillColor(Color::Red);
	scoreText.setFillColor(Color::Red);

	//posición del texto
	FloatRect textRect = messageText.getLocalBounds();

	messageText.setOrigin(textRect.left +
		textRect.width / 2.0f,
		textRect.top +
		textRect.height / 2.0f);

	messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);

	scoreText.setPosition(20, 20);

	creditos.setPosition(1450,1025);
	creditos.setString("Programado por Federico Simone");

	// Fondo para el texto
	RectangleShape rect1;
	rect1.setFillColor(sf::Color(0, 0, 0, 150));
	rect1.setSize(Vector2f(600, 105));
	rect1.setPosition(0, 30);

	RectangleShape rect2;
	rect2.setFillColor(sf::Color(0, 0, 0, 150));
	rect2.setSize(Vector2f(1000, 105));
	rect2.setPosition(1150, 30);

	RectangleShape rect3;
	rect3.setFillColor(sf::Color(0, 0, 0, 150));
	rect3.setSize(Vector2f(1000, 105));
	rect3.setPosition(1425, 1000);

	//Preparamos las 6 ramas
	Texture textureBranch;
	textureBranch.loadFromFile("graphics/branch.png");

	// Set the texture for each branch sprite
	for (int i = 0; i < NUM_BRANCHES; i++) {
		branches[i].setTexture(textureBranch);
		branches[i].setPosition(-2000, -2000);

		// Set the sprite's origin to dead centre
		// We can then spin it round without changing its position
		branches[i].setOrigin(220, 20);
	}

	
	
	//preparamos al jugador
	Texture texturePlayer;
	texturePlayer.loadFromFile("graphics/player.png");
	Sprite spritePlayer;
	spritePlayer.setTexture(texturePlayer);
	spritePlayer.setPosition(580,720);

	//El jugador comienza a la izquierda
	side playerSide = side::LEFT;

	//prearamos la tumba pa cuando muera el jugador
	Texture textureRIP;
	textureRIP.loadFromFile("graphics/rip.png");
	Sprite spriteRIP;
	spriteRIP.setTexture(textureRIP);
	spriteRIP.setPosition(600,860);

	//preparamos la hacha
	Texture textureAxe;
	textureAxe.loadFromFile("graphics/axe.png");
	Sprite spriteAxe;
	spriteAxe.setTexture(textureAxe);
	spriteAxe.setPosition(700,830);

	// alineamos la hacha con el arbolito
	const float AXE_POSITION_LEFT = 700;
	const float AXE_POSITION_RIGHT = 1075;

	// preparamos el tronco que sale volando
	Texture textureLog;
	textureLog.loadFromFile("graphics/log.png");
	Sprite spriteLog;
	spriteLog.setTexture(textureLog);
	spriteLog.setPosition(810,720);

	//algunas variables utiles para los troncos
	bool logActive = false;
	float logSpeedX = 1000;
	float logSpeedY = -1500;
	// controlamos la entrada del jugador con una bandera
	bool acceptInput = false;

	//preparamos los sonidos
	//sonido cuando cortas troncos
	SoundBuffer chopBuffer;
	chopBuffer.loadFromFile("sound/chop.wav");
	Sound chop;
	chop.setBuffer(chopBuffer);
	//sonido cuando moris
	SoundBuffer deathBuffer;
	deathBuffer.loadFromFile("sound/death.wav");
	Sound death;
	death.setBuffer(deathBuffer);
	//sonido cuando te quedas sin tiempo
	SoundBuffer ootBuffer;
	ootBuffer.loadFromFile("sound/out_of_time.wav");
	Sound outOfTime;
	outOfTime.setBuffer(ootBuffer);

	// control del dibujo del score
	int lastDrawn = 0;
	// variable para saber si el juego no empezo
	bool comenzo = false;
	bool activoHachazo = false;
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event)) {
				if (event.type == Event::KeyReleased && !paused) {
				//vemos si la tecla se vuelve a apretar
				acceptInput = true;

				//ocultamos el hacha
				spriteAxe.setPosition(-3000,830);
				}
		}
		/*
		****************************************
		Handle the players input
		****************************************
		*/
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}

		// Start the game
		if (Keyboard::isKeyPressed(Keyboard::Return)) {
			paused = false;
			comenzo = true;
			//resetiamo el tiempo y los puntos
			score = 0;
			timeRemaining = 6;

			//hacemos que todos los troncos desaparezcan
			for (int i = 1; i < NUM_BRANCHES;i++) {
				branchPositions[i] = side::NONE;
			}
			// nos aseguramos de ocultar la tumbita
			spriteRIP.setPosition(675,2000);

			//movemos al jugador en la posición inicial
			spritePlayer.setPosition(580,720);

			acceptInput = true;
		}

		// envolvemos los controles del jugador
		// para asegurarnos que aceptamos la entrada
		if (acceptInput) {
			//más codigo a continuación
			//primero vamos a manejar si el usuario esta presionando la tecla derecha
			if (Keyboard::isKeyPressed(Keyboard::Right)) {
				//nos aseguramos que el jugador este en la derecha
				playerSide = side::RIGHT;
				score++;
				activoHachazo = true;
				// añadimos tiempo
				timeRemaining += (2 / score) + .15;
				spriteAxe.setPosition(1225,830+25);
				spriteAxe.setRotation(180.0f);
				spritePlayer.setPosition(1200, 720);

				// actualizamo la ramita
				updateBranches(score);

				//mandamo un tronquito a volar a la izquierda
				spriteLog.setPosition(810, 720);
				logSpeedX = -5000;
				logActive = true;

				acceptInput = false;
				// suena el sonido del chop
				chop.play();
			}

			//manejamos por si toca la tecla izquierda

			if (Keyboard::isKeyPressed(Keyboard::Left)) {
				// nos aseguramos que el jugador este en la izquierda
				playerSide = side::LEFT;
				score++;
				activoHachazo = true;
				//añadimos tiempo
				timeRemaining += (2 / score) + .15;

				spriteAxe.setPosition(AXE_POSITION_LEFT,830);
				spriteAxe.setRotation(0);
				spritePlayer.setPosition(580, 720);

				//actualizamos las ramitas
				updateBranches(score);

				// mandamo un tronquito a volar
				spriteLog.setPosition(810, 720);
				logSpeedX = 5000;
				logActive = true;

				acceptInput = false;
				// suena el sonido del chop
				chop.play();
			}
		}

		/*
		****************************************
		Update the scene
		****************************************
		*/
		if (!paused){
			// medida de tiempo
			Time dt = clock.restart();
			// restar por la cantidad de tiempo disponible
			timeRemaining -= dt.asSeconds();
			// ajustamos el tamaño a la barra de tiempo
			timeBar.setSize(Vector2f(timeBarWidthPerSecond *
				timeRemaining, timeBarHeight));
			if (timeRemaining <= 0.0f) {
				// Pausamos el juego
				paused = true;

				// cambiamos el texto a mostrar en la pausa
				messageText.setString("Se te acabo el tiempo!!");

				//reposicionamos el texto basado en el nuevo tamaño
				FloatRect textRect = messageText.getLocalBounds();
				messageText.setOrigin(textRect.left +
					textRect.width / 2.0f,
					textRect.top +
					textRect.height / 2.0f);
				messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);

				//ponemos sonidito que se quedo sin tiempo
				outOfTime.play();
			}


			// Setup the bee
			if (!beeActive)
			{
				// How fast is the bee
				srand((int)time(0));
				beeSpeed = (rand() % 200) + 200;
				// How high is the bee
				srand((int)time(0) * 10);
				float height = (rand() % 500) + 500;
				spriteBee.setPosition(2000, height);
				beeActive = true;
			}
			else
			{// si ta activa la abejita la movemo
				spriteBee.setPosition(
					spriteBee.getPosition().x -//obtenemo la posición x
					(beeSpeed * dt.asSeconds()),//la velocidad de la abeja * por los segudos entre frame y frame de la computadora
					spriteBee.getPosition().y);
				// Has the bee reached the left hand edge of the screen?
				if (spriteBee.getPosition().x < -100)
				{
					// Set it up ready to be a whole new bee next frame
					beeActive = false;
				}
			}

			// Manage the clouds with arrays
			for (int i = 0; i < NUM_CLOUDS; i++)
			{
				if (!cloudsActive[i])
				{
					// How fast is the cloud
					srand((int)time(0) * i);
					cloudSpeeds[i] = (rand() % 200);

					// How high is the cloud
					srand((int)time(0) * i);
					float height = (rand() % 150);
					clouds[i].setPosition(-200, height);
					cloudsActive[i] = true;

				}
				else
				{
					// Set the new position
					clouds[i].setPosition(
						clouds[i].getPosition().x +
						(cloudSpeeds[i] * dt.asSeconds()),
						clouds[i].getPosition().y);

					// Has the cloud reached the right hand edge of the screen?
					if (clouds[i].getPosition().x > 1920)
					{
						// Set it up ready to be a whole new cloud next frame
						cloudsActive[i] = false;
					}

				}

			}


			/*
			// Manage the clouds
			// Cloud 1
			if (!cloud1Active)
			{
				// How fast is the cloud
				srand((int)time(0) * 10);
				cloud1Speed = (rand() % 200);
				// How high is the cloud
				srand((int)time(0) * 10);
				float height = (rand() % 150);
				spriteCloud1.setPosition(-200, height);
				cloud1Active = true;
			}
			else
			{
				spriteCloud1.setPosition(
					spriteCloud1.getPosition().x +
					(cloud1Speed * dt.asSeconds()),
					spriteCloud1.getPosition().y);
				// Has the cloud reached the right hand edge of the screen?
				if (spriteCloud1.getPosition().x > 1920)
				{
					// Set it up ready to be a whole new cloud next frame
					cloud1Active = false;
				}
			}
			// Cloud 2
			if (!cloud2Active)
			{
				// How fast is the cloud
				srand((int)time(0) * 20);
				cloud2Speed = (rand() % 200);
				// How high is the cloud
				srand((int)time(0) * 20);
				float height = (rand() % 300) - 150;
				spriteCloud2.setPosition(-200, height);
				cloud2Active = true;
			}
			else
			{
				spriteCloud2.setPosition(
					spriteCloud2.getPosition().x +
					(cloud2Speed * dt.asSeconds()),
					spriteCloud2.getPosition().y);
				// Has the cloud reached the right hand edge of the screen?
				if (spriteCloud2.getPosition().x > 1920)
				{
					// Set it up ready to be a whole new cloud next frame
					cloud2Active = false;
				}
			}

			// Cloud 3
			if (!cloud3Active)
			{
				// How fast is the cloud
				srand((int)time(0) * 30);
				cloud3Speed = (rand() % 200);
				// How high is the cloud
				srand((int)time(0) * 30);
				float height = (rand() % 450) - 150;
				spriteCloud3.setPosition(-200, height);
				cloud3Active = true;
			}
			else
			{
				spriteCloud3.setPosition(
					spriteCloud3.getPosition().x +
					(cloud3Speed * dt.asSeconds()),
					spriteCloud3.getPosition().y);
				// Has the cloud reached the right hand edge of the screen?
				if (spriteCloud3.getPosition().x > 1920)
				{
					// Set it up ready to be a whole new cloud next frame
					cloud3Active = false;
				}
			}
			*/
			
			// Draw the score and the frame rate once every 100 frames
			lastDrawn++;
			if (lastDrawn == 100) {
				// Update the score text
				std::stringstream ss;
				ss << "Puntos = " << score;
				scoreText.setString(ss.str());

				// Draw the fps
				std::stringstream ss2;
				ss2 << "FPS = " << 1 / dt.asSeconds();
				fpsText.setString(ss2.str());
				lastDrawn = 0;
			}

			/*
				// actualizar el score text
				std::stringstream ss;
				ss << "Puntos = " << score;
				scoreText.setString(ss.str());

			*/
			
			
			// actualizamos los sprites de las ramas
			for (int i = 0; i < NUM_BRANCHES; i++) {
				float height = i * 150;
				if (branchPositions[i] == side::LEFT){
					//Movemos el sprite de la rama a la izquierda
					branches[i].setPosition(610,height);

					// damo vuelta el sprite pal otro lado
					branches[i].setRotation(180);
				}
				else if (branchPositions[i]== side::RIGHT) {
					//movemos el sprite de la rama a la derecha
					branches[i].setPosition(1330, height);
					// dejamo la rotación en normal porque por defecto el sprite ta pa la derecha
					branches[i].setRotation(0);
				}
				else
				{
					//ocultamos las ramitas si no tan ni izquierda ni derecha
					branches[i].setPosition(3000, height);
				}
			}
			
			// vamo a poner a los tronquitos a volar
			if (logActive) {
				spriteLog.setPosition(
					spriteLog.getPosition().x +
					(logSpeedX * dt.asSeconds()),
					spriteLog.getPosition().y +
					(logSpeedY * dt.asSeconds()));

				// el tronquito llego al limite de la pantalla?
				if (spriteLog.getPosition().x < -100 ||
					spriteLog.getPosition().x > 2000) {
					// lo ponemos en listo para mostrar otro tronquito volando
					logActive = false;
					spriteLog.setPosition(810, 720);
				}
			}

			// el jugador se choco una rama?
			if (branchPositions[5]==playerSide) {
				//muerte
				paused = true;
				acceptInput = false;

				// vamo a dibujar la tumbita pa
				if (playerSide==side::RIGHT) {
					spriteRIP.setPosition(1200, 760);
				}
				else {
					spriteRIP.setPosition(525, 760);
				}

				//hide the player
				spritePlayer.setPosition(2000, 660);
				//hide the axe
				//ocultamos el hacha
				spriteAxe.setPosition(-3000, 830);

				//cambiamos el texto del mensaje
				messageText.setString("TE MORISTE!!");

				//lo centramos al medio de la pantalla
				FloatRect textRect = messageText.getLocalBounds();

				messageText.setOrigin(textRect.left+
				textRect.width / 2.0f,
					textRect.top + textRect.height / 2.0f);
				
				messageText.setPosition(1920/ 2.0f, 1080 / 2.0f);

				//ponemos sonidito que se comio una rama
				death.play();
			}

		}// end if(!paused)

		


		/*
		****************************************
		Draw the scene
		****************************************
		*/
		// Clear everything from the last frame
		window.clear();

		// Draw our game scene here
		window.draw(spriteBackground);

		/*
			// dibujamo las nubesita
			window.draw(spriteCloud1);
			window.draw(spriteCloud2);
			window.draw(spriteCloud3);
		*/
		for (int i = 0; i < NUM_CLOUDS; i++)
		{
			window.draw(clouds[i]);
		}

		// Dibujamos los arbolitos de fondo
		window.draw(spriteTree2);
		window.draw(spriteTree3);
		window.draw(spriteTree4);
		window.draw(spriteTree5);
		window.draw(spriteTree6);
		
		// dibujamo la ramita
		for (int i = 0; i < NUM_BRANCHES; i++) {
			window.draw(branches[i]);
		}
		
		
		// dibujamo el arbolito
		window.draw(spriteTree);

		//dibujamo al chaboncito
		window.draw(spritePlayer);

		//dibujamo la hachita del chabonsito
		if (activoHachazo) {
			window.draw(spriteAxe);
		}
		// dibujamo el tronquito volando
		window.draw(spriteLog);

		// dibujamo la tumbita
		if (comenzo) {
			window.draw(spriteRIP);
		}
		

		//dibujamo lo fonditos de los textitos
		window.draw(rect1);
		if (comenzo) {
			window.draw(rect2);
		}
		// dibujamo la abejita
		if (comenzo) {
			window.draw(spriteBee);
		}
		

		// dibujamo lo punto
		window.draw(scoreText);

		// dibujamo lo fps
		window.draw(fpsText);

		// dibujamo la barrita
		if (comenzo) {
			window.draw(timeBar);
		}

		if (paused){
			//dibujamo el mensaje
			window.draw(messageText);
		}
		if (!comenzo){
			window.draw(rect3);
			window.draw(creditos);
		}
		// Show everything we just drew
		window.display();
	}
	return 0;
}


void updateBranches(int seed)
{
	//movemos todas las ramas un lugar pa abajo
	for (int j = NUM_BRANCHES - 1; j > 0; j--) {
		branchPositions[j] = branchPositions[j - 1];
	}

	// hacemos spawn una nueva rama en la posición 0
	// izquierda, derecha o ninguna
	srand((int)time(0) + seed);
	int r = (rand() % 5);
	switch (r) {
	case 0:
		branchPositions[0] = side::LEFT;
		break;

	case 1:
		branchPositions[0] = side::RIGHT;
		break;
	default:
		branchPositions[0] = side::NONE;
		break;
	}
}

