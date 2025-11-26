#include <iostream>
#include <thread>
#include <mutex>
#include <semaphore>
#include <map>
#include <chrono>
#include <queue>
#include <algorithm>

std::map<std::string, std::unique_ptr<std::binary_semaphore>> sems;
std::mutex m;

std::string now() {
    time_t t = time(nullptr);
    tm* lt = localtime(&t);
    char buf[32];
    strftime(buf, sizeof(buf), "%H:%M:%S", lt);
    return buf;
}

void train_way(std::string station, std::thread::id train_id){
    std::binary_semaphore* sem;
    {
        std::lock_guard<std::mutex> lock(m);
        auto it = sems.find(station);
        if(it == sems.end()){
            sems[station] = std::make_unique<std::binary_semaphore>(1);
            sem = sems[station].get();
        }
        else{
            sem = it->second.get();
        }
    }

    sem->acquire();
    {
        std::lock_guard<std::mutex> lock(m);
        std::cout << "["<< now() << "] " <<  "Train " << train_id << " move towords station " << station << "\n";
    }

    std::this_thread::sleep_for(std::chrono::seconds(1 + std::rand() % 10));

    {
        std::lock_guard<std::mutex> lock(m);
        std::cout << "["<< now() << "] " << "Train " << train_id << " arrived at station " << station << "\n";
    }

    std::this_thread::sleep_for(std::chrono::seconds(1 + std::rand() % 10));

    {
        std::lock_guard<std::mutex> lock(m);
        std::cout << "["<< now() << "] " << "Train " << train_id << " left station " << station << "\n";
    }

    sem->release();
}

int main(){
    srand(time(NULL));

    std::vector<std::string> routeA = {"Dushanbe", "Vahdat", "Obigarm", "Rasht", "Nurobod"};
    std::vector<std::string> routeB = {"Khujand", "Gafurov", "Buston", "Dushanbe", "Vahdat"};
    std::vector<std::string> routeC = {"Kulyab", "Vose", "Dangara", "Dushanbe", "Obigarm"};
    std::vector<std::string> routeD = {"Bokhtar", "Qurghonteppa", "Vose", "Rudaki", "Dushanbe"};
    std::vector<std::string> routeE = {"Khujand", "Istaravshan", "Gafurov", "Buston", "Kulyab"};
    std::vector<std::string> routeF = {"Rasht", "Nurobod", "Obigarm", "Vahdat", "Dushanbe"};

    std::vector<std::vector<std::string>> allRoutes = {routeA, routeB, routeC, routeD, routeE, routeF};

    std::vector<std::jthread> trains;
    trains.reserve(8);
    std::vector<std::string> route = allRoutes[std::rand() % allRoutes.size()];

    for (int i = 0; i < 8; ++i) {
        std::vector<std::string> trainRoute = route;
        std::rotate(trainRoute.begin(), trainRoute.begin() + (i % route.size()), trainRoute.end());
        trains.emplace_back([trainRoute]() {
            {
                std::lock_guard<std::mutex> lock(m);
                std::cout << "Train " << std::this_thread::get_id()
                          << " has route " << trainRoute[0] << " - " << trainRoute[trainRoute.size() - 1] << "\n";
            }
            for (auto& way : trainRoute) {
                train_way(way, std::this_thread::get_id());
            }
        });
    }

    {
        std::lock_guard<std::mutex> lock(m);
        std::cout << "\n=== SIMULATION COMPLETE ===\n";
    }
    return 0;
}
