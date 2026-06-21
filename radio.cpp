#include <iostream>
#include <string>
#include <cstdlib>


int main() {
    int input;

    std::string url = "";
    std::cout << "C++ FM | Russian Radio" << std::endl;
    std::cout << "Active statios: " << std::endl;
    std::cout << "" << std::endl;
    std::cout << "1. Vesti FM" << std::endl;
    std::cout << "2. Radio Mayak" << std::endl;
    std::cout << "3. Russkoe Radio" << std::endl;
    std::cout << "4. Radio Shanson" << std::endl;
    std::cout << "5. Hype FM" << std::endl;
    std::cout << "6. Retro FM" << std::endl;
    std::cout << "7. Dorozhnoe Radio" << std::endl;
    std::cout << "8. Nashe Radio" << std::endl;
    std::cout << "9. Radio Vanya" << std::endl;
    std::cout << "10. My own radio(mp3-stream-link)" << std::endl;
    std::cout << "" << std::endl;
    std::cout << "https://github.com/SystemOfExploit" << std::endl;
    std::cout << "" << std::endl;
    std::cout << "Select: ";
    std::cin >> input;

    if (input == 1) {
        url = "http://icecast.vgtrk.cdnvideo.ru/vestifm_mp3_128kbps";
    } else if (input == 2) {
        url = "https://icecast-vgtrk.cdnvideo.ru/mayakfm_aac_64kbps";
    } else if (input == 3) {
        url = "https://rusradio.hostingradio.ru/rusradio128.mp3";
    } else if (input == 4) {
        url = "https://chanson.hostingradio.ru:8041/chanson256.mp3";
    } else if (input == 5) {
        url = "http://air.volna.top/HypeFM";
    } else if (input == 6) {
        url = "https://retro.hostingradio.ru:8014/retro320.mp3";
    } else if (input == 7) {
        url = "https://dorognoe.hostingradio.ru/radio";
    } else if (input == 8) {
        url = "https://nashe1.hostingradio.ru/nashe-256";
    } else if (input == 9) {
        url = "http://icecast-radiovanya.cdnvideo.ru/radiovanya";
    } else if (input == 10) {
        std::cin >> url;
    } else {
        std::cout << "Unknown Station" << std::endl;
    }

    std::string command = "mpv " + url;
    std::cout << "Connecting...";
    std::system(command.c_str());

    return 0;
}
