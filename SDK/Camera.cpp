#include "Camera.h"

#include "../Utils/Utils.h"

void Camera::getEulerAngles(Vec3* vec) {
	using cam_getEuler_t = void(__fastcall*)(Camera*, Vec3*);
	static auto cam_getEuler = reinterpret_cast<cam_getEuler_t>(FindSignature("48 8B C4 53 48 81 EC ?? ?? ?? ?? 0F 29 70 ?? 48 8B DA 0F 29 78 ?? F3"));
	cam_getEuler(this, vec);
}
void Camera::setOrientation(float pitch, float yaw, float roll) {
	using cam_setOrientation_t = void(__fastcall*)(Camera*, float, float, float);
	static auto cam_setOrientation = reinterpret_cast<cam_setOrientation_t>(FindSignature("40 53 48 81 EC ?? ?? ?? ?? 0F 29 74 24 ?? 0F 57"));
	cam_setOrientation(this, pitch, yaw, roll);
}
void Camera::getForwardVector(Vec3* forward) {
	Vec3 eulerAngles;
	this->getEulerAngles(&eulerAngles);

	float calcYaw = eulerAngles.y - (90 * (PI / 180));
	float calcPitch = -eulerAngles.x;

	forward->x = cos(calcYaw) * cos(calcPitch);
	forward->y = sin(calcPitch);
	forward->z = sin(calcYaw) * cos(calcPitch);
}

Camera* CameraManager::getCameraOrDebugCamera() {
	/*using camerManager_getCameraOrDebugCamera_t = Camera*(__fastcall*)(CameraManager*);
	static auto camerManager_getCameraOrDebugCamera = reinterpret_cast<camerManager_getCameraOrDebugCamera_t>(FindSignature("40 53 48 83 EC ?? 48 8B 05 ?? ?? ?? ?? 48 33 C4 48 89 44 24 ?? 80 39 00 48 8B D9 74 ?? 48"));
	return camerManager_getCameraOrDebugCamera(this);*/
	return reinterpret_cast<Camera*>(reinterpret_cast<__int64>(this) + 0x48);
}
