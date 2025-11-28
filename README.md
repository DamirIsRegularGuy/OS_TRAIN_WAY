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
2. Проходит промежуток времени, имитирующий движение и пребывание на станции.  
3. Освобождает семафор после отбытия.

### 4. Логирование событий
- Все действия (отбытие, прибытие) выводятся в консоль с текущим временем.  
- Формат вывода позволяет отслеживать порядок движения поездов и занятие станций.


## Вывод программы
```console
Train 2 has route Khujand - Kulyab
Train 4 has route Gafurov - Istaravshan
Train 6 has route Kulyab - Buston
Train 9 has route Gafurov - Istaravshan
Train 3 has route Istaravshan - Khujand
Train 5 has route Buston - Gafurov
Train 8 has route Istaravshan - Khujand
Train 7 has route Khujand - Kulyab

[10:47:53]  Train 2 move towords station Khujand
[10:47:53]  Train 5 move towords station Buston
[10:47:53]  Train 3 move towords station Istaravshan
[10:47:53]  Train 6 move towords station Kulyab
[10:47:53]  Train 4 move towords station Gafurov
[10:47:55] Train 3 arrived at station Istaravshan
[10:47:55] Train 5 arrived at station Buston
[10:47:55] Train 4 arrived at station Gafurov
[10:47:55] Train 2 arrived at station Khujand
[10:47:55] Train 6 arrived at station Kulyab
[10:48:03] Train 5 left station Buston
[10:48:03] Train 6 left station Kulyab
[10:48:03] Train 4 left station Gafurov
[10:48:03] Train 3 left station Istaravshan
[10:48:03]  Train 5 move towords station Kulyab
[10:48:03]  Train 4 move towords station Buston
[10:48:03]  Train 8 move towords station Istaravshan
[10:48:03] Train 2 left station Khujand
[10:48:03]  Train 9 move towords station Gafurov
[10:48:03]  Train 6 move towords station Khujand
[10:48:05] Train 9 arrived at station Gafurov
[10:48:05] Train 8 arrived at station Istaravshan
[10:48:08] Train 6 arrived at station Khujand
[10:48:08] Train 5 arrived at station Kulyab
[10:48:08] Train 4 arrived at station Buston
[10:48:09] Train 5 left station Kulyab
[10:48:09] Train 4 left station Buston
[10:48:09] Train 6 left station Khujand
[10:48:09]  Train 4 move towords station Kulyab
[10:48:09]  Train 5 move towords station Khujand
[10:48:13] Train 8 left station Istaravshan
[10:48:13] Train 9 left station Gafurov
[10:48:13]  Train 8 move towords station Gafurov
[10:48:13]  Train 9 move towords station Buston
[10:48:13]  Train 6 move towords station Istaravshan
[10:48:18] Train 8 arrived at station Gafurov
[10:48:18] Train 9 arrived at station Buston
[10:48:19] Train 9 left station Buston
[10:48:19] Train 8 left station Gafurov
[10:48:19] Train 4 arrived at station Kulyab
[10:48:19] Train 5 arrived at station Khujand
[10:48:19]  Train 8 move towords station Buston
[10:48:19]  Train 3 move towords station Gafurov
[10:48:23] Train 6 arrived at station Istaravshan
[10:48:24] Train 3 arrived at station Gafurov
[10:48:24] Train 5 left station Khujand
[10:48:24] Train 4 left station Kulyab
[10:48:24]  Train 9 move towords station Kulyab
[10:48:24]  Train 7 move towords station Khujand
[10:48:25] Train 3 left station Gafurov
[10:48:26] Train 7 arrived at station Khujand
[10:48:28] Train 6 left station Istaravshan
[10:48:28]  Train 2 move towords station Istaravshan
[10:48:28]  Train 6 move towords station Gafurov
[10:48:29] Train 8 arrived at station Buston
[10:48:33] Train 2 arrived at station Istaravshan
[10:48:34] Train 9 arrived at station Kulyab
[10:48:34] Train 7 left station Khujand
[10:48:34] Train 8 left station Buston
[10:48:34] Train 2 left station Istaravshan
[10:48:34]  Train 5 move towords station Istaravshan
[10:48:34]  Train 3 move towords station Buston
[10:48:34]  Train 4 move towords station Khujand
[10:48:37] Train 6 arrived at station Gafurov
[10:48:39] Train 9 left station Kulyab
[10:48:39]  Train 8 move towords station Kulyab
[10:48:43] Train 5 arrived at station Istaravshan
[10:48:43] Train 4 arrived at station Khujand
[10:48:44] Train 3 arrived at station Buston
[10:48:46] Train 6 left station Gafurov
[10:48:46]  Train 2 move towords station Gafurov
[10:48:48] Train 8 arrived at station Kulyab
[10:48:49] Train 3 left station Buston
[10:48:49]  Train 6 move towords station Buston
[10:48:52] Train 5 left station Istaravshan
[10:48:52]  Train 7 move towords station Istaravshan
[10:48:52] Train 4 left station Khujand
[10:48:52] Train 6 arrived at station Buston
[10:48:52]  Train 9 move towords station Khujand
[10:48:56] Train 2 arrived at station Gafurov
[10:48:57] Train 7 arrived at station Istaravshan
[10:48:57] Train 8 left station Kulyab
[10:48:57]  Train 3 move towords station Kulyab
[10:48:57] Train 6 left station Buston
[10:48:58] Train 7 left station Istaravshan
[10:48:58]  Train 4 move towords station Istaravshan
[10:49:01] Train 2 left station Gafurov
[10:49:01]  Train 7 move towords station Gafurov
[10:49:01]  Train 2 move towords station Buston
[10:49:01] Train 4 arrived at station Istaravshan
[10:49:01] Train 9 arrived at station Khujand
[10:49:06] Train 3 arrived at station Kulyab
[10:49:06] Train 4 left station Istaravshan
[10:49:10] Train 2 arrived at station Buston
[10:49:10] Train 9 left station Khujand
[10:49:10]  Train 9 move towords station Istaravshan
[10:49:10]  Train 8 move towords station Khujand
[10:49:11] Train 7 arrived at station Gafurov
[10:49:13] Train 9 arrived at station Istaravshan
[10:49:13] Train 8 arrived at station Khujand
[10:49:15] Train 3 left station Kulyab
[10:49:16] Train 7 left station Gafurov
[10:49:16]  Train 5 move towords station Gafurov
[10:49:18] Train 9 left station Istaravshan
[10:49:18] Train 8 left station Khujand
[10:49:18]  Train 3 move towords station Khujand
[10:49:19] Train 2 left station Buston
[10:49:19]  Train 2 move towords station Kulyab
[10:49:19]  Train 7 move towords station Buston
[10:49:19] Train 5 arrived at station Gafurov
[10:49:21] Train 3 arrived at station Khujand
[10:49:22] Train 2 arrived at station Kulyab
[10:49:24] Train 5 left station Gafurov
[10:49:26] Train 3 left station Khujand
[10:49:27] Train 2 left station Kulyab
[10:49:28] Train 7 arrived at station Buston
[10:49:37] Train 7 left station Buston
[10:49:37]  Train 7 move towords station Kulyab
[10:49:40] Train 7 arrived at station Kulyab
[10:49:45] Train 7 left station Kulyab
Train 3 stopped.
Train 2 stopped.
Train 4 stopped.
Train 6 stopped.
Train 9 stopped.
Train 5 stopped.
Train 8 stopped.
Train 7 stopped.

=== SIMULATION COMPLETE ===
```
## Анализ Вывода
Рассмотрим поезд номер 7, за один круг, по маршруту Худжанд - Куляб (*Train 7 has route Khujand - Kulyab*), маршрут состоит из станций в 5 городах:
 - Худжанд
 - Истарафшан
 - Гафуров
 - Бустон
 - Куляб

В Худжанд есть очередь из поездов, первым прибыл поезд 2, остальные в очереди
Худжанд:
```console
[10:47:53] Train 2 move towords station Khujand
[10:48:03] Train 2 left station Khujand
[10:48:03] Train 6 move towords station Khujand
[10:48:09] Train 6 left station Khujand
[10:48:09] Train 5 move towords station Khujand
[10:48:24] Train 5 left station Khujand
[10:48:24] Train 7 move towords station Khujand
[10:48:26] Train 7 arrived at station Khujand
```
Наш поезд 7 был в очереди. Как только поезд начинает движение в сторону станции в каком-либо городе, станция становиться не доступной для других поездов.

Истарафшан:
```console
[10:48:26] Train 7 arrived at station Khujand
[10:48:28] Train 2 move towords station Istaravshan
[10:48:34] Train 2 left station Istaravshan
[10:48:34] Train 5 move towords station Istaravshan
[10:48:52] Train 5 left station Istaravshan
[10:48:52] Train 7 move towords station Istaravshan
[10:48:58] Train 7 left station Istaravshan
```
Как и ожидалось на станции в Истарафшане так же была очередь.

Гафуров:
```console
[10:48:58] Train 7 left station Istaravshan
[10:49:01] Train 2 left station Gafurov
[10:49:01] Train 7 move towords station Gafurov
[10:49:16] Train 7 left station Gafurov
```
В очереди на эту санцию поезд 7 был первым, поэтому сразу направился туда

Бустон:
```console
[10:49:19] Train 2 left station Buston
[10:49:19] Train 7 move towords station Buston
[10:49:37] Train 7 left station Buston
```
Поезд 2 имеет такой же маршрут как и наш поезд 7, поэтому он был в очереди за ним. 

Куляб:
```console
[10:49:37] Train 7 left station Buston
[10:49:37] Train 7 move towords station Kulyab
[10:49:40] Train 7 arrived at station Kulyab
[10:49:45] Train 7 left station Kulyab
```
Так как поезд 2 уже уехал со станции в Кулябе, она свободна, то поезд сразу напрвляется к этой станции

## Заключение
- **Правильность работы семафоров**  
  Логи показывают, что на каждой станции одновременно находится только один поезд.
  Использование бинарных семафоров (`std::binary_semaphore`) обеспечивает эксклюзивный доступ к станции и корректное ожидание поезда в очереди.

- **Синхронизация потоков**  
  Каждый поезд реализован как отдельный поток (`std::jthread`), что позволяет моделировать реальное одновременное движение поездов с задержкой на перемещение между станциями.
  Все события логируются с точными временными метками.

- **Очередность прибытия на станцию**  
  Пример с поездом 7 демонстрирует корректное ожидание поезда, если станция занята: поезд выезжает только после того, как предыдущий поезд освободил станцию.

- **Практическая ценность логов**  
  Консольный вывод позволяет наглядно отслеживать движение поездов, моменты прибытия и отбытия, а также подтверждает корректность работы синхронизации потоков.
