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
                    if (string[i] == 44 || string[i] == 46)
                    {
                        points++;
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
                //Приведение к нужному формату, если формат не нужный
                if(size != B.Size() || SearchPoint() != B.SearchPoint())
                {
                    //Удаление нулей в начале
                    FormatNumberString(B);
                }
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

        int EndSearchZero()
        {
            for (int i = size-1; string[i] == 48; i--)
                if(string[i-1] == 44 || string[i-1] == 46)
                    return i;
            return size;
        }

        int SearchZero()
        {
            int a = 0;
            char b = Get(a);
            while (b == 48)
            {
                a++;
                b = Get(a);
            }
            if (b == 44 || b == 46)
                a--;
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

        void AddZeroesBegin(var& B)
        {
            if(SearchPoint() > B.SearchPoint())
            {
                int difference = B.SearchPoint() - SearchPoint();
                ExpandStringBy(difference);
                for (int i = size-1; i <=difference; i--)
                {
                    string[i] = string[i-difference];
                }
                for (int i = 0; i < difference; i++)
                {
                    string[i] = 0;
                }
            }
            else if(SearchPoint() < B.SearchPoint())
            {
                int difference = SearchPoint() - B.SearchPoint();
                B.ExpandStringBy(difference);
                for (int i = size-1; i <=difference; i--)
                {
                    B.string[i] = string[i-difference];
                }
                for (int i = 0; i < difference; i++)
                {
                    B.string[i] = 0;
                }
            }
        }
        void AddZeroesEnd(var& B)
        {
            if(size < B.Size())
            {
                Add(44);
                int differenceZero = B.Size() - size;
                ExpandStringBy(differenceZero);
                for(int i = size-differenceZero-1; i < size; i++)
                    string[i] = 48;
            }
            else if(size > B.Size())
            {
                B.Add(44);
                int differenceZero = size - B.Size();
                B.ExpandStringBy(differenceZero);
                for(int i = B.Size()-differenceZero-1; i < B.Size(); i++)
                    B.string[i] = 48;
            }
        }
        void FormatNumberString(var& B)
        {
            DeleteFirstUselessZeroes();
            B.DeleteFirstUselessZeroes();       
            //Добавление нулей в начале
            AddZeroesBegin(B);
            //Удаление нулей в конце
            int uselessZeroLastA = EndSearchZero();
            int uselessZeroLastB = B.EndSearchZero();
            ReduceStringBy(size-uselessZeroLastA);
            B.ReduceStringBy(B.Size()-uselessZeroLastB);
            //Удаляю запятую если она лишняя
            if(string[size-1] == 44 || string[size-1] == 46)
                ReduceString();
            if(B.string[B.Size()-1] == 44 || B.string[B.Size()-1] == 46)
                B.ReduceString();
            
            //Добавление нулей в конце
            AddZeroesEnd(B);
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

        void ReduceStringBy(int howMuchReduce)
        {
            if(size>0) {
                char *tempString = new char[size - howMuchReduce];
                for (int i = 0; i < size - howMuchReduce; ++i) {
                    tempString[i] = string[i];
                }
                delete[] string;
                string = tempString;
                size -= howMuchReduce;
            }
            else
                std::cout << "ERROR! Array size = 0! You can not do it!" << std::endl;
        }



    };
}