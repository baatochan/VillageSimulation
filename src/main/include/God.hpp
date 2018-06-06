//
// Created by black on 06.06.18.
//

#pragma once


#include <list>
#include <thread>
#include <mutex>
#include "Villager.hpp"

class God
{
protected:
	static std::list<std::shared_ptr<Villager>> creations_;
	static std::list<std::thread> souls_;

	static std::mutex villagerMutex_;
	static std::chrono::milliseconds refresh_;
protected:
	static void clear();
	static void end();
public:
	static void run();
	static void print();
	static std::weak_ptr<Villager> createVillager();
	static std::list<std::shared_ptr<Villager>> const& getCreations();
};

