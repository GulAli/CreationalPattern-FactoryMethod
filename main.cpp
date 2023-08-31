/*
 * Creational Pattern / Factory Method
 * https://refactoring.guru/design-patterns/factory-method
*/

#include <iostream>

class Logistic
{
    public:
        virtual ~Logistic() = default;
        virtual int calculatePrice() const = 0;
};

class GroundLogistic : public Logistic
{
    private:
        int groundCostConstant = 3;
    public:
        int calculatePrice() const override { return groundCostConstant * 2; }
};

class SeaLogistic : public Logistic
{
    private:
        int seaCostConstant = 4;
    public:
        int calculatePrice() const override { return (seaCostConstant * 2) + 1; }
};

class Creator
{
    public:
        virtual ~Creator() = default;
        virtual Logistic* FactoryMethod() const = 0;

        int calculatePrice() const
        {
            int dummyPrice = 0;

            Logistic* L1 = this->FactoryMethod();

            dummyPrice = L1->calculatePrice();

            delete L1;
            return dummyPrice;
        }
};

class GroundLogisticCreator : public Creator
{
    public:
        Logistic* FactoryMethod() const override
        {
            return new GroundLogistic();
        }
};

class SeaLogisticCreator : public Creator
{
    public:
        Logistic* FactoryMethod() const override
        {
            return new SeaLogistic();
        }
};

void ClientCodeCalculatePrice(Creator& creator)
{
    if( nullptr != dynamic_cast<GroundLogisticCreator*>(&creator) )
    {
        // Ground logistic was created. Calculate ground logistic price.
        std::cout << "Ground Logistic Price  is " << creator.calculatePrice() << '\n';
    }
    else if (nullptr != dynamic_cast<SeaLogisticCreator*>(&creator))
    {
        // Sea logistic was created. Calculate sea logistic price.
        std::cout << "Sea Logistic Price  is " << creator.calculatePrice() << '\n';
    }
    else
    {
        std::cout << "WTF!?\n";
    }
}

int main()
{
    std::cout << "//////////////////////// START \n";
    Creator* GL = new GroundLogisticCreator();
    ClientCodeCalculatePrice(*GL);

    Creator* SL = new SeaLogisticCreator();
    ClientCodeCalculatePrice(*SL);
    std::cout << "//////////////////////// END \n";
    return 0;
}