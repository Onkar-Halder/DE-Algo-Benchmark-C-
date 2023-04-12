#include <bits/stdc++.h>
using namespace std;

float f = 0.5;
float cr = 0.7;
float lb = -5.12, ub = +5.12;
float pi = 3.14;

int main()
{
    ofstream fout, myfile;
    fout.open("Levy_excel.csv");
    myfile.open("Levy_graph.csv");
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
        /*cout << endl
             << endl;
        cout << "Initial search space" << endl;*/
        float arr1[10][5];
        for (int i = 0; i < 10; i++)
        {
            int ran_var = 0 + rand() % 100;
            for (int j = 0; j < 5; j++)
            {
                arr1[i][j] = arr[ran_var][j];
                //cout << setprecision(2) << arr1[i][j] << " ";
            }
            //cout << endl;
        }
        /*cout << endl
             << endl;*/

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
            float ar[10][5];
            for(int i=0;i<10;i++){
                for(int j=0;j<5;j++){
                    ar[i][j]= 1+((arr1[i][j]-1)/4);
                }
            }
            float t1=pow(sin(pi*ar[0][0]), 2);
            float t2=pow(ar[9][4]-1, 2) * (1+pow(sin(2*pi*ar[9][4]),2));
            for (int i = 0; i < 10; i++)
            {
                float xp = 0, xtri = 0;
                float sum_f = 0;
                for (int j = 0; j < 5-1; j++)
                {
                    xp = pow(ar[i][j]-1,2);
                    xtri = 1+ (10 * pow(sin((pi*ar[i][j])+1),2));
                    sum_f += (xp * xtri);
                }
                costRes[i] = sum_f;
            }

            // print array of cost
            /*
             cout << "Array of cost" << endl;
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
                float ar1[5];
            
                for(int j=0;j<5;j++){
                    ar1[j]= 1+((arrXoff1[j]-1)/4);
                }
                float t1=pow(sin(pi*ar1[0]), 2);
                float t2=pow(ar1[4]-1, 2) * (1+pow(sin(2*pi*ar1[4]),2));
                float xp = 0, xtri = 0;
                float sum_f = 0;
                for (int j = 0; j < 5; j++)
                {
                   xp = pow(ar1[j]-1,2);
                    xtri = 1+ (10 * pow(sin((pi*ar1[j])+1),2));
                    sum_f += (xp * xtri);
                }
                Xoffcost = sum_f;

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

        if (w > 0 && w < 2)
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
