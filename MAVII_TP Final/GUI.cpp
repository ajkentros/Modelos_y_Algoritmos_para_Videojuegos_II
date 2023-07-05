#include <SFML/Audio.hpp>
#include "GUI.h"
#include "Game.h"


using namespace sf;
using namespace std;

GUI::GUI(RenderWindow* _ventana, int _alto_ventana1, int _ancho_ventana1)
{
	/*
		Instancia una ventana con parámetros que recibe de la clase Game (gestionador del juego)
		define alto, ancho y la ventana

	*/
	ventanaGUI = new RenderWindow;
	ventanaGUI = _ventana;
	alto_ventana1 = _alto_ventana1;
	ancho_ventana1 = _ancho_ventana1;
	
	//Llama a las funciones que: inicia la escena, inicia los textos, inicia los sonidos, a utilizar en cada escena
	InitGUIScenes();
	InitGUIText();
	IniciaSonidos();
}


GUI::~GUI()
{
	delete musica;
	delete musica_exit;
	delete buff_ganaGame;
	delete sound_ganaGame;
	delete buff_golpeRagdoll;
	delete sound_golpeRagdoll;
}

void GUI::InitGUIScenes()
{
	/*
		Inicializa la textura y sprite de las distintas escenas
		cada escena tiene un fondo distito que depende del gameState (estado del juego)
		Posiciona los sprite de cada escena
	*/
	for (int i = 0; i < 5; i++) {
		txt_scene[i] = new Texture;
		spr_scene[i] = new Sprite;

		if (!txt_scene[i]->loadFromFile("assets/scene" + to_string(i) + ".jpg"))
		{
			cout << "no carga la textura de la escena";
		}
		spr_scene[i]->setTexture(*txt_scene[i]);
		spr_scene[i]->setScale(0.015f, 0.020f);
		spr_scene[i]->setPosition(46.f, 90.f);
	}
}

void GUI::InitGUIText()
{
	/*
		Inicializa las fuentes a utilizar en cada escena, dependiendo del gameState
	*/
	font = new Font;

	if (!font->loadFromFile("assets/Nice_Sugar.ttf"))
	{
		cout << "no carga la fuente";
	}

	//Texto nombre del juego
	tex_Titulo = new Text;
	tex_Titulo->setFont(*font);
	tex_Titulo->setScale(0.015f, 0.020f);
	tex_Titulo->setCharacterSize(60);
	tex_Titulo->setPosition(Vector2f(48.f, 92.f));
	
	//Texto Play
	menu[0] = new Text;
	menu[0]->setFont(*font);
	menu[0]->setScale(0.015f, 0.020f);
	menu[0]->setCharacterSize(30);
	menu[0]->setPosition(Vector2f(50.f, 95.f));
	menu[0]->setFillColor(Color::Red);
	
	//Texto Exit
	menu[1] = new Text;
	menu[1]->setFont(*font);
	menu[1]->setScale(0.015f, 0.020f);
	menu[1]->setCharacterSize(30);
	menu[1]->setPosition(Vector2f(50.f, 97.f));
	menu[1]->setFillColor(Color::Black);
	
	//Texto cantidad de ragdoll en escena
	tex_cantidad_Ragdoll = new Text;
	tex_cantidad_Ragdoll->setFont(*font);
	tex_cantidad_Ragdoll->setScale(0.015f, 0.020f);
	tex_cantidad_Ragdoll->setCharacterSize(30);
	tex_cantidad_Ragdoll->setPosition(46.5f, 90.2f);
	tex_cantidad_Ragdoll->setFillColor(Color::Black);

	//Texto NIvel del Juego
	tex_Nivel = new Text;
	tex_Nivel->setFont(*font);
	tex_Nivel->setScale(0.015f, 0.020f);
	tex_Nivel->setPosition(56.f, 90.2f);
	tex_Nivel->setCharacterSize(30);
	tex_Nivel->setFillColor(Color::Red);

	//Texto de mensajes
	tex_mensaje = new Text;
	tex_mensaje->setFont(*font);
	tex_mensaje->setScale(0.015f, 0.020f);
	tex_mensaje->setPosition(50.5f, 98.f);
	tex_mensaje->setCharacterSize(30);

	//Texto Exit del Juego
	tex_Exit = new Text;
	tex_Exit->setFont(*font);
	tex_Exit->setScale(0.015f, 0.020f);
	tex_Exit->setPosition(50.f, 96.f);
}

void GUI::IniciaSonidos()
{
	//Instancia y carga la música del juego
	musica = new Music();
	if (!musica->openFromFile("assets/RagdollParanoid.ogg"))
	{
		cout << "no carga la música";
	}

	//Instancia y carga la música cuando se abandona el juego
	musica_exit = new Music();
	if (!musica_exit->openFromFile("assets/exit.ogg"))
	{
		cout << "no carga la música";
	}

	//Instancia el sonido gana el juego
	buff_ganaGame = new SoundBuffer();
	if (!buff_ganaGame->loadFromFile("assets/ganasteJuego.ogg"))
	{
		cout << "no carga buffer gana";
	}
	sound_ganaGame = new Sound;
	sound_ganaGame->setBuffer(*buff_ganaGame);

	//Instancia el sonido ragdoll disparado
	buff_golpeRagdoll = new SoundBuffer();
	if (!buff_golpeRagdoll->loadFromFile("assets/golpe.ogg"))
	{
		cout << "no carga buffer pierde";
	}
	sound_golpeRagdoll = new Sound;
	sound_golpeRagdoll->setBuffer(*buff_golpeRagdoll);

}

void GUI::ActivaMusica()
{
	//play música del juego
	musica->stop();
	musica->play();
	musica->setVolume(10.f);
	musica->getLoop();
}

void GUI::ActivaGolpeRagdoll()
{
	//play sonido de disparo del ragdoll
	sound_golpeRagdoll->play();
}

void GUI::ActivaExitJuego()
{
	//play sonido exit del juego
	musica->stop();
	musica_exit->play();
	musica_exit->setVolume(10.f);
	musica_exit->getLoop();
}

void GUI::ActivaGanaGame()
{
	//play sonido gana el juego (completa todos los niveles)
	musica->stop();
	sound_ganaGame->play();
}

void GUI::DrawGUI(RenderWindow* _ventana, int _gameState, int _gameLevel, int _cantidad_Ragdoll)
{
	//Dibuja menú principal si gameState = 0
	if(_gameState == 0)
	{
		tex_Titulo->setFillColor(Color::Blue);
		tex_Titulo->setString("murderers rags");
		menu[0]->setString("Play");
		menu[1]->setString("Exit");

		_ventana->draw(*spr_scene[0]);
		_ventana->draw(*tex_Titulo);
		
		for (int i = 0; i < ITEMS; i++)
		{
			_ventana->draw(*menu[i]);
		}
	}

	//Dibuja menú Exit si gameState = 2
	if (_gameState == 2)
	{
		tex_Titulo->setFillColor(Color::Blue);
		tex_Titulo->setString("murderers rags");
		tex_Exit->setFillColor(Color::Black);
		tex_Exit->setString("Adios - Nos vemos pronto");

		_ventana->draw(*spr_scene[0]);
		_ventana->draw(*tex_Titulo);
		_ventana->draw(*tex_Exit);
	}

	//Dibuja menú gana Nivel si gameState = 3
	if (_gameState == 3)
	{
		tex_Titulo->setFillColor(Color::White);
		tex_Titulo->setString("Ganaste el nivel: " + to_string(_gameLevel - 1));
		menu[0]->setString("Continuar en el siguiente nivel");
		menu[1]->setString("Reiniciar el juego");

		_ventana->draw(*spr_scene[4]);
		_ventana->draw(*tex_Titulo);
		for (int i = 0; i < ITEMS; i++)
		{
			_ventana->draw(*menu[i]);
		}
	}

	//Dibuja menú perdiste Nivel si gameState = 4
	if (_gameState == 4)
	{
		tex_Titulo->setFillColor(Color::White);
		tex_Titulo->setString("Perdiste el nivel: " + to_string(_gameLevel));
		menu[0]->setString("Continuar en el mismo nivel");
		menu[1]->setString("Reiniciar el juego");

		_ventana->draw(*spr_scene[4]);
		_ventana->draw(*tex_Titulo);
		for (int i = 0; i < ITEMS; i++)
		{
			_ventana->draw(*menu[i]);
		}
	}
	
	//Dibuja menú ganaste el juego si gameState = 5
	if (_gameState == 5)
	{
		tex_Titulo->setFillColor(Color::Blue);
		tex_Titulo->setString("murderers rags");
		tex_mensaje->setFillColor(Color::Red);
		tex_mensaje->setString("----GANASTE EL JUEGO----");

		_ventana->draw(*spr_scene[0]);
		_ventana->draw(*tex_Titulo);
		_ventana->draw(*tex_mensaje);
	}

	//Dibuja el nivel del juego, imprime en pantalla la cantidad de ragdoll que quedan por disparar y el número de nivel
	if (_gameState == 1 && _gameLevel <= 3)
	{

		_ventana->draw(*spr_scene[_gameLevel]);

		//actualiza texto: cantidad de Ragdoll y Nivel
		tex_cantidad_Ragdoll->setString("Ragdolls Restantes: " + to_string(5 - _cantidad_Ragdoll));
		tex_Nivel->setString("Nivel: " + to_string(_gameLevel));

		//dibuja texto: cantidad de Ragdoll y Nivel
		_ventana->draw(*tex_cantidad_Ragdoll);
		_ventana->draw(*tex_Nivel);
	}
}

void GUI::MoveUpMenu()
{
	//Controla el cambio de color del texto del menú según la selección que se haga
	menu[0]->setFillColor(Color::Red);
	menu[1]->setFillColor(Color::Black);
}

void GUI::MoveDownMenu()
{
	//Controla el cambio de color del texto del menú según la selección que se haga
	menu[0]->setFillColor(Color::Black);
	menu[1]->setFillColor(Color::Red);
}