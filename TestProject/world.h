#pragma once
#include "entity.h"
#include "SDL.h"
class world // Needs to iterate through entities 
{
public:
	const int LevelWidth = 1920;
	const int LevelHeight = 1080;
	~world()
	{
		for (auto v : entities)
		{
			delete v.second;
		}
		entities.clear();
		delete this;
	}

	inline std::map<int, entity*> getEntityList()
	{
		return this->entities;
	}

	inline std::map<int, component*> getComponentList(int ID) // takes ID of entity
	{
		for (auto entity : entities)
		{
			if (entity.first == ID)
			{
				return entity.second->getComponentList();
			}
		}
	}
	inline entity*& createEntity() // returns entity copy from inside the map
	{
		entity* newEnt = new entity;
		if (newEnt->getEID() == -1)
		{
			newEnt->setEID(((int)entities.size() + 1));
			entities.emplace(newEnt->getEID(), newEnt); // why do i do this to myself and copy this?
			return newEnt;
		}
		std::cout << "could not create entity as it already exists!" << std::endl;
		return newEnt;
	}
	inline int getID(){return this->ID;}
	inline int setID(int Id) { this->ID = Id; return Id; }
	inline entity* getEntity(int id)
	{
		for (auto entity : entities)
		{
			if (entity.first == id)
				return entity.second;
		}
		return nullptr;
	}
	inline entity* getEntityByTag(const char* name)
	{
		for (auto entity : entities)
		{
			if (entity.second->tag == name)
				return entity.second;
		}
		return nullptr;
	}

	inline void start(SDL_Renderer* renderer)
	{
		for (auto entity : entities)
		{
			entity.second->start(renderer);
		}
	}

	inline void update(SDL_Renderer* renderer)
	{
		for (auto entity : entities)
		{
			entity.second->update(renderer);
		}
	}

private: // contains all entities;
	std::map<int, entity*> entities; // entityList
	int ID = -1;


};