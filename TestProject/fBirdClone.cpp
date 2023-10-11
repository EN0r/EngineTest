#include "fBirdClone.h"
enum gameStates // should probably port this to main.cpp and store the state as a global in a namespace or world object.
{
	PLAY = 0,
	PAUSE = 1
};

// globals
unsigned int maxEntitiesSpawned;

// scrolling backdrop manager.

unsigned int startTime = 0;
unsigned int backDropChangeTime = 2;
unsigned int goal = 200;
// gravity manager.
unsigned int plrStartTime = 0;
unsigned int playerDownForce = 5; // every 10 frames apply a downforce
unsigned int playerGravity = 3;

//  player jump physics handler
unsigned int plrJumpStart = 0;
unsigned int playerJumpPower = 1;
unsigned int plrDestTime = 5;

unsigned int pickupStart = 0;
unsigned int pickupSpawn = 0;


/*
#################################
Work on number factory!!!!
#################################
*/


void fBirdClone::start(SDL_Renderer* renderer, sceneManager* manager)
{
	backDrop.setPath(files[0].c_str());
	backDrop.initImage(renderer);
	backDropAbove.setPath(files[0].c_str());
	backDropAbove.initImage(renderer);
	manager->addWorld(thisWorld, thisWorldID);
	manager->loadWorld(thisWorldID);

	// init game score and text!
	Score.init(renderer,"Score: ", 25,{0,0},{255,255,255,255});
	ScoreValue.init(renderer,std::to_string(playerScore).c_str(), 25, {(float)Score.size.w + 1,(float)Score.size.y}, {255,255,255,255});

	// create player.
	transform* plrPosition = new transform;
	sprite* plrSprite = new sprite;
	boxCollider2D* plrCollider = new boxCollider2D;
	player->tag = "player";
	player->addComponent(plrPosition);
	player->addComponent(plrSprite);
	player->addComponent(plrCollider);

	player->getComponentEX<transform*>()->position = { (400 - 32), (300 - 32) };
	player->getComponentEX<transform*>()->w = 64;
	player->getComponentEX<transform*>()->h = 64;
	player->getComponentEX<sprite*>()->init(player, files[1].c_str());
	player->getComponentEX<sprite*>()->filePath = files[1].c_str();
	player->getComponentEX<boxCollider2D*>()->initColliderPosition(manager, player->getEID());

}

void fBirdClone::update(SDL_Renderer* renderer, sceneManager* manager, unsigned int deltaTime)
{
	switch (gameState)
	{
	case PLAY:
		//backDropAbove.createImage(renderer, backDropAboveRect);
		SDL_PollEvent(&e);
		keys = SDL_GetKeyboardState(&keycode);
		SDL_GetMouseState(&this->x, &this->y);
		// creating scrolling effect
		startTime++;
		{
			if (startTime == backDropChangeTime)
			{
				startTime = 0;
				backDropAboveRect.y = backDropAboveRect.y + 1;
				backDropRect.y = backDropRect.y + 1;
			}
			if (backDropRect.y >= 590)
			{
				backDropAboveRect.y = -600;
				backDropRect.y = 0;
			}
			backDrop.createImage(renderer, backDropRect);
			backDropAbove.createImage(renderer, backDropAboveRect);
		}


		
		/*
			create player downforce and also need to create angled fall.
		*/
		plrStartTime++;
		if (plrStartTime == playerDownForce)
		{
			plrStartTime = 0;
			player->getComponentEX<transform*>()->position.y = player->getComponentEX<transform*>()->position.y - playerGravity;
			// add tilt
			if (player->getComponentEX<sprite*>()->flip == true)
			{
				if (player->getComponentEX<transform*>()->angle != -45)
				{
					player->getComponentEX<transform*>()->angle -= 1;
				} else {
					player->getComponentEX<transform*>()->angle = player->getComponentEX<transform*>()->angle;
				}
			} else {

				if (player->getComponentEX<transform*>()->angle != 45)
				{
					player->getComponentEX<transform*>()->angle += 1;
				}
				else
					player->getComponentEX<transform*>()->angle = player->getComponentEX<transform*>()->angle;
			}
		}

		// create Entity to pickup and add to score.
		{
			pickupStart++;
			if (pickupStart == pickupSpawn)
			{
				pickupStart = 0;
				entity*& pEnt = thisWorld->createEntity();
				transform* newTransform;
				spawnedID.push_back(pEnt->getEID());
				pEnt->addComponent(newTransform);

				pEnt->getComponentEX<transform*>()->position.y -= 1;
				for (auto entityID : spawnedID)
				{
					// if offscreen X
					if (thisWorld->getEntity(entityID)->getComponentEX<transform*>()->position.x >= 800 || thisWorld->getEntity(entityID)->getComponentEX<transform*>()->position.x >= -1)
					{
						// need to also remove it from entity list;

						delete thisWorld->getEntity(entityID);
					}
					// if off screen Y
					if (thisWorld->getEntity(entityID)->getComponentEX<transform*>()->position.y >= 600 || thisWorld->getEntity(entityID)->getComponentEX<transform*>()->position.y >= -1)
					{
						delete thisWorld->getEntity(entityID);
					}
				}

			}

		}

		// movement -- need to make it so player cant go higher than y of screen,
		{
			plrJumpStart++;
			if (keys[SDL_SCANCODE_SPACE])
			{
				if (plrJumpStart >= plrDestTime)
				{
					jumping = true;
					player->getComponentEX<transform*>()->position.y += playerJumpPower;
				}
			}
			if (keys[SDL_SCANCODE_D])
			{
				player->getComponentEX<transform*>()->position.x -= 1;
				player->getComponentEX<sprite*>()->flip = false;

			}
			if (keys[SDL_SCANCODE_A])
			{
				player->getComponentEX<transform*>()->position.x += 1;
				player->getComponentEX<sprite*>()->flip = true;
			}
		}

		// renderUI
		{
			// Text/UI rendering
			Score.renderText(renderer);
			ScoreValue.renderText(renderer);
		}

		

	case PAUSE:
		SDL_PollEvent(&e);
		keys = SDL_GetKeyboardState(&keycode);
		SDL_GetMouseState(&this->x, &this->y);
		if (keys[SDL_SCANCODE_SPACE])
			gameState = PLAY;

	}





}