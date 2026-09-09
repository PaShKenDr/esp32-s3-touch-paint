# Подробный гайд: Открытие проекта в VS Code с PlatformIO

## 📋 Содержание
1. [Установка необходимого ПО](#установка-необходимого-по)
2. [Открытие проекта](#открытие-проекта)
3. [Автоматическая установка зависимостей](#автоматическая-установка-зависимостей)
4. [Настройка окружения](#настройка-окружения)
5. [Решение проблем](#решение-проблем)

---

## 🛠️ Установка необходимого ПО

### Шаг 1: Установить Visual Studio Code
1. Перейдите на https://code.visualstudio.com/
2. Скачайте версию для вашей ОС (Windows, macOS, Linux)
3. Установите и запустите VS Code

### Шаг 2: Установить расширение PlatformIO
1. **Откройте VS Code**
2. **Нажмите на иконку расширений** (квадратик слева в боковой панели)
   ```
   Или используйте: Ctrl+Shift+X (Windows/Linux) 
                    Cmd+Shift+X (macOS)
   ```
3. **В строке поиска напишите:** `PlatformIO IDE`
4. **Нажмите на результат "PlatformIO IDE"** от компании *PlatformIO*
5. **Нажмите кнопку "Install"** (зелёная кнопка)

   ![PlatformIO Install](https://user-images.githubusercontent.com/placeholder/platformio-install.png)

6. **Дождитесь завершения установки** (может занять 1-2 минуты)
7. **VS Code попросит перезагрузиться** - нажмите "Reload"

### Шаг 3: Проверить установку
1. После перезагрузки в левой панели появится **иконка Муравья** 🐜
2. Нажмите на неё - откроется панель PlatformIO
3. Вы должны увидеть пункты меню:
   - Quick Access
   - Favorites
   - Open
   - Recent Projects

---

## 📂 Открытие проекта

### Вариант A: Через VS Code интерфейс (рекомендуется)

1. **Откройте VS Code**

2. **Нажмите File → Open Folder** (или Ctrl+K Ctrl+O)
   ```
   File → Open Folder
   ```

3. **Навигируйте к папке проекта:**
   ```
   C:\Users\YourName\Downloads\esp32-s3-touch-paint
   ```
   (Или там, где вы клонировали репозиторий)

4. **Выберите папку `esp32-s3-touch-paint`** и нажмите **"Select Folder"**

5. **VS Code откроет проект** - вы увидите структуру файлов слева:
   ```
   esp32-s3-touch-paint/
   ├── platformio.ini
   ├── README.md
   ├── .gitignore
   ├── src/
   │   └── main.cpp
   └── include/
       └── config.h
   ```

### Вариант B: Через командную строку

**Windows (PowerShell):**
```powershell
cd C:\path\to\esp32-s3-touch-paint
code .
```

**macOS/Linux:**
```bash
cd ~/path/to/esp32-s3-touch-paint
code .
```

---

## 🔄 Автоматическая установка зависимостей

### Что произойдёт автоматически:

Когда вы откроете папку проекта, PlatformIO **автоматически**:

1. **Обнаружит файл `platformio.ini`**
   - Это конфиг-файл PlatformIO, в котором описаны все параметры

2. **Прочитает конфигурацию:**
   ```ini
   [env:esp32-s3-devkitc-1]
   platform = espressif32
   board = esp32-s3-devkitc-1
   framework = arduino
   lib_deps = 
       bodmer/TFT_eSPI@^2.5.0
       ArduinoJson@^6.21.2
   ```

3. **Загрузит необходимые компоненты:**
   - ✅ **ESP32-S3 плата** (компилятор, утилиты)
   - ✅ **Arduino framework**
   - ✅ **Библиотека TFT_eSPI** для управления дисплеем
   - ✅ **Библиотека ArduinoJson** для работы с JSON

### Как это выглядит на экране:

1. **Сразу после открытия проекта** вы увидите внизу экрана:
   ```
   [Platform IO] Initializing project environment for "esp32-s3-devkitc-1"...
   ```

2. **В нижнем левом углу** появится иконка ⚙️ (крутится в процессе)

3. **В выходном окне** (`View → Output` или `Ctrl+J`) будут логи:
   ```
   PlatformIO: Installing dependencies...
   Downloading ESP32-S3 toolchain...
   [████████████████████] 100%
   Downloading library: bodmer/TFT_eSPI...
   [████████████████████] 100%
   ...
   ```

4. **После завершения** (обычно 5-10 минут в первый раз):
   ```
   PlatformIO: Environment has been successfully initialized
   ```

### Где скачиваются файлы?

Все компоненты установятся в папку:
```
~/.platformio/  (на Linux/macOS)
C:\Users\YourName\.platformio\  (на Windows)
```

Эту папку добавлять в Git не нужно - она указана в `.gitignore`

---

## ⚙️ Настройка окружения

### Шаг 1: Выбор нужной платформы

Когда вы откроете проект, PlatformIO может предложить выбрать окружение:

1. **Внизу справа** нажмите на кнопку **"esp32-s3-devkitc-1"** (или подобное)
   ```
   Статус-бар: [esp32-s3-devkitc-1] PlatformIO
   ```

2. Если окружение не выбрано, нажмите на эту кнопку
3. **Выберите:** `esp32-s3-devkitc-1`

### Шаг 2: Проверить COM порт

1. **Подключите ESP32-S3 через USB Type-C к компьютеру**

2. **Откройте PlatformIO → Devices** (нажмите на 🐜 слева → Devices)
   ```
   В левой панели должна появиться строка:
   "COM3 (USB Serial Device)"  - Windows
   "/dev/ttyUSB0"               - Linux
   "/dev/cu.usbserial-*"        - macOS
   ```

3. Если в списке появилась ваша плата - всё хорошо ✅

### Шаг 3: Настроить COM порт (если требуется)

Если вы видите много устройств или нужно указать конкретный порт:

1. **Отредактируйте `platformio.ini`:**
   ```ini
   [env:esp32-s3-devkitc-1]
   platform = espressif32
   board = esp32-s3-devkitc-1
   framework = arduino
   monitor_port = COM3           ; ← Добавьте эту строку
   upload_port = COM3            ; ← И эту
   upload_speed = 921600
   monitor_speed = 115200
   ```

2. **Замените COM3 на ваш порт** (из пункта 2 выше)

---

## 🔨 Сборка и загрузка проекта

### Метод 1: Через кнопки в боковой панели (самый простой)

1. **Нажмите на иконку 🐜 (PlatformIO)** в левой панели

2. **Развернёте дерево** esp32-s3-devkitc-1

3. **Нажмите на нужную операцию:**
   ```
   📁 esp32-s3-devkitc-1
   ├── 🔨 Build           ← Сборка проекта
   ├── ⬆️ Upload           ← Загрузить на плату
   ├── 📺 Monitor         ← Открыть Serial Monitor
   ├── ⬆️ Upload and Monitor
   └── 🧹 Clean           ← Очистить построение
   ```

### Метод 2: Через командную панель

1. **Нажмите Ctrl+Shift+P** (или Cmd+Shift+P на macOS)

2. **Введите команду:**
   ```
   PlatformIO: Build
   PlatformIO: Upload
   PlatformIO: Monitor
   ```

3. **Выберите нужную операцию**

### Метод 3: Через терминал PlatformIO

1. **Откройте терминал:** Ctrl+` (backtick)

2. **Введите команды:**
   ```bash
   pio run              # Сборка
   pio run -t upload    # Загрузить
   pio device monitor   # Монитор
   ```

---

## 📺 Просмотр вывода и логов

### Вывод компиляции

Когда вы нажимаете **Build**, внизу экрана откроется панель с логом:

```
Building with ESP32-S3...
[...                         ] 0%
Compiling src/main.cpp...
[████████████████░░░░░░░░░░░░] 50%
Linking firmware...
[████████████████████████████] 100%

Build complete! ✓
```

### Serial Monitor

После загрузки прошивки откроется **Serial Monitor** с выводом:

```
--- Miniterm on /dev/ttyUSB0 115200,8,N,1 ---
--- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+H ---

=== Touch Paint - ESP32-S3 ===
Инициализация дисплея...
Дисплей готов!
Инициализация сенсорных пинов...
Готово! Используйте сенсорные кнопки для рисования.
GPIO1-GPIO16: рисование
GPIO17: очистить
GPIO18: инвертировать
```

---

## 🆘 Решение проблем

### Проблема 1: "Cannot find platform definition"

**Решение:**
```bash
# В терминале VS Code выполните:
pio platform install espressif32
pio boards ESP32-S3
```

### Проблема 2: Плата не обнаруживается в списке устройств

**Проверка:**
1. Переподключите USB кабель
2. Нажмите кнопку **EN** на плате (перезагрузка)
3. В командной строке проверьте порты:
   
   **Windows (PowerShell):**
   ```powershell
   Get-WmiObject Win32_SerialPort
   ```
   
   **Linux/macOS:**
   ```bash
   ls /dev/tty* | grep -E 'USB|usbserial'
   ```

4. Если порта нет - установите драйвер:
   - Скачайте: https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers
   - Переустановите USB кабель
   - Перезагрузитесь

### Проблема 3: "Upload failed"

**Проверьте:**
1. Плата подключена и порт правильный
2. На плате горит светодиод питания (красный)
3. Попробуйте нажать **BOOT + EN** перед загрузкой
4. Увеличьте скорость загрузки в `platformio.ini`:
   ```ini
   upload_speed = 460800  ; вместо 921600
   ```

### Проблема 4: "Library not found: TFT_eSPI"

**Решение:**
```bash
# В терминале выполните:
pio lib install "bodmer/TFT_eSPI"
pio lib install "ArduinoJson"

# Затем пересборка:
pio run -t upload
```

### Проблема 5: Serial Monitor показывает мусор

**Проверьте скорость:**
1. В `platformio.ini` убедитесь:
   ```ini
   monitor_speed = 115200
   ```

2. Вверху Serial Monitor должна быть скорость **115200**

3. Нажмите **RESET** на плате

---

## ✅ Готово!

Когда вы выполните все эти шаги:

1. ✅ VS Code установлен
2. ✅ PlatformIO расширение установлено
3. ✅ Проект открыт
4. ✅ Зависимости загружены
5. ✅ Плата подключена и обнаружена
6. ✅ Проект собран и загружен

**Теперь вы можете:**
- 📝 Редактировать код в `src/main.cpp`
- 🔨 Собирать проект: `pio run`
- ⬆️ Загружать на плату: `pio run -t upload`
- 📺 Смотреть вывод: `pio device monitor`

---

## 🎓 Полезные советы

### Автозаполнение в коде
- Когда вы начнёте писать код, PlatformIO предложит автозаполнение
- Нажмите Ctrl+Space для вызова подсказок
- Выберите нужное из списка

### Быстрые клавиши
```
Ctrl+Shift+B       → Сборка (Build)
Ctrl+Alt+U         → Загрузить (Upload)
Ctrl+Alt+S         → Загрузить + Монитор
Ctrl+Alt+C         → Очистить
Ctrl+K Ctrl+0      → Свернуть все папки
Ctrl+K Ctrl+J      → Развернуть все папки
```

### Отладка
- Если есть ошибки - нажмите на красную линию
- PlatformIO покажет подсказку об ошибке
- Нажмите на ошибку → переход на строку с проблемой

---

## 📚 Дополнительные ресурсы

- [Официальная документация PlatformIO](https://docs.platformio.org/)
- [Гайды для ESP32](https://docs.platformio.org/en/latest/boards/espressif32/esp32-s3-devkitc-1.html)
- [Библиотека TFT_eSPI](https://github.com/Bodmer/TFT_eSPI)
- [Форум PlatformIO](https://community.platformio.org/)

---

**Удачи в разработке! 🚀**
