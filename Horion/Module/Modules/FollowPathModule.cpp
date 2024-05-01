#include "FollowPathModule.h"

#include "../../../Utils/Logger.h"

FollowPathModule::FollowPathModule() : IModule(0, Category::MOVEMENT, "Follows joe paths.") {}

const char *FollowPathModule::getModuleName() {
	return "FollowPath";
}

void FollowPathModule::startSearch(Vec3i startNode, BlockSource* region, float searchTimeout, std::function<void(bool, JoePath)> callback){
	if(pathFinder){
		logF("Already searching!");
		return;
	}
	pathFinder = std::make_shared<JoePathFinder>(startNode, region, goal);
	pathFinder->pathSearchTimeout = searchTimeout;
	//std::thread([this, callback](){
		auto ref = pathFinder; // so it won't get deleted when followpathmodule is disabled
		auto tempPath = pathFinder->findPath();
		pathFinder.reset();
		if(tempPath.getNumSegments() == 0 || !isEnabled()){
			callback(false, tempPath);
			return;
		}
		callback(true, tempPath);
	//}).detach();
}


bool shouldStartSearch = false;
void FollowPathModule::onEnable() {
	if(!Game.isInGame() || !Game.getLocalPlayer()->isAlive()){
		setEnabled(false);
		return;
	}

	if(!goal){
		logF("goal not set");
		setEnabled(false);
		return;
	}
	shouldStartSearch = true;
}

void FollowPathModule::onDisable() {
	shouldStartSearch = false;
	if(pathFinder)
		pathFinder->terminateSearch = true;
	engageDelay = -1;

	pathFinder.reset();
	path.reset();
	nextPath.reset();
	movementController.reset();
	goal.reset();
}

void FollowPathModule::onTick(GameMode *mode) {
	if (!shouldStartSearch)
		return;
	shouldStartSearch = false;

	auto player = Game.getLocalPlayer();
	auto pPos = *player->getPos();
	Vec3i startNode((int)floorf(pPos.x), (int)roundf(pPos.y - 1.62f), (int)floorf(pPos.z));

	startSearch(startNode, player->getRegion(), 0.5f, [&](bool succeeded, JoePath tempPath) {
		if (!succeeded) {
			clientMessageF("%sCould not find a path!", RED);
			path.reset();
			movementController.reset();
			setEnabled(false);
			engageDelay = -1;
			return;
		}

		clientMessageF("%sFound %s path!", tempPath.isIncomplete1() ? YELLOW : GREEN, tempPath.isIncomplete1() ? "incomplete" : "complete");

		if (tempPath.isIncomplete1()) {
			tempPath.cutoff(0.9f);
		}
		engageDelay = 10;

		path = std::make_shared<JoePath>(tempPath.getAllSegments(), tempPath.isIncomplete1());
		movementController = std::make_unique<JoeMovementController>(path);
	});
}

void FollowPathModule::onMove(MoveInputHandler *handler) {
	if(movementController){
		movementController->step(Game.getLocalPlayer(), Game.getClientInstance()->getMoveTurnInput());
		if(engageDelay > 0)
			engageDelay--;

		if(movementController->isDone()){
			if(movementController->getCurrentPath()->isIncomplete1()){
				// Replace with next path if it exists
				if(nextPath && !pathFinder){
					clientMessageF("%sContinuing on next path...", GREEN);

					path = nextPath;
					nextPath.reset();
					movementController = std::make_unique<JoeMovementController>(path);
				}else if(!pathFinder){
					setEnabled(false);
				}else if(Game.getLocalPlayer()->isInWater()){
					handler->isJumping = true;
				}
			}else{
				clientMessageF("%sDone!", GREEN);
				setEnabled(false);
				return;
			}
		}else if(!pathFinder && engageDelay == 0 && path && path->isIncomplete1() && !nextPath){
			engageDelay = 10;

			// Estimate time to completion
			auto curPath = movementController->getCurrentPath();
			float timeSpent = 0;
			if(curPath->getNumSegments() == 0){
				setEnabled(false);
				return;
			}
			for(size_t i = curPath->getNumSegments() - 1; i > movementController->getCurrentPathSegment(); i--){
				auto cur = curPath->getSegment(i);
				timeSpent += cur.getCost();
				if(timeSpent > 11)
					break;
			}

			if(timeSpent > 11)
				return;

			clientMessageF("%sCalculating next path...", YELLOW);

			float timeForSearch = std::clamp(timeSpent - 0.5f, 1.f, 3.f);
			auto lastSeg = curPath->getSegment(curPath->getNumSegments() - 1);
			nextPath.reset();
			startSearch(lastSeg.getEnd(), Game.getLocalPlayer()->getRegion(), timeForSearch, [&](bool succeeded, JoePath tempPath) {
			  if(!succeeded){
				  clientMessageF("%sCould not find subsequent path!", RED);

				  engageDelay = -1;
				  return;
			  }

			  clientMessageF("%sFound subsequent %s path!", tempPath.isIncomplete1() ? YELLOW : GREEN, tempPath.isIncomplete1() ? "incomplete" : "complete");

			  if(tempPath.isIncomplete1()){
				  tempPath.cutoff(0.9f);
			  }

			  nextPath = std::make_shared<JoePath>(tempPath.getAllSegments(), tempPath.isIncomplete1());
			});
		}
	}
}
void FollowPathModule::onLevelRender() {
	if(!Game.isInGame()){
		setEnabled(false);
		return;
	}

	if(movementController && path){
		path->draw(movementController->getCurrentPathSegment());
	} /* else if (pathFinder) {
		JoePath localPath = pathFinder->getCurrentPath();
		localPath.draw(-1); // copy so we avoid drawing while its being updated by the pathfinder
	}*/
}
