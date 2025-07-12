#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

/*Этот код имитирует работу с GPIO на микроконтроллерах STM32, используя структуры
 * для представления регистров.*/

// Определение структуры, описывающей регистры GPIO (общий порт ввода/вывода)
// для микроконтроллеров STM32
typedef struct {
    uint32_t MODER; // Регистр режима (input/output/alternate/analog)
    uint32_t OTYPER; // Регистр типа выхода (push-pull/open-drain)
    uint32_t OSPEEDR; // Регистр скорости
    uint32_t PUPDR; // Регистр подтяжки (pull-up/pull-down)
    uint32_t IDR; // Входной регистр данных (чтение состояния пинов)
    /* ODR сделан 32-битным, хотя в некоторых STM32 он 16-битный*/
    uint32_t ODR; // Выходной регистр данных (установка состояния пинов)
    uint32_t BSRR; // Регистр установки/сброса битов (атомарная запись)
    uint32_t LCKR; // Регистр блокировки конфигурации
    uint32_t AFR[2]; // Массив регистров альтернативных функций (AFR[0] и AFR[1])
} GPIO_TypeDef;

// =============================================
// Создание тестовых структур для имитации GPIO портов
// Все поля инициализируются нулями благодаря {0,}
GPIO_TypeDef a = {0,}, b = {0,}, c = {0,}, d = {0,}, e = {0,};

// =============================================
// Определение макросов для адресов GPIO портов
// Макросы преобразуют адреса структур в целочисленные значения (size_t)
// ВОПРОС: тут не define должны быть, а присваивания?
// Адреса передаются как целые числа
#define GPIOA ((size_t) & a) // Адрес структуры 'a' как GPIO порт A
/// Не все адреса могут быть в наличии
// #define GPIOB ((size_t) &b)
#define GPIOC ((size_t) & c) // Адрес структуры 'c' как GPIO порт C
#define GPIOD ((size_t) & d) // Адрес структуры 'd' как GPIO порт D

/**
 * \brief функция устанавливает указанный бит в регистре ODR указанного порта
 * (см. описание GPIO_TypeDef)
 * \retval bit при успешном выполнении либо 0, если
 * указанный порт не определён
 * \param[in] base — целочисленное представление
 * адреса некой структуры
 * \param[in] bit — номер бита, который нужно установить
 * в регистре ODR той структуры, адрес которой нам передан
 *
 * Задача: реализовать эту функцию.
 */
uint16_t set_bit(size_t base, uint16_t bit);

int main()
{
    size_t port = GPIOA; // Выбор порта GPIOA для теста
    uint16_t bit = 10; // Бит 10 будет установлен в ODR

    /*Если бит - это маска, то переводим*/

    uint16_t result = set_bit(port, bit); // Вызов функции установки бита

    // Вывод результата и значения ODR (в шестнадцатеричном формате)
    printf("Result: %u, ODR: 0x%08X\n", result, ((GPIO_TypeDef*)port)->ODR);

    return 0;
}

// Начало решения
uint16_t set_bit(size_t base, uint16_t bit)
{
    // Преобразуем номер бита в маску
    uint16_t bit_mask = (1 << bit);

    // Инициализация указателя на порт как NULL
    GPIO_TypeDef* port = 0;

// Проверка, определён ли макрос GPIOA, и если да — сравнение base с его значением
#if defined GPIOA
    if (base == GPIOA) port = (GPIO_TypeDef*)base;
#endif
// Аналогично для GPIOB, GPIOC, GPIOD
#if defined GPIOB
    if (base == GPIOB) port = (GPIO_TypeDef*)base;
#endif
#if defined GPIOC
    if (base == GPIOC) port = (GPIO_TypeDef*)base;
#endif
#if defined GPIOD
    if (base == GPIOD) port = (GPIO_TypeDef*)base;
#endif

    // Если порт найден, устанавливаем бит в ODR, иначе обнуляем bit
    if (port)
    {
        port->ODR |= bit_mask;
    }
    else
    {
        bit = 0;
    }
    return bit;
}
// Конец решения