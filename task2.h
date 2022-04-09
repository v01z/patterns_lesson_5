#include <vector>

class MenuItemFish;
class MenuItemMeat;
class Visitor;

class Ingredient{
public:
    int _healthRating;
    float _calories;
    float _protein;
    float _carbs;
    float _fats;

    Ingredient(int healthRating, float Calories, float Protein,
               float Carbs, float Fats):
               _healthRating{ healthRating },
               _calories { Calories },
               _protein { Protein },
               _carbs { Carbs },
               _fats { Fats }
               {}
};

class Menu{
private:
    Ingredient _ingredient;

protected:
    float _price;

    Menu(const Ingredient &ingredient, float price):
        _ingredient{ ingredient },
        _price{ price }
            {}

public:

    const Ingredient &getIngredient() const{
        return _ingredient;
    }

    virtual void printDescription() const = 0;

    //accept()
    virtual void getState(Visitor*) = 0;
};

class Visitor{
protected:
    virtual void shortDescription() = 0;

    void printIngredientInfo(Menu *menuItem) const{
        std::printf("Health rating: %d\n", menuItem->getIngredient()._healthRating);
        std::printf("Calories: %.2f\n", menuItem->getIngredient()._calories);
        std::printf("Protein: %.2f\n", menuItem->getIngredient()._protein);
        std::printf("Carbs: %.2f\n", menuItem->getIngredient()._carbs);
        std::printf("Fats: %.2f\n", menuItem->getIngredient()._fats);
    }

public:
    virtual void visit(MenuItemFish*) = 0;
    virtual void visit(MenuItemMeat*) = 0;
};

class MenuItemFish: public Menu{
private:
    std::string _name;
    bool _isSeaFish;
public:
    MenuItemFish(const Ingredient &ingredient, float price,
        const std::string &name, bool isSeaFish) :
            Menu(ingredient, price),
            _name{ name },
            _isSeaFish { isSeaFish }
                {}

    void printDescription() const override{
        std::printf("%s is a %s fish. Price: %.2f RUB\n",
                    _name.c_str(), ((_isSeaFish)?"sea":"river"), _price);
    }

    void getState(Visitor *visitor) override{
        visitor->visit(this);
    }
};

class MenuItemMeat: public Menu{
private:
    std::string _type;
public:
    MenuItemMeat(const Ingredient &ingredient, float price,
        const std::string &type):
            Menu(ingredient, price),
            _type{ type }
               {}

    void printDescription() const override{
        std::printf ("%s. Price: %.2f RUB\n", _type.c_str(), _price);
    }

    void getState(Visitor *visitor) override{
        visitor->visit(this);
    }
};

class InspectionVisitor: public Visitor{
private:
    bool descriptionShown { false };

    void shortDescription() override{
        if (!descriptionShown)
        {
            std::cout << "\n********************************************\n";
            std::cout << "Inspector visited restaurant and made some tests.\n";
            descriptionShown = true;
        }
    }

public:
    void visit (MenuItemFish *menuItemFish) override{

        shortDescription();
        std::cout << "\nInspector asked for a fish info.\n";

        menuItemFish->printDescription();
        printIngredientInfo(menuItemFish);
    }

    void visit (MenuItemMeat *menuItemMeat) override{

        shortDescription();
        std::cout << "\nInspector asked for a meat info.\n";

        menuItemMeat->printDescription();
        printIngredientInfo(menuItemMeat);
    }
};

class OrdinaryVisitor: public Visitor{
private:
    bool descriptionShown { false };

    void shortDescription() override{
        if (!descriptionShown)
        {
            std::cout << "\n********************************************\n";
            std::cout << "Ordinary person visited restaurant and had a meal.\n";
            std::cout << "He always took care of his health, so he asked for\n";
            std::cout << "a more detailed information about food he had eaten.\n";

            descriptionShown = true;
        }
    }

public:
    void visit (MenuItemFish *menuItemFish) override{

        shortDescription();
        std::cout << "\nClient asked for a fish info.\n";

        menuItemFish->printDescription();
        printIngredientInfo(menuItemFish);
    }

    void visit (MenuItemMeat *menuItemMeat) override{

        shortDescription();
        std::cout << "\nClient asked for a meat info.\n";

        menuItemMeat->printDescription();
        printIngredientInfo(menuItemMeat);
    }
};
