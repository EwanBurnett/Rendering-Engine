#pragma once

namespace Engine {
    class GameComponent {
    public:
        typedef unsigned long ComponentID;

        GameComponent();
        virtual ~GameComponent();

        bool IsEnabled() const;
        void SetEnabled(bool state);

        virtual void Init();
        virtual void Update(float dt);
        virtual void FixedUpdate(float dt);
        virtual void Draw(float dt);

    protected:
        bool m_bEnabled;
    };
}