#include "classes.hpp"

namespace ts
{
    class var
    {
        //Создаю массив чаров, длиной 0.
        char *string = new char[0];
        int size = 0;
    public:
        var() {}

        var(char &symbol)
        {
            ExpandString();
            string[size-1] = symbol;
        }



        ~var(){delete[] string;}



        void Add(char symbol)
        {
            ExpandString();
            string[size-1] = symbol;
        }

        void Replace(char symbol, unsigned int numberElement)
        {
            if(numberElement < size)
                string[numberElement] = symbol;
            else
                std::cout << "ERROR! Element " << numberElement <<" not found!" << std::endl;
        }
        void ReplaceLast(char symbol)
        {
            if(!IsEmpty())
                string[size-1] = symbol;
        }

        void Paste(char symbol, int wherePaste)
        {
            if(wherePaste <= size && wherePaste >= 0)
            {
                ExpandString();
                for (int i = size - 1; i > wherePaste - 1; --i)
                {
                    string[i + 1] = string[i];
                }
                string[wherePaste] = symbol;
            }
            else
                std::cout << "ERROR! WherePaste " << wherePaste <<" not found!" << std::endl;
        }

        void PasteFirst(char symbol)
        {
            ExpandString();
            for (int i = size - 1; i >= 0; --i)
            {
                string[i + 1] = string[i];
            }
            string[0] = symbol;
        }


        int Size()
        {
            return size;
        }

        

        char Get(int symbolNumber)
        {
            return string[symbolNumber];
        }
        char GetLast()
        {
            return string[size-1];
        }

        bool IsEmpty()
        {
            if (size == 0)
                return 1;
        }

        bool IsDigit(int symbolNumber)
        {
            if (string[symbolNumber] >= 48 && string[symbolNumber] < 58)
                return 1;
            else
                return 0;
        }

        bool IsNumber()
        {
            if (string[0] == 44 || string[0] == 46 || string[size-1] == 44 || string[size-1] == 46)
                return 0;
            int points = 0;
            for (int i = 0; i < size; i++)
            {
                if(!IsDigit(i))
                {
                    std::cout << string[i] << "    ETO NE CIFRA" << std::endl;
                    if (string[i] == 44 || string[i] == 46)
                    {
                        points++;
                        std::cout << "points:" << points;
                        if(points > 1)
                            return 0;
                    }
                    else
                        return 0;
                }
            }
            return 1;
        }

        void Sum(var B)
        {
            //НАДО УДАЛИТЬ ВСЕ НУЛИ В НАЧАЛЕ МАССИВОВ, НО ЕСЛИ ЕСТЬ ТОЧКА, ТО ЕЕ НЕ УДАЛЯТЬ//ЕСЛИ ПРЕДЫДУЩАЯ ЦИФРА ТОЧКА ИЛИ ЗАПЯТАЯ, ТО ПРИ ПЕРЕНОСЕ РАЗРЯДА НАДО ПЕРЕНЕСТИ НА 1 ЭЛЕМЕНТ РАНЬШЕ
            //Добавить поддержку отрицательных чисел
            //Добавлять нули
            //если точка и размер строки одинаковый
            if(IsNumber() && B.IsNumber())
            {
                FormatNumberString(B);
                bool mind = 0;
                for (int i = 1; i <= size; i++)
                {
                    if(string[size-i] != 44 && string[size-i] != 46)
                    {
                        char a = Get(size-i);
                        char b = B.Get(B.Size()-i)-48;
                        a = a + b + mind;
                        mind = 0;
                        if (a > 57)
                        {
                            mind = 1;
                            a -= 10;
                        }
                        Replace(a, size-i);
                    }
                    else
                    std::cout << "aaaaaaaaaaaaaaaa" << size << std::endl;
                }
                if (mind == 1)
                {
                    PasteFirst(49);
                }
                //mind = 0;
            }
            else
            {
                ExpandStringBy(B.Size());
                for (int i = 0; i < B.Size(); i++)
                {
                    Replace(B.Get(i), size-B.Size()+i);
                }
            }
        }

        int SearchZero()
        {
            int a = 0;
            char b = Get(a);
            while (b == 48)
            {
                a += 1;
                b = Get(a);
            }
            if (b == 44 || b == 46)
                a -= 1;
            return a-1;
        }

        int SearchPoint() 
        {
            char b;
            for (int i = 0; i < size; i++) 
            {
                b = Get(i);
                if (b == 44 || b == 46)
                    return i;
            }
            return size;
        }

        void ReduceBeginBy(int howMuchReduce)
        {
            char *tempString = new char[size-howMuchReduce];
            for (int i = 0; i < size-howMuchReduce; ++i)
            {
                tempString[i] = string[howMuchReduce+i];
            }
            delete[] string;
            string = tempString;
            size-=howMuchReduce;
        }


        void DeleteFirstUselessZeroes()
        {
            ReduceBeginBy(SearchZero()+1);
        }

        void AddZeroes(int pointA, int pointB)
        {
            int difference = pointB - pointA;
            ExpandStringBy(difference);
            for (int i = size-1; i <=difference; i--)
            {
                string[i] = string[i-1];
            }
            for (int i = 0; i < difference; i++)
            {
                string[i] = 0;
            }
        }

        void FormatNumberString(var b)
        {
            std::cout << "Hello, world" << std::endl;
            int pointA = SearchPoint();
            int pointB = b.SearchPoint();
            if(pointA != pointB || size != b.Size())
            {
                DeleteFirstUselessZeroes();
                b.DeleteFirstUselessZeroes();
                if(pointA < pointB)
                {
                    AddZeroes(pointA, pointB);
                }
                else
                    b.AddZeroes(pointB, pointA);
            }
        }

    private:
        void ExpandString()
        {
            char *tempString = new char[size+1];
            for (int i = 0; i < size; ++i)
            {
                tempString[i] = string[i];
            }
            delete[] string;
            string = tempString;
            size++;
        }

        void ExpandStringBy(int howMuch)
        {
            char *tempString = new char[size+howMuch];
            for (int i = 0; i < size; ++i)
            {
                tempString[i] = string[i];
            }
            delete[] string;
            string = tempString;
            size+=howMuch;
        }

        void ReduceString()
        {
            if(size>0) {
                char *tempString = new char[size - 1];
                for (int i = 0; i < size - 1; ++i) {
                    tempString[i] = string[i];
                }
                delete[] string;
                string = tempString;
                size--;
            }
            else
                std::cout << "ERROR! Array size = 0! You can not do it!" << std::endl;
        }
    };
}