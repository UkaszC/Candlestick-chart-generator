#include <iostream>
#include <fstream>
#include <cstdlib>
#include <iomanip>

using namespace std;

int menu(ifstream& input_data, ofstream& data_output);
int setting_cursor(ifstream& input_data, char nameIn[]);
int collecting_data(double data[200][8], ifstream& input_data);
int max(double data[200][8], double& maxV);
int min(double data[200][8], double& minV);
int generate_table(double maxV, double minV, double table[1000], double height = 50);
int drawing(double data[200][8], double table[1000], ofstream& data_output, double height = 50);

int main()
{
    ifstream input_data;
    ofstream data_output;
    menu(input_data, data_output);
    input_data.close();
    data_output.close();
    system("pause");
    return 0;
}

int menu(ifstream& input_data, ofstream& data_output)
{
    char keyboard;
    cout << "Lukasz Ciesielski, 198014" << endl << endl;
    cout << "G. WYSWIETL WYKRES DLA PLIKU \"intc_us_data.csv\"" << endl;
    cout << "F. WYSWIETL WYKRES DLA WYBRANEGO PLIKU" << endl;
    cout << "Q. ZAKONCZ DZIALANIE PROGRAMU" << endl;
    cin >> keyboard;
    switch (keyboard)
    {
    case 'G':
    case 'g':
    {
        char nameIn[] = "intc_us_data.csv", nameOut[] = "chart.txt";
        input_data.open(nameIn);
        data_output.open(nameOut);
        if (!input_data || !data_output)
        {
            cout << "Nie udalo sie wczytac pliku!";
            exit(1);
        }
        else
        {
            double data[200][8];
            double maxV = 0.0, minV = 1000000000.0;
            double table[1000];
            double height = 0.0;
            setting_cursor(input_data, nameIn);
            collecting_data(data, input_data);
            max(data, maxV);
            min(data, minV);
            system("cls");
            cout << "Czy uzyc ustawien domyslnych?" << endl;
            cout << "1. TAK" << endl;
            cout << "2. NIE" << endl;
            cin >> keyboard;
            if (keyboard == '2')
            {
                cout << "Podaj wysokosc wykresu: ";
                cin >> height;
                generate_table(maxV, minV, table, height);
                drawing(data, table, data_output, height);
                return 0;
            }
            else
            {
                generate_table(maxV, minV, table);
                drawing(data, table, data_output);
                return 0;
            }
        }
    }
    break;

    case 'F':
    case 'f':
    {
        char nameIn[200], nameOut[200];
        system("cls");
        cout << "Podaj nazwe pliku z danymi do wczytania: ";
        cin >> nameIn;
        system("cls");
        cout << "Podaj nazwe pliku do zapisu wykresu: ";
        cin >> nameOut;
        input_data.open(nameIn);
        data_output.open(nameOut);
        if (!input_data || !data_output)
        {
            cout << "Nie udalo sie wczytac pliku!";
            exit(1);
        }
        else
        {
            double data[200][8];
            double maxV = 0.0, minV = 1000000000.0;
            double table[1000];
            double height = 0.0;
            setting_cursor(input_data, nameIn);
            collecting_data(data, input_data);
            max(data, maxV);
            min(data, minV);
            system("cls");
            cout << "Czy uzyc ustawien domyslnych?" << endl;
            cout << "1. TAK" << endl;
            cout << "2. NIE" << endl;
            cin >> keyboard;
            if (keyboard == '2')
            {
                cout << "Podaj wysokosc wykresu: ";
                cin >> height;
                generate_table(maxV, minV, table, height);
                drawing(data, table, data_output, height);
                return 0;
            }
            else
            {
                generate_table(maxV, minV, table);
                drawing(data, table, data_output);
                return 0;
            }
        }
    }
    break;

    case 'Q':
    case 'q':
    {
        exit(0);
    }
    break;

    default:
    {
        system("cls");
        menu(input_data, data_output);
        return 0;
    }
    }
}

int setting_cursor(ifstream& input_data, char nameIn[])
{
    ifstream counting_data;
    counting_data.open(nameIn);
    int i = 0;
    int j = 0;
    char buffer[100];
    while (counting_data.getline(buffer, 100))
    {
        i++;
    }

    if (i < 201)
    {
        input_data.getline(buffer, 100);
        counting_data.close();
        return 0;
    }

    while (input_data.getline(buffer, 100))
    {
        if (j == i - 201)
            return 0;

        j++;
    }
    counting_data.close();
    return 0;
}


int collecting_data(double data[200][8], ifstream& input_data)
{
    char buffer[30];

    for (int i = 0; i < 200; i++)
    {
        input_data.getline(buffer, 30, '-');
        data[i][0] = atof(buffer);
        input_data.getline(buffer, 30, '-');
        data[i][1] = atof(buffer);
        input_data.getline(buffer, 30, ',');
        data[i][2] = atof(buffer);
        input_data.getline(buffer, 30, ',');
        data[i][3] = atof(buffer);
        input_data.getline(buffer, 30, ',');
        data[i][4] = atof(buffer);
        input_data.getline(buffer, 30, ',');
        data[i][5] = atof(buffer);
        input_data.getline(buffer, 30, ',');
        data[i][6] = atof(buffer);
        input_data.getline(buffer, 30);
        if (data[i][6] > data[i][3])
        {
            data[i][7] = 1.0;
        }
        else
        {
            data[i][7] = 0.0;
        }
    }
    return 0;
}

int max(double data[200][8], double& maxV)
{
    for (int i = 0; i < 200; i++)
    {
        if (data[i][4] > maxV)
            maxV = data[i][4];
    }
    return 0;
}

int min(double data[200][8], double& minV)
{
    for (int i = 0; i < 200; i++)
    {
        if (data[i][5] < minV)
            minV = data[i][5];
    }
    return 0;
}

int generate_table(double maxV, double minV, double table[1000], double height)
{
    double scale = (maxV - minV) / (height);
    table[0] = maxV;
    for (int i = 1; i < height; i++)
    {
        table[i] = table[i - 1] - scale;
    }
    return 0;
}

int drawing(double data[200][8], double table[1000], ofstream& data_output, double height)
{
    char nCena[] = "CENA";
    char nDzien[] = "DZIEN";
    int counter = 0;
    system("cls");
    data_output << table[0] << endl;
    cout << table[0] << endl;
    for (int i = 0; i < height; i++)
    {
        if (i > height / 2 - 2 && counter < 4)
        {
            data_output << "    " << nCena[counter] << "|_";
            cout << "    " << nCena[counter] << "|_";
            counter++;
        }
        else
        {
            data_output << "     |_";
            cout << "     |_";
        }

        for (int j = 0; j < 200; j++)
        {
            if (data[j][7] == 1.0 && data[j][3] <= table[i] && data[j][6] >= table[i])
            {
                data_output << 'O';
                cout << 'O';
            }
            else if (data[j][7] == 0.0 && data[j][3] >= table[i] && data[j][6] <= table[i])
            {
                data_output << '#';
                cout << '#';
            }
            else if (data[j][4] >= table[i] && data[j][5] <= table[i])
            {
                data_output << '|';
                cout << '|';
            }
            else
            {
                data_output << '.';
                cout << '.';
            }
        }
        data_output.put('\n');
        cout << endl;
    }
    data_output << table[(int)height - 1] << endl;
    data_output << "       ";
    cout << table[(int)height - 1] << endl;
    cout << "       ";
    for (int i = 0; i < 200; i++)
    {
        data_output << "|";
        cout << "|";
    }
    data_output << endl;
    data_output << "       ";
    cout << endl;
    cout << "       ";
    for (int i = 0; i < 200; i++)
    {
        data_output << "-";
        cout << "-";
    }
    data_output << endl;
    data_output << "   " << data[0][0] << "-" << data[0][1] << "-" << data[0][2];
    cout << endl;
    cout << "   " << data[0][0] << "-" << data[0][1] << "-" << data[0][2];
    counter = 0;
    for (int i = 0; i < 190; i++)
    {
        if (i > 90 && counter < 6)
        {
            cout << nDzien[counter];
            data_output << nDzien[counter];
            counter++;
        }
        else
        {
            data_output << " ";
            cout << " ";
        }
    }
    data_output << data[199][0] << "-" << data[199][1] << "-" << data[199][2];
    cout << data[199][0] << "-" << data[199][1] << "-" << data[198][2];
    return 0;
}
