#include <iostream>

struct Stack {
    int info;
    Stack* next;
} *root;

static Stack* InStack(Stack* p, int data) {
    Stack* now = new Stack;
    now->info = data;
    now->next = p;
    return now;
}

static void View(Stack* p) {
    if (p == nullptr) {
        std::cout << "Стек пуст." << std::endl;
        return;
    }
    while (p->next != nullptr) {
        std::cout << p->info << " ";
        p = p->next;
    }
    std::cout << std::endl;
}

static void Sort_p(Stack** p) {
    if (*p == nullptr) return;
    Stack* t_n = new Stack;
    t_n->info = 100000;
    t_n->next = *p;
    Stack* t = nullptr, * t1, * r;
    if (t_n->next->next == nullptr) return;
    do {
        for (t1 = t_n; t1->next->next != t; t1 = t1->next)
            if (t1->next->info > t1->next->next->info) {
                r = t1->next->next;
                t1->next->next = r->next;
                r->next = t1->next;
                t1->next = r;
            }
        t = t1->next;
    } while (t_n->next->next != t);
    *p = t_n->next;
    delete t_n;
}

static void Sort_info(Stack* p) {
    if (p == nullptr) return;
    Stack* t = nullptr, * t1 = nullptr;
    int r;
    do {
        for (t1 = p; t1->next != t; t1 = t1->next)
            if (t1->info > t1->next->info) {
                r = t1->info;
                t1->info = t1->next->info;
                t1->next->info = r;
            }
        t = t1;
    } while (p->next != t);
}

static float Average(Stack* p) {
    if (p == nullptr) return 0;
    int count = 0;
    float sum = 0;
    while (p != nullptr) {
        Stack* t = p;
        count++;
        sum += p->info;
        p = p->next;
    }
    return sum / count;
}

static int Count_Delete(Stack*& p) {
    if (p == nullptr) return 0;
    float av = Average(p);
    int count = 0;
    while (p->info < av) {
        Stack* t = p;
        p = p->next;
        delete t;
        count++;
    }
    return count;
}

static Stack* OutStack(Stack* p, int n) {
    bool b = false;
    while (p->next != nullptr) {
        if (p->info == n) {
            Stack* t = p->next;
            delete p;
            return t;
        }
        b = true;
    }
    if (b) std::cout << "В стеке нет такого элемента!" << std::endl;
    return p;
}

static void Del_All(Stack** p) {
    Stack* t;
    while (*p != nullptr) {
        t = *p;
        *p = (*p)->next;
        delete t;
    }
}

int main() {
    setlocale(LC_ALL, "RU");
    root = nullptr;
    int n, m;
    do {
        std::cout << "1. Просмотр стека.\n" 
            << "2. Добавление элемента.\n"
            << "3. Заполнение случайным числами.\n"
            << "4. Удаление элемента.\n"
            << "5. Среднее значение всех элементов.\n" 
            << "6. Задание.\n"
            << "7. Сортировка по значению.\n"
            << "8. Сортировка обменом адресом.\n"
            << "9. Выход.\n";
        std::cout << "Выберите действие: ";
        std::cin >> n;
        switch (n) {
        case 1: {
            std::cout << "Элементы стека: ";
            View(root);
            break;
        }
        case 2: {
            std::cout << "Добавить элемент: ";
            std::cin >> m;
            root = InStack(root, m);
            break;
        }
        case 3: {
            std::cout << "Сколько элементов добавить?: ";
            std::cin >> m;
            if (m < 0) {
                std::cout << std::endl << "Число не может быть меньше 0!" << std::endl;
                break;
            }
            for (int i = 0; i < m; i++) root = InStack(root, rand() % 10);
            break;
        }
        case 4: {
            std::cout << "Удалить элемент: ";
            std::cin >> m;
            root = OutStack(root, m);
            std::cout << std::endl;
            break;
        }
        case 5: {
            std::cout << "Среднее значение всех элементов: " << Average(root) << std::endl;
            break;
        }
        case 6: {
            std::cout << "Количество удалённых элементов: " << Count_Delete(root) << std::endl;
            break;
        }
        case 7: {
            Sort_info(root);
            break;
        }
        case 8: {
            Sort_p(&root);
            break;
        }
        case 9: {
            Del_All(&root);
            std::cout << "Стек очищен." << std::endl;
            std::cout << "Выход из программы...";
            break;
        }
        }
    } while (n != 9);
}