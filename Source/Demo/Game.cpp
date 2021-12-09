#include "Game.h"
#include <Components/FPSComponent.h>
#include <Components/TextComponent.h>
#include <Components/SpriteComponent.h>
#include <Components/AnimatedSpriteComponent.h>
#include <Components/ModelComponent.h>
#include <iostream>
#include <Utils/Animator.h>

//Engine::TextComponent*              textComponent;
//Engine::TextComponent*              keyboardView;
//Engine::FPSComponent*               fpsComponent;
//Engine::TextComponent*              cameraMatrices;
//Engine::TextComponent*              warning;
//Engine::SpriteComponent*            sprite;
//Engine::AnimatedSpriteComponent*    sprite2;
//Engine::AnimatedSpriteComponent*    sprite3[1];
Engine::ModelComponent*             model;
//Engine::ModelComponent*             model2;
//Engine::ModelComponent*             model3[50];

//DirectX::XMFLOAT4X4 viewproj;
//int frameLimitSwitch = 0;

//Init is called when the application is started.
void Game::Init()
{
    //textComponent = new Engine::TextComponent(m_Graphics.get());
    //textComponent->SetPosition(10, 10);
    //textComponent->SetText("Default Rendering Demo\nEwan Burnett [2021]\nA simple demo, demonstrating rendered text.\nFramerate Controls:\n    F1 - uncapped\n    F2 - 15 FPS\n    F3 - 30 FPS\n    F4 - 60 FPS");
    //m_Components.push_back(textComponent);

    //fpsComponent = new Engine::FPSComponent(&m_Time, m_Graphics.get());
    //fpsComponent->TextPosition() = DirectX::XMFLOAT2(400, 10);
    //fpsComponent->SetColor(0.0f, 1.0f, 0.25f);
    //m_Components.push_back(fpsComponent);

    //keyboardView = new Engine::TextComponent(m_Graphics.get());
    //keyboardView->SetPosition(10, 460);
    //keyboardView->SetColor(0.05f, 0.2f, 1.0f, 1.0f);
    //m_Components.push_back(keyboardView);


    //warning = new Engine::TextComponent(m_Graphics.get());
    //warning->SetText("DON'T EVEN THINK ABOUT MOVING ONTO\nRENDERING BEFORE YOU FULLY IMPLEMENT AND TEST\nALL THIS BACKEND STUFF!!!\n+ Keyboard Input\n- Mouse Input\n+ Building Fonts\n- Object Pooling\n+ Camera Matrices\n+ Framerate Limiting\n- Game Objects\n- Byte Alignment\n- OPTIMISATIONS\n+ Warnings\n+ Memory Leaks\n+ COM Pointers\n+ Sprite Component\n- COMMENTING\n- ARCHITECTURAL DESIGN DOCUMENT!!!!!!!!!\n+ Icons\n- ...and tidying up :D\nHave Fun <3");
    //warning->SetColor(1.0f, 0.0f, 0.05f, 1.0f);
    //warning->SetPosition(800, 10);
    //m_Components.push_back(warning);

    //


    //cameraMatrices = new Engine::TextComponent(m_Graphics.get());
    //cameraMatrices->SetColor(0.3f, 0.3f, 0.5f, 1.0f);
    //cameraMatrices->SetPosition(700, 500);
    //m_Components.push_back(cameraMatrices);
    //   

    

   model = new Engine::ModelComponent(m_Graphics.get(), m_Camera);
   model->SetOrigin(0.5, 0.5, 0.5);
   model->SetRotation(30, 30, 45);
   model->SetTranslation(0, 0, -10);
   model->SetScale(2, 2, 2);
   m_Components.push_back(model);

   //model2 = new Engine::ModelComponent(m_Graphics.get(), m_Camera);
   //model2->SetOrigin(0.5, 0.5, 0.5);
   //// model2->SetRotation(30, 30, 45);
   //model2->SetTranslation(0, 0, -10);
   //model2->SetScale(1, 1, 1);
   //m_Components.push_back(model2);
    //sprite = new Engine::SpriteComponent(m_Graphics.get());
    //sprite->SetPosition(800, 200);
    //sprite->SetColor(0, 1, 0, 1);
    //sprite->SetRect(0, 0, 200, 200);
    //m_Components.push_back(sprite);

    //model2 = new Engine::ModelComponent(m_Graphics.get(), m_Camera);
    //m_Components.push_back(model2);
    //m_Camera->SetPosition(0, 0, 5);

    //
    //
    //
    //sprite2 = new Engine::AnimatedSpriteComponent(m_Graphics.get());
    //sprite2->SetLayerDepth(1);
    //sprite2->SetSprite(L"..\\..\\Resources\\Textures\\walker1.dds");
    //sprite2->SetPosition(500, 500);
    //sprite2->SetScale(2);
    //sprite2->AddClip("Walking_Up", { 64, 64, 1024, 512 }, 0.1f, 0, 16);
    //sprite2->AddClip("Walking_Right", { 64, 64, 1024, 512 }, 0.1f, 16, 16);
    //sprite2->AddClip("Walking_Down", { 64, 64, 1024, 512 }, 0.1f, 64, 16);
    //sprite2->AddClip("Walking_Left", { 64, 64, 1024, 512 }, 0.1f, 96, 16);
    //sprite2->AddClip("Idle", { 64, 64, 1024, 512 }, 1.0f / 24.0f, 0, 256, true);

    //m_Components.push_back(sprite2);

    //for (int i = 0; i < std::size(sprite3); i < i++) {
    //    sprite3[i] = new Engine::AnimatedSpriteComponent(m_Graphics.get());
    //    sprite3[i]->SetLayerDepth(1);
    //    sprite3[i]->SetSprite(L"..\\..\\Resources\\Textures\\Fire.dds");
    //    sprite3[i]->SetPosition(64 * i * cos(i), 128 * (sin(i)));
    //    sprite3[i]->SetScale(i % 8);
    //    sprite3[i]->AddClip("Idle", { 64, 64, 640, 384 }, 1.0f / 24.0f, 0, 60, true);
    //    sprite3[i]->SetClip("Idle");
    //    m_Components.push_back(sprite3[i]);
    //}

    /*for (int i = 0; i < std::size(model3); i++) {
        model3[i] = new Engine::ModelComponent(m_Graphics.get(), m_Camera);
        model3[i]->SetTranslation(i, i, i);
        model3[i]->SetTranslation(cos(i) * 100, cos(i) * 100, sin(i) * 100);
        model3[i]->SetRotation(360 * sin(i), 360 * cos(i), 360 * tan(i));
        model3[i]->SetScale((i % 10) / 1);
        m_Components.push_back(model3[i]);
    }*/

    
    //
}

//Update is called once per frame. 
void Game::Update(float dt)
{
    static float speed = 5;
    if (m_Keyboard->KeyDown(KB_DIR_UP)) {
        speed += 10.0f * dt;
    }
    if (m_Keyboard->KeyDown(KB_DIR_DOWN)) {
        speed -= 10.0f * dt;
    }
    static float rot;
    model->SetRotation(-rot, rot, rot / 2);
    rot += speed * dt;

    ////TODO: Format this properly (16 rows, 2 columns, 8 bits per column)
    //std::stringstream out;
    //std::string kbd = m_Keyboard->GetKeyboardState().to_string();

    //std::reverse(kbd.begin(), kbd.end());
    //kbd.insert(32, "\n");
    //kbd.insert(64, "\n");
    //kbd.insert(96, "\n");
    //kbd.insert(128, "\n");

    //std::string kbd2 = m_Keyboard->GetKeyboardState().to_string();

    //std::reverse(kbd2.begin(), kbd2.end());
    //kbd2.insert(32, "\n");
    //kbd2.insert(64, "\n");
    //kbd2.insert(96, "\n");
    //kbd2.insert(128, "\n");

    //out << "Keyboard State [Starting from bit 0]: \n" << kbd << "\n\n Last Keyboard State\n" << kbd2 << std::endl;
    //keyboardView->SetText(out.str());


    //if (m_Keyboard->KeyPressed(KB_FNC_F1)) {
    //    SetFrameRate(0);
    //}
    //if (m_Keyboard->KeyPressed(KB_FNC_F2)) {
    //    SetFrameRate(15);
    //}
    //if (m_Keyboard->KeyPressed(KB_FNC_F3)) {
    //    SetFrameRate(30);
    //}
    //if (m_Keyboard->KeyPressed(KB_FNC_F4)) {
    //    SetFrameRate(60);
    //}

    //float speed = 45.0f;

    ///*m_Camera->SetTarget(sprite2->SpritePosition().x, sprite2->SpritePosition().y, 0);
    //m_Camera->SetPosition(sprite2->SpritePosition().x, sprite2->SpritePosition().y, 0);*/
    ////Cam
    //if (m_Keyboard->KeyDown(KB_KEY_I)) {
    //    m_Camera->Position().y += speed * dt;
    //}
    //if (m_Keyboard->KeyDown(KB_KEY_J)) {
    //    m_Camera->Position().x += speed * dt;
    //}
    //if (m_Keyboard->KeyDown(KB_KEY_K)) {
    //    m_Camera->Position().y -= speed * dt;
    //}
    //if (m_Keyboard->KeyDown(KB_KEY_L)) {
    //    m_Camera->Position().x -= speed * dt;
    //}
    //if (m_Keyboard->KeyDown(KB_KEY_O)) {
    //    m_Camera->Position().z += speed * dt;
    //}
    //if (m_Keyboard->KeyDown(KB_KEY_P)) {
    //    m_Camera->Position().z -= speed * dt;
    //}

    ////TODO: Defer these calculations into the camera object, so these can just call a function.
    //if (m_Keyboard->KeyDown(KB_KEY_W)) {
    //    m_Camera->Direction().y += 0.3 * speed * dt;        
    //}
    //if (m_Keyboard->KeyDown(KB_KEY_A)) {
    //    m_Camera->Direction().x += 0.3 * speed * dt;
    //}
    //if (m_Keyboard->KeyDown(KB_KEY_S)) {
    //    m_Camera->Direction().y -= 0.3 * speed * dt;
    //}
    //if (m_Keyboard->KeyDown(KB_KEY_D)) {
    //    m_Camera->Direction().x -= 0.3 * speed * dt;
    //}
    //
    //static float theta = 0;
    //static float phi = 0;
    //static float radius = 10.0f;

    //if (m_Keyboard->KeyPressed(KB_NUM_0)) {
    //    m_Camera->SetViewMode(Engine::Camera::ViewMode::VIEW_PERSPECTIVE);
    //}
    //if (m_Keyboard->KeyPressed(KB_NUM_1)) {       
    //    theta = 0;
    //    phi = 0;
    //    radius = 10.0f;
    //    m_Camera->SetViewMode(Engine::Camera::ViewMode::VIEW_ORBIT);
    //}
    //if (m_Keyboard->KeyPressed(KB_NUM_2)) {
    //    m_Camera->SetViewMode(Engine::Camera::ViewMode::VIEW_TARGET);
    //}
    //if (m_Keyboard->KeyPressed(KB_NUM_3)) {
    //    m_Camera->SetViewMode(Engine::Camera::ViewMode::VIEW_TOP);
    //}
    //if (m_Keyboard->KeyPressed(KB_NUM_4)) {
    //    m_Camera->SetViewMode(Engine::Camera::ViewMode::VIEW_RIGHT);
    //}
    //if (m_Keyboard->KeyPressed(KB_NUM_5)) {
    //    m_Camera->SetViewMode(Engine::Camera::ViewMode::VIEW_FRONT);
    //}
    //if (m_Keyboard->KeyPressed(KB_NUM_6)) {
    //    m_Camera->Reset();
    //}
    //



    //if (m_Keyboard->KeyDown(KB_KEY_0)) {
    //    if (radius >= 0.2f) {
    //        radius += speed * dt;
    //        m_Camera->SetOrbitalAxis(radius, theta, phi);
    //    }
    //    
    //}
    //if (m_Keyboard->KeyDown(KB_KEY_9)) {
    //    if (radius >= 0.2f) {
    //        radius -= speed * dt;
    //        m_Camera->SetOrbitalAxis(radius, theta, phi);
    //    }
    //}

    //if (m_Keyboard->KeyDown(KB_NUM_ADD)) {
    //    if (theta < XMConvertToRadians(180)) {
    //        theta += XMConvertToRadians(4 * speed * dt);
    //        m_Camera->SetOrbitalAxis(radius, theta, phi);
    //    } 
    //    else {
    //        theta = XMConvertToRadians(-180);
    //    }
    //}

    //if (m_Keyboard->KeyDown(KB_NUM_SUB)) {
    //    if (theta > XMConvertToRadians(-180)) {
    //        theta -= XMConvertToRadians(4 * speed * dt);
    //        m_Camera->SetOrbitalAxis(radius, theta, phi);
    //    }
    //    else {
    //        theta = XMConvertToRadians(180);
    //    }
    //}

    //if (m_Keyboard->KeyDown(KB_NUM_MUL)) {
    //    if (phi < XMConvertToRadians(90)) {
    //        phi += XMConvertToRadians(2 * speed * dt);
    //        m_Camera->SetOrbitalAxis(radius, theta, phi);
    //    }
    //}

    //if (m_Keyboard->KeyDown(KB_NUM_DIV)) {
    //    if (phi > XMConvertToRadians(-90)) {
    //        phi -= XMConvertToRadians(2 * speed * dt);
    //        m_Camera->SetOrbitalAxis(radius, theta, phi);
    //    }
    //}
    //
    //

    //DirectX::XMStoreFloat4x4(&viewproj, m_Camera->GetViewMatrix() * m_Camera->GetProjectionMatrix());
    //DirectX::XMMATRIX m = m_Camera->GetViewMatrix() * m_Camera->GetProjectionMatrix();
    //std::stringstream out2;
    //for (int i = 0; i < 4; i++) {
    //    XMFLOAT4 r;
    //    DirectX::XMStoreFloat4(&r, m.r[i]);

    //    out2 << "[" << r.x << ", " << r.y << ", " << r.z << ", " << r.w << "]" << std::endl;
    //}

    //cameraMatrices->SetText(out2.str());
}

//FixedUpdate is called at a constant rate.
void Game::FixedUpdate(float dt)
{
    //float speed = 150.0f;
    //if (m_Keyboard->KeyDown(KB_DIR_UP)) {
    //    sprite2->SpritePosition().y -= speed * dt;
    //    sprite2->SetClip("Walking_Up");
    //}
    //if (m_Keyboard->KeyDown(KB_DIR_DOWN)) {
    //    sprite2->SpritePosition().y += speed * dt;
    //    sprite2->SetClip("Walking_Down");
    //}
    //if (m_Keyboard->KeyDown(KB_DIR_LEFT)) {
    //    sprite2->SpritePosition().x -= speed * dt;
    //    //sprite2->SetClip("NULL");
    //    sprite2->SetClip("Walking_Left");
    //}
    //if (m_Keyboard->KeyDown(KB_DIR_RIGHT)) {
    //    sprite2->SpritePosition().x += speed * dt;
    //    sprite2->SetClip("Walking_Right");
    //}
    //if (m_Keyboard->KeyPressed(KB_KEY_SPACE)) {
    //    //sprite2->SetPosition(0, 0);
    //    sprite2->SetClip("Idle");
    //}
}


//Exit is called before the application shuts down.
void Game::Exit()
{

}

