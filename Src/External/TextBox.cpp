#include "TextBox.h"

TextBox::TextBox(sf::Vector2f position, sf::Vector2f size, sf::Font* font, unsigned int fontSize) {
    this->font = font;
    isSelected = false;
    cursorTimer = 0.0f;
    showCursor = false;
    float centerY = box.getPosition().y + (box.getSize().y - text.getLocalBounds().height) / 2 - text.getLocalBounds().top;

    // Thiết lập hình chữ nhật
    box.setPosition(position);
    box.setSize(size);
    box.setFillColor(sf::Color::White);
    box.setOutlineColor(sf::Color::Black);
    box.setOutlineThickness(2.0f);

    // Thiết lập văn bản
    text.setFont(*font);
    text.setCharacterSize(fontSize - 7);
    text.setFillColor(sf::Color::Black);
    float paddingX = 5.0f;

    float textHeight = font->getLineSpacing(fontSize); // Dòng cao chuẩn của font
    float textY = position.y + (box.getSize().y - textHeight) / 2.f - 2.f;

    text.setPosition(position.x + 5.0f, textY);
}

void TextBox::handleEvent(sf::Event event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
        // Kiểm tra xem chuột có click vào TextBox không
        isSelected = box.getGlobalBounds().contains(mousePos);
    }
    else if (isSelected && event.type == sf::Event::TextEntered) {
        if (event.text.unicode < 128 && event.text.unicode >= 32) { // Ký tự ASCII in được
            inputString += static_cast<char>(event.text.unicode);
            updateDisplayString();
        }
    }
    else if (isSelected && event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Backspace && !inputString.empty()) {
            inputString.pop_back();
            updateDisplayString();
        }
        else if (event.key.code == sf::Keyboard::Enter) {
            isSelected = false; // Thoát chế độ nhập khi nhấn Enter
            playerName = inputString;
        }
    }

    // Cập nhật văn bản hiển thị
    text.setString(displayString);

    updateTextPosition();
}

void TextBox::update(float deltaTime) {
    if (isSelected) {
        cursorTimer += deltaTime;
        if (cursorTimer >= 0.5f) { // Nhấp nháy mỗi 0.5 giây
            showCursor = !showCursor;
            cursorTimer = 0.0f;
        }
    }
    else {
        showCursor = false;
    }
}

void TextBox::draw(sf::RenderWindow& window) {
    window.draw(box);
    window.draw(text);

    // Vẽ con trỏ nếu đang chọn
    if (isSelected && showCursor) {
        sf::Text cursorText("|", *font, text.getCharacterSize());
        cursorText.setFillColor(sf::Color::Black);

        float cursorX = text.getPosition().x + text.getLocalBounds().width - 4.f;
        float cursorY = text.getPosition().y - 2.f;

        cursorText.setPosition(cursorX, cursorY);
        window.draw(cursorText);
    }
}

std::string TextBox::getText() const {
    return inputString;
}

void TextBox::setSelected(bool selected) {
    isSelected = selected;
}

void TextBox::setPosition(const sf::Vector2f& position) {
    box.setPosition(position);

    float paddingX = 5.0f;
    float lineSpacing = font->getLineSpacing(text.getCharacterSize());
    float textY = position.y + (box.getSize().y - lineSpacing) / 2.f;

    text.setPosition(position.x + paddingX, textY);
    updateTextPosition();
}

void TextBox::setSize(const sf::Vector2f& size) {
    box.setSize(size);

    float paddingX = 5.0f;
    float lineSpacing = font->getLineSpacing(text.getCharacterSize());
    float textY = box.getPosition().y + (size.y - lineSpacing) / 2.f;

    text.setPosition(box.getPosition().x + paddingX, textY);
    updateTextPosition();
}

void TextBox::updateTextPosition() {
    float paddingX = 5.0f;
    float lineSpacing = font->getLineSpacing(text.getCharacterSize());
    float textY = box.getPosition().y + (box.getSize().y - lineSpacing) / 2.f;

    // Vị trí mặc định
    float textX = box.getPosition().x + paddingX;
    text.setPosition(textX, textY);
}


void TextBox::updateDisplayString() {
    displayString = inputString;
    text.setString(displayString);

    float padding = 10.0f;
    float maxWidth = box.getSize().x - 2 * padding;

    // Cắt đầu chuỗi cho đến khi phần cuối vừa với khung textbox
    while (text.getLocalBounds().width > maxWidth && displayString.length() > 1) {
        displayString.erase(0, 1);
        text.setString(displayString);
    }

    updateTextPosition();
}
