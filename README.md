# 🎓 AnimalCrossSteve 
Introduction to Computer Graphics Project – 3D Scene

👥 Group Members: Adam BELLIK, Emilie Kevine KENGNI MBOU, Floriane TANG

## 📌 Project Overview

This project was developed as part of the **"Introduction to Computer Graphics"** course. 
The goal was to design and implement an original 3D scene that integrates the concepts covered in class.

The final result is an interactive 3D scene featuring a controllable character, multiple imported models (including an animated one), and a dynamic environment.

## 🎨 Inspiration

This project **"AnimalCrossSteve"** was inspired by the artistic style of **"Animal Crossing"** and the humorous internet meme known as **"Poisson Steve"**. 

<img src="https://github.com/user-attachments/assets/f1bd455f-a01f-4191-8d1a-50b7cd845e84" alt="Poisson Steve" width="250"/>
<img src="https://github.com/user-attachments/assets/5d64de09-98bc-485c-ad51-f14b2a8e5ce0" alt="Animal crossing 1" width="250"/>
<img src="https://github.com/user-attachments/assets/1f1b6d83-9281-4900-a6eb-4b71e401092d" alt="Animal crossing 2" width="250"/>

The scene combines handmade elements with imported assets for textures and props from "Animal Crossing".

### ✅ Handmade Elements

- Character "Steve" modeled from scratch using primitives (spheres, cylinders, etc.)
- Custom shaders, animation logic, and scene graph hierarchy
- Manual composition and positioning of the scene

### 📦 Imported Assets

- **Textures for walls and floors**  
  Source: [Textures Resource](https://www.textures-resource.com/)  
  Used to create a realistic environment in the room.

- **3D models (non-animated props)**  
  Source: [Models Resource](https://www.models-resource.com/)  
  Used for some objects such as bed, sofa, guitar and clock.

---

## 📝 Features Demonstrated

| Feature            | Description                                                                 |
|--------------------|-----------------------------------------------------------------------------|
| **Modeling**       | Steve was modeled using primitive shapes and hierarchical node structure.   |
| **Texturing**      | Multiple textures applied to imported models and environment (skybox).      |
| **Lighting**       | Implemented Phong lighting on custom objects and models.                    |
| **Shaders**        | Custom GLSL shaders used (Phong, skybox, color-based).                      |
| **Animation**      | Object and character movement over time and user input.                     |
| **Camera System**  | Free camera navigation (ZQSD + mouse + space/ctrl).                         |

## 💡 Bonus Features

We implemented the following **bonus features** from the TPs:

- 🖱️ **Mouse-Controlled Camera**  
  Implemented a free-fly camera using mouse input (GLFW) to control orientation and enhance navigation.

- 📦 **Model Loading with Assimp**  
  Loaded complex 3D models (`.fbx`, `.dae`) using **Assimp**, including textures and materials. Each model is integrated via a `mesh_shape` class.

- 🏠 **Skybox Environment**  
  Created rooms' environments using **skyboxes**, with cube-mapped textures rendered via a custom GLSL shader.

- ✨ **Shader Combination**  
  Combined texturing and Phong illumination in custom shaders to render both **lit textured objects** and unlit skybox elements appropriately.

---

## 🎮 Playable Demo

The project is fully interactive. Users can:

- Control the **camera** (movement and orientation).
- Control the character **Steve** using the keyboard.
- Observe **imported 3D models** and their animations.
- Explore a scene featuring skyboxes, lights, shaders, and textures.

### Camera

| Key        | Action            |
| ---------- | ----------------- |
| Z / S      | Move forward/back |
| Q / D      | Move left/right   |
| SPACE/CTRL | Move up/down      |
| Mouse      | Look around       |
| SHIFT      | Move faster       |

### Steve (Character)

| Key   | Action                         |
| ----- | ------------------------------ |
| ↑ / ↓ | Move forward/back              |
| ← / → | Rotate body (with animation)   |
| J / L | Rotate body (without animation)|

---

## 🖼️ Scene Content

* **Character (Steve)**: Articulated using lighting spheres and cylinders.
* **Skyboxes**: Two environment textures simulating indoor scenes.
* **Imported Models**:

  * Character (FBX)
  * Bed, Sofa, TV, Guitar, Clock, Table, Bookshelf...
* **Lighting**: Phong lighting per object.
* **Shaders**: Custom GLSL vertex/fragment shaders.

---

## 🧑‍🤝‍🧑 Work Distribution

- **Adam BELLIK**
  - Developed the interactive camera system (`Camera.cpp`)
  - Set up the skybox environment and textured cube rendering
  - Managed 3D model imports using Assimp (`ModelLoader.cpp`)
  - Managed the walls' collisions and the transitions of the rooms

- **Emilie Kevine KENGNI MBOU**
  - Set up the GitHub repository for the team
  - Integrated and positioned external 3D object in the main and secondary rooms
  - Worked on the keyboard input logic for the character motion of "Steve"
  - Create the PowerPoint

- **Floriane TANG**
  - Built the character "Steve" (handled hierarchical transformations, its light and color)
  - Implemented the animation function for the character "Steve"
  - Customized and adapted the walls' and floors' texture
  - Wrote the README

---

## 📷 Preview

![preview](https://github.com/user-attachments/assets/a1b2e362-b9d2-4268-99c0-d84794894208)

---

## 🛠️ Build Instructions

### Prerequisites

- C++17 compiler
- [GLFW](https://www.glfw.org/)
- [GLEW](http://glew.sourceforge.net/)
- [GLM](https://github.com/g-truc/glm)
- [Assimp](https://github.com/assimp/assimp)

### Compilation

1. Clone the repo:
   ```bash
   git clone https://github.com/EmilieKevine/AnimalCrossSteve.git
   cd AnimalCrossSteve
   ```

2. Configure and build:

   ```bash
   mkdir build && cd build
   cmake ..
   make
   ```

3. Run the project:

   ```bash
   ./AnimalCrossSteve
   ```

---



# Skeleton code for OpenGL using C++

This is the skeleton code for creating graphics applications using OpenGL and C++.

# Installation

You would need CMake(to build our project) which can be downloaded from [here](https://cmake.org/download/).

# Setup

After cloning this repo, you also need to load the submodules GLEW, GLFW and GLM using the following command.

    git submodule update --init --recursive


## Run the Application

To launch the window, simply run:

    cmake .
    make
    ./opengl_program
