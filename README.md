[![AlexGyver YouTube](http://alexgyver.ru/git_banner.jpg)](https://www.youtube.com/channel/UCgtAOyEQdAyjvm9ATCi_Aig?sub_confirmation=1)
# Игра "Повтори последовательность" на Arduino
* [Описание проекта](#chapter-0)
* [Папки проекта](#chapter-1)
* [Схемы подключения](#chapter-2)
* [Материалы и компоненты](#chapter-3)
* [Настройка и использование](#chapter-4)
* [FAQ](#chapter-5)
* [Полезная информация](#chapter-6)
* [Мой сайт](http://alexgyver.ru/)
* [Основной YouTube канал](https://www.youtube.com/channel/UCgtAOyEQdAyjvm9ATCi_Aig?sub_confirmation=1)
* [YouTube канал про Arduino](https://www.youtube.com/channel/UC4axiS76D784-ofoTdo5zOA?sub_confirmation=1)

<a id="chapter-0"></a>
## Описание проекта
Игра, суть которой заключается в повторении сгенерированной случайно последовательности нажатий кнопки
- Подробности в видео: https://youtu.be/lsCDHxN6abU

<a id="chapter-1"></a>
## Папки
- **Library** - библиотеки для дисплея и прочего, скопировать в  
`C:\Program Files (x86)\Arduino\libraries\` (Windows x64)  
`C:\Program Files\Arduino\libraries\` (Windows x86)
- **randomGame** - прошивка для Arduino, файлы в папках открыть в Arduino IDE (читай [FAQ](#chapter-5))

<a id="chapter-2"></a>
## Схема
![СХЕМА](https://github.com/AlexGyver/randomGame/blob/master/scheme.jpg)

<a id="chapter-3"></a>
## Материалы и компоненты
* Arduino NANO https://ali.ski/K3Cdf
* Сенсорная кнопка https://ali.ski/pksiN
* Батарейный отсек https://ali.ski/ekTK93
* Светодиод RGB общий катод http://www.voltmaster.ru/cgi-bin/qwery.pl/id=416425062
* Резистор 220 Ом
* Пищалка из компьютера

## Вам скорее всего пригодится
* [Всё для пайки (паяльники и примочки)](http://alexgyver.ru/all-for-soldering/)
* [Недорогие инструменты](http://alexgyver.ru/my_instruments/)
* [Все существующие модули и сенсоры Arduino](http://alexgyver.ru/arduino_shop/)
* [Электронные компоненты](http://alexgyver.ru/electronics/)
* [Аккумуляторы и зарядные модули](http://alexgyver.ru/18650/)

<a id="chapter-4"></a>
## Настройка и использование
* [Загрузка прошивки](http://alexgyver.ru/arduino-first/) - ультра подробная статья по началу работы с Ардуино

## Настройки в коде
    #define difficulty 100  // миллисекунд на реакцию
    #define min_blinks 3    // минимум вспышек за раунд
    #define max_blinks 6    // максимум вспышек за раунд

    int timers[] = {100, 800}; // временные паузы между вспышками, число пауз равно числу "ступеней" в игре

    #define debug 0         // режим отладки - вывод в порт информации о процессе игры

<a id="chapter-5"></a>
## FAQ
### Основные вопросы
В: Как скачать с этого грёбаного сайта?  
О: На главной странице проекта (где ты читаешь этот текст) вверху справа зелёная кнопка **Clone or download**, вот её жми, там будет **Download ZIP**

В: Скачался какой то файл .zip, куда его теперь?  
О: Это архив. Можно открыть стандартными средствами Windows, но думаю у всех на компьютере установлен WinRAR, архив нужно правой кнопкой и извлечь.

В: Я совсем новичок! Что мне делать с Ардуиной, где взять все программы?  
О: Читай и смотри видос http://alexgyver.ru/arduino-first/

В: Компьютер никак не реагирует на подключение Ардуины!  
О: Возможно у тебя зарядный USB кабель, а нужен именно data-кабель, по которому можно данные передавать

В: Ошибка! Скетч не компилируется!  
О: Путь к скетчу не должен содержать кириллицу. Положи его в корень диска.

В: Сколько стоит?  
О: Ничего не продаю.

### Вопросы по этому проекту

<a id="chapter-6"></a>
## Полезная информация
* [Мои видеоуроки по пайке](https://www.youtube.com/playlist?list=PLOT_HeyBraBuMIwfSYu7kCKXxQGsUKcqR)
* [Мои видеоуроки по Arduino](http://alexgyver.ru/arduino_lessons/)