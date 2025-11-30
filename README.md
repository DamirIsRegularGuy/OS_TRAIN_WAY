# Симуляция движения поездов по маршрутам в Таджикистане.
## Постановка задачи

Цель проекта — смоделировать движение поездов по железнодорожным маршрутам Таджикистана с использованием многопоточности в C++.

Условия задачи:
1. **Выбор маршрута**  
   Взять одну из железнодорожных веток Таджикистана, например:  
   - Душанбе — Пахтаабад  
   - Душанбе — Куляб  
   - маршруты вокруг Худжанда

2. **Создание программы на C++**  
   Программа должна соответствовать следующим условиям:  
   - Поезда стартуют из различных пунктов по своему маршруту.  
   - Каждый поезд — отдельный поток (`std::jthread`) с уникальным номером. Минимальное количество поездов — 8 (то есть 8 потоков).  
   - Одновременно на одной станции может находиться только один поезд (станция является ресурсом, который блокируется). Остальные поезда ждут своей очереди.  
   - Все события (отбытие и прибытие поездов) должны логироваться в консоль с текущим временем.  
   - Перемещение между станциями занимает некоторое время, чтобы имитировать реальное движение поезда.


## Работа программы
Программа выполняет следующие действия:

### 1. Инициализация маршрутов и поездов
- Потокам (поездам) назначается маршрут (рандомно) — список станций, которые они должены пройти.  
- Минимальное количество потоков (поездов) — 8.

### 2. Семафоры для станций
- Создается map с ключами имен станций и значениями (`std::binary_semaphore`). 
- Семафор обеспечивает эксклюзивный доступ поезда к станции, то есть одновременно на станции может находиться только один поезд.

### 3. Движение поездов
1. Поезд захватывает семафор станции при въезде на нее.
2. На одной станции имеется две станции, прибытие(северная), отбытие(южная). 
3. Проходит промежуток времени, имитирующий движение и пребывание на станции.  
4. Освобождает семафор после отбытия.

### 4. Логирование событий
- Все действия (отбытие, прибытие) выводятся в консоль с текущим временем.  
- Формат вывода позволяет отслеживать порядок движения поездов и занятие станций.


## Вывод программы
Здесь представлен вывод одного пероида симуляции движения поездов.
```console
...
Press Enter to stopped simulation
...
Train 3 has route Vahdat - Khujand in the north
Train 4 has route Gafurov - Khujand in the south
Train 6 has route Dushanbe - Buston in the south
Train 8 has route Khujand - Vahdat in the south
Train 10 has route Buston - Gafurov in the south
Train 7 has route Khujand - Gafurov in the north
Train 5 has route Buston - Gafurov in the south
Train 9 has route Gafurov - Khujand in the south

[08:18:57] Train 3 move towords station Vahdat from the north
[08:18:57] Train 4 move towords station Gafurov from the south
[08:18:57] Train 6 move towords station Dushanbe from the south
[08:18:57] Train 8 move towords station Khujand from the south
[08:18:57] Train 10 move towords station Buston from the south
[08:18:57] Train 7 move towords station Khujand from the north
[08:18:57] Train 5 move towords station Buston from the south
[08:18:57] Train 9 move towords station Gafurov from the south
[08:18:59] Train 3 arrived at station Vahdat from the north
[08:18:59] Train 4 arrived at station Gafurov from the south
[08:18:59] Train 7 arrived at station Khujand from the north
[08:18:59] Train 10 arrived at station Buston from the south
[08:18:59] Train 8 arrived at station Khujand from the south
[08:18:59] Train 6 arrived at station Dushanbe from the south
[08:19:07] Train 4 left station Gafurov in the south
[08:19:07] Train 3 left station Vahdat in the north
[08:19:07] Train 3 move towords station Dushanbe from the north
[08:19:07] Train 4 move towords station Buston from the south
[08:19:07] Train 8 left station Khujand in the south
[08:19:07] Train 8 move towords station Gafurov from the south
[08:19:07] Train 7 left station Khujand in the north
[08:19:07] Train 7 move towords station Vahdat from the north
[08:19:07] Train 6 left station Dushanbe in the south
[08:19:07] Train 6 move towords station Vahdat from the south
[08:19:07] Train 10 left station Buston in the south
[08:19:07] Train 10 move towords station Dushanbe from the south
[08:19:09] Train 9 arrived at station Gafurov from the south
[08:19:09] Train 5 arrived at station Buston from the south
[08:19:12] Train 3 arrived at station Dushanbe from the north
[08:19:12] Train 10 arrived at station Dushanbe from the south
[08:19:12] Train 6 arrived at station Vahdat from the south
[08:19:12] Train 7 arrived at station Vahdat from the north
[08:19:13] Train 3 left station Dushanbe in the north
[08:19:13] Train 3 move towords station Buston from the north
[08:19:13] Train 7 left station Vahdat in the north
[08:19:13] Train 6 left station Vahdat in the south
[08:19:13] Train 6 move towords station Khujand from the south
[08:19:13] Train 7 move towords station Dushanbe from the north
[08:19:13] Train 10 left station Dushanbe in the south
[08:19:13] Train 10 move towords station Vahdat from the south
[08:19:17] Train 9 left station Gafurov in the south
[08:19:17] Train 9 move towords station Buston from the south
[08:19:17] Train 5 left station Buston in the south
[08:19:17] Train 5 move towords station Dushanbe from the south
[08:19:22] Train 8 arrived at station Gafurov from the south
[08:19:22] Train 5 arrived at station Dushanbe from the south
[08:19:22] Train 4 arrived at station Buston from the south
[08:19:23] Train 3 arrived at station Buston from the north
[08:19:23] Train 8 left station Gafurov in the south
[08:19:23] Train 8 move towords station Buston from the south
[08:19:23] Train 7 arrived at station Dushanbe from the north
[08:19:23] Train 10 arrived at station Vahdat from the south
[08:19:23] Train 6 arrived at station Khujand from the south
[08:19:23] Train 4 left station Buston in the south
[08:19:23] Train 5 left station Dushanbe in the south
[08:19:23] Train 5 move towords station Vahdat from the south
[08:19:23] Train 4 move towords station Dushanbe from the south
[08:19:28] Train 3 left station Buston in the north
[08:19:28] Train 3 move towords station Gafurov from the north
[08:19:28] Train 10 left station Vahdat in the south
[08:19:28] Train 6 left station Khujand in the south
[08:19:28] Train 6 move towords station Gafurov from the south
[08:19:28] Train 10 move towords station Khujand from the south
[08:19:28] Train 7 left station Dushanbe in the north
[08:19:28] Train 7 move towords station Buston from the north
[08:19:33] Train 4 arrived at station Dushanbe from the south
[08:19:33] Train 8 arrived at station Buston from the south
[08:19:37] Train 3 arrived at station Gafurov from the north
[08:19:37] Train 6 arrived at station Gafurov from the south
[08:19:37] Train 10 arrived at station Khujand from the south
[08:19:37] Train 7 arrived at station Buston from the north
[08:19:38] Train 5 arrived at station Vahdat from the south
[08:19:38] Train 8 left station Buston in the south
[08:19:38] Train 4 left station Dushanbe in the south
[08:19:38] Train 4 move towords station Vahdat from the south
[08:19:38] Train 8 move towords station Dushanbe from the south
[08:19:43] Train 9 arrived at station Buston from the south
[08:19:43] Train 5 left station Vahdat in the south
[08:19:43] Train 5 move towords station Khujand from the south
[08:19:44] Train 9 left station Buston in the south
[08:19:44] Train 9 move towords station Dushanbe from the south
[08:19:46] Train 3 left station Gafurov in the north
[08:19:46] Train 3 move towords station Khujand from the north
[08:19:46] Train 10 left station Khujand in the south
[08:19:46] Train 6 left station Gafurov in the south
[08:19:46] Train 6 move towords station Buston from the south
[08:19:46] Train 10 move towords station Gafurov from the south
[08:19:46] Train 7 left station Buston in the north
[08:19:46] Train 7 move towords station Gafurov from the north
[08:19:47] Train 8 arrived at station Dushanbe from the south
[08:19:49] Train 3 arrived at station Khujand from the north
[08:19:49] Train 10 arrived at station Gafurov from the south
[08:19:49] Train 6 arrived at station Buston from the south
[08:19:49] Train 7 arrived at station Gafurov from the north
[08:19:52] Train 4 arrived at station Vahdat from the south
[08:19:54] Train 3 left station Khujand in the north
[08:19:54] Train 3 move towords station Vahdat from the north
[08:19:54] Train 6 left station Buston in the south
[08:19:54] Train 10 left station Gafurov in the south
[08:19:54] Train 10 move towords station Buston from the south
[08:19:54] Train 7 left station Gafurov in the north
[08:19:54] Train 6 move towords station Dushanbe from the south
[08:19:54] Train 7 move towords station Khujand from the north
[08:19:55] Train 5 arrived at station Khujand from the south
[08:19:56] Train 8 left station Dushanbe in the south
[08:19:56] Train 8 move towords station Vahdat from the south
[08:20:00] Train 3 arrived at station Vahdat from the north
[08:20:00] Train 10 arrived at station Buston from the south
[08:20:00] Train 7 arrived at station Khujand from the north
[08:20:01] Train 4 left station Vahdat in the south
[08:20:01] Train 4 move towords station Khujand from the south
[08:20:04] Train 5 left station Khujand in the south
[08:20:04] Train 5 move towords station Gafurov from the south
[08:20:04] Train 8 arrived at station Vahdat from the south
[08:20:06] Train 9 arrived at station Dushanbe from the south
[08:20:06] Train 3 left station Vahdat in the north
[08:20:06] Train 3 move towords station Dushanbe from the north
[08:20:06] Train 10 left station Buston in the south
[08:20:06] Train 10 move towords station Dushanbe from the south
[08:20:06] Train 7 left station Khujand in the north
[08:20:06] Train 7 move towords station Vahdat from the north
[08:20:07] Train 5 arrived at station Gafurov from the south
[08:20:07] Train 4 arrived at station Khujand from the south
[08:20:08] Train 3 arrived at station Dushanbe from the north
[08:20:08] Train 7 arrived at station Vahdat from the north
[08:20:09] Train 8 left station Vahdat in the south
[08:20:09] Train 8 move towords station Khujand from the south
[08:20:11] Train 9 left station Dushanbe in the south
[08:20:11] Train 9 move towords station Vahdat from the south
[08:20:12] Train 4 left station Khujand in the south
[08:20:12] Train 5 left station Gafurov in the south
[08:20:12] Train 5 move towords station Buston from the south
[08:20:12] Train 4 move towords station Gafurov from the south
[08:20:16] Train 3 left station Dushanbe in the north
[08:20:16] Train 3 move towords station Buston from the north
[08:20:16] Train 7 left station Vahdat in the north
[08:20:16] Train 7 move towords station Dushanbe from the north
[08:20:17] Train 6 arrived at station Dushanbe from the south
[08:20:18] Train 8 arrived at station Khujand from the south
[08:20:18] Train 3 arrived at station Buston from the north
[08:20:18] Train 4 arrived at station Gafurov from the south
[08:20:18] Train 5 arrived at station Buston from the south
[08:20:18] Train 7 arrived at station Dushanbe from the north
[08:20:20] Train 9 arrived at station Vahdat from the south
[08:20:20] Train 3 left station Buston in the north
[08:20:20] Train 3 move towords station Gafurov from the north
[08:20:20] Train 7 left station Dushanbe in the north
[08:20:20] Train 7 move towords station Buston from the north
[08:20:23] Train 6 left station Dushanbe in the south
[08:20:23] Train 6 move towords station Vahdat from the south
[08:20:24] Train 8 left station Khujand in the south
[08:20:24] Train 8 move towords station Gafurov from the south
[08:20:24] Train 4 left station Gafurov in the south
[08:20:24] Train 5 left station Buston in the south
[08:20:24] Train 5 move towords station Dushanbe from the south
[08:20:24] Train 4 move towords station Buston from the south
[08:20:25] Train 10 arrived at station Dushanbe from the south
[08:20:26] Train 8 arrived at station Gafurov from the south
[08:20:26] Train 3 arrived at station Gafurov from the north
[08:20:26] Train 4 arrived at station Buston from the south
[08:20:26] Train 7 arrived at station Buston from the north
[08:20:29] Train 9 left station Vahdat in the south
[08:20:29] Train 9 move towords station Khujand from the south
[08:20:29] Train 3 left station Gafurov in the north
[08:20:29] Train 3 move towords station Khujand from the north
[08:20:29] Train 7 left station Buston in the north
[08:20:29] Train 7 move towords station Gafurov from the north
[08:20:31] Train 6 arrived at station Vahdat from the south
[08:20:32] Train 9 arrived at station Khujand from the south
[08:20:33] Train 10 left station Dushanbe in the south
[08:20:33] Train 10 move towords station Vahdat from the south
[08:20:34] Train 4 left station Buston in the south


Train 5 stopped.
Train 8 stopped.
Train 9 stopped.
Train 3 stopped.
Train 7 stopped.
Train 10 stopped.
Train 6 stopped.
Train 4 stopped.
=== SIMULATION COMPLETE ===
```
## Анализ Вывода
Рассмотрим поезд номер 9, за один круг, по маршруту Гафуров - Худжанд (*Train 9 has route Gafurov - Khujand in the south*), маршрут состоит из станций в 5 городах:
 - Гафуров
 - Бустон
 - Душанбе
 - Вахдат
 - Худжанд

Перед поездом 9 по точно такому же марщруту едет поез 4, поэтому поезд 9 не сможет сразу приехать на станцию
Гафуров:
```console
[08:18:57] Train 4 move towords station Gafurov from the south
[08:18:57] Train 9 move towords station Gafurov from the south
[08:18:59] Train 4 arrived at station Gafurov from the south
[08:19:07] Train 4 left station Gafurov in the south
[08:19:09] Train 9 arrived at station Gafurov from the south
[08:19:17] Train 9 left station Gafurov in the south
```
Наш поезд 9 был в очереди, и как только поезд 4 покидает станцию по определенному направления, другой поезд получает сигнал и движется туда.

Бустон:
```console
[08:19:17] Train 9 move towords station Buston from the south
[08:19:22] Train 4 arrived at station Buston from the south
[08:19:23] Train 3 arrived at station Buston from the north
[08:19:23] Train 4 left station Buston in the south
[08:19:23] Train 8 move towords station Buston from the south
[08:19:33] Train 8 arrived at station Buston from the south
[08:19:38] Train 8 left station Buston in the south
[08:19:43] Train 9 arrived at station Buston from the south
[08:19:44] Train 9 left station Buston in the south
```
На станции Бустон есть очередь: 4 -> 8 и только после этого 9 поезд прибывает на станцию.
Так же хочется отметить, что у станции есть две платформы и здесь это видно:
```console
[08:19:22] Train 4 arrived at station Buston from the south
[08:19:23] Train 3 arrived at station Buston from the north
```

Душанбе:
```console
[08:19:44] Train 9 move towords station Dushanbe from the south
[08:19:47] Train 8 arrived at station Dushanbe from the south
[08:19:56] Train 8 left station Dushanbe in the south
[08:20:06] Train 9 arrived at station Dushanbe from the south

```
Тут опять же 9 поезд пришел на станцию посе 8 поезда как на прошлой станции.

Вахдат:
```console
[08:20:11] Train 9 left station Dushanbe in the south
[08:20:11] Train 9 move towords station Vahdat from the south
[08:20:20] Train 9 arrived at station Vahdat from the south
[08:20:29] Train 9 left station Vahdat in the south
```
На станции Вахдат не было очереди, поэтому проезд сразу прибыл на нее.

Худжанд:
```console
[08:20:29] Train 9 left station Vahdat in the south
[08:20:29] Train 9 move towords station Khujand from the south
[08:20:32] Train 9 arrived at station Khujand from the south
[08:20:37] Train 9 left station Khujand in the south
```
На станцию Худжанда так же поезд 9 пришел без очереди - это объясняется тем что промежутки по прибытию разные и по остановке на станциях.

Так же по логам видно, что симуляция не заканчивается, пока пользователь не нажмет Enter, и поезд идет по новому кругу:
```console
[08:20:37] Train 9 left station Khujand in the south
[08:20:37] Train 9 move towords station Gafurov from the south
[08:20:43] Train 9 arrived at station Gafurov from the south
```
и дальше по тому же маршруту.

## Заключение
- **Правильность работы семафоров**  
  Логи показывают, что на каждой станции одновременно находится только один поезд по одному направлению движения (на одной платформе).
  Использование бинарных семафоров (`std::binary_semaphore`) обеспечивает эксклюзивный доступ к станции и корректное ожидание поезда в очереди.

- **Синхронизация потоков**  
  Каждый поезд реализован как отдельный поток (`std::jthread`), что позволяет моделировать реальное одновременное движение поездов с задержкой на перемещение между станциями.
  Все события логируются с точными временными метками.

- **Очередность прибытия на станцию**  
  Пример с поездом 9 демонстрирует корректное ожидание поезда, если станция занята: поезд выезжает только после того, как предыдущий поезд освободил станцию по определенной платформе.

- **Практическая ценность логов**  
  Консольный вывод позволяет наглядно отслеживать движение поездов, моменты прибытия и отбытия, а также подтверждает корректность работы синхронизации потоков.
