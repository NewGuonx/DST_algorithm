// author - sonaspy@outlook.com
// coding - utf_8

#include "../src/dsa.h"

using namespace std;
using namespace dsa;
inline void quit()
{
    cout << endl
         << endl
         << endl
         << "sonaspy@outlook.com  💻  github.com/newguonx" << endl
         << " 🚗 🚗 🚗 🚗 🚗 🚗 🚗 🚗 🚗    THANS FOR USE    💣 💣 💣 💣 💣 💣 💣 💣 💣\n";
    exit(0);
}
int main(int argc, char const *argv[])
{
    /* code */
    //test();
    srand(time(NULL));
    int n, range, val, nofvals;
    string valtype, instruction;
    cout << " 🚗 🚗 🚗 🚗 🚗 🚗 🚗 🚗 🚗    WELCOME TO THE RBTREE SAMPLE USE PROGRAM    💣 💣 💣 💣 💣 💣 💣 💣 💣\n"
         << "sonaspy@outlook.com  💻  github.com/newguonx" << endl
         << endl
         << endl;
    while (cout << "input \"build\" or \"rebuild\"to build a avltree, or \"quit\" to end it." << endl && cin >> instruction)
    {
        if (instruction[0] == 'q')
            quit();
        else if (instruction[0] == 'b' || instruction[0] == 'r')
        {
            cout << "input (size) and the (valtype) (only provide char or int) of avltree" << endl;
            cin >> n >> valtype;

            if (valtype[0] == 'c')
            {
                avltree<char> avlx;
                vector<char> a(n);
                a.reserve(10);
                generate(a.begin(), a.end(), [&]() { return rand() % 93 + 33; });
                avlx.build(a);
                cout << "build successful \nthen you can input (1/2/3/4/5/6) 1.print 2.search 3.earse 4.insert 5.rebuild 6.quit 7.insert vals\n";

                while (cin >> instruction)
                {
                    switch (instruction[0])
                    {
                    case '1':
                        avlx.printhorizon();
                        break;
                    case '2':
                        cout << "which value you wanna search ? \n";
                        cin >> val;
                        cout << avlx.search(val) << endl;
                        break;
                    case '3':
                        cout << "which value you wanna erase ? \n";
                        cin >> val;
                        cout << (avlx.erase(val) ? "erase successful" : "erase failed") << endl;
                        break;
                    case '4':
                        cout << "what value you wanna insert ? \n";
                        cin >> val;
                        cout << (avlx.insert(val) ? "insert successful" : "insert failed") << endl;
                        break;
                    case '5':
                        goto end;
                        break;
                    case '6':
                        quit();
                        break;
                    case '7':
                        cin >> nofvals;
                        for (int i = 0; i < nofvals; i++)
                        {
                            cin >> a[0];
                            avlx.insert(a[0]);
                        }
                        cout << "insert successful" << endl;
                        break;
                    default:
                        cout << "input legitimate instruction please" << endl;
                    }
                }
            }
            else
            {
                avltree<int> avlx;
                cout << "input (max int val you wanted)" << endl;
                cin >> range;
                vector<int> a(n);
                a.reserve(10);
                generate(a.begin(), a.end(), [&]() { return rand() % range; });
                avlx.build(a);
                cout << "build successful \n then you can input (1/2/3/4/5/6) 1.print 2.search 3.earse 4.insert 5.rebuild 6.quit 7.insert vals\n";
                while (cin >> instruction)
                {
                    switch (instruction[0])
                    {
                    case '1':
                        avlx.printhorizon();
                        break;
                    case '2':
                        cout << "which value you wanna search ? \n";
                        cin >> val;
                        cout << avlx.search(val) << endl;
                        break;
                    case '3':
                        cout << "which value you wanna erase ? \n";
                        cin >> val;
                        cout << (avlx.erase(val) ? "erase successful" : "erase failed") << endl;
                        break;
                    case '4':
                        cout << "what value you wanna insert ? \n";
                        cin >> val;
                        cout << (avlx.insert(val) ? "insert successful" : "insert failed") << endl;
                        break;
                    case '5':
                        goto end;
                        break;
                    case '6':
                        quit();
                        break;
                    case '7':
                        cin >> nofvals;
                        for (int i = 0; i < nofvals; i++)
                        {
                            cin >> a[0];
                            avlx.insert(a[0]);
                        }
                        cout << "insert successful" << endl;
                        break;
                    default:
                        cout << "input legitimate instruction please" << endl;
                    }
                    cout << " 1.print 2.search 3.earse 4.insert 5.rebuild 6.quit\n";
                }
            }
        end:
            continue;
        }
    }

    return 0;
}