/*
   Скетч для игры "повтори случайную последовательность нажатий"
   Генерируется число нажатий от min_blinks до max_blinks
   Генерируется время между нажатиями, время фиксированное, берётся из массива timers
   Как работает:
   При нажатии система просыпается (ЗЕЛЁНАЯ ВСПЫШКА)
   СИНИМИ вспышками показывает новую последовательность для раунда
   Начинается раунд, система ждёт ваших нажатий
   При нажатии вспыхивает СИНИЙ светодиод
   Если вы торопитесь, раунд сбросится, КРАСНЫЙ светодиод мигнёт дважды
   Если вы нажимаете слишком поздно, КРАСНЫЙ мигнёт один раз
   Если вы не начнёте нажимать в течение 5 секунд, мигнёт КРАСНЫЙ
   Если вы правильно введёте комбинацию, ЗЕЛЁНЫЙ мигнёт три раза
   Также предусмотрен сон, система спит всё неактивное время
*/

//----- НАСТРОЙКИ -----
#define difficulty 100  // миллисекунд на реакцию
#define min_blinks 3    // минимум вспышек за раунд
#define max_blinks 6    // максимум вспышек за раунд

int timers[] = {100, 800}; // временные паузы между вспышками, число пауз равно числу "ступеней" в игре

#define debug 0         // режим отладки - вывод в порт информации о процессе игры
//----- НАСТРОЙКИ -----

#define buzzPin 7       // пин пищалки
#define LEDGND 5        // земля питания светодиодов
#define buzzGND 4       // земля пищалки
#define sensGND 3       // земля сенсора
#define sensVCC 6       // питание сенсора

byte timers_num = sizeof(timers) / 2;  // вычисляет размер массива timers - число "ступеней" игры
byte LED[] = {11, 10, 9};  // светодиод на 9, 10, 11 пинах
#include <LowPower.h>      // библиотека сна
byte fade_count;
volatile byte mode;
boolean cap_flag;
volatile boolean debonce_flag, threshold_flag;
volatile unsigned long debounce_time;
unsigned long last_fade, last_try;

byte count, try_count;
int wait_time[max_blinks], min_wait[max_blinks], max_wait[max_blinks];

void setup() {
  Serial.begin(9600);
  // настраиваем пины питания как выходы
  pinMode(buzzPin, OUTPUT);
  pinMode(LEDGND, OUTPUT);
  pinMode(buzzGND, OUTPUT);
  pinMode(sensGND, OUTPUT);
  pinMode(sensVCC, OUTPUT);

  // подаём нужные сигналы
  digitalWrite(buzzPin, 0);
  digitalWrite(LEDGND, 0);
  digitalWrite(buzzGND, 0);
  digitalWrite(sensGND, 0);
  digitalWrite(sensVCC, 1);

  pinMode(2, INPUT);              // пин датчика касания или кнопка
  for (int i = 0; i < 3; i++) {   // сделать все светодиодные пины выходами и выключить
    pinMode(LED[i], OUTPUT);
    digitalWrite(LED[i], 0);
  }
  attachInterrupt(0, threshold, RISING);     // настраиваем прерывание датчика
  good_night();                              // сразу спать
}

// функция плавной вспышки светодиода, на вход цвет и яркость, а также пищалка
void fade (int color, int bright) {
  for (byte i = 0; i < 252; i += 2) {
    analogWrite(LED[color], i);
    delay(1);
  }
  tone(buzzPin, 500);   // БУЗИТЬ ЁПТА!
  delay(bright);        // ждать
  noTone(buzzPin);      // НЕ БУЗИТЬ БОЛЬШЕ!
  for (byte i = 254; i > 3; i -= 2) {
    analogWrite(LED[color], i);
    delay(1);
  }
  digitalWrite(LED[color], 0);
}

void loop() {
  if (threshold_flag && mode == 0) {  // срабатывание в нулевом режиме - переход к режиму генерации раунда игры
    fade(1, 50);                      // мигнуть зелёным
    threshold_flag = 0;
    mode = 1;
    delay(800);
  }

  if (mode == 1) {                                // режим генерации раунда
    randomSeed(millis());                         // сбросить генератор случайных чисел на основе таймера
    count = random(min_blinks, max_blinks);       // получить число вспышек (от минимума до максимума)
    for (byte i = 0; i < count; i++) {            // забиваем массивы времён игры
      byte rnd = random(0, timers_num);           // получаем случайное число rnd от 0 до количества "ступеней"
      wait_time[i] = timers[rnd];                 // выбрать время "ступени"
      min_wait[i] = wait_time[i] - difficulty;    // определить время с учётом времени реакции
      max_wait[i] = wait_time[i] + difficulty;    // определить время с учётом времени реакции
    }

    // показать комбинацию "раунда"
    for (byte i = 0; i < count; i++) {
      fade(2, 30);                       // пыхнуть светодиодом
      delay(wait_time[i]);               // ждать время шага одного хода
      if (debug) Serial.println(wait_time[i]);
    }
    mode = 2;                            // перейти в режим игры
  }

  if (mode == 2) {
    threshold_flag = 0;
    debounce_time = millis();
    while (!threshold_flag) if (millis() - debounce_time > 5000) {
        fade(0, 300);
        delay(100);
        fade(0, 300);
        debounce_time = millis();
        mode = 0;
        if (debug) Serial.println("sucker");
        break;
      }
    if (threshold_flag) {
      fade(2, 30);
      last_try = millis();      // обнулить таймер
      try_count = 0;
      threshold_flag = 0;
      while (1) {

        // если не нажал в установленное время (проигрыш)
        if (millis() - last_try > max_wait[try_count]) {
          // мигнуть красным два раза
          fade(0, 300);
          delay(1000);
          mode = 0;             // перейти в начало! Это начало нового раунда
          if (debug) Serial.println("too slow");
          threshold_flag = 0;
          break;
        }
        if (threshold_flag) {

          // если нажатие попало во временной диапазон (правильное нажатие)
          if (millis() - last_try > min_wait[try_count] && millis() - last_try < max_wait[try_count]) {
            fade(2, 30);               // мигнуть
            try_count++;               // увеличить счётчик правильных нажатий
            last_try = millis();       // ВОТ ТУТ СЧЁТЧИК СБРАСЫВАЕТСЯ, ЧТОБЫ УБРАТЬ ВЛИЯНИЕ ЗАДЕРЖЕК!
            threshold_flag = 0;        // сбросить флаг
            if (debug) Serial.println("good");

            // если нажал слишком рано (проигрыш)
          } else if (millis() - last_try < min_wait[try_count] && threshold_flag) {
            fade(0, 300);
            delay(100);
            fade(0, 300);        // мигнуть красным дважды
            delay(1000);
            mode = 0;            // перейти в начало! Это начало нового раунда
            if (debug) Serial.println("too fast");
            threshold_flag = 0;
            break;
          }

          // если число правильных нажатий совпало с нужным для раунда (выигрыш)
          if (try_count == count - 1) {
            // мигнуть 3 раза
            delay(200);
            fade(1, 100);
            delay(200);
            fade(1, 100);
            delay(200);
            fade(1, 100);
            delay(200);
            mode = 0;   // вернуться в начало игры
            if (debug) Serial.println("victory");
            break;
          }
        }
      }
    }
  }

  if (millis() - debounce_time > 10000) {
    good_night();
  }
}

void threshold() {
  if (millis() - debounce_time > 50) debonce_flag = 1;
  if (debonce_flag) {
    debounce_time = millis();
    threshold_flag = 1;
    debonce_flag = 0;
  }
}

void good_night() {
  if (debug) Serial.println("good night");
  delay(5);
  LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF);    // спать. mode POWER_OFF, АЦП выкл
}
