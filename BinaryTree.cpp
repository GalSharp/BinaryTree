#include <iostream>
#include <fstream>

using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
};

// Функция для создания новой вершины дерева
Node* createNode(int data) {
    Node* newNode = new Node();
    if (!newNode) {
        cout << "Ошибка при выделении памяти!" << endl;
        return nullptr;
    }
    newNode->data = data;
    newNode->left = newNode->right = nullptr;
    return newNode;
}

// Функция для вставки новой вершины в дерево
Node* insertNode(Node* root, int data) {
    // Если дерево пусто, создаем новую вершину и делаем ее корнем
    if (root == nullptr) {
        root = createNode(data);
        return root;
    }

    // Рекурсивно вставляем новую вершину в соответствующее поддерево
    if (data < root->data) {
        root->left = insertNode(root->left, data);
    }
    else if (data > root->data) {
        root->right = insertNode(root->right, data);
    }

    return root;
}

// Функция для обхода дерева в порядке "in-order" и сохранения прохождения в файл
void inorderTraversal(Node* root, ofstream& outputFile) {
    if (root == nullptr) {
        return;
    }

    // Рекурсивно обходим левое поддерево
    inorderTraversal(root->left, outputFile);

    // Записываем значение текущей вершины в файл
    outputFile << root->data << " ";

    // Рекурсивно обходим правое поддерево
    inorderTraversal(root->right, outputFile);
}

int main() {

    system("chcp 1251");

    Node* root = nullptr;
    int data;

    // Ввод последовательности данных и построение дерева
    cout << "Введите последовательность данных (введите -1 для завершения ввода):" << endl;
    while (true) {
        cin >> data;
        if (data == -1) {
            break;
        }
        root = insertNode(root, data);
    }

    // Создаем файл для записи прохождения дерева
    ofstream outputFile("tree_traversal.txt");
    if (!outputFile.is_open()) {
        cout << "Ошибка при открытии файла для записи!" << endl;
        return 0;
    }

    // Выполняем обход дерева и записываем прохождение в файл
    inorderTraversal(root, outputFile);

    // Закрываем файл
    outputFile.close();

    cout << "Бинарное дерево построено, и его прохождение сохранено в файле 'tree_traversal.txt'." << endl;

    return 0;
}
