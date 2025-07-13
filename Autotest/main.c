#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

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

GPIO_TypeDef a = {0,}, b = {0,}, c = {0,}, d = {0,}, e = {0,};

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
    size_t port = GPIOC;
    uint16_t bit = 0;

    // Защита от неверных битов
    if (bit > 15)
    {
        printf("Error: invalid bit (%u > 15)\n", bit);
        return 0;
    }

    uint16_t result = set_bit(port, bit);

    if (result != 0 || bit == 0)
    {
        printf("Result: %u, ODR: 0x%08X\n", result, ((GPIO_TypeDef*)port)->ODR);
    }
    else
    {
        printf("Error: invalid port 0x%08zX\n", port);
    }
    return 0;
}

uint16_t set_bit(size_t base, uint16_t bit)
{
    uint16_t bit_mask = (1 << bit);

    GPIO_TypeDef* port = 0;

#if defined GPIOA
    if (base == GPIOA) port = (GPIO_TypeDef*)base;
#endif
#if defined GPIOB
    if (base == GPIOB) port = (GPIO_TypeDef*)base;
#endif
#if defined GPIOC
    if (base == GPIOC) port = (GPIO_TypeDef*)base;
#endif
#if defined GPIOD
    if (base == GPIOD) port = (GPIO_TypeDef*)base;
#endif

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
