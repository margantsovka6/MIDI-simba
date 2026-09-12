#include "MIDIUSB.h"

const int NUM_ROWS = 4;
const int NUM_COLS = 8;

// Ваша распиновка для Arduino Pro Micro
int rowPins[NUM_ROWS] = {2, 3, 4, 5}; 
int colPins[NUM_COLS] = {7, 6, 8, 9, 10, 16, 14, 15};

// Двумерный массив для хранения текущего состояния клавиш (0 - отпущена, 1 - нажата)
bool keyState[NUM_ROWS][NUM_COLS];

// MIDI-карта клавиш (числа вместо текста)
const byte noteMap[NUM_ROWS][NUM_COLS] = {
  {72, 71, 70, 69, 68, 67, 66, 65}, // Строка 1
  {64, 63, 62, 61, 60, 59, 58, 57}, // Строка 2
  {56, 55, 54, 53, 52, 51, 50, 49}, // Строка 3
  {48, 47, 46, 45, 44, 43, 42, 41}  // Строка 4
};

void setup() {
  // Все строки переводим в INPUT для безопасности
  for (int r = 0; r < NUM_ROWS; r++) {
    pinMode(rowPins[r], INPUT);
  }

  // Все колонки переводим в INPUT_PULLUP
  for (int c = 0; c < NUM_COLS; c++) {
    pinMode(colPins[c], INPUT_PULLUP);
  }
}

void loop() {
  // Поочередно сканируем каждую строку
  for (int r = 0; r < NUM_ROWS; r++) {
    
    // АКТИВАЦИЯ СТРОКИ: переводим текущую строку на ВЫХОД и подаем LOW
    pinMode(rowPins[r], OUTPUT);
    digitalWrite(rowPins[r], LOW);
    
    delayMicroseconds(10); // Микропауза для стабилизации емкости шлейфа

    // Читаем состояние всех колонок для этой строки
    for (int c = 0; c < NUM_COLS; c++) {
      bool isPressed = (digitalRead(colPins[c]) == LOW);

      // Проверяем, изменилось ли состояние клавиши
      if (isPressed != keyState[r][c]) {
        keyState[r][c] = isPressed; // Запоминаем новое состояние
        
        byte midiNote = noteMap[r][c]; // Извлекаем номер ноты из таблицы

        if (isPressed) {
          // Нажатие клавиши: канал 0, нота, громкость (velocity) 64
          noteOn(0, midiNote, 64);  
        } else {
          // Отпускание клавиши: канал 0, нота, громкость 64
          noteOff(0, midiNote, 64); 
        }
        MidiUSB.flush(); // Немедленно отправляем команду в USB-порт компьютера
      }
    }

    // ДЕАКТИВАЦИЯ СТРОКИ: возвращаем её в безопасный режим INPUT
    pinMode(rowPins[r], INPUT);
  }

  // Задержка 8 мс — оптимальный баланс против дребезга контактов и минимального пинга
  delay(8); 
}

// Низкоуровневая функция библиотеки MIDIUSB для включения ноты (Note On)
void noteOn(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOn = {0x09, 0x90 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOn);
}

// Низкоуровневая функция библиотеки MIDIUSB для выключения ноты (Note Off)
void noteOff(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOff = {0x08, 0x80 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOff);
}
