#include <iostream>
#include <map>
#include <ctime>
#include <iomanip>
#include <string>
#include <time.h>

std::map<std::time_t, std::string> filling_base() {
    std::map<std::time_t, std::string> temp;
    std::string nameTemp;
    std::time_t t = std::time(nullptr);
    std::tm t_temp = *std::localtime(&t);
    std::map<std::time_t, std::string>::iterator it;
    while (true) {
        std::cout << "Input name: ";
        std::cin >> nameTemp;
        if (nameTemp == "end") break;
        std::cout << "Input birth day date YYYY/MM/DD: ";
        std::cin >> std::get_time(&t_temp, "%Y/%m/%d");
        it = temp.find(mktime(&t_temp));
        if (it != temp.end()) it->second += ", " + nameTemp;
        else temp.insert(std::pair<std::time_t, std::string> (mktime(&t_temp), nameTemp));
    }
    return temp;
}

std::time_t checking(std::map<std::time_t, std::string> db) {
    int result = 365;
    std::map<std::time_t, std::string>::iterator it = db.begin();
    std::time_t temp = it->first;
    std::time_t now = std::time(nullptr);
    std::tm t_now = *std::localtime(&now);
    std::tm t_temp;
    while (it != db.end()) {
        t_temp = *localtime(&temp);
        if ((t_temp.tm_yday - t_now.tm_yday > 0) && (t_temp.tm_yday - t_now.tm_yday < result)) {
            temp = it->first;
            result = t_temp.tm_yday - t_now.tm_yday;
        }
        ++it;
    }
    return temp;
}

int main() {
    std::map<std::time_t, std::string> birthdaysDB = filling_base();

    std::time_t nearestBirthDay = checking(birthdaysDB);

    std::map<std::time_t, std::string>::iterator it = birthdaysDB.find(nearestBirthDay);
    std::cout << it->second;
    return 0;
}
