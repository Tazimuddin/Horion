#pragma once

#include "../Utils/HMath.h"
#include <glm/ext/matrix_float4x4.hpp>

class Camera {
private:
	char pad_0000[0x30];  // 0x0000
public:
	Vec4 lookingAt;  // 0x0030
	Vec3 cameraPos;  // 0x0040
private:
	char pad_004C[0xC];  // 0x004C
public:
	float uiScale;             // 0x0058
	float fieldOfView;         // 0x005C
	float nearClippingPlane;   // 0x0060
	float farClippingPlane;    // 0x0064
	glm::mat4 nausea;  // 0x0068
private:
	char pad_00A8[0x30];  // 0x00A8
public:
	Vec4 lookingAt2;   // 0x00D8
	Vec3 cameraPos2;  // 0x00E8
private:
	char pad_00F4[0xC];  // 0x00F4
public:
	float uiScale2;  // 0x0100
private:
	char pad_0104[0x4];  // 0x0104
public:
	float nearClippingPlane2;  // 0x0108
	float farClippingPlane2;   // 0x010C
	
	void getForwardVector(Vec3*);
	void getEulerAngles(Vec3*);
	void setOrientation(float pitch, float yaw, float roll);
	void setOrientationDeg(float pitch, float yaw, float roll) {
		setOrientation((-yaw - 180) * RAD_DEG, -pitch * RAD_DEG, roll * RAD_DEG);
	}
};

class CameraManager {
public:
	Camera* getCameraOrDebugCamera();
};