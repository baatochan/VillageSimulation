//
// Created by black on 28.05.18.
//

#pragma once


#include <ScreenManager.hpp>

class MainController
{
	static MainController* instance_;
protected:
	std::condition_variable      var;
	std::mutex                   mutex;
	std::unique_lock<std::mutex> scopedLock{mutex};

	std::map<std::string, std::shared_ptr<eng::Place>> places_;
	std::shared_ptr<msm::WindowStorage>      windowStoragePtr_;

	std::thread GodThread;

	void allocateStorage();
	void loadPlaces();
	void initialiseLogger();
	void summonGod();

public:
	void init();
	void stop();
	void close();

	std::map<std::string, std::shared_ptr<Engine::Place>> const& getPlaces() const;
	std::shared_ptr<MainScreenManager::WindowStorage> const& getWindowStorage() const;

	static MainController& getInstance();
};

