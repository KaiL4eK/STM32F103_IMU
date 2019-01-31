# IMU sensors global project adapted for STM32F103C8T6 uC

### TARGET

The template runs on an STM32F103C8T6 board.

### Useful links

* [Reference manual (RM)](https://www.st.com/content/ccc/resource/technical/document/reference_manual/59/b9/ba/7f/11/af/43/d5/CD00171190.pdf/files/CD00171190.pdf/jcr:content/translations/en.CD00171190.pdf)
* [Datasheet (DS)](https://www.st.com/resource/en/datasheet/cd00161566.pdf)
* [Maple mini pinout](https://istarik.ru/blog/arduino/102.html)
---
* [Alternate functions](https://www.st.com/resource/en/datasheet/cd00161566.pdf#page=28)
* [Pins assignment (+analogs)](https://www.st.com/resource/en/datasheet/cd00161566.pdf#page=28)

### Структура

Проект включает в себя реализация аппаратной части и протоколы работы с датчиками. Папка `sensors` содержит модули реализации работы с датчиками, папка `sensors/public` должна содержать заголовочные файлы, которые имеют конечные прототипы функций для использования. Внутри папки `sensors` можно использовать закрытые заголовочные файлы, которые содержат информацию о регистрах, структуры и т.д.

Файл `ch_hw.c` содержит реализацию функций, которые используются в модулях AHRS.

Файл `sensors/hardware.h` содержит прототипы используемых в AHRS функций. Они должны быть реализованы на аппаратной стороне проекта.

