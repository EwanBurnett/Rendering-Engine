#include "Camera.h"

using namespace DirectX;
using namespace Engine;

Engine::Camera::Camera()
{
    //TODO: Initialize member variables
    Reset();
    m_ViewMode = ViewMode::VIEW_PERSPECTIVE;
}

void Engine::Camera::Update(float dt)
{
    //Calculate the camera's view and projection matrices once per frame.

    XMVECTOR upVector = XMLoadFloat3(&m_UpVector);

    XMVECTOR position = XMLoadFloat3(&m_Position);

    XMVECTOR direction = XMVectorZero();

    XMVECTOR targetPos = XMVectorZero();

    XMFLOAT3 directionCache;


    //Generally speaking, the main difference between the view modes are their directions. With the exception of the Orbital camera.
    switch (m_ViewMode) {
    case(ViewMode::VIEW_PERSPECTIVE):
        direction = XMLoadFloat3(&m_Direction);
        break;

    case(ViewMode::VIEW_ORBIT):
        //Calculate the base direction of the camera target
        targetPos = XMLoadFloat3(&m_TargetPos);
        direction = position - targetPos;

        //Orbit the camera about its origin point
        Orbit();
        position = XMLoadFloat3(&m_OrbitalPosition);
        break;

    case(ViewMode::VIEW_TARGET):
        //Target mode will lock the camera's direction to a target position.
        targetPos = XMLoadFloat3(&m_TargetPos);
        direction = position - targetPos;
        break;

    case(ViewMode::VIEW_TOP):
        directionCache = m_Direction;
        directionCache.y = -1;
        direction = XMLoadFloat3(&directionCache);
        
        break;

    case(ViewMode::VIEW_RIGHT):
        directionCache = m_Direction;
        directionCache.x = -1;
        direction = XMLoadFloat3(&directionCache);

        break;

    case(ViewMode::VIEW_FRONT):
        directionCache = m_Direction;
        directionCache.z = -1;
        direction = XMLoadFloat3(&directionCache);

        break;

    default:
        break;
    }

    //Work out the resultant view matrix, and store it
    XMMATRIX viewMatrix = XMMatrixLookAtLH(position, position + direction, upVector);
    XMMATRIX orientation = XMMatrixRotationRollPitchYaw(m_Pitch, -m_Yaw, m_Roll);

    XMStoreFloat4x4(&m_ViewMatrix, viewMatrix * orientation);

    //Work out the Projection Matrix, and store it
    XMStoreFloat4x4(&m_ProjMatrix, XMMatrixPerspectiveFovLH(XMConvertToRadians(m_FoV), m_AspectRatio, m_NearPlane, m_FarPlane));
    
}

void Engine::Camera::Reset()
{
    XMStoreFloat3(&m_Position, XMVectorSet(0, 0, 0, 1));
    XMStoreFloat3(&m_Direction, XMVectorSet(0, 0, -1, 1));
    XMStoreFloat3(&m_UpVector, XMVectorSet(0, 1, 0, 1));
    m_Roll = 0.0f;
    m_Pitch = 0.0f;
    m_Yaw = 0.0f;
    m_Speed = 5.0f;

    SetCameraView(90.0f, 16.0f / 9.0f, 0.1f, 50.0f);
    SetOrbitalAxis(10.0f, 0.0f, 0.0f);
}

DirectX::XMMATRIX Engine::Camera::GetViewProjMatrix()
{
    FXMMATRIX viewMatrix = XMLoadFloat4x4(&m_ViewMatrix);
    FXMMATRIX projMatrix = XMLoadFloat4x4(&m_ProjMatrix);
    return XMMatrixMultiply(viewMatrix, projMatrix);
}

void Engine::Camera::SetViewMode(ViewMode mode)
{
    m_ViewMode = mode;
}

void Engine::Camera::SetPosition(float x, float y, float z)
{
    m_Position.x = x;
    m_Position.y = y;
    m_Position.z = z;
}

void Engine::Camera::SetPosition(DirectX::FXMVECTOR position)
{
    XMStoreFloat3(&m_Position, position);
}

DirectX::XMFLOAT3& Engine::Camera::Position()
{
    return(m_Position);
}

void Engine::Camera::SetRollPitchYaw(float roll, float pitch, float yaw)
{
    m_Roll = roll;
    m_Pitch = pitch;
    m_Yaw = yaw;
}

void Engine::Camera::SetSpeed(float speed)
{
    m_Speed = speed;
}

void Engine::Camera::SetUpVector(float x, float y, float z)
{
    m_UpVector.x = x;
    m_UpVector.y = y;
    m_UpVector.z = z;
}

void Engine::Camera::SetCameraView(float fieldOfView, float aspectRatio, float nearPlane, float farPlane)
{
    m_FoV = fieldOfView;
    m_AspectRatio = aspectRatio;
    m_NearPlane = nearPlane;
    m_FarPlane = farPlane;
}

void Engine::Camera::SetOrbitalAxis(float radius, float theta, float phi)
{
    m_Radius = radius;
    m_Theta = theta;
    m_Phi = phi;
}

void Engine::Camera::Orbit()
{
    //Calculate the orbital camera's values
    if (m_Radius <= 0) {
        m_Radius = 0.1f;    //Ensure the radius isn't less than or equal to 0
    }

    XMVECTOR orbitPos = XMVector3Transform(
        XMVectorSet(m_Position.x, m_Position.y, m_Position.z - m_Radius, 1.0f),
        XMMatrixRotationRollPitchYaw(m_Phi, -m_Theta, 0.0f)
    );

    DirectX::XMStoreFloat3(&m_OrbitalPosition, orbitPos);
}
