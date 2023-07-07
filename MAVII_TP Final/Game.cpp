#include <iostream>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include "Game.h"


using namespace sf;
using namespace std;

Game::Game(int _ancho_ventana, int _alto_ventana, string _titulo_ventana)
{

	/*
		inicia variables de ancho y alto de la ventana
		inicia fps = 60 segundos por cada frame
		inicia frameTime = 0.0166
	*/
	ancho_ventana = _ancho_ventana;
	alto_ventana = _alto_ventana;

	fps = 60;
	frameTime = 1.0f / fps;

	/*inicia ventana1
		establece alto, ancho y t�tulo
		visible = true
		limita el FrameLimit = fps
	*/
	ventana = new RenderWindow(VideoMode(ancho_ventana, alto_ventana), _titulo_ventana);
	ventana->setFramerateLimit(fps);
	ventana->setVisible(true);

	/*
		InitVariables: inicia variables del juego e instancia objetos
		InitGame = inicia sonidos: InitSound(); f�sicas: InitPhysics(); loop del juego:	GameLoop();
	*/
	InitVariables();

	InitGame();
}

Game::~Game()
{
}

void Game::InitVariables()
{
	//inicia evento1
	evento1 = new Event();

	//inicia tiempo1
	tiempo1 = new Time();

	//inicia reloj1 y reloj de espera
	reloj1 = new Clock();

	//inicia gui
	gui = new GUI(ventana, ancho_ventana, alto_ventana);

	//inicia variable de desplazamiento de cajas
	offsetCajas = Vector2f(0.f, 0.f);

	/*
		variables del juego
			gameLevel comienza en nivel 1 el juego
			gameState cimienzo con el estado 0 del juego
			selectedItem �tem del men�
	*/
	gameLevel = 1;
	gameState = 0;
	selectedItem = 1;


	/*
		variables de objetos
			cajasEnPiso sin cajas cuendo comienza el juego
			cantidad_ragdoll sin ragdoll generados cuando comienza el juego
			ragdoll desactivados cuando comienza el juego
	*/
	cajasEnPiso = 0;
	cantidad_ragdoll = 0;
	active_ragdoll = false;

	//variable de tiempo
	tiempo = 0.f;

	//inicia la c�mara en un centro, un tama�o y un offset de movimiento
	SetCamara({ 19.f,19.f }, { 12.f, 12.f }, { 33.f, 77.f });

}

void Game::SetCamara(Vector2f center, Vector2f size, Vector2f offset)
{
	/*
		inicializa posici�n de camara1
		inicializa tama�o de camara1
		asigna camara1 a la ventana1
	*/
	camara1 = new View({ center }, { size });
	camara1->move({ offset });
	ventana->setView(*camara1);
}

void Game::InitGame()
{
	/*
		inicia m�sica del juego
		inicia las f�sicas que utilizar� el juego
		inicia loop del juego
	*/
	InitSound();

	InitPhysics();

	GameLoop();

}

void Game::InitSound()
{
	//Activa la m�sica del juego, se repite mientras dura el nivel
	gui->ActivaMusica();
}

void Game::InitPhysics()
{
	/*
		inicializa mundo con la gravedad = 9.81
		inicia el objeto suelo
		inicia el objeto arma
		inicia el objeto cajas (cantidad 3: este par�metro se puede setear)
	*/
	mundo = new b2World(b2Vec2(0.0f, 9.8f));

	suelo = new Suelo(mundo, b2Vec2(50.f, 102.f));

	arma = new Arma(mundo, b2Vec2(47.9f, 100.68f), 1);

	cajas = new Cajas(mundo, offsetCajas, gameLevel, 3);
}

void Game::GameLoop()
{
	/*
	mientras la ventana1 est� abierta = >
		procesa eventos
		dibuja en ventana
		controla las condiciones del juego
	*/
	while (ventana->isOpen())
	{

		ProssesEvent();

		DrawGame();

		gameStateCondition();

	}
}

void Game::gameStateCondition()
{
	/*
		si gameState = 1 (estado del juego) =>
			si el tiempo + 1/60 > tiempo transcurrido del juego =>
				actualiza las f�sicas creadas (suelo, cajas, arma, ragdoll
				detecta colisiones entre los ragdoll y las cajas m�viles
				controla las condiciones del jeugo (niveles, gana, peirde)
		si gameState = 6 =>
			se reinicia el juego (nuevo)
	*/
	if (gameState == 1)
	{
		*tiempo1 = reloj1->getElapsedTime();
		if (tiempo + frameTime < tiempo1->asSeconds())
		{
			tiempo = tiempo1->asSeconds();

			UpdatePhysics();

			DetectColission();

			ConditionGame();

		}
	}

	if (gameState == 6)
	{
		gui->~GUI();
		ventana->close();
		new Game(800, 600, "AKE MAVII TP Final");
	}
}

void Game::ConditionGame()
{
	/*
			si el estado del juego = 0 =>
				se muestra el men�
			sino si el estado del juego = 2 =>
				se cierra la ventana y se termina el juego
			sino si el estado del juego = 1 =>
				se juego en el nivel 1
			sino si el estado del juego = 4 se reinicia el juego desde el men�
	*/

	if (cajasEnPiso >= 3)
	{
		/*
			si todas las cajas fueron tiradas =>
				actualiza el valor de gameState = 3: Fuerza al Men� Gana Nivel
				incrementa el nivel de juego
		*/
		gameLevel++;
		gameState = 3;

		/*
			si el nivel del juego > 3 =>
				si est� habilitado el juego pero se ha llegado al nivel 4 => fuerza al Men� Ganaste el Juego
				activa el sonido de ganaste el juego
			sino =>
				limpia las variables del juego
				Inicia el juego desde el nivel actual
		*/
		if (gameLevel > 3)
		{
			gameState = 5;
			gui->ActivaGanaGame();
		}
		else
		{
			cajasEnPiso = 0;
			cantidad_ragdoll = 0;
			offsetCajas.x = 0.f;
			offsetCajas.y = 0.f;
			InitGame();
		}
	}

	/*
		si las cajas en el piso < 3 y los ragdoll disparados = 5 =>
			si el ragdoll4 (es el �ltimo disparado) no es nulo => verdadero
				si la posicion del ragdoll4 est� fuera de pantalla o intercepto el suelo o intercepta alguna caja fija (qued� colgado)  => verdadero
					gameState = 4 (perdiste, repetir el nivel)
					modificar variables
					Iniciar el juego
		
	*/
	if (cajasEnPiso < 3 && cantidad_ragdoll == 5)
	{

		if (ragdoll[4] != NULL)
		{
			/*
				define vector positionCoordRagdoll = posici�n del ragdoll4 en coordenadas del mundo
				define vector positionPixelRagdoll = posici�n del ragdoll4 en  coordenadas pixeles
				define boxRagdoll4 = box del ragdoll
				define box_suelo = box del suelo
			
			*/
			Vector2f positionCoordRagdoll = Vector2f(ragdoll[4]->GetPositionRagdoll(4));
			Vector2i positionPixelRagdoll = ventana->mapCoordsToPixel(positionCoordRagdoll);

			FloatRect boxRagdoll4 = ragdoll[4]->BoxRagdoll(4);
			FloatRect box_suelo = suelo->GetBoxSuelo();

			bool ragdollSobreRagdoll = false;

			if (positionPixelRagdoll.x < 0.f || positionPixelRagdoll.x > 800.f || positionPixelRagdoll.y < 0.f || positionPixelRagdoll.y > 500.f ||
				boxRagdoll4.intersects(box_suelo) ||
				boxRagdoll4.intersects(cajas->GetBoxCajaFija(0)) ||
				boxRagdoll4.intersects(cajas->GetBoxCajaFija(1)) ||
				boxRagdoll4.intersects(cajas->GetBoxCajaFija(2)))
			{
				gameState = 4;
				for (int i = 0; i < cantidad_ragdoll; i++)
				{
					ragdoll[i] = NULL;
				}

				cajasEnPiso = 0;
				cantidad_ragdoll = 0;
				offsetCajas.x = 0.f;
				offsetCajas.y = 0.f;
				InitGame();

			}

		}

	}
}

void Game::ProssesEvent()
{
	/*
		mientras la ventana1 escuche event1 =>
			cierra ventana (clic en X => se cierra la ventana1)
			mouse se mueve =>
				llama a la funci�n UpdateArma() que mantiene la posici�n origen del del arma, pero cambia el �ngulo. 
			mouse es presionado =>
				llama a la funci�n UpdateRagdoll() que controla la instancia, la direcci�n de disparo, la fuerza de disparo en fucni�n de la distancia
				y la cantidad de ragdoll generados
			tecla es presionada =>
				para el selector del men� (up, down, return)
				seg�n elecci�n del men� se dispara un estado nuevo del juego

	*/
	while (ventana->pollEvent(*evento1))
	{

		switch (evento1->type)
		{
			//cierra ventana
		case Event::Closed:
			ventana->close();
			break;

			//mouse se mueve
		case Event::MouseMoved:
			//controla el movimiento del arma
			UpdateArma();
			break;

			//mouse es presionado
		case Event::MouseButtonPressed:
			/*
				si la cantidad de Ragdoll disparados en < 5 y el nivel del juego es mayor a 0 =>
					obtiene ubicaci�n del mouse en pixeles y se convierte a coordenadas
					se activa el disparo del Ragdoll

			*/
			//Controla el disparo de cada ragdoll
			UpdateRagdoll();
			break;

		case Event::KeyPressed:

			if (evento1->key.code == Keyboard::Up)
			{
				//mueve hacia arriba en las opciones
				ItemSelectUp();
			}
			else if (evento1->key.code == Keyboard::Down)
			{
				// Mover hacia abajo en las opciones
				ItemSelectDown();
			}
			else if (evento1->key.code == Keyboard::Enter)

				//Selecciona la opci�n actual
				switch (gameState)
				{
				case 0:		//gameSatet = 0 = inicio del juego, se presenta el Men� Principal (necesita selectedItem)
					if (selectedItem == 1)
					{
						gameState = 1;		//Play => gameState = 1
					}
					else if (selectedItem == 2)
					{
						gameState = 2;		//Exit => gameState = 2
						gui->ActivaExitJuego();			//activa sonido de perdiste
					}
					else
					{
						gameState = 0;		// no selecciona y se qeuda en el Men� principal => gameState = 0
					}
					break;

				case 3:		//gameState = 3 = gana nivel, se presenta el Men� Gana Nivel (necesita selectedItem)

					if (selectedItem == 1)
					{
						gameState = 1;		//Play => gameState = 1
					}
					else if (selectedItem == 2)
					{
						gameState = 6;		//Reinicia con un nuevo juego

					}
					else
					{
						gameState = 0;		// no selecciona y se qeuda en el Men� principal => gameState = 0
					}
					break;

				case 4:		//gameState = 4 = pierde nivel, se presenta el Men� Pierde Nivel (necesita selectedItem)

					if (selectedItem == 1)
					{
						gameState = 1;		//Play => gameState = 1

					}
					else if (selectedItem == 2)
					{
						gameState = 6;		//Reinicia con un nuevo juego

					}
					else
					{
						gameState = 0;		// no selecciona y se qeuda en el Men� principal => gameState = 0
					}
					break;
				}
		}
	}
}

void Game::UpdateArma()
{
	/*
		define dos vectores como variables:
			Vector2i = guarda la posici�n del mouse en coordenadas de la ventana1
			Vector2F = guarda la posici�n del mouse en voordenadas del mundo1
		llama a la funci�n UpdateArma para actualizar la posici�n del arma
	*/
	Vector2i positionMouse;				//posicion del mouse en coordenadas de la ventana1
	Vector2f positionMouseCoordinates;	//posicion del mouse en voordenadas del mundo1
	positionMouse = Mouse::getPosition(*ventana);
	positionMouseCoordinates = ventana->mapPixelToCoords(positionMouse);

	arma->UpdateArma(positionMouseCoordinates);
}

void Game::UpdateRagdoll()
{
	/*
		define dos vectores como variables:
			Vector2i = guarda la posici�n del mouse en coordenadas de la ventana1
			Vector2F = guarda la posici�n del mouse en voordenadas del mundo1
		llama a la funci�n ActivaGolpeRagdoll para activar sonido disparo del ragdoll
		si la cantidad de ragdoll < 5 y el nivel del jeugo > 1 =>
			activa la creaci�n y dibujo de los ragdoll que se generen
			cuenta la cantidad de ragdoll generados y disparados
			limita la generaci�n hasta 5 m�ximo
			instancia un ragdoll saliendo del arma
			aplica una fuerza al ragdoll, se llama al m�todo ApplyForceRagdoll (est� en Ragdoll.cpp)
	*/
	Vector2i positionMouse;				//posicion del mouse en coordenadas de la ventana1
	Vector2f positionMouseCoordinates;	//posicion del mouse en voordenadas del mundo1
	positionMouse = Mouse::getPosition(*ventana);
	positionMouseCoordinates = ventana->mapPixelToCoords(positionMouse);
	gui->ActivaGolpeRagdoll();

	if (cantidad_ragdoll < 5 && gameLevel > 0)

	{
		//activa el Ragdoll para dibujarlos
		active_ragdoll = true;

		/*
			si la cantidad de cajas en el piso es < 3 = >
				genera nuevos Ragdoll en la posici�n del arma
				aplica una fuerza al Ragdoll en funci�n de la posici�n del mouse
				incrementa la cantidad de Ragdoll disparados
		*/
		if (cajasEnPiso < 3)
		{
			if (cantidad_ragdoll < 5)
			{
				/*ragdoll[cantidad_ragdoll] = new Ragdoll({ bdy_arma->GetPosition().x + 0.5f,bdy_arma->GetPosition().y - 2.f }, *mundo);*/
				ragdoll[cantidad_ragdoll] = new Ragdoll(arma->GetPositionArma(), *mundo);
				ragdoll[cantidad_ragdoll]->ApplyForceRagdoll({ positionMouseCoordinates.x - arma->GetPositionArma().x,positionMouseCoordinates.y - arma->GetPositionArma().y });
				cantidad_ragdoll++;
			}
		}
	}
}

void Game::UpdatePhysics()
{
	//Crea la fisica del juego
	mundo->Step(frameTime, 8, 8);
	mundo->ClearForces();
	mundo->DebugDraw();
}

void Game::ItemSelectUp()
{
	/*
		control del selector del men�
	*/
	if (selectedItem == 2)
	{
		selectedItem = (selectedItem - 1);
		gui->MoveUpMenu();

	}
	else if (selectedItem == 1)
	{
		gui->MoveUpMenu();
	}
}

void Game::ItemSelectDown()
{
	/*
		control del selector del men�
	*/
	if (selectedItem == 1)
	{
		selectedItem = (selectedItem + 1);
		gui->MoveDownMenu();

	}
	else if (selectedItem == 2)
	{
		gui->MoveDownMenu();
	}
}

void Game::DetectColission()
{
	/*
		si las cajas en el piso <= 3 =>
			por todas las cajas que hay en la escena =>
				si la caja m�vil intercepta a la caja fija => no se incrementa el contador de aciertos (cajaEnPiso)
				sino si la caja m�vil intercepta al suelo => se incrementa el contador de aciertos (cajaEnPiso)
				sino si no hay ninguna caja m�vil interpectando a una caja fina y tampoco al suelo => se incrementa el contador de aciertos (cajaEnPiso)
	*/
	if (cajasEnPiso <= 3)
	{
		for (int i = 0; i < 3; i++)
		{
			FloatRect box_cM = cajas->GetBoxCajaMovil(i);
			FloatRect box_cF = cajas->GetBoxCajaFija(i);
			FloatRect box_suelo = suelo->GetBoxSuelo();

			if (box_cM.intersects(box_cF))
			{
				cajasEnPiso = 0;
			}
			else if (box_cM.intersects(box_suelo))
			{
				cajasEnPiso++;
			}
			else if (!box_cM.intersects(box_cF))
			{
				cajasEnPiso++;
			}
		}
	}
}

void Game::DrawGame()
{
	/*
		Limpia ventana
		envia a dibujar seg�n el estado del juego, el nivel y la cantidad de ragdoll
		si gameState = 1 =>
			dibuja el nivel correspondiente del juego, incluyendo: suelo, cajas, ragdoll, arma
		Muestra en pantalla
	*/

	ventana->clear();

	//Envia a dibujar
	gui->DrawGUI(ventana, gameState, gameLevel, cantidad_ragdoll);

	if (gameState == 1)
	{
		gui->DrawGUI(ventana, gameState, gameLevel, cantidad_ragdoll);

		//dibuja el suelo (no cambia con las escenas)
		suelo->DrawSuelo(ventana);

		//dibuja el arma y el apoyo del arma
		arma->DrawArma(ventana);

		//dibuja los actores: las cajas fijas y m�viles
		cajas->DrawCajas(ventana);

		//dibuja los 5 ragdoll
		for (int i = 0; i < cantidad_ragdoll; i++)
		{
			if (!ragdoll[i] || active_ragdoll)
			{
				ragdoll[i]->DrawRagdoll(*ventana);
			}
		}
	}
	ventana->display();
}

float Game::deg2rad(float degrees)
{
	//convierte grados a radianes
	return degrees * 3.1416f / 180;
}

