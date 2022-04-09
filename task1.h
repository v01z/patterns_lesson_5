class Device{
public:
    std::string type;

    Device(const std::string &type) : type(type) {}
    virtual void On(){
        std::cout << type <<" is on" << std::endl;
    }
    virtual void Off(){
        std::cout << type <<" is off" << std::endl;
    }
};

class MediaPlayer: public Device{
private:
    std::string currentMovie;
public:
    MediaPlayer(const std::string &type) : Device(type) {}
    void play(std::string newMovie) {
        currentMovie = newMovie;
        std::cout << "Movie " << currentMovie << " started" << std::endl;

    }
};

class Amplifier: public Device{
    Device* streamingPLayer;
    int volume;
public:
    Amplifier(const std::string &type) : Device(type), volume(0) {}
    void setStreamingPlayer(Device* d){
        streamingPLayer = d;
        std::cout << "Streaming player is " << d->type << std::endl;
    }

    void setSurroundSound(){
        std::cout << "Surround Sound Mode" << std::endl;
    }

    void setVolume(int v){
        volume = v;
    }

};

class Projector: public Device{
private:
    Amplifier* _amplifier;
    Device* _input;
public:
    Projector(const std::string &type) : Device(type) {}

    void setInput(Device* d){
        _input = d;
        std::cout << "Projector input is " << d->type << std::endl;
    }
    void wideScreenMode(){
        std::cout << "Wide Screen Mode" << std::endl;
    }
};

//class Tuner{
class Tuner: public Device{
private:
    Amplifier* _amplifier;
public:
    void on(){
        std::cout << "Tuner on" << std::endl;
    }

    void off(){
        std::cout << "Tuner off" << std::endl;
    }
};

class Popper: public Device{
public:
    Popper(const std::string &type) : Device(type) {}

    void pop(){
        std::cout << "Popcorn will be ready soon" << std::endl;
    }
};

class Lights: public Device{
private:
    int currentLight;
public:
    Lights(const std::string &type) : Device(type), currentLight(100) {}
    void dim(int light){
        currentLight = light;
    }
};

class Screen: public Device{
public:
    Screen(const std::string &type) : Device(type) {}

    void down(){
        std::cout << "Screen is down" << std::endl;
    }

    void up(){
        std::cout << "Screen is up" << std::endl;
    }
};

//Фасад
class MovieScreeningSession{
private:
    std::string _filmName;

    MediaPlayer _mediaPlayer;
    Popper _popper;
    Lights _lights;
    Projector _projector;
    Screen _screen;
    Amplifier _amplifier;

public:
    //Каждый сеанс смотрим разные фильмы,
    MovieScreeningSession(const std::string &filmName,
    //а вот оборудование обычно не меняется, поэтому
    //предусмотрим дефолтные названия (к тому же это
    //упростит клиенту создание объекта-фасада)
           const std::string &mediaPlayerType = "media player",
           const std::string &popperType = "popper",
           const std::string &lightsType = "light",
           const std::string &projectorType = "projector",
           const std::string &screenType = "screen",
           const std::string &amplifierType = "Amplifier"):
                _filmName(filmName),
                _mediaPlayer(mediaPlayerType),
                _popper(popperType),
                _lights(lightsType),
                _projector(projectorType),
                _screen(screenType),
                _amplifier(amplifierType)
                    {}

    void On(){
        std::cout << "\n****** Starting Movie Screening Session.. *****\n";

        _popper.On();
        _popper.pop();

        _lights.dim(0);
        _screen.down();

        _projector.On();
        _projector.setInput(&_mediaPlayer);
        _projector.wideScreenMode();

        _amplifier.On();
        _amplifier.setStreamingPlayer(&_mediaPlayer);
        _amplifier.setSurroundSound();
        _amplifier.setVolume(5);

        _mediaPlayer.On();
        _mediaPlayer.play(_filmName);

    }

    void Off(){
       std::cout << "\n****** Movie Screening Session is turning off.. *****\n";

       //projector можно выключить и после выключения amplifier, так как
       //поле projector->_amplifier не инициализировано (не используется),
       //но оставлю так порядка ради
       _projector.Off();

       _amplifier.setVolume(0);
       _amplifier.Off();

       _mediaPlayer.Off();

       _screen.up();
       _lights.dim(100);

       _popper.Off();
    }
};

