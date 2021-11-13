//Camera Component
//Ewan Burnett 2021

#pragma once
#include <Windows.h>
#include <DirectXMath.h>
#include "GameComponent.h"

namespace Engine {
    class Camera : public GameComponent {
    public:
        enum class ViewMode {
            VIEW_PERSPECTIVE = 0,
            VIEW_ORBIT,
            VIEW_TARGET,
            VIEW_TOP,
            VIEW_RIGHT,
            VIEW_FRONT
        };

        Camera();
        ~Camera() = default;
        
        void Update(float dt) override;

        void Reset();   //Resets the camera to its default position and orientation.

        DirectX::XMMATRIX GetViewProjMatrix(); //Returns the ViewProj matrix.

        //Setter Methods
        void SetViewMode(ViewMode mode);

        void SetPosition(float x = 0, float y = 0, float z = 0);
        void SetPosition(DirectX::FXMVECTOR position);
        DirectX::XMFLOAT3& Position();

        void SetRollPitchYaw(float roll = 0, float pitch = 0, float yaw = 0);
        void SetSpeed(float speed);
        void SetUpVector(float x, float y, float z);
        void SetCameraView(float fieldOfView, float aspectRatio, float nearPlane, float farPlane);
        void SetOrbitalAxis(float radius, float theta, float phi);

    private:
        //Matrix Cache
        DirectX::XMFLOAT4X4 m_ViewMatrix;
        DirectX::XMFLOAT4X4 m_ProjMatrix;

        //Standard Camera Parameters 
        float m_FoV;
        float m_AspectRatio;
        float m_NearPlane;
        float m_FarPlane;

        float m_Roll;
        float m_Pitch;
        float m_Yaw;
        float m_Speed;

        ViewMode m_ViewMode;

        //Camera Vectors
        DirectX::XMFLOAT3 m_Position;
        DirectX::XMFLOAT3 m_Direction;
        DirectX::XMFLOAT3 m_UpVector;
        DirectX::XMFLOAT3 m_RightVector;
        DirectX::XMFLOAT3 m_TargetPos;
        
        //Orbital Camera Parameters (Only used in VIEW_ORBIT)
        DirectX::XMFLOAT3 m_OrbitalPosition;

        float m_Radius; 
        float m_Phi;    //Orbital camera pitch (Y axis)
        float m_Theta;  //Orbital camera roll (X axis)

    private:
        void Orbit();
    };
}