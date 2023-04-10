#include <bits/stdc++.h>
using namespace std;

float f = 0.5;
float cr = 0.7;
float lb = -10, ub = 10;

int main()
{
    ofstream fout, myfile;
    fout.open("DixonPrice_xcel.csv");
    myfile.open("Dixon_graph.csv");
    float runMin[50];
    const int iter=200;
    for (int w = 0; w < 50; w++)
    {
        cout << endl
             << "RUN-" << w + 1 << endl;
        float minCostArr[10];
        float arr[100][5];
        /*cout << endl
             << "Search Space" << endl;*/
        for (int i = 0; i < 100; i++)
        {
            for (int j = 0; j < 5; j++)
            {
                float r = (float)rand() / RAND_MAX;
                arr[i][j] = lb + r * (ub - lb);
                //cout << setprecision(2) << arr[i][j] << " ";
            }
            //cout << endl;
        }
        cout << endl
             << endl;
        cout << "Initial search space" << endl;
        float arr1[10][5];
        for (int i = 0; i < 10; i++)
        {
            int ran_var = 0 + rand() % 100;
            for (int j = 0; j < 5; j++)
            {
                arr1[i][j] = arr[ran_var][j];
                cout << setprecision(2) << arr1[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl
             << endl;

        float lowcost_arr[iter][5];
        float ans[iter];

        int b = 0;
        while (b <= iter-1)
        {
            /*cout << endl
                  << endl
                  << "GENERATION-" << b + 1 << endl;*/

            //********                     COST COMPUTE                 *******

            float costRes[10];

            for (int i = 0; i < 10; i++)
            {
                float xp = 0, xoid = 0, xsum = 0;
                float x1 = arr1[i][0] - 1;
                float term1 = x1 * 2;
                float sum = 0;
                for (int j = 1; j < 5; j++)
                {
                    xp = pow(arr1[i][j], 2);
                    xoid = arr[i][j - 1];
                    xsum = ((2 * xp) - xoid);
                    sum += j*pow(xsum, 2);
                }
                costRes[i] = term1 + sum;
            }

             //print array of cost
            
             /*cout << "Array of cost" << endl;
             for (int i = 0; i < 10; i++)
             {
                 cout << costRes[i] << " ";
             }
             cout << endl;*/
            //

            // storing minimum cost row vector's index
            int cost_index;
            float minVal = FLT_MAX;
            for (int i = 0; i < 10; i++)
            {
                if (costRes[i] < minVal)
                {
                    minVal = costRes[i];
                    cost_index = i;
                }
            }

            // taking 100*5 matrix and copying minimum cost row vector from 10*5 matrix to the 100*5 matrix
            for (int j = 0; j < 5; j++)
            {
                lowcost_arr[b][j] = arr1[cost_index][j];
            }

            // printing minimum cost from the cost res
            /*cout << "Minimum value from cost array"
                 << " " << minVal;*/
            ans[b] = minVal;

            for (int p = 0; p < 10; p++)
            {
                //********MUTATION**********

                int Xr = 0, Xs = 0, Xt = 0;
                do
                {
                    Xr = 0 + rand() % 10;
                    Xs = 0 + rand() % 10;
                    Xt = 0 + rand() % 10;
                } while (Xr == Xs && Xs == Xt);

                float arrXr[5];
                for (int k = 0; k < 5; k++)
                {
                    arrXr[k] = arr1[Xr][k];
                }
                float arrXs[5];
                for (int k = 0; k < 5; k++)
                {
                    arrXs[k] = arr1[Xs][k];
                }
                float arrXt[5];
                for (int k = 0; k < 5; k++)
                {
                    arrXt[k] = arr1[Xt][k];
                }
                float arrXoff2[5];
                for (int k = 0; k < 5; k++)
                {
                    arrXoff2[k] = arrXt[k] + (f * (arrXr[k] - arrXt[k]));
                }

                //*******CROSSOVER*****

                float arrXoff1[5];
                for (int k = 0; k < 5; k++)
                {
                    arrXoff1[k] = arrXoff2[k];
                }
                for (int j = 0; j < 5; j++)
                {
                    float ran = (float)rand() / (float)RAND_MAX;
                    if (ran < cr)
                    {
                        arrXoff1[j] = arr1[p][j];
                    }
                }

                //*****SELECTION****
                float Xoffcost;
                float sum1 = 0;
                float xp = 0, xoid = 0, xsum = 0;
                float term1 = (arrXoff1[0] - 1) * 2;
                for (int j = 1; j < 5; j++)
                {
                    xp = pow(arrXoff1[j], 2);
                    xoid = arrXoff1[j - 1];
                    xsum = ((2 * xp) - xoid);
                    sum1 += j * pow(xsum, 2);
                }
                Xoffcost = term1 + sum1;

                if (Xoffcost <= costRes[p])
                {
                    for (int j = 0; j < 5; j++)
                    {
                        arr1[p][j] = arrXoff1[j];
                    }
                }
            }

            // checking new matrix is in the bound
            for (int i = 0; i < 10; i++)
            {

                for (int j = 0; j < 5; j++)
                {
                    if (arr1[i][j] < lb)
                    {
                        arr1[i][j] = lb;
                    }
                    else if (arr1[i][j] > ub)
                    {
                        arr1[i][j] = ub;
                    }
                }
            }

            b++;
        }

        /*cout << endl
             << endl
             << "Minimum cost population" << endl;
        for (int i = 0; i < 100; i++)
        {
            for (int j = 0; j < 5; j++)
            {
                cout << setprecision(2) << lowcost_arr[i][j] << " ";
            }
            cout << endl;
        }*/
        cout << endl
             << endl
             << "Minimum Cost Array"
             << " ";
        for (int i = 0; i < iter; i++)
        {
            cout << ans[i] << "  ";
        }
        cout << endl
             << endl;

        if (w <1)
        {
            myfile << "iteration"
                   << ","
                   << "cost" << endl;
            for (int i = 0; i < iter; i++)
            {
                myfile << setprecision(3) << i << "," << ans[i] << endl;
            }
            myfile.close();
        }
        float minVal1 = FLT_MAX;
        for (int i = 0; i < iter; i++)
        {
            if (ans[i] < minVal1)
            {
                minVal1 = ans[i];
            }
        }
        runMin[w] = minVal1;
    }

    cout << "Min cost from 50 run" << endl;
    for (int i = 0; i < 50; i++)
    {
        cout << setprecision(4) << runMin[i] << "  ";
    }

    for (int i = 0; i < 50; i++)
    {
        fout << setprecision(4) << runMin[i] << endl;
    }
    fout.close();

    return 0;
}