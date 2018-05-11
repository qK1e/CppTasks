
#include<stdint.h>
#include"tritset.h"
#include<stdlib.h>
#include<iostream>
using std::cout;
using std::endl;

Tritset::reference::reference(size_t tritPos, Tritset* thisTritset)
{
    tset = thisTritset;
    byte = tritPos/4 + 1; //Отсчёт от 1..1..1..1..2..2..2..2..3..
    pos = (tritPos)%4 + 1;  //Отсчёт от 1..2..3..4;  позиция в байте
}

TritValue Tritset::reference::getvalue()
{
    if (((byte-1)*4 + pos) <= tset->size )
    {
        uint8_t value;

        value = tset -> trits[byte - 1];
        value = value >> (pos - 1) * 2;  //%%%%%%**
        value = value & 3;  //& 00000011
        switch(value)
        {
            case(0):return UNKNOWN;
            break;
            case(1):return TRUE;
            break;
            case(2):return FALSE;
            break;
            default: exit(1);
        }
    }
    else
        return UNKNOWN;
}


void Tritset::reference::operator=(TritValue right)
{
    if (byte <= tset->bytes)
    {
        if (((byte-1)*4 + pos) > tset->size)
        {
            tset->size = ((byte-1)*4 + pos);
        }
//        std::cout << std::endl << "enough memory case";
        switch(right)
            {
                case TRUE:
                    {
//                        std::cout << std::endl << "case TRUE: ";

                        uint8_t mask1;
                        uint8_t mask2;

                        mask1 = 0|(1<<(pos*2 - 2));  //00...01...00; 00000001 - 00000100 - 00010000 - 01000000
//                        cout << endl << "mask1 = " << (int)mask1 << endl;

                        mask2 = 255^(1<<(pos*2 - 1));  //11...01...11; 11111101 - 11110111 - 11011111 - 01111111
//                        cout << endl << "mask2 = " << (int)mask2 << endl;

                        tset->trits[byte - 1] = ( tset->trits[byte - 1] & mask2 ) | mask1;

//                        cout << endl << "trits[byte] = " << (int)(tset->trits[byte - 1]);
                        break;

                    }

                case FALSE:
                    {
//                        std::cout << std::endl << "case FALSE: ";

                        uint8_t mask1;
                        uint8_t mask2;

                        mask1 = 0|(1<<(this->pos*2 - 1));  //00...10...00
                        mask2 = 255^(1<<(this->pos*2 - 2));  //11...10...11

                        tset->trits[byte - 1] = tset->trits[byte - 1] & mask2;
                        tset->trits[byte - 1] = tset->trits[byte - 1] | mask1;
//                        std::cout << (int)(tset->trits[byte - 1]);
                        break;
                    }

                case UNKNOWN:
                    {
//                        std::cout << std::endl << "case UNKNOWN: ";

                        uint8_t mask;

                        mask = 255^( 3 << (pos*2 - 2) ); //11...00...11

                        tset->trits[byte - 1] = tset->trits[byte - 1] & mask;
//                        std::cout << (int)(tset->trits[byte - 1]);
                        break;
                    }
            }
    }
    else if ((int)right != (int)UNKNOWN)
    {
//        std::cout << std::endl << "Not enough memory case";
        tset->trits = new uint8_t[byte];

        for (size_t i = tset->bytes ; i < byte ; i++)
        {
            tset->trits[i] = 0;
        }

        tset->bytes = byte;
        tset->size = (byte - 1)*4 + pos;

        *this = right;
    }
    /*std::cout << std::endl << "End of If" << std::endl;*/
}
void Tritset::reference::operator= (reference right)
{

    TritValue right_value = right.getvalue();

    *this = right_value;

}

TritValue Tritset::reference::operator==(TritValue right)
{
    TritValue left_value = getvalue();

    return (TritValue)((int)left_value * (int)right);  //Произведение даёт ту же таблицу истинности
}
TritValue Tritset::reference::operator==(reference right)
{
    TritValue right_value = right.getvalue();
    TritValue left_value = getvalue();

    return (TritValue)((int)right_value * (int)left_value);   //Произведение даёт ту же таблицу истинности
}

TritValue Tritset::reference::operator&&(reference right)
{
   if ( ((int)getvalue() == (int)FALSE) || ((int)right.getvalue() == (int)FALSE) )
   {return FALSE;}

   else if( ((int)getvalue() == (int)UNKNOWN) || ((int)right.getvalue() == (int)UNKNOWN) )
   {return UNKNOWN;}

   else
   {return TRUE;}
}
TritValue Tritset::reference::operator&&(TritValue right)
{
    if ( ((int)getvalue() == (int)FALSE) || ((int)right == (int)FALSE) )
    {return FALSE;}

    else if( ((int)getvalue() == (int)UNKNOWN) || ((int)right == (int)UNKNOWN) )
    {return UNKNOWN;}

    else
    {return TRUE;}
}

TritValue Tritset::reference::operator||(reference right)
{
    if ( ((int)getvalue() == (int)TRUE) || ((int)right.getvalue() == (int)TRUE) )
    {return TRUE;}

    else if( ((int)getvalue() == (int)UNKNOWN) || ((int)right.getvalue() == (int)UNKNOWN) )
    {return UNKNOWN;}

    else
    {return FALSE;}
}
TritValue Tritset::reference::operator||(TritValue right)
{
    if  ( ((int)getvalue() == (int)TRUE) || ((int)right == (int)TRUE) )
    {return TRUE;}

    else if( ((int)getvalue() == (int)UNKNOWN) || ((int)right == (int)UNKNOWN) )
    {return UNKNOWN;}

    else
    {return FALSE;}
}

TritValue Tritset::reference::operator!()
{
    return (TritValue)(((int)getvalue())*(-1));
}

TritValue Tritset::reference::operator!=(reference right)
{
    return (TritValue)((int)(*this == right.getvalue())*(-1));
}
TritValue Tritset::reference::operator!=(TritValue right)
{
    return (TritValue)((int)(*this == right)*(-1));
}


Tritset::Tritset()
{
    this->bytes = 1;
    this->size = 0;
    this->trits = new uint8_t[bytes];
    this->trits[0] = 85;
}
Tritset::Tritset(size_t nOfTrits)
{
    bytes = nOfTrits/4 + 1;
    size = nOfTrits;
    trits = new uint8_t[bytes];
    set(UNKNOWN);
}

Tritset::reference Tritset::operator[](size_t tritPosition)
{

    reference returnRef(tritPosition, this); //tritPosition 0..1..2..n..
    return returnRef;
}

int Tritset::set(TritValue value)
{
    for(size_t i = 0; i < bytes; i++)//Могут пострадать неинициализированные байты, но это ничего
    {
        switch(value)
        {

        case(TRUE): trits[i] = 85; //01010101
            return 1;

        case(FALSE): trits[i] = 170; //10101010
            return -1;

        case(UNKNOWN): trits[i] = 0;
            return 0;

        default: return -2;
        }
    }
    return -3;
}
int Tritset::set(TritValue value, size_t begin_pos, size_t end_pos)
{
    for (size_t i = end_pos + 1; i > begin_pos ; i--) //Лучше это не трогать
    {
        (*this)[i-1] = value;
    }



    return 0;
}

Tritset::~Tritset()
{
    delete [] trits;
}



Tritset::reference::~reference()
{
    delete(tset);
}
