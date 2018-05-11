#ifndef TRITSET
#define TRITSET
//Биты считаются справа налево

#include <stdint.h>

enum TritValue{TRUE = 1, FALSE = -1, UNKNOWN = 0};

class Tritset;
class reference;


class Tritset
{
private:
    typedef uint8_t trits_type;
    trits_type *trits;                                    //uint8_t - восьмибитовый int без знака(на самом деле unsigned char)

                                                            /*
                                                             https://habrahabr.ru/post/154033/
                                                            */
    size_t size;            //Размер в тритах
    size_t bytes;           //Размер в байтах


                    //~~~~~~~~~~~~~~~~~~~CLASS REFERENCE~~~~~~~~~~~~~~~~~~~~~
    class reference
    {
private:
        friend class Tritset;
        Tritset* tset;
        size_t byte;              //Номер байта в trits[] минимальное значение - 1
        size_t pos;                    //Позиция трита в байте 1..4


        reference(size_t tritPos, Tritset* thisTritset);


        TritValue getvalue();   //Возвращает значение трита, на который ссылается reference.
    public:
        ~reference();

                //~~~~~~~~~~~~~OPERATOR=~~~~~~~~~~~~~
        void operator= (TritValue right);
        void operator= (reference right);


        //~~~~~~~~~~~~~~~~~~~~~~Operator==~~~~~~~~~~~~~~~~~~~~~
        TritValue operator== (TritValue right);
        TritValue operator== (reference right);


        //~~~~~~~~~~~~~~~~~~~~~~Operator&&~~~~~~~~~~~~~~~~~~~~~
        TritValue operator&& (reference right);
        TritValue operator&& (TritValue right);

        //~~~~~~~~~~~~~~~~~~~~~~Operator||~~~~~~~~~~~~~~~~~~~~~
        TritValue operator|| (reference right);
        TritValue operator|| (TritValue right);
        //~~~~~~~~~~~~~~~~~~~~~~Operator!~~~~~~~~~~~~~~~~~~~~~
        TritValue operator! ();
        //~~~~~~~~~~~~~~~~~~~~~~Operator!=~~~~~~~~~~~~~~~~~~~~~
        TritValue operator!= (reference right);
        TritValue operator!= (TritValue right);

        //Функции для отладки
        int getInt()
        {
            return (int)this->getvalue();
        }
    };
        //~~~~~~~~~~~~~~~~~~~~~~~~~~~END_OF_REFERENCE_DECLARATION~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


public:
    Tritset();
    Tritset(size_t trits);
    Tritset(const Tritset &Tset)
    {
        bytes = Tset.size/4 + 1;
        size = Tset.size;
        trits = new uint8_t[bytes];
        set(UNKNOWN);
        for (size_t i = 0; i < bytes; i++)
        {
            trits[i] = Tset.trits[i];
        }
    }

    size_t capacity()
    {
        return bytes;
    }
    //~~~Bit access~~~//
    reference operator[](size_t tritPosition);



    int getInt(size_t pos)
    {
        return (*this)[pos].getInt();
    }

    //~~~Bit operations~~~//
    int set(TritValue value);                    //Sets all bits to value

    int set(TritValue value, size_t begin_pos, size_t end_pos);

    //Функции для отладки:
    int seeByte(size_t position)
    {
        return trits[position];
    }
    size_t getSize()
    {
        return size;
    }
    size_t getBytes()
    {
        return bytes;
    }
    ~Tritset();
};



#endif // TRITSET

//1)Переезд на enum: Done!
//2)Константный тритсет:
//3)Довыделение памяти: Done!
//4)Виртуальный деструктор: Что?
//5)Тесты: Done!
