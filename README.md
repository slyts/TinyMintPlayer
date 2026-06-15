# TinyMint Player

A desktop music player using Qt6 and C++17. My tutorial project for learning GUI development in Qt.

## Features
- MP3, WAV, FLAC, and OGG playback
- Play/Pause button
- Volume control
- Rewind/Seek position slider
- Open file dialog
- Playlist

## Plans


- Next/Previous buttons
- Time display

## Building and running

### Requirements
- Qt 6.11.1 or later (with the Multimedia module)
- CMake 3.16+
- Compiler with C++17 support (MSVC 2022 / MinGW / GCC)

### Building with CMake
```bash
mkdir build
cd build
cmake .. -DCMAKE_PREFIX_PATH="path/to/your/Qt/version/msvc2022_64"
cmake --build . --config Release
```
> Replace path/to/your/Qt with the current path to your Qt installation.

### Launch
```bash
./Release/TinyMint_Player.exe
```

## Technologies
- C++17
- Qt6 (Core, Widgets, Multimedia)
- CMake

# TinyMint Player

Десктопный музыкальный плеер на Qt6 и C++17. Мой учебный проект для освоения GUI-разработки на Qt.

## Возможности
- Воспроизведение MP3, WAV, FLAC, OGG
- Кнопка Старт/Пауза
- Регулировка громкости
- Ползунок позиции (перемотка)
- Диалог открытия файла
- Плейлист

## В планах


- Кнопки Следующий/Предыдущий
- Отображение времени

## Сборка и запуск

### Требования
- Qt 6.11.1 или новее (с модулем Multimedia)
- CMake 3.16+
- Компилятор с поддержкой C++17 (MSVC 2022 / MinGW / GCC)

### Сборка через CMake
```bash
mkdir build
cd build
cmake .. -DCMAKE_PREFIX_PATH="путь/к/вашей/Qt/версии/msvc2022_64"
cmake --build . --config Release
```
> Замените путь/к/вашей/Qt на актуальный путь к установленной Qt.

### Запуск
```bash
./Release/TinyMint_Player.exe
```

## Технологии
- C++17
- Qt6 (Core, Widgets, Multimedia)
- CMake
