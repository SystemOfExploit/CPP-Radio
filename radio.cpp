#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <termios.h>
#include <unistd.h>

struct RadioStation {
    std::string name;
    std::string url;
};

int getch_linux() {
    struct termios oldt, newt;
    int ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    return ch;
}

void displayMenu(const std::vector<RadioStation>& stations, int selectedIdx, const std::string& currentPlaying) {
    std::system("clear");
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
        } else {
            std::cout << "   [ ] " << i + 1 << ". " << stations[i].name << std::endl;
        }
    }

    std::cout << std::endl;
    std::cout << "https://github.com/SystemOfExploit" << std::endl;
    std::cout << std::endl;
    std::cout << "[Arrows UP/DOWN] - Select | [ENTER] - Play | [СTRL+C] - Quit" << std::endl;
}

int main() {
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

        int ch = getch_linux();

        if (ch == 27) {
            struct termios oldt, newt;
            tcgetattr(STDIN_FILENO, &oldt);
            newt = oldt;
            newt.c_cc[VMIN] = 0;
            newt.c_cc[VTIME] = 1;
            tcsetattr(STDIN_FILENO, TCSANOW, &newt);

            int next_ch1 = getchar();
            int next_ch2 = getchar();

            tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

            if (next_ch1 == '[' || next_ch1 == 'O') {
                if (next_ch2 == 'A') {
                    selectedIdx = (selectedIdx - 1 + totalStations) % totalStations;
                }
                else if (next_ch2 == 'B') {
                    selectedIdx = (selectedIdx + 1) % totalStations;
                }
            }
            else if (next_ch1 == EOF) {
                running = false;
            }
        }
        else if (ch == 10) {
            std::string url = stations[selectedIdx].url;

            if (url == "CUSTOM") {
                std::system("clear");
                std::cout << "Enter your mp3-stream-link: ";
                struct termios oldt;
                tcgetattr(STDIN_FILENO, &oldt);
                struct termios newt = oldt;
                newt.c_lflag |= (ICANON | ECHO);
                tcsetattr(STDIN_FILENO, TCSANOW, &newt);

                std::cin >> url;

                tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
            }

            currentPlaying = url;
            std::system("clear");
            std::cout << "Connecting to " << stations[selectedIdx].name << "..." << std::endl;

            std::string command = "pkill mpv; mpv --no-video " + url + " > /dev/null 2>&1 &";
            std::system(command.c_str());

            sleep(1);
        }
    }

    std::system("pkill mpv");
    std::system("clear");
    std::cout << "Radio Closed!" << std::endl;

    return 0;
}
