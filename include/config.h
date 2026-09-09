#ifndef CONFIG_H
#define CONFIG_H

// ============================================
// КОНФИГУРАЦИЯ ПРОЕКТА: Touch Paint
// ESP32-S3 с сенсорными кнопками и GC9A01
// ============================================

// ============================================
// 📺 ДИСПЛЕЙ GC9A01
// ============================================
#define TFT_WIDTH           240
#define TFT_HEIGHT          240
#define TFT_ROTATION        0

// SPI пины для дисплея (измените в соответствии с вашей платой)
#define TFT_CS              10      // Chip Select
#define TFT_DC              9       // Data/Command
#define TFT_MOSI            11      // Master Out Slave In
#define TFT_SCLK            12      // Serial Clock
#define TFT_RST             14      // Reset
#define TFT_BL              15      // Backlight (опционально)

#define SPI_FREQUENCY       80000000  // 80 МГц (максимум для GC9A01)

// ============================================
// 🔘 СЕНСОРНЫЕ КНОПКИ
// ============================================

// Основная сетка 4x4 (16 кнопок)
// Строка 1: GPIO1, GPIO2, GPIO3, GPIO4
// Строка 2: GPIO5, GPIO6, GPIO7, GPIO8
// Строя 3: GPIO9, GPIO10, GPIO11, GPIO12
// Строка 4: GPIO13, GPIO14, GPIO15, GPIO16

#define GRID_COLS           4       // Колонки сетки
#define GRID_ROWS           4       // Строки сетки
#define TOUCH_PINS_GRID     {GPIO_NUM_1, GPIO_NUM_2, GPIO_NUM_3, GPIO_NUM_4, \
                             GPIO_NUM_5, GPIO_NUM_6, GPIO_NUM_7, GPIO_NUM_8, \
                             GPIO_NUM_9, GPIO_NUM_10, GPIO_NUM_11, GPIO_NUM_12, \
                             GPIO_NUM_13, GPIO_NUM_14, GPIO_NUM_15, GPIO_NUM_16}

// Дополнительные кнопки управления
#define TOUCH_CLEAR_BTN     GPIO_NUM_17    // Очистить сетку
#define TOUCH_INVERT_BTN    GPIO_NUM_18    // Инвертировать цвета

// Параметры сенсоров
#define TOUCH_THRESHOLD     40000   // Порог срабатывания (меньше = чувствительнее)
#define TOUCH_HYSTERESIS    5000    // Гистерезис для фильтрации помех

// ============================================
// 🎨 ВИЗУАЛЬНЫЕ ПАРАМЕТРЫ
// ============================================

// Размеры ячеек сетки
#define CELL_SIZE           50      // Размер одной ячейки в пикселях
#define GRID_OFFSET_X       0       // Смещение сетки по X
#define GRID_OFFSET_Y       25      // Смещение сетки по Y (место для заголовка)

// Цвета (в формате TFT_eSPI)
#define COLOR_BG            TFT_BLACK       // Фон
#define COLOR_ACTIVE        TFT_WHITE       // Активная ячейка
#define COLOR_INACTIVE      TFT_BLACK       // Неактивная ячейка
#define COLOR_BORDER_ACTIVE TFT_BLUE        // Граница активной ячейки
#define COLOR_BORDER_INACTIVE TFT_GREY      // Граница неактивной ячейки
#define COLOR_INVERT_ACTIVE TFT_BLACK       // Активная ячейка (инверт)
#define COLOR_INVERT_INACTIVE TFT_WHITE     // Неактивная ячейка (инверт)
#define COLOR_TEXT          TFT_WHITE       // Текст
#define COLOR_HEADER        TFT_CYAN        // Заголовок
#define COLOR_INDICATOR     TFT_YELLOW      // Индикаторы режимов

// ============================================
// ⏱️ ВРЕМЕННЫЕ ПАРАМЕТРЫ
// ============================================

#define UPDATE_INTERVAL     50      // Интервал обновления экрана (мс)
#define TOUCH_DEBOUNCE      100     // Защита от дребезга (мс)
#define SERIAL_BAUD_RATE    115200  // Скорость серийного порта

// ============================================
// 🔧 DEBUG И ЛОГИРОВАНИЕ
// ============================================

#define DEBUG_ENABLED       1       // 1 = включить отладку, 0 = выключить
#define DEBUG_TOUCH_VALUES  0       // Выводить ли значения сенсоров в Serial
#define DEBUG_GRID_STATE    0       // Выводить ли состояние сетки

#if DEBUG_ENABLED
  #define DEBUG_PRINT(x)      Serial.print(x)
  #define DEBUG_PRINTLN(x)    Serial.println(x)
  #define DEBUG_PRINTF(...)   Serial.printf(__VA_ARGS__)
#else
  #define DEBUG_PRINT(x)
  #define DEBUG_PRINTLN(x)
  #define DEBUG_PRINTF(...)
#endif

// ============================================
// 🌐 ИНТЕРНЕТ (опционально для будущего)
// ============================================

// Раскомментируйте для использования Wi-Fi
// #define ENABLE_WIFI         1
// #define WIFI_SSID           "YOUR_SSID"
// #define WIFI_PASSWORD       "YOUR_PASSWORD"

// ============================================
// 📊 СТРУКТУРЫ ДАННЫХ
// ============================================

// Структура для кнопки сетки
typedef struct {
    int row;
    int col;
    int gpio_pin;
    bool pressed;
    unsigned long last_press_time;
} GridButton;

// Структура для параметров сетки
typedef struct {
    int cols;
    int rows;
    int cell_size;
    int offset_x;
    int offset_y;
    bool inverted;
} GridConfig;

// ============================================
// 🔍 КАЛИБРОВКА СЕНСОРОВ
// ============================================

// При необходимости отрегулировать порог для каждого пина:
// Запустите calibrateSensors() и смотрите значения в Serial Monitor
// Обычно:
// - Не нажато: 40000 - 50000
// - Нажато:   10000 - 30000

#define CALIBRATION_MODE    0       // 1 = режим калибровки, 0 = нормальный режим

#endif // CONFIG_H
