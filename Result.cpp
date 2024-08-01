#include "Result.h"

void Result::Initialize()
{
	position = { -0.90f,0.3f,0.0f, };
	angle = 0.0f;


	cameraRotate = { 0.0f,0.0f,0.0f };

	cameraTranslate = { 0.0f,0.0f,0.0f };
	cameraPosition = SphericalToCartesian(radius, theta, phi);
	cameraTarget = { 0.0f, 0.0f, 0.0f };
	cameraUp = { 0.0f, 1.0f, 0.0f };

	viewMatrix = MakeLookAtMatrix4x4(cameraPosition, cameraTarget, cameraUp);
	worldMatrix = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, cameraRotate, cameraTranslate);
	projectionMatrix = MakePerspectiveFovMatrix(0.45f, float(kWindowWidth) / float(kWindowHeight), 0.1f, 100.0f);
	worldViewProjectionMatrix = Multiply(worldMatrix, Multiply(viewMatrix, projectionMatrix));
	viewProjectionMatrix = Multiply(viewMatrix, projectionMatrix);
	viewportMatrix = MakeViewportMatrix(0, 0, float(kWindowWidth), float(kWindowHeight), 0.0f, 1.0f);
}

void Result::Update()
{
	 cameraPosition = SphericalToCartesian(radius, theta, phi);
	 cameraTarget = { 0.0f, 0.0f, 0.0f };
	 cameraUp = { 0.0f, 1.0f, 0.0f };


	 viewMatrix = MakeLookAtMatrix4x4(cameraPosition, cameraTarget, cameraUp);
	 worldMatrix = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, cameraRotate, cameraTranslate);
	 projectionMatrix = MakePerspectiveFovMatrix(0.45f, float(kWindowWidth) / float(kWindowHeight), 0.1f, 100.0f);
	 worldViewProjectionMatrix = Multiply(worldMatrix, Multiply(viewMatrix, projectionMatrix));
	 viewProjectionMatrix = Multiply(viewMatrix, projectionMatrix);
	 viewportMatrix = MakeViewportMatrix(0, 0, float(kWindowWidth), float(kWindowHeight), 0.0f, 1.0f);
	Transform(Transform(position, viewProjectionMatrix), viewMatrix);
	
	if (start == true)
	{
		RotateInCircle(sphere, position, angle);
	}
}

void Result::Draw()
{
	DrawSphere({ position,sphere.radius }, viewProjectionMatrix, viewportMatrix, sphere.color);

	DrawGrid(viewProjectionMatrix, viewportMatrix);

	ImGui::Begin("Window");
	ImGui::DragFloat("theta", &theta, 0.01f);
	ImGui::DragFloat("phi", &phi, 0.01f);
	ImGui::DragFloat("angle", &angle, 0.01f);
	/*ImGui::DragFloat3("CameraTranslate", &cameraTranslate.x, 0.01f);
	ImGui::DragFloat3("CameraRotate", &cameraRotate.x, 0.01f);*/
	if (ImGui::Button("Start"))
	{
		start = true;
	}
	ImGui::DragFloat3("sphere", &sphere.center.x, 0.01f);
	ImGui::DragFloat3("pos", &position.x, 0.01f);

	ImGui::End();
}
