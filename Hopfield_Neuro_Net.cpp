// 
// ����� �������� ��������� ���� �������� �� �++ ��� ��������� ������� [1, -1, 1, -1] �� ������ ����. 
// � ���������� � ��� ������ ���������� ���������� ������� 4x4.
//

#include <iostream>
#include <locale.h>
#include <string>



// ����� �������
#define num_neuron 4



// ���������� ������
int correct_vector[num_neuron] = { 1, -1, 1, -1 };

// ���������� ������
int distorted_vector[num_neuron] = { 1, -1, 1, 1 };

// ������� ������� (����������� ������� �����) (W = x^t*x)
int weight_matrix[num_neuron][num_neuron];

// ������ ��������������� ������ ��������
int combined_input[num_neuron];

// ������ ����������� ��������
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

    std::cout << "������� ������: ������ X = ";
    vector_print(correct_vector, num_neuron);

    // �������� ��������������� ����� ��������
    for (int i = 0; i < num_neuron; i++) {
        combined_input[i] = 0;
    }

    // ���������� ��������� ������� ������� �� ������� W = x^t*x
    std::cout << "���������� ��������� ������� ������� �� ������� W = x^t*x\n";
    for (int j = 0; j < num_neuron; j++) {
        for (int i = 0; i < num_neuron; i++) {
            weight_matrix[j][i] = correct_vector[j] * correct_vector[i];
        }
    }
    std::cout << " W = \n";
    matrix_print(&weight_matrix);



    // �������� ������������ �������� ������� �������
    std::cout << " �������� ������������ �������� ������� �������\n";
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

    // �������� ��������������� ����� ��������
    for (int i = 0; i < num_neuron; i++) {
        combined_input[i] = 0;
    }

    // ������� �� ���� ���������� ������ (distorted_vector)
    // ��������������� ���� ��������
    std::cout << "�������� ���������� ��������� ���� �������� ��� �������� ����� W, �� ��� ����������� �������:\n";
    std::cout << "���������� ������: ������ Xdistr = ";
    vector_print(distorted_vector, num_neuron);
    for (int j = 0; j < num_neuron; j++) {
        for (int i = 0; i < num_neuron; i++) {
            combined_input[j] += (distorted_vector[i] * weight_matrix[j][i]);
        }
    }
    std::cout << "�������� ��������������� ���� ��������: ������ Xcomb = ";
    vector_print(combined_input, num_neuron);

    // ���������� ��������
    std::cout << "���������� ���������� ��������: ������ Xactiv = ";
    for (int i = 0; i < num_neuron; i++) {
        element_activity[i] = read_element_activity(combined_input[i]);
    }
    std::cout << "�������� ������ Xactiv = ";
    vector_print(element_activity, num_neuron);

    //�������������� ���������� ������ �� �����
    std::cout << "�������������� ���������� ������ �� �����";
    for (int i = 0; i < num_neuron; i++) {
        distorted_vector[i] = element_activity[i];
    }
    std::cout << "������ Xdistr = ";
    vector_print(distorted_vector, num_neuron);
}




int main()
{
    setlocale(LC_ALL, "Russian"); // ����� ������� �����
    system("chcp 1251"); // ����������� ��������� �������

    std::cout << "�����!\n";
    std::cout << "\n������� ����\n\n";
    learn_neuro_net();
    std::cout << "\n��������� ����\n\n";
    check_neuro_net();
    std::cout << "\n\n";


    std::cout << "������� ��������, ��� �� ������� �������� ������ ";
    vector_print(distorted_vector, num_neuron);
    std::cout << "��������������� ���������� ��������� ���� \n";

    system("pause");
}

