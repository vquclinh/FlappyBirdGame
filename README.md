# 🐦 Flappy Bird - SFML C++ Version

This is a Flappy Bird clone built using **C++14** and **SFML 2.6.2**, designed for learning game development and testing reusable components for future personal game projects.

---

## 🎯 Purpose

- Practice 2D game development with C++ and SFML.
- Explore modular code organization (separating UI, game screens, entities).
- Prototype systems like screen managers, UI handling, and scoring logic.

---

## 🛠️ Technologies Used

- **Language**: C++14
- **Graphics Library**: [SFML 2.6.2](https://www.sfml-dev.org/)
- **Operating System**: Windows
- **Compiler / IDE**: Visual Studio
- **Package Manager**: [vcpkg](https://github.com/microsoft/vcpkg)

---

## 📦 Installation & Build

### Project Structure
```
FlappyBird-SFML/
├── Assets/
│   ├── Fonts/
│   │   └── LilitaOne-Regular.ttf
│   ├── Images/
│   │   └── background.png
│   │   └── bird1.png
│   │   └── bird2.png
│   │   └── pipe1.png
│   │   └── pipe2.png
│   └── Sounds/
│       └── backgroundsound.mp3
│
├── Src/
│   ├── External/
│   │   ├── TextBox.h
│   │   └── TextBox.cpp
│   │   └── RoundedRectangleShape.h
│       └── RoundedRectangleShape.cpp
│
│   ├── Screens/
│   │   ├── AboutScreen/
│   │   │   └── AboutScreen.h
│   │   │   └── AboutScreen.cpp
│   │    
│   │   ├── MenuScreen/
│   │   │   └── MenuScreen.h
│   │   │   └── MenuScreen.cpp
│   │   
│   │   ├── PlayScreen/
│   │   │   └── PlayScreen.h
│   │   │   └── PlayScreen.cpp
│   │   │   └── Bird.h
│   │   │   └── Bird.cpp
│   │   │   └── PipeManager.h
│   │   │   └── PipeManager.cpp
│   │   │   └── ScoreManager.h
│   │   │   └── ScoreManager.cpp
│   │   
│   │   └── SettingsScreen/
│   │   │   └── SettingsScreen.h
│   │   │   └── SettingsScreen.cpp
│   │
│   ├── UI/
│   │   └── UI.h
│   │   └── UI.cpp
│   │   └── Constants.h
│   │   └── Constants.cpp
│   │   └── main.cpp
```

### How to Run
Once successfully built, you can run the game via:
Visual Studio (Debug → Start Without Debugging), or
The generated executable file (e.g., FlappyBird.exe).
Make sure the Assets folder is in the same directory as the executable.

## Author
- Leader and Developer: Vo Quoc Linh, Student at APCS (Advanced Program in Computer Science), University of Science - Vietnam National University, Ho Chi Minh City.
- UI Designer: Nguyen Thanh Nhat, Student at Information Technology, University of Science - VietNam National University, Ho Chi Minh City.

## License
This project is the intellectual property of the author.
Please do not use for commercial purposes without permission.