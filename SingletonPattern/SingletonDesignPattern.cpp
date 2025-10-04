#include<iostream>

using namespace std;

class GameConfiguration
{
private:
    static GameConfiguration* _gameConfig;
    int _brightness;
    int _mode;
    int _width;
    int _height;
    GameConfiguration(int brightness, int mode, int width, int height) : \
        _brightness(brightness), _mode(mode), _width(width), _height(height) {}
public:
    ~GameConfiguration() = default;
    void set_Brightness(int val) {
        _brightness = val;
    }
    void set_Width(int val) {
        _width = val;
    }
    void set_Height(int val) {
        _height = val;
    }
    static GameConfiguration* getInstance() {
        if (_gameConfig == nullptr)
            return new GameConfiguration(80, 1, 766, 1080);
        return _gameConfig;
    }
    void displayConfig()
    {
        cout << "Brightness = " << _brightness << " Height= " << _height << " Width = " << _width << endl;
    }

};

GameConfiguration* GameConfiguration::_gameConfig = nullptr;

int main()
{
    GameConfiguration* conf = GameConfiguration::getInstance();

    conf->displayConfig();
    conf->set_Brightness(100);
    conf->displayConfig();
}