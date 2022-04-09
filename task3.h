#include <algorithm>

class ICitizen{
public:
    virtual void listen(int, const std::string&) = 0;
};

//Доктор немного глуховат
class Doctor: public ICitizen{
private:
    int hearingPower = 100;
public:
    void listen(int voicePower, const std::string& announcement) override {
        if (voicePower > hearingPower)
            std::cout << "\nThe Doctor have heard:\n\'"
                << announcement << '\'';
    }
};

class Blacksmith: public ICitizen{
private:
    int hearingPower = 30;
public:
    void listen(int voicePower, const std::string& announcement) override {
        if (voicePower > hearingPower)
            std::cout << "\nThe Blacksmith have heard:\n\'"
                << announcement << '\'';
    }
};

class Child: public ICitizen{
private:
    int hearingPower = 50;
public:
    void listen(int voicePower, const std::string& announcement) override {
        if (voicePower > hearingPower);
            std::cout << "\nThe Child have heard:\n\'"
                << announcement << '\'';
    }
};

//Subject Observable
class Herald{
private:
    int voicePower;
    std::string announcement;
    std::vector<ICitizen*> citizens;

public:
    Herald() : voicePower { 70 },
               announcement { "Achtung!" },
               citizens{}
                 {}

    ~Herald(){
        for (const auto &citizen: citizens)
            delete citizen;
    }

    const int getVoicePower() const {
        return voicePower;
    };

    const std::string &getAnnouncement() const{
        return announcement;
    };

    void setVoicePower(int inputAir){
        voicePower = inputAir;
    }

    void setAnnouncement(const std::string &textFromScroll){
        announcement = textFromScroll;
    }

    //registerObserver()
    void inviteOneCitizen(ICitizen *oneCitizen){
        citizens.push_back(oneCitizen);
    }

    //notifyObservers()
    void changeAnnouncment(){

        for(const auto citizen : citizens){
            citizen->listen(voicePower, announcement);
        }
    }

    //removeObserver(), позвать стражу и выгнать неугодного горожанина с площади
    void kickAwayOneCitizen(ICitizen *unwantedCitizen){
       auto citizenToKick = std::find(citizens.begin(),
        citizens.end(), unwantedCitizen);

       citizens.erase(citizenToKick);
    }
};
