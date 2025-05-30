#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include "../UI/Constants.h"

class TextBox {
private:
    sf::RectangleShape box;        // Hình chữ nhật làm nền TextBox
    sf::Text text;                 // Văn bản hiển thị
    sf::Font* font;                // Con trỏ tới phông chữ
    std::string inputString;       // Chuỗi người dùng nhập
    bool isSelected;               // Trạng thái được chọn
    float cursorTimer;             // Thời gian để điều khiển nhấp nháy con trỏ
    bool showCursor;               // Có hiển thị con trỏ không
    std::string displayString;

    void updateTextPosition();
    void updateDisplayString();
public:
    TextBox(sf::Vector2f position, sf::Vector2f size, sf::Font* font, unsigned int fontSize);
    void handleEvent(sf::Event event); // Xử lý sự kiện bàn phím và chuột
    void update(float deltaTime);      // Cập nhật trạng thái con trỏ
    void draw(sf::RenderWindow& window); // Vẽ TextBox
    std::string getText() const;       // Lấy chuỗi đã nhập
    void setSelected(bool selected);   // Đặt trạng thái chọn
    void setPosition(const sf::Vector2f& position);
    void setSize(const sf::Vector2f& size);
};
