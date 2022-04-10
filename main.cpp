#include <iostream>
#include "task1.h"
#include "task2.h"
#include "task3.h"


int main() {
    //*************** task1 ******************

    MovieScreeningSession movieScreeningSession
        ("\'Star Wars: The Book of Bobba Fett\'");

    //Начнём просмотр
    movieScreeningSession.On();

    //Киносеанс окончен
    movieScreeningSession.Off();

    //*************** task2 ******************

    //Let us suppose that ingredient for a carp fish including the fish itself equals:
    Ingredient fishIngredient
        (85, 200.01f, 70.50f, 15.30f, 21.12f);

    //Let us suppose that ingredient for a pork meat including the pork itself equals:
    Ingredient porkIngredient
        (21, 500.55f, 370.77f, 30.15f, 170.18f);

    InspectionVisitor inspector;
    OrdinaryVisitor ordinaryVisitor;

    std::vector<Menu*> menu
    { new MenuItemFish(fishIngredient, 130.15f, "Carp", false),
      new MenuItemMeat(porkIngredient, 87.72f, "Pork") };

    for (const auto &menuItem : menu)
    {
        menuItem->getState(&inspector);
    }

    for (const auto &menuItem : menu)
    {
        menuItem->getState(&ordinaryVisitor);
    }

    for (const auto &menuItem : menu)
        delete menuItem;

    //*************** task3 ******************

    //"Слушайте все и не говорите, что не слышали!"
    const std::string announcement
    { "Hören Sie alle zu und sagen Sie nicht, Sie hätten es nicht gehört!" };

    //На площади находилось три гражданина
    ICitizen *doctor { new Doctor };
    ICitizen *blacksmith { new Blacksmith };
    ICitizen *child { new Child };

    //И один глашатай
    Herald herald;

    //Глашатай подозвал их поближе
    herald.inviteOneCitizen(doctor);
    herald.inviteOneCitizen(blacksmith);
    herald.inviteOneCitizen(child);

    //И прокричал
    herald.changeAnnouncment();

    //Заметив, что доктор его не услышал, повысил голос
    herald.setVoicePower(120);

    //Развернул лист пергамента с королевской печатью
    herald.setAnnouncement(announcement);

    //Теперь услышали все
    herald.changeAnnouncment();

	return 0;
}
