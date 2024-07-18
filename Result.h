#pragma once
#include "MathFunc.h"
#include "Novice.h"


class Result
{
public:

	Sphere sphere
	{
		0,0,0, //center
		0.1f, // radius
		(int)WHITE,
	};

	Vector3 position = { -0.90f,0.3f,0.0f, };
	float angle;


	Vector3 cameraRotate{ 0.0f,0.0f,0.0f };

	Vector3 cameraTranslate{ 0.0f,0.0f,0.0f };
	Vector3 cameraPosition = SphericalToCartesian(radius, theta, phi);
	Vector3 cameraTarget = { 0.0f, 0.0f, 0.0f };
	Vector3 cameraUp = { 0.0f, 1.0f, 0.0f };

	Matrix4x4 viewMatrix = MakeLookAtMatrix4x4(cameraPosition, cameraTarget, cameraUp);
	Matrix4x4 worldMatrix = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, cameraRotate, cameraTranslate);
	Matrix4x4 projectionMatrix = MakePerspectiveFovMatrix(0.45f, float(kWindowWidth) / float(kWindowHeight), 0.1f, 100.0f);
	Matrix4x4 worldViewProjectionMatrix = Multiply(worldMatrix, Multiply(viewMatrix, projectionMatrix));
	Matrix4x4 viewProjectionMatrix = Multiply(viewMatrix, projectionMatrix);
	Matrix4x4 viewportMatrix = MakeViewportMatrix(0, 0, float(kWindowWidth), float(kWindowHeight), 0.0f, 1.0f);

	float radius = 10.0f;
	float theta = -3.46f;
	float phi = 1.5f;
	bool start = false;

	void Initialize();


	void Update();


	void Draw();
};

