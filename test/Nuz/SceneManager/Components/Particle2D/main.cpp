#include "../../../include/Nuz.h"
#include <iostream>
#include <memory>
#include "../../../src/Nuz/Renderer/OpenGL/glew.h"
#include "../../../src/Nuz/Renderer/OpenGL/Texture.h"
#include "../../../src/Nuz/Renderer/OpenGL/CallList.h"
#include "../../../src/Nuz/Renderer/ImageCacheManager.h"
using namespace std;
using namespace Nuz;

shared_ptr<ICamera2D> pCamera2D;

int wmain(){
	auto& e = IEngine::GetGameDevice();
	e.GetFileSystem().Mount(e.GetLocalFile());
	//AddStdLogWhiteFliter("Nuz::Renderer");
	AddStdLogWhiteFliter("NuzTest");
	e.SetWindowTitle("Nuz zuN");
	e.SetFPSShowEnable(true);

	e.InitWindow(800, 600, false);
	e.SetSkipFrame(0);
	
	e.BindMessageProcessor(Nuz::IEngine::Message::Quit, []() {
		IEngine::GetGameDevice().GetSceneManager().Exit();
	});
	auto sA = Nuz::IScene::CreateScene();
	pCamera2D = Nuz::ICamera2D::CreateCamera2D();
	pCamera2D->SetCamera(-32, 16, -32, 16);
	sA->SetCamera2D(pCamera2D);

	auto particle2D = Nuz::IParticle2D::CreateParticle2D();
	particle2D->UseImage("/demo.ctx", 0);
	particle2D->BindSingle([](Nuz::IParticle2D& p, Nuz::IParticle2D::Dot2D& d) {
		//d.speed += 0.0001f;
		//d.alpha -= 0.001f;
		d.angle -= 0.1;
		d.size += 0.01;
		//d.angle += 0.01f;
		//d.r -= 0.01f;
		//d.g -= 0.001f;
		//if(d.speed>=0.01) d.speed -= 0.001f;
		//d.size -= (0.005f);
	});

	particle2D->BindIniter([](Nuz::IParticle2D& p, Nuz::IParticle2D::Dot2D& d) {
		d.speed = 1;//float(rand()) / RAND_MAX;
		d.angle = float(rand()) / RAND_MAX * 2 * M_PI;
		d.size = 0.5;
	});
	particle2D->AddDot(0, 0,1);

	sA->MountComponent(particle2D);

	e.GetSceneManager().Start(sA);

	return 0;
}