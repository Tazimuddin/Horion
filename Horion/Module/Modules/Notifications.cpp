#include "Notifications.h"

#include "../ModuleManager.h"

Notifications::Notifications() : IModule(0, Category::CLIENT, "Gives Notifications For Disabling/Enabling Modules") {
}

Notifications::~Notifications() {
}

const char* Notifications::getModuleName() {
	return ("Notifications");
}