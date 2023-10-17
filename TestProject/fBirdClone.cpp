#include "fBirdClone.h"
#include "numFactory.h"
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


// pick up items spawn
unsigned int pickupStart = 0;
unsigned int pickupSpawn = 3000;

// pick up items physics handler
unsigned int pickUpStartPhys = 0;
unsigned int pickUpStartPhysGoal = 5;


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
	player->getComponentEX<boxCollider2D*>()->drawDebugGeometry();

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
				entity* pEnt = thisWorld->createEntity();
				transform* newTransform = new transform;
				renderedPosition* rPos = new renderedPosition;
				sprite* pEntSprite = new sprite;
				boxCollider2D* boxCollider = new boxCollider2D;
				
				pEntSprite->filePath = files[3].c_str();
				pEnt->addComponent(newTransform);
				pEnt->addComponent(rPos);
				pEnt->addComponent(boxCollider);
 				pEnt->addComponent(pEntSprite);
				pEnt->getComponentEX<boxCollider2D*>()->initColliderPosition(manager,pEnt->getEID());
				pEnt->tag = "PickUpObject";

				newTransform->w = 64;
				newTransform->h = 64;
				rPos->position.x = numFactory::randNumDT(800, deltaTime);
				rPos->position.y = numFactory::randNumDT(20, deltaTime*10);
				newTransform->position.x = numFactory::randNumDT(800, deltaTime);
				newTransform->position.y = numFactory::randNumDT(20, deltaTime*10);
				pEntSprite->start(renderer);

 				pEntSprite->init(pEnt,files[3].c_str());
				spawnedID.push_back(pEnt->getEID());

				//std::cout << "spawned!! :" << newTransform->position.x << "," << newTransform->position.x << std::endl;


				for (auto entityID : spawnedID)
				{
					// if offscreen X
					if (thisWorld->getEntity(entityID)->getComponentEX<transform*>()->position.x <= 800 || thisWorld->getEntity(entityID)->getComponentEX<transform*>()->position.x <= -1)
					{
						// need to also remove it from entity list;
						//delete thisWorld->getEntity(entityID);
						//delete newTransform;
						//delete pEntSprite;
					}
					// if off screen Y
					if (thisWorld->getEntity(entityID)->getComponentEX<transform*>()->position.y > 600)
					{
						thisWorld->getEntity(entityID)->getComponentEX<sprite*>()->setVisiblity(false);
						std::cout << entityID << " , Has been made invisible." << std::endl;
						//delete thisWorld->getEntity(entityID);
						//delete newTransform;
						//delete pEntSprite;
					}
				}

			}

		}

		// update spawned pickup objects.
		pickUpStartPhys++;
		{
			if (pickUpStartPhys == pickUpStartPhysGoal)
			{
				pickUpStartPhys = 0;
				for (auto object : thisWorld->getEntityList())
				{
					if (object.second->tag == "PickUpObject")
					{
						object.second->getComponentEX<transform*>()->position.y -= 1;
						object.second->getComponentEX<boxCollider2D*>()->updateColliderPosition(manager);
						object.second->getComponentEX<transform*>()->angle += 1;
						if (object.second->getComponentEX<transform*>()->angle == 360)
							object.second->getComponentEX<transform*>()->angle = 0;
					
					}
				}
			}
		}

		// check if picked up

		{
			for (auto pickUpObj : thisWorld->getEntityList())
			{
				pickUpObj.second->getComponentEX<boxCollider2D*>()->drawDebugGeometry();
				if (pickUpObj.second->tag == "PickUpObject") {
					pickUpObj.second->getComponentEX<boxCollider2D*>()->updateColliderPosition(manager);
					if (pickUpObj.second->getComponentEX<boxCollider2D*>()->isCollidingEX(thisWorld))
					{
						pickUpObj.second->getComponentEX<sprite*>()->setVisiblity(false);
						std::cout << "Picked up! " << std::endl;
					}
				}
				else {
					
					if (pickUpObj.second->getComponentEX<boxCollider2D*>()->isCollidingEX(thisWorld))
					{
						pickUpObj.second->getComponentEX<sprite*>()->setVisiblity(false);
					}

				}
			}
		}

		// movement -- need to make it so player cant go higher than y of screen,
		{
			plrJumpStart++;
			player->getComponentEX<boxCollider2D*>()->updateColliderPosition(manager);
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