#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <conio.h>
#include <windows.h>

struct RadioStation {
    std::string name;
    std::string url;
};


void displayMenu(const std::vector<RadioStation>& stations, int selectedIdx, const std::string& currentPlaying) {
    std::system("cls");
    std::cout << "C++ FM | Russian Radio" << std::endl;
    std::cout << "Active Stations: " << std::endl;
    std::cout << "" << std::endl;


    for (size_t i = 0; i < stations.size(); i++) {
        if (i == static_cast<size_t>(selectedIdx)) {
            std::cout << "-> [*] " << i + 1 << ". " << stations[i].name;
            if (currentPlaying == stations[i].url && !currentPlaying.empty()) {
                std::cout << " (NOW PLAYING)";
            }
            std::cout << std::endl;
        }
        else {
            std::cout << "   [ ] " << i + 1 << ". " << stations[i].name << std::endl;
        }
    }

    std::cout << std::endl;
    std::cout << "https://github.com/SystemOfExploit" << std::endl;
    std::cout << std::endl;
    std::cout << "[Arrows UP/DOWN] - Select | [ENTER] - Play | [СTRL+C] - Quit" << std::endl;
}

int main() {

    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    std::vector<RadioStation> stations = {
        {"Vesti FM", "http://icecast.vgtrk.cdnvideo.ru/vestifm_mp3_128kbps"},
        {"Radio Mayak", "https://icecast-vgtrk.cdnvideo.ru/mayakfm_aac_64kbps"},
        {"Russkoe Radio", "https://rusradio.hostingradio.ru/rusradio128.mp3"},
        {"Radio Shanson", "https://chanson.hostingradio.ru:8041/chanson256.mp3"},
        {"Hype FM", "http://air.volna.top/HypeFM"},
        {"Retro FM", "https://retro.hostingradio.ru:8014/retro320.mp3"},
        {"Dorozhnoe Radio", "https://dorognoe.hostingradio.ru/radio"},
        {"Nashe Radio", "https://nashe1.hostingradio.ru/nashe-256"},
        {"Radio Vanya", "http://icecast-radiovanya.cdnvideo.ru/radiovanya"},
        {"My own radio(mp3-stream-link)", "CUSTOM"}
    };

    int selectedIdx = 0;
    int totalStations = stations.size();
    std::string currentPlaying = "";
    bool running = true;

    while (running) {
        displayMenu(stations, selectedIdx, currentPlaying);

        int ch = _getch();

        if (ch == 0 || ch == 224) {
            int arrow = _getch();

            if (arrow == 72) {
                selectedIdx = (selectedIdx - 1 + totalStations) % totalStations;
            }
            else if (arrow == 80) {
                selectedIdx = (selectedIdx + 1) % totalStations;
            }
        }

        else if (ch == 27) {
            running = false;
        }

        else if (ch == 13) {
            std::string url = stations[selectedIdx].url;

            if (url == "CUSTOM") {
                std::system("cls");
                std::cout << "Enter your mp3-stream-link: ";
                std::cin >> url;
            }

            currentPlaying = url;
            std::system("cls");
            std::cout << "Connecting to " << stations[selectedIdx].name << "..." << std::endl;

            std::string command = "taskkill /F /IM mpv.exe >nul 2>&1 & start /b lib\\mpv --no-video " + url + " >nul 2>&1";
            std::system(command.c_str());
            Sleep(1000);
        }
    }

    std::system("taskkill /F /IM mpv.exe >nul 2>&1");
    std::system("cls");
    std::cout << "Radio Closed!" << std::endl;

    return 0;
}