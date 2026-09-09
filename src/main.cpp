#include <Arduino.h>
#include <TFT_eSPI.h>

// ============================================
// Touch Paint - Матрица для рисования
// ESP32-S3 с сенсорными кнопками (GPIO1-GPIO14)
// Дисплей: GC9A01 (240x240)
// ============================================

// Конфигурация сетки
#define GRID_COLS 4
#define GRID_ROWS 4
#define CELL_SIZE 50
#define THRESHOLD 40000  // Порог срабатывания сенсора

// Сенсорные пины для сетки (GPIO1-GPIO16)
const int touchPins[GRID_COLS * GRID_ROWS] = {
    GPIO_NUM_1,  GPIO_NUM_2,  GPIO_NUM_3,  GPIO_NUM_4,
    GPIO_NUM_5,  GPIO_NUM_6,  GPIO_NUM_7,  GPIO_NUM_8,
    GPIO_NUM_9,  GPIO_NUM_10, GPIO_NUM_11, GPIO_NUM_12,
    GPIO_NUM_13, GPIO_NUM_14, GPIO_NUM_15, GPIO_NUM_16
};

// Матрица состояния ячеек (нажата/не нажата)
bool grid[GRID_ROWS][GRID_COLS] = {false};

// Дополнительные кнопки управления
#define CLEAR_BTN GPIO_NUM_17    // Очистить всё
#define INVERT_BTN GPIO_NUM_18   // Инвертировать цвета

// Переменные состояния
bool lastClearState = false;
bool lastInvertState = false;
bool invertColors = false;
unsigned long lastUpdateTime = 0;
const unsigned long UPDATE_INTERVAL = 50; // мс между обновлениями

TFT_eSPI tft = TFT_eSPI();

// ============================================
// Прототипы функций
// ============================================
void drawGrid();
void checkTouches();
void drawCell(int row, int col);
void clearGrid();
void invertGrid();
void displayInfo();

// ============================================
// Инициализация
// ============================================
void setup() {
    Serial.begin(115200);
    delay(1000);
    
    Serial.println("\n\n=== Touch Paint - ESP32-S3 ===");
    Serial.println("Инициализация дисплея...");
    
    // Инициализация дисплея
    tft.init();
    tft.setRotation(0);
    tft.fillScreen(TFT_BLACK);
    
    Serial.println("Дисплей готов!");
    Serial.println("Инициализация сенсорных пинов...");
    
    // Инициализация сенсорных пинов (если требуется)
    // Большинство пинов ESP32-S3 поддерживают touch по умолчанию
    
    Serial.println("Готово! Используйте сенсорные кнопки для рисования.");
    Serial.println("GPIO1-GPIO16: рисование");
    Serial.println("GPIO17: очистить");
    Serial.println("GPIO18: инвертировать");
    
    displayInfo();
    drawGrid();
}

// ============================================
// Основной цикл
// ============================================
void loop() {
    unsigned long currentTime = millis();
    
    // Проверка сенсоров с ограничением по времени
    if (currentTime - lastUpdateTime >= UPDATE_INTERVAL) {
        checkTouches();
        drawGrid();
        lastUpdateTime = currentTime;
    }
    
    delay(10);
}

// ============================================
// Отрисовка сетки
// ============================================
void drawGrid() {
    tft.fillScreen(TFT_BLACK);
    
    // Отрисовка заголовка
    tft.setTextColor(TFT_CYAN);
    tft.setTextSize(1);
    tft.setCursor(5, 5);
    tft.print("Touch Paint");
    
    // Отрисовка индикатора режима
    if (invertColors) {
        tft.setTextColor(TFT_YELLOW);
        tft.setCursor(150, 5);
        tft.print("[INVERT]");
    }
    
    // Отрисовка ячеек сетки
    for (int row = 0; row < GRID_ROWS; row++) {
        for (int col = 0; col < GRID_COLS; col++) {
            int x = col * CELL_SIZE;
            int y = 25 + row * CELL_SIZE;  // +25 для отступа сверху
            
            drawCell(row, col);
        }
    }
    
    // Отрисовка информации внизу
    tft.setTextColor(TFT_WHITE);
    tft.setTextSize(1);
    tft.setCursor(5, 225);
    tft.print("CLR:[17] INV:[18]");
}

// ============================================
// Отрисовка одной ячейки
// ============================================
void drawCell(int row, int col) {
    int x = col * CELL_SIZE;
    int y = 25 + row * CELL_SIZE;
    
    uint32_t fillColor, borderColor;
    
    if (grid[row][col]) {
        // Ячейка нажата
        fillColor = invertColors ? TFT_BLACK : TFT_WHITE;
        borderColor = invertColors ? TFT_WHITE : TFT_BLUE;
    } else {
        // Ячейка не нажата
        fillColor = invertColors ? TFT_WHITE : TFT_BLACK;
        borderColor = invertColors ? TFT_DARKGREY : TFT_GREY;
    }
    
    tft.fillRect(x, y, CELL_SIZE, CELL_SIZE, fillColor);
    tft.drawRect(x, y, CELL_SIZE, CELL_SIZE, borderColor);
}

// ============================================
// Проверка сенсорных входов
// ============================================
void checkTouches() {
    // Проверка основной сетки (GPIO1-GPIO16)
    for (int i = 0; i < GRID_COLS * GRID_ROWS; i++) {
        uint32_t touchValue = touchRead(touchPins[i]);
        int row = i / GRID_COLS;
        int col = i % GRID_COLS;
        
        bool pressed = (touchValue < THRESHOLD);
        
        // Обновляем состояние только при изменении
        if (pressed && !grid[row][col]) {
            grid[row][col] = true;
            Serial.printf("Touch: GPIO%d (Row:%d, Col:%d) Value:%d\n", 
                         touchPins[i], row, col, touchValue);
        } else if (!pressed && grid[row][col]) {
            grid[row][col] = false;
        }
    }
    
    // Проверка кнопки очистки (GPIO17)
    uint32_t clearValue = touchRead(CLEAR_BTN);
    bool clearPressed = (clearValue < THRESHOLD);
    
    if (clearPressed && !lastClearState) {
        clearGrid();
        Serial.println("Сетка очищена!");
    }
    lastClearState = clearPressed;
    
    // Проверка кнопки инвертирования (GPIO18)
    uint32_t invertValue = touchRead(INVERT_BTN);
    bool invertPressed = (invertValue < THRESHOLD);
    
    if (invertPressed && !lastInvertState) {
        invertGrid();
        Serial.println(invertColors ? "Цвета инвертированы: ВКЛ" : "Цвета инвертированы: ВЫКЛ");
    }
    lastInvertState = invertPressed;
}

// ============================================
// Очистка сетки
// ============================================
void clearGrid() {
    for (int row = 0; row < GRID_ROWS; row++) {
        for (int col = 0; col < GRID_COLS; col++) {
            grid[row][col] = false;
        }
    }
}

// ============================================
// Инвертирование цветов и всей сетки
// ============================================
void invertGrid() {
    invertColors = !invertColors;
    
    for (int row = 0; row < GRID_ROWS; row++) {
        for (int col = 0; col < GRID_COLS; col++) {
            grid[row][col] = !grid[row][col];
        }
    }
}

// ============================================
// Вывод информации в Serial
// ============================================
void displayInfo() {
    Serial.println("\n╔════════════════════════════════════════╗");
    Serial.println("║       Touch Paint - ESP32-S3          ║");
    Serial.println("╚════════════════════════════════════════╝");
    Serial.println();
    Serial.println("📋 УПРАВЛЕНИЕ:");
    Serial.println("  • GPIO1-GPIO4   → Строка 1");
    Serial.println("  • GPIO5-GPIO8   → Строка 2");
    Serial.println("  • GPIO9-GPIO12  → Строка 3");
    Serial.println("  • GPIO13-GPIO16 → Строка 4");
    Serial.println();
    Serial.println("⚙️  КНОПКИ:");
    Serial.println("  • GPIO17 → Очистить сетку");
    Serial.println("  • GPIO18 → Инвертировать цвета");
    Serial.println();
    Serial.println("📊 ХАРАКТЕРИСТИКИ:");
    Serial.printf("  • Сетка: %d x %d ячеек\n", GRID_COLS, GRID_ROWS);
    Serial.printf("  • Размер ячейки: %d x %d пикселей\n", CELL_SIZE, CELL_SIZE);
    Serial.printf("  • Порог сенсора: %d\n", THRESHOLD);
    Serial.printf("  • Интервал обновления: %lums\n", UPDATE_INTERVAL);
    Serial.println();
}

// ============================================
// Дополнительная функция: вывод значений сенсоров
// ============================================
void calibrateSensors() {
    Serial.println("\n📏 КАЛИБРОВКА СЕНСОРОВ:");
    Serial.println("Значения при расстоянии 2-3см от пи��а:");
    Serial.println();
    
    for (int i = 0; i < GRID_COLS * GRID_ROWS; i++) {
        uint32_t value = touchRead(touchPins[i]);
        Serial.printf("GPIO%2d: %5d %s\n", 
                     touchPins[i], 
                     value,
                     value < THRESHOLD ? "[ACTIVE]" : "");
    }
    
    uint32_t clearValue = touchRead(CLEAR_BTN);
    Serial.printf("GPIO%2d (CLEAR): %5d %s\n", CLEAR_BTN, clearValue, 
                 clearValue < THRESHOLD ? "[ACTIVE]" : "");
    
    uint32_t invertValue = touchRead(INVERT_BTN);
    Serial.printf("GPIO%2d (INVERT): %5d %s\n", INVERT_BTN, invertValue, 
                 invertValue < THRESHOLD ? "[ACTIVE]" : "");
    
    Serial.println();
}
