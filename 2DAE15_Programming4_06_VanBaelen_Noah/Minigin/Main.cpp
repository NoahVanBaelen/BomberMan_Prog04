//#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "TextObject.h"
#include "Scene.h"
#include "TextComponent.h"
#include "RenderComponent.h"
#include "FPSComponent.h"
#include "MoveInCircleComponent.h"
#include "Controller.h"
#include "ScoreComponent.h"
#include "LiveComponent.h"
#include "Input.h"

#include "UIDisplay.h"

void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	auto go_BackGround = std::make_shared<dae::GameObject>();
	go_BackGround->AddComponent<RenderComponent>();
	go_BackGround->GetComponent<RenderComponent>()->SetTexture("background.tga");
	scene.Add(go_BackGround);

	auto go_Logo = std::make_shared<dae::GameObject>();
	go_Logo->AddComponent<RenderComponent>();
	go_Logo->GetComponent<RenderComponent>()->SetTexture("logo.tga");
	go_Logo->GetComponent<TransformComponent>()->SetLocalPosition(glm::vec3(216.f, 180.f, 0.f));
	scene.Add(go_Logo);

	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);

	auto go_Text = std::make_shared<dae::GameObject>();
	go_Text->AddComponent<TextComponent>();
	go_Text->AddComponent<RenderComponent>();
	go_Text->GetComponent<TextComponent>()->SetText("Programming 4 Assignment");
	go_Text->GetComponent<TextComponent>()->SetFont(font);
	go_Text->GetComponent<TransformComponent>()->SetLocalPosition(glm::vec3(80.f, 20.f, 0));
	scene.Add(go_Text);

	auto go_FPS = std::make_shared<dae::GameObject>();
	go_FPS->AddComponent<FPSComponent>();
	go_FPS->AddComponent<TextComponent>();
	go_FPS->AddComponent<RenderComponent>();
	go_FPS->GetComponent<TextComponent>()->SetFont(font);
	go_FPS->GetComponent<TextComponent>()->SetColor(SDL_Color{ 0, 255, 0 });
	scene.Add(go_FPS);

	//WEEK3
	/*auto go_BomberMan = std::make_shared<dae::GameObject>();
	go_BomberMan->AddComponent<RenderComponent>();
	go_BomberMan->GetComponent<RenderComponent>()->SetTexture("BomberMan.png");
	go_BomberMan->GetComponent<TransformComponent>()->SetLocalPosition(glm::vec3(320.f, 280.f, 0.f));
	go_BomberMan->AddComponent<MoveInCircleComponent>();
	go_BomberMan->GetComponent<MoveInCircleComponent>()->SetRadius(30.f);
	go_BomberMan->GetComponent<MoveInCircleComponent>()->SetMoveCounterClockWise(true);
	go_BomberMan->GetComponent<MoveInCircleComponent>()->SetSpeed(0.3f);

	auto go_Bomb = std::make_shared<dae::GameObject>();
	go_Bomb->AddComponent<RenderComponent>();
	go_Bomb->GetComponent<RenderComponent>()->SetTexture("Bomb.png");
	go_Bomb->AddComponent<MoveInCircleComponent>();
	go_Bomb->GetComponent<MoveInCircleComponent>()->SetRadius(30.f);
	go_Bomb->GetComponent<MoveInCircleComponent>()->SetSpeed(0.3f);
	go_Bomb->SetParent(go_BomberMan, false);

	scene.Add(go_BomberMan);
	scene.Add(go_Bomb);*/

	////WEEK 5 & 6
	float moveSpeedBomberMan{ 0.2f };
	float moveSpeedBomb{ 0.1f };
	font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 12);

	auto go_BomberManScoreCounter = std::make_shared<dae::GameObject>();
	go_BomberManScoreCounter->AddComponent<RenderComponent>();
	go_BomberManScoreCounter->AddComponent<TextComponent>();
	go_BomberManScoreCounter->GetComponent<TextComponent>()->SetColor(SDL_Color{ 0, 255, 0 });
	go_BomberManScoreCounter->GetComponent<TextComponent>()->SetFont(font);
	go_BomberManScoreCounter->GetComponent<TextComponent>()->SetText("Points: 0");
	go_BomberManScoreCounter->GetComponent<TransformComponent>()->SetLocalPosition(glm::vec3(0.f, 100.f, 0.f));
	scene.Add(go_BomberManScoreCounter);

	auto go_BomberManLiveCounter = std::make_shared<dae::GameObject>();
	go_BomberManLiveCounter->AddComponent<RenderComponent>();
	go_BomberManLiveCounter->AddComponent<TextComponent>();
	go_BomberManLiveCounter->GetComponent<TextComponent>()->SetColor(SDL_Color{ 0, 255, 0 });
	go_BomberManLiveCounter->GetComponent<TextComponent>()->SetFont(font);
	go_BomberManLiveCounter->GetComponent<TextComponent>()->SetText("Lives: 3");
	go_BomberManLiveCounter->GetComponent<TransformComponent>()->SetLocalPosition(glm::vec3(0.f, 130.f, 0.f));
	scene.Add(go_BomberManLiveCounter);


	auto go_BomberMan = std::make_shared<dae::GameObject>();
	go_BomberMan->AddComponent<RenderComponent>();
	go_BomberMan->GetComponent<RenderComponent>()->SetTexture("BomberMan.png");
	go_BomberMan->GetComponent<TransformComponent>()->SetLocalPosition(glm::vec3(320.f, 280.f, 0.f));

	go_BomberMan->AddComponent<ScoreComponent>();
	go_BomberMan->GetComponent<ScoreComponent>()->AddObserver(new UIDisplay{ go_BomberManScoreCounter.get() });
	go_BomberMan->AddComponent<LiveComponent>();
	go_BomberMan->GetComponent<LiveComponent>()->SetRespawn(glm::vec3(320.f, 280.f, 0.f));
	go_BomberMan->GetComponent<LiveComponent>()->AddObserver(new UIDisplay{ go_BomberManLiveCounter.get() });

	scene.Add(go_BomberMan);

	auto go_BombScoreCounter = std::make_shared<dae::GameObject>();
	go_BombScoreCounter->AddComponent<RenderComponent>();
	go_BombScoreCounter->AddComponent<TextComponent>();
	go_BombScoreCounter->GetComponent<TextComponent>()->SetColor(SDL_Color{ 255, 255, 0 });
	go_BombScoreCounter->GetComponent<TextComponent>()->SetFont(font);
	go_BombScoreCounter->GetComponent<TextComponent>()->SetText("Points: 0");
	go_BombScoreCounter->GetComponent<TransformComponent>()->SetLocalPosition(glm::vec3(0.f, 180.f, 0.f));
	scene.Add(go_BombScoreCounter);

	auto go_BombLiveCounter = std::make_shared<dae::GameObject>();
	go_BombLiveCounter->AddComponent<RenderComponent>();
	go_BombLiveCounter->AddComponent<TextComponent>();
	go_BombLiveCounter->GetComponent<TextComponent>()->SetColor(SDL_Color{ 255, 255, 0 });
	go_BombLiveCounter->GetComponent<TextComponent>()->SetFont(font);
	go_BombLiveCounter->GetComponent<TextComponent>()->SetText("Lives: 3");
	go_BombLiveCounter->GetComponent<TransformComponent>()->SetLocalPosition(glm::vec3(0.f, 210.f, 0.f));
	scene.Add(go_BombLiveCounter);

	auto go_Bomb = std::make_shared<dae::GameObject>();
	go_Bomb->AddComponent<RenderComponent>();
	go_Bomb->GetComponent<RenderComponent>()->SetTexture("Bomb.png");
	go_Bomb->GetComponent<TransformComponent>()->SetLocalPosition(glm::vec3(320.f, 200.f, 0.f));

	go_Bomb->AddComponent<ScoreComponent>();
	go_Bomb->GetComponent<ScoreComponent>()->AddObserver(new UIDisplay{ go_BombScoreCounter.get() });
	go_Bomb->AddComponent<LiveComponent>();
	go_Bomb->GetComponent<LiveComponent>()->SetRespawn(glm::vec3(320.f, 200.f, 0.f));
	go_Bomb->GetComponent<LiveComponent>()->AddObserver(new UIDisplay{ go_BombLiveCounter.get() });

	scene.Add(go_Bomb);

	////INPUT
	auto& input = Input::GetInstance();
	int numController1 = input.AddController();
	int numController2 = input.AddController();
	//Input Player 1
	input.AddCommand(numController1, Controller::ControllerButton::DPadUp, Input::ButtonLogic::Pressed, new MoveCommand{ go_BomberMan.get(),moveSpeedBomberMan,glm::vec3(0.f,-1.f,0.f) });
	input.AddCommand(numController1, Controller::ControllerButton::DPadDown, Input::ButtonLogic::Pressed, new MoveCommand{ go_BomberMan.get(),moveSpeedBomberMan,glm::vec3(0.f,1.f,0.f) });
	input.AddCommand(numController1, Controller::ControllerButton::DPadRight, Input::ButtonLogic::Pressed, new MoveCommand{ go_BomberMan.get(),moveSpeedBomberMan,glm::vec3(1.f,0.f,0.f) });
	input.AddCommand(numController1, Controller::ControllerButton::DPadLeft, Input::ButtonLogic::Pressed, new MoveCommand{ go_BomberMan.get(),moveSpeedBomberMan,glm::vec3(-1.f,0.f,0.f) });
	input.AddCommand(numController1, Controller::ControllerButton::ButtonRight, Input::ButtonLogic::Down, new AddScoreCommand{ go_BomberMan.get(),100 });
	input.AddCommand(numController1, Controller::ControllerButton::ButtonBottom, Input::ButtonLogic::Down, new LoseLiveCommand{ go_BomberMan.get() });
	//Input Player 2
	input.AddCommand(SDL_SCANCODE_W, new MoveCommand{ go_Bomb.get(),moveSpeedBomb,glm::vec3(0.f,-1.f,0.f) });
	input.AddCommand(SDL_SCANCODE_S, new MoveCommand{ go_Bomb.get(),moveSpeedBomb,glm::vec3(0.f,1.f,0.f) });
	input.AddCommand(SDL_SCANCODE_D, new MoveCommand{ go_Bomb.get(),moveSpeedBomb,glm::vec3(1.f,0.f,0.f) });
	input.AddCommand(SDL_SCANCODE_A, new MoveCommand{ go_Bomb.get(),moveSpeedBomb,glm::vec3(-1.f,0.f,0.f) });
	input.AddCommand(SDL_SCANCODE_Q, new AddScoreCommand{ go_Bomb.get(),100 });
	input.AddCommand(SDL_SCANCODE_E, new LoseLiveCommand{ go_Bomb.get() });

	//Controls

	std::cout << "\nMove Player 1 with controller DPad & Player 2 with Keyboard WASD\n";
	std::cout << "To Gain Points press on the B button on the controller (XBOX) and Q on the Keyboard\n";
	std::cout << "To Lose Lives press on the A button on the controller (XBOX) and E on the Keyboard\n";
}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);

    return 0;
}