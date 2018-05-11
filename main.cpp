#include "tritset.h"
#include <iostream>
#include <stdlib.h>

using std::cout;
using std::endl;

int main()
{
    Tritset myTrits;
    Tritset hisTrits(10);
    //Отработка конструктора
    {
        cout << myTrits.seeByte(0) << endl;
        cout << myTrits.getBytes() << " bytes." << endl;
        cout << myTrits.getSize() << " trits." << endl;
    }
    //Works well

    cout << endl;

    //Отработка второго конструктора
    {
        cout << "Trits: " << hisTrits.getSize() << endl;
        cout << "Bytes: " << hisTrits.getBytes() << endl;
    }
    //works well

    cout << endl;

    //Отработка второй функции set
        {
            hisTrits.set(TRUE, 3, 13);
            for ( size_t i = 0 ; i < 13 ; i++ )
            {
                cout << (hisTrits[i]).getInt() << " ";
            }
            cout << endl;
        }
    //works well

    cout << endl;

    //Отработка функции set
    {
        cout << "Set returns: " << myTrits.set(FALSE) << endl;
        cout << "First byte: " << myTrits.seeByte(0) << endl;
    }
    //Works well

    cout << endl;

    //Вывод тритов
    {
        cout << "myTrits[0] = " << (myTrits[0]).getInt() << endl;
        cout << "myTrits[1] = " << (myTrits[1]).getInt() << endl;
        cout << "myTrits[2] = " << (myTrits[2]).getInt() << endl;
        cout << "myTrits[3] = " << (myTrits[3]).getInt() << endl;
    }
    //Выводит верно в случае одинаковых тритов точно

    cout << endl;

    //Запись тритов с выводом
    {
        cout << endl << "myTrits = TRUE";
        myTrits[0] = TRUE;
        cout << endl << "myTrits = FALSE";
        myTrits[1] = FALSE;
        cout << endl << "myTrits = UNKNOWN";
        myTrits[2] = UNKNOWN;
        cout << endl << "myTrits = TRUE" << endl;
        myTrits[3] = TRUE;
        cout << "myTrits[0] = " << (myTrits[0]).getInt() << endl;
        cout << "myTrits[1] = " << (myTrits[1]).getInt() << endl;
        cout << "myTrits[2] = " << (myTrits[2]).getInt() << endl;
        cout << "myTrits[3] = " << (myTrits[3]).getInt() << endl;
    }
    //В пределах первого байта всё хорошо работает.

    cout << endl;

    //Проверка невыделения памяти
    {
        myTrits[77] = UNKNOWN;
        cout << "Bytes " << myTrits.getBytes() << endl;
        cout << "Trits " << myTrits.getSize() << endl;
    }
    //Работает

    cout  << endl;

    //Запись за пределы трита
    {
        myTrits[77] = FALSE;
        cout << "Bytes " << myTrits.getBytes() << endl;
        cout << "Trits " << myTrits.getSize() << endl;
        cout << "FALSE <-> " << (myTrits[77]).getInt() << endl;
    }
    //Works well

    cout << endl;

    //Запрос за пределы трита
    {cout << (myTrits[1000]).getInt() << endl;}
    //Возврат UNKNOWN

    cout << endl;

    //Логические операторы: ==
    {
        myTrits[0] = UNKNOWN;
        myTrits[1] = TRUE;
        myTrits[2] = FALSE;

        cout << "X == Y: UTF" << endl;
        int k = 3;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                myTrits[k] = myTrits[i] == myTrits[j];
                cout << (myTrits[k]).getInt() << " ";
                k++;
            }
            cout << endl;
        }
    }
    // == works well

    cout << endl;

    //Логические операторы: &&
    {
        int k;
        myTrits[0] = UNKNOWN;
        myTrits[1] = TRUE;
        myTrits[2] = FALSE;

        cout << "X && Y: UTF" << endl;
        k = 3;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                myTrits[k] = myTrits[i] && myTrits[j];
                cout << (myTrits[k]).getInt() << " ";
                k++;
            }
            cout << endl;
        }
    }
    //&& works well

    cout <<  endl;

    //Логические операторы: ||
    {
        int k;
        myTrits[0] = UNKNOWN;
        myTrits[1] = TRUE;
        myTrits[2] = FALSE;

        cout << "X || Y: UTF" << endl;
        k = 3;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                myTrits[k] = myTrits[i] || myTrits[j];
                cout << (myTrits[k]).getInt() << " ";
                k++;
            }
            cout << endl;
        }
    }
    //|| works well

    cout << endl;

    //Логические операторы: !=
    {
        int k;
        myTrits[0] = UNKNOWN;
        myTrits[1] = TRUE;
        myTrits[2] = FALSE;

        cout << "X != Y: UTF" << endl;
        k = 3;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                myTrits[k] = myTrits[i] != myTrits[j];
                cout << (myTrits[k]).getInt() << " ";
                k++;
            }
            cout << endl;
        }
    }
    // != works well

    cout <<  endl;

    //Логические операторы: !
    {
        myTrits[0] = UNKNOWN;
        myTrits[1] = TRUE;
        myTrits[2] = FALSE;
        cout << "!X : UTF" << endl;
        for (int i = 0; i < 3; i++)
        {
            myTrits[3 + i] = !myTrits[i];
            cout << (myTrits[3 + i]).getInt() << " ";
        }
    }
    //works well

    //Логические операции с двумя reference выполняются успешно

    cout << endl;
    cout << endl;

    //Логические операторы: ==
    {
        myTrits[0] = UNKNOWN;
        myTrits[1] = TRUE;
        myTrits[2] = FALSE;

        cout << "X == Y: UTF" << endl;

        for (int i = 0; i < 3; i++)
        {
            cout << (int)(myTrits[i] == UNKNOWN) << " ";
            cout << (int)(myTrits[i] == TRUE) << " ";
            cout << (int)(myTrits[i] == FALSE) << " ";

            cout << endl;
        }
    }
    //works well

    cout << endl;

    //Логические операторы: &&
    {
        myTrits[0] = UNKNOWN;
        myTrits[1] = TRUE;
        myTrits[2] = FALSE;

        cout << "X && Y: UTF" << endl;
        for (int i = 0; i < 3; i++)
        {
            cout << (int)(myTrits[i] && UNKNOWN) << " ";
            cout << (int)(myTrits[i] && TRUE) << " ";
            cout << (int)(myTrits[i] && FALSE) << " ";

            cout << endl;
        }
    }
    //&& works well

    cout <<  endl;

    //Логические операторы: ||
    {
        myTrits[0] = UNKNOWN;
        myTrits[1] = TRUE;
        myTrits[2] = FALSE;
        cout << "X || Y: UTF" << endl;
        for (int i = 0; i < 3; i++)
        {
            cout << (int)(myTrits[i] || UNKNOWN) << " ";
            cout << (int)(myTrits[i] || TRUE) << " ";
            cout << (int)(myTrits[i] || FALSE) << " ";

            cout << endl;
        }
    }
    //|| works well

    cout << endl;


        //Логические операторы: !=
    {
        myTrits[0] = UNKNOWN;
        myTrits[1] = TRUE;
        myTrits[2] = FALSE;
        cout << "X != Y: UTF" << endl;
        for (int i = 0; i < 3; i++)
        {
            cout << (int)(myTrits[i] != UNKNOWN) << " ";
            cout << (int)(myTrits[i] != TRUE) << " ";
            cout << (int)(myTrits[i] != FALSE) << " ";

            cout << endl;
        }
    }
        // != works well

    //Все логические операторы работают хорошо


    cout << endl;

    //Проверка записи трита
    {
        myTrits[0] = myTrits[2];
        cout << (myTrits[0]).getInt();
    }
    //works well

    cout << endl << endl;


    /*Тесты:
     1.Конструктор по умолчанию: Done
     2.Второй конструктор: Done
     3.Set: Done
     4.Второй Set: Done
     5.Вывод тритов: Done
     6.Запись тритов по [] = Trit:Done
     6.Запись тритов по [] = []: Done
     7.Запись за пределы трита:Done
     8.Запись UNKNOWN c невыделением памяти:Done
     9.Получение UNKNOWN при запросе за пределы трита:Done
     10.Логика reference-reference: Done
     11.Логика reference-trit: Done
*/
    return 0;
}

