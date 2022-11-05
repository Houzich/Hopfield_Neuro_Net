// 
// Нужно написать Нейронную сеть Хопфилда на С++ для умножения вектора [1, -1, 1, -1] на самого себя. 
// В результате у вас должна получиться квадратная матрица 4x4.
//

#include <iostream>
#include <locale.h>
#include <string>



// Длина вектора
#define num_neuron 4



// Правильный вектор
int correct_vector[num_neuron] = { 1, -1, 1, -1 };

// Искаженный вектор
int distorted_vector[num_neuron] = { 1, -1, 1, 1 };

// Весовая матрица (Запоминание образца сетью) (W = x^t*x)
int weight_matrix[num_neuron][num_neuron];

// Массив комбинированных вводов нейронов
int combined_input[num_neuron];

// Массив активностей нейронов
int element_activity[num_neuron];

void vector_print(const int vct[], size_t size)
{
    std::cout << "{";
    for (size_t i = 0; i < size; ++i) {
        if(i != size-1)
            std::cout << std::to_string(vct[i]) << ", ";
        else
            std::cout << std::to_string(vct[i]);
    }
    std::cout << "}\n";
}

void matrix_print(const int(*mtx)[num_neuron][num_neuron])
{
    for (int j = 0; j < num_neuron; j++) {
        for (int i = 0; i < num_neuron; i++) {
            if (i != num_neuron - 1)
            {
                if ((*mtx)[j][i] < 0)
                    std::cout << std::to_string((*mtx)[j][i]) << ", ";
                else
                    std::cout << " " << std::to_string((*mtx)[j][i]) << ", ";
            }
                
            else
            {
                if ((*mtx)[j][i] < 0)
                    std::cout << std::to_string((*mtx)[j][i]);
                else
                    std::cout << " " << std::to_string((*mtx)[j][i]);
            }
                
        }
        std::cout << "\n";
    }
}


void learn_neuro_net() {

    std::cout << "Входной сигнал: вектор X = ";
    vector_print(correct_vector, num_neuron);

    // Обнуляем комбинированные вводы нейронов
    for (int i = 0; i < num_neuron; i++) {
        combined_input[i] = 0;
    }

    // Определяем начальную весовую матрицу по формуле W = x^t*x
    std::cout << "Определяем начальную весовую матрицу по формуле W = x^t*x\n";
    for (int j = 0; j < num_neuron; j++) {
        for (int i = 0; i < num_neuron; i++) {
            weight_matrix[j][i] = correct_vector[j] * correct_vector[i];
        }
    }
    std::cout << " W = \n";
    matrix_print(&weight_matrix);



    // Обнуляем диагональные элементы весовой матрицы
    std::cout << " Обнуляем диагональные элементы весовой матрицы\n";
    for (int i = 0; i < num_neuron; i++) {
        weight_matrix[i][i] = 0;
    }
    std::cout << " W = \n";
    matrix_print(&weight_matrix);
}

int read_element_activity(int val) {
    int i;
    if (val > 0 || val == 0) {
        i = 1;
    }
    if (val < 0) {
        i = -1;
    }
    return i;
}

void check_neuro_net() {

    // Обнуляем комбинированные вводы нейронов
    for (int i = 0; i < num_neuron; i++) {
        combined_input[i] = 0;
    }

    // Подадим на вход Искаженный вектор (distorted_vector)
    // Комбинированный ввод нейронов
    std::cout << "Проверим устойчивое состояние сети Хопфилда для найденых весов W, но для искаженного образца:\n";
    std::cout << "Искаженный вектор: вектор Xdistr = ";
    vector_print(distorted_vector, num_neuron);
    for (int j = 0; j < num_neuron; j++) {
        for (int i = 0; i < num_neuron; i++) {
            combined_input[j] += (distorted_vector[i] * weight_matrix[j][i]);
        }
    }
    std::cout << "Получили Комбинированный ввод нейронов: вектор Xcomb = ";
    vector_print(combined_input, num_neuron);

    // Активность нейронов
    std::cout << "Определяем активность нейронов: вектор Xactiv = ";
    for (int i = 0; i < num_neuron; i++) {
        element_activity[i] = read_element_activity(combined_input[i]);
    }
    std::cout << "Получили вектор Xactiv = ";
    vector_print(element_activity, num_neuron);

    //Перезаписываем искаженный вектор на новый
    std::cout << "Перезаписываем искаженный вектор на новый";
    for (int i = 0; i < num_neuron; i++) {
        distorted_vector[i] = element_activity[i];
    }
    std::cout << "вектор Xdistr = ";
    vector_print(distorted_vector, num_neuron);
}




int main()
{
    setlocale(LC_ALL, "Russian"); // задаём русский текст
    system("chcp 1251"); // настраиваем кодировку консоли

    std::cout << "Старт!\n";
    std::cout << "\nОБУЧАЕМ СЕТЬ\n\n";
    learn_neuro_net();
    std::cout << "\nПРОВЕРЯЕМ СЕТЬ\n\n";
    check_neuro_net();
    std::cout << "\n\n";


    std::cout << "Следует отметить, что мы выявили исходный вектор ";
    vector_print(distorted_vector, num_neuron);
    std::cout << "характеризующий устойчивое состояние сети \n";

    system("pause");
}

