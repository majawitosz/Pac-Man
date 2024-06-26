#include "stdafx.h"

#include "Game.h"


static size_t my_write(void* buffer, size_t size, size_t nmemb, void* param)
{
    std::string& text = *static_cast<std::string*>(param);
    size_t totalsize = size * nmemb;
    text.append(static_cast<char*>(buffer), totalsize);
    return totalsize;
}

int main()
{
    //std::string result;
    //// Inicjalizacja curl
    //CURL* curl;
    //CURLcode res;
    //curl_global_init(CURL_GLOBAL_DEFAULT);
    //curl = curl_easy_init();
    //if (curl) {
    //    curl_easy_setopt(curl, CURLOPT_URL, "http://130.61.181.55:3000/request2"); //Podajemy na jaki adres chcemy wysłac żadanie
    //    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, my_write); //Wywolujemy funkcje
    //    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &result); // Podajemy zmienna do jakie chcemy zapisac dane
    //    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
    //    res = curl_easy_perform(curl);
    //    curl_easy_cleanup(curl);
    //    //Wyrzucenie bledu w przypadku blednej inicjalizacji curl
    //    if (CURLE_OK != res) {
    //        std::cerr << "CURL error: " << res << '\n';
    //    }
    //}
    //curl_global_cleanup();
    //std::cout << result << "\n\n";


    //Init srand
    std::srand(static_cast<unsigned>(time(NULL)));

    //Init game engine
    Game game;
    game.run();

    return 0;
}


