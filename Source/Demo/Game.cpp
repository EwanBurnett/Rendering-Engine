#include "Game.h"
#include <Components/FPSComponent.h>
#include <Components/AnimatedSpriteComponent.h>
#include <Components/ModelComponent.h>
#include <Components/TextComponent.h>

using namespace Engine;

FPSComponent* fpsComponent;
AnimatedSpriteComponent* animation;
TextComponent* controls;
ModelComponent* skysphere;
ModelComponent* planets[50];
ModelComponent* crystal;

//Init is called when the application is started.
void Game::Init()
{   
    //Skysphere - this mesh is always bound to the camera's position, and acts as a backdrop.
    skysphere = new ModelComponent(m_Graphics.get(), m_Camera);
    skysphere->SetModelPath("D:\\University\\Projects\\Year 2\\Rendering Engine\\Build\\Debug\\Content\\Models\\Sphere.fbx");
    skysphere->SetTexture(L"D:\\University\\Projects\\Year 2\\Rendering Engine\\Build\\Debug\\Content\\Textures\\Galaxy.dds");
    skysphere->SetScale(4000, 4000, 4000);
    m_Components.push_back(skysphere);

    //Debug Framerate Profiler
    fpsComponent = new FPSComponent(&m_Time, m_Graphics.get());
    fpsComponent->SetPosition(10, 10);
    //m_Components.push_back(fpsComponent);

    //Animated Fire Sprite
    animation = new AnimatedSpriteComponent(m_Graphics.get());
    animation->SetSprite(L"D:\\University\\Projects\\Year 2\\Rendering Engine\\Build\\Debug\\Content\\Textures\\Fire.dds");
    animation->SetPosition(10, 400);
    animation->SetScale(6);
    animation->AddClip("Burn", { 64, 64, 640, 364 }, (1.0f / 24.0f), 0, 60);
    animation->SetClip("Burn");
    //m_Components.push_back(animation);

    //Planet Meshes
    for (int i = 0; i < std::size(planets); i++) {
        planets[i] = new ModelComponent(m_Graphics.get(), m_Camera);
        planets[i]->SetModelPath("D:\\University\\Projects\\Year 2\\Rendering Engine\\Build\\Debug\\Content\\Models\\Sphere.fbx");
        planets[i]->SetTexture(L"Invalid Texture Path");
        planets[i]->SetScale(i % 10, i % 10, i % 10);
        planets[i]->SetTranslation(cos(i) * 100, tan(i) * 50, sin(i) * 100);
        m_Components.push_back(planets[i]);
    }

    //Crystal Mesh
    crystal = new ModelComponent(m_Graphics.get(), m_Camera);
    crystal->SetModelPath("D:\\University\\Projects\\Year 2\\Rendering Engine\\Build\\Debug\\Content\\Models\\rune_stone_low.fbx");
    crystal->SetTexture(L"D:\\University\\Projects\\Year 2\\Rendering Engine\\Build\\Debug\\Content\\Textures\\Crystal.dds");
    crystal->SetScale(10, 10, 10);
    crystal->SetTranslation(0, 0, 0);
    crystal->SetRotation(45, 0, 20);
    m_Components.push_back(crystal);

    controls = new TextComponent(m_Graphics.get());
    controls->SetColor(0.1f, 0.8f, 0.6f);
    controls->SetPosition(800, 10);
    controls->SetText("Directional Arrow Keys and Numpad + and - to orbit the camera. Spritebatch messes with render states, so hit F5 to toggle.");

}

//Update is called once per frame. 
void Game::Update(float dt)
{
    static float radius = 100;
    static float phi;
    static float theta;
    static float speed = 30;

    m_Camera->SetViewMode(Camera::ViewMode::VIEW_ORBIT);
    if (m_Keyboard->KeyDown(KB_DIR_UP)) {
        phi -= XMConvertToRadians(speed * dt);        
    }

    if (m_Keyboard->KeyDown(KB_DIR_DOWN)) {
        phi += XMConvertToRadians(speed * dt);
    }

    if (m_Keyboard->KeyDown(KB_DIR_LEFT)) {
        theta -= XMConvertToRadians(speed * dt);
    }

    if (m_Keyboard->KeyDown(KB_DIR_RIGHT)) {
        theta += XMConvertToRadians(speed * dt);
    }

    if (m_Keyboard->KeyDown(KB_NUM_ADD)) {
        radius += speed * dt;
    }
    if (m_Keyboard->KeyDown(KB_NUM_SUB)) {
        radius -= speed * dt;
    }

    m_Camera->SetOrbitalAxis(radius, theta, phi);
}

//FixedUpdate is called at a constant rate.
void Game::FixedUpdate(float dt)
{
    //Update the sky sphere's position to match that of the camera.
    skysphere->SetTranslation(m_Camera->Position().x, m_Camera->Position().y, m_Camera->Position().z);

    static float rotx = 0;
    static float roty = 0;
    static float rotz = 0;
    static float rotspeed = 15;

    rotx += rotspeed * dt;
    roty -= rotspeed * dt;
    rotz += rotspeed * dt;

    crystal->SetRotation(rotx, roty, rotz);

    if (m_Keyboard->KeyPressed(KB_FNC_F5)) {
        controls->SetEnabled(!controls->IsEnabled());
        animation->SetEnabled(!animation->IsEnabled());
        fpsComponent->SetEnabled(!fpsComponent->IsEnabled());
    }
}


//Exit is called before the application shuts down.
void Game::Exit()
{
}

