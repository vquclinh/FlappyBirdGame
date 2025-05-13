#include "UI.h"

UI::UI()
    : window(sf::VideoMode(Screen_w, Screen_h), "Flappy Bird"),
    currentState(ScreenState::MAINMENU),
    menu(window),      // Truyền window vào constructor của MenuScreen
    settings(window),  // Truyền window vào constructor của SettingsScreen
    about(window)      // Truyền window vào constructor của AboutScreen
{
    window.setFramerateLimit(60);  // Giới hạn số khung hình
}

void UI::run() {
    while (window.isOpen()) {
        processEvents();  // Xử lý sự kiện
        update();         // Cập nhật trạng thái
        render();         // Vẽ lại cửa sổ
    }
}

void UI::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();  // Đóng cửa sổ nếu nhận sự kiện đóng

        switch (currentState) {
        case ScreenState::MAINMENU:
            menu.handleEvent(event, currentState);  // Xử lý sự kiện cho màn hình menu
            break;
        case ScreenState::SETTINGS:
            settings.handleEvent(event, currentState);  // Xử lý sự kiện cho màn hình cài đặt
            break;
        case ScreenState::ABOUT:
            about.handleEvent(event, currentState);  // Xử lý sự kiện cho màn hình giới thiệu
            break;
        case ScreenState::GAMEPLAY:
            // TODO: Xử lý sự kiện cho gameplay
            break;
        }
    }
}

void UI::update() {
    switch (currentState) {
    case ScreenState::MAINMENU:
        menu.update();  // Cập nhật màn hình menu
        break;
    case ScreenState::SETTINGS:
        settings.update();  // Cập nhật màn hình cài đặt
        break;
    case ScreenState::ABOUT:
        about.update();  // Cập nhật màn hình giới thiệu
        break;
    case ScreenState::GAMEPLAY:
        // TODO: Cập nhật trạng thái gameplay
        break;
    }
}

void UI::render() {
    window.clear();  // Xóa màn hình

    switch (currentState) {
    case ScreenState::MAINMENU:
        menu.draw();  // Vẽ menu
        break;
    case ScreenState::SETTINGS:
        settings.draw();  // Vẽ cài đặt
        break;
    case ScreenState::ABOUT:
        about.draw();  // Vẽ giới thiệu
        break;
    case ScreenState::GAMEPLAY:
        // TODO: Vẽ gameplay
        break;
    }

    window.display();  // Hiển thị nội dung lên cửa sổ
}
