#include <iostream>
#include <string>

class Car {
private:
    std::string m_name;
    int m_id;

public:
    Car(const std::string& name, int id)
        : m_name { name }
        , m_id { id }
    {
    }

    const std::string& getName() const { return m_name; }
    int getId() const { return m_id; }
};

// CarLot 本质上是一个 static 的 Car 数组，以及一个用于获取它们的查询函数。
// 因为是 static 的，不需要为其分配一个 CarLot 类型的对象
class CarLot {
private:
    static Car s_carLot[4];

public:
    CarLot(/* args */) = delete; // 确保不会创建一个 CarLot

    static Car* getCar(int id)
    {
        for (int count { 0 }; count < 4; ++count) {
            if (s_carLot[count].getId() == id) {
                return &(s_carLot[count]);
            }
        }

        return nullptr;
    }
};

Car CarLot::s_carLot[4] {
    { "Prius", 4 }, { "Corolla", 17 }, { "Accord", 84 }, { "Matrix", 62 }
};

class Driver {
private:
    std::string m_name;
    int m_carId; // 可以通过 ID 而不是指针来关联 Car

public:
    Driver(const std::string& name, int carId)
        : m_name { name }
        , m_carId { carId }
    {
    }

    const std::string& getName() const { return m_name; }
    int getCarId() const { return m_carId; }
};
