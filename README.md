Rendering Engine

# FILE STRUCTURE
```
ROOT
├─Build     -   Contains the complete output of the project
│  ├─Debug
│  └─Release
├─External  -   Any External libraries used go in here. 
│  ├─DXTK   -   DirectX Tool Kit [https://github.com/microsoft/DirectXTK]
│  │  ├─Inc
│  │  └─lib
│  ├─FX11   -   Effects11 Shader Library [https://github.com/microsoft/FX11]
│  │  ├─inc
│  │  └─lib
│  ├─ASSIMP -   Open Asset Importer Library [https://github.com/assimp/assimp]
│  │  ├─lib
│  │  └─include
│  ├─ReactPhysics3D -   React Physics 3D [https://github.com/DanielChappuis/reactphysics3d]
│  │  ├─include
│  │  └─lib
│  └─FMOD   -  FMOD Audio Library [https://www.fmod.com] 
│      ├─inc
│      └─lib
├─lib       -   Contains the built library from the Engine project
├─Content   -   Content for the Demo project. 
│  ├─GameObjects
│  ├─Effects
│  └─Resources
├─Resources -   Resources to be included in the Engine library. 
│  ├─Fonts
│  ├─Effects
│  └─Textures
└─Source    -   Source code for both the Engine library and an example Demo project.
    ├─Demo
    │  └─Resources
    │      └─Fonts
    └─Engine
        ├─Components
        ├─Backend
        ├─Build
        │  ├─Debug
        │  └─Release
        └─Utils
```

