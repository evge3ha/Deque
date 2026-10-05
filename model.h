#pragma once

#include <deque>
#include <string>
#include <random>

struct Model {
    using Deque = std::deque<std::string>;
    Deque items;
    Deque::iterator iterator = items.begin();

    std::mt19937 random_gen{std::random_device{}()};

    inline static const Deque tea {
        "Чай Лунцзин",
        "Эрл Грей",
        "Сенча",
        "Пуэр",
        "Дарджилинг",
        "Ассам",
        "Матча",
        "Ганпаудер",
        "Оолонг",
        "Лапсанг Сушонг"
    };

    inline static const Deque cakes {
        "Красный бархат",
        "Наполеон",
        "Медовик",
        "Тирамису",
        "Прага",
        "Чизкейк",
        "Захер",
        "Эстерхази",
        "Морковный торт",
        "Чёрный лес",
    };
};