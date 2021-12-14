#include <iostream>
#include <vector>
#include <random>
#include <thread>

using namespace std;

void BubbleSort(vector<int>& forSort)
{
    for (size_t i = 0; i < 10; i++) {
        for (size_t j = 0; j < 9; j++) {
          if (forSort[j] > forSort[j + 1]) {
            int b = forSort[j]; // создали дополнительную переменную
            forSort[j] = forSort[j + 1]; // меняем местами
            forSort[j + 1] = b; // значения элементов
          }
        }
      }
}
void DisplayMatrix(vector<vector<int>> Processes)
{
    for(size_t i = 0; i < Processes.size(); i++)
    {
        for(size_t j = 0; j < Processes[i].size(); j++)
        {
            cout << Processes[i][j] << " | ";
        }
        cout << endl;
    }
}
int main()
{
    std::mt19937 gen(time(0));
    std::uniform_int_distribution<> uid(1, 1000000);
    size_t N;                  // Количество элементов в массиве
    cout << "Enter the number of items: "; cin >> N;
    size_t CountThread;        // Количество потоков
    cout << "Enter the number of thread: "; cin >> CountThread;
    vector<int> array;      // Массив элементов
    vector<thread> Threads(CountThread); // Массив потоков
    for(size_t i = 0; i < N; i++)
    {
        int inputVal = uid(gen);
        array.push_back(inputVal);
    }
    /*  Разделение массива элементов для параллельной
        сортировки последовательным алгоритмом        */
    vector<vector<int>> Processes;      // Матрица массивов с элементами
    size_t count = N / CountThread;     // Количество элементов в одном процессе
    size_t ost = N % CountThread;       // Количество процессов где элементов больше на 1 чем count
    size_t q = 0;
    for(size_t i = 0; i < CountThread; i++)
    {
        vector<int> tmp;
        if(q < ost){
            tmp.insert(std::end(tmp), std::begin(array), std::begin(array) + (int)count + 1);
            array.erase(array.begin(), array.begin() + (int)count + 1);
            q++;
        }else{
            tmp.insert(std::end(tmp), std::begin(array), std::begin(array) + (int)count);
            array.erase(array.begin(), array.begin() + (int)count);
        }
        Processes.push_back(tmp);
    }

    for(size_t i = 0; i < CountThread; i++)
    {
        Threads[i] = thread(BubbleSort, std::ref(Processes[i]));
    }
    for (auto &t : Threads)
    {
        t.join();
    }

    DisplayMatrix(Processes);
    /*for(size_t i = 0; i < array.size(); i++)
            cout << array[i] << ' ';*/
    return 0;
}
