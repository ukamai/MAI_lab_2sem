/*
 * Операции обработки выражений
 */

#include <stdio.h>
#include <stdlib.h>

#include "str.h"
#include "deque.h"
#include "tree.h"
#include "tools.h"

// Проверка типа данного оператора
Type type_op(char op) {
    if (op == '+' || op == '-')
        return PLUS_MINUS;
    if (op == '*' || op == '/')
        return MUL_DIV;
    if (op == '^')
        return POWER;
    return NONE;
}

// Проверка, является ли данный символ оператором или скобкой
int is_operator_or_bracket(char chr) {
    char *this = "+-/*()^";
    for (int i = 0; i < 7; i++) {
        if (this[i] == chr)
            return 1;
    }
    return 0;
}

// Чтение выражения из стандартного ввода и запись в дек
// На этом этапе многобуквенные переменные записываются, как единое целое
int read_expression(Deque *input) {
    // С помощью этих флагов определяется, нужно ли дописать очередной символ
    // к существующей строке, или создать новую строку (элемент дека)
    int is_char = 0, was_space = 0;

    char chr;
    while ((chr = getchar()) != '\n') {
        if (chr == ' ' || chr == '\t') {
            was_space = 1;
            continue;
        }
        if (is_operator_or_bracket(chr)) {
            was_space = 0;
            String *now = string();
            now->is_operand = 0;
            add(chr, now);
            deque_push_front(now, input);
            is_char = 0;
        } else if (!is_operator_or_bracket(chr) && !is_char) {
            was_space = 0;
            String *now = string();
            now->is_operand = 1;
            add(chr, now);
            deque_push_front(now, input);
            is_char = 1;
        } else if (is_char) {
            if (was_space)
                return 0;
            was_space = 0;
            add(chr, input->tail->value);
        }
    }
    return 1;
}

// Проверка на наличие операндов в выражении
// Или на отсутствие идущих подряд операторов
int check_ops(Deque *exp, int mode) {
    Deque *temp = deque_create();
    int res = 0;
    while (!deque_is_empty(exp)) {
        deque_push_front(deque_pop_back(exp), temp);
        if (temp->tail->value->is_operand && !mode) {
            res = 1;
            break;
        }
        if (!temp->tail->value->is_operand && temp->tail->value->head->chr != '(' &&
            temp->tail->value->head->chr != ')' && mode) {
            res = 1;
            break;
        }
    }
    while (!deque_is_empty(temp))
        deque_push_back(deque_pop_front(temp), exp);
    deque_erase(temp);
    if (exp->size == 1 && mode)
        return 1;
    return res;
}

// Проверка на наличие ошибок вида ...+)..., ...)*... и ...)(...
int check_no_ops_brackets(Deque *exp) {
    Deque *temp = deque_create();
    int res = 1;

    while (deque_size(exp) != 1) {
        deque_push_back(deque_pop_front(exp), temp);
        if (temp->head->value->head->chr == '(' && (exp->tail->value->is_operand || exp->tail->value->head->chr == ')'))
            res = 0;
        if (exp->tail->value->head->chr == ')' && temp->head->value->is_operand)
            res = 0;
        if (!res) break;
    }

    while (!deque_is_empty(temp))
        deque_push_front(deque_pop_back(temp), exp);

    deque_erase(temp);
    return res;
}

// Проверка на наличие незакрытых скобок
// При strict = 0 удаляются лишние обволакивающие выражение скобки
// = 1 - возвращает 0, если есть лишние скобки
int check_extra_brackets(Deque *expr, int strict) {
    while ((expr->tail->value->head->chr == ')' && expr->head->value->head->chr == '(') || strict) {
        String *left_bracket, *right_bracket;
        if (!strict) {
            left_bracket = deque_pop_back(expr);
            right_bracket = deque_pop_front(expr);
        }
        int level = 0;
        Deque *temp = deque_create();
        while (!deque_is_empty(expr)) {
            deque_push_back(deque_pop_front(expr), temp);
            if (temp->head->value->head->chr == ')')
                level++;
            if (temp->head->value->head->chr == '(') {
                if (!level && !strict)
                    level = expr->size + 10;
                else
                    level--;
            }
        }
        while (!deque_is_empty(temp))
            deque_push_front(deque_pop_back(temp), expr);
        if (level) {
            if (!strict) {
                deque_push_back(left_bracket, expr);
                deque_push_front(right_bracket, expr);
            }
            deque_erase(temp);
            return 0;
        } else {
            if (!strict) {
                erase(left_bracket);
                erase(right_bracket);
            } else {
                deque_erase(temp);
                return 1;
            }
        }
        deque_erase(temp);
    }
    return 1;
}

int parse_expression(Deque *exp, BNode *tree) {
    // Проверка на наличие операндов
    if (!check_ops(exp, 0))
        return 0;

    // Удаление обволакивающих скобок
    check_extra_brackets(exp, 0);

    int minus_check = 0;

    // Проверка на наличие унарного минуса и добавление фиктивного операнда (табуляции),
    // если унарный минус перед скобками
    if (exp->head->value->tail->chr == '-' && exp->head->next->value->tail->chr == '(') {
        deque_pop_back(exp);
        if (exp->head->value->tail->chr == '(' && exp->tail->value->tail->chr == ')') {
            check_extra_brackets(exp, 0);
            if (exp->head->value->tail->chr != '(') {
                deque_push_back(chr_string('('), exp);
                deque_push_back(chr_string('-'), exp);
                deque_push_back(chr_string('\t'), exp);
                exp->head->value->is_operand = 1;
                deque_push_front(chr_string(')'), exp);
                minus_check = -1;
            } else minus_check = 1;
        } else minus_check = 1;
    }

    // Вторичная проверка на лишние скобки и наличие идущих подряд операторов
    if (!check_extra_brackets(exp, 1) || !check_ops(exp, 1))
        return 0;

    // Проверка на наличие скобок и операторов рядом или скобок, не разделённых оператором
    if (!check_no_ops_brackets(exp))
        return 0;

    // Удаление унарного плюса в случае наличия
    if (exp->head->value->head->chr == '+') {
        deque_pop_back(exp);
        check_extra_brackets(exp, 0);
    }

    int brackets = 0, check_operator = 0;

    // Корректная обработка унарного минуса не перед скобками
    // (он засовывается в текст первого операнда)
    if (exp->head->value->tail->chr == '-' && minus_check != -1) {
        if (deque_size(exp) == 2) {
            insert('-', exp->tail->value);
            tree->value = copy_string(exp->tail->value);
            tree->is_brackets_minus = 1;
            return 1;
        }
        deque_pop_back(exp);
        insert('-', exp->head->value);
    }

    // Проверка на наличие операторов по краям
    if (!(exp->head->value->is_operand || exp->head->value->head->chr == '(') ||
        !(exp->tail->value->is_operand || exp->tail->value->head->chr == ')'))
        return 0;

    // Обработка выражения из одного элемента
    if (deque_size(exp) == 1) {
        if (!exp->head->value->is_operand)
            return 0;
        tree->value = deque_pop_back(exp);
        return 1;
    }
    // ... из двух элементов
    if (deque_size(exp) == 2 && exp->head->value->tail->chr == '-' && exp->tail->value->is_operand) {
        add(exp->tail->value->head->chr, exp->head->value);
        tree->value = exp->head->value;
        return 1;
    }

    Deque *temp = deque_create();
    Type type = NONE;
    DequeNode *base = NULL;

    // Парсинг дека с выражением
    while (!deque_is_empty(exp)) {
        deque_push_back(deque_pop_front(exp), temp);
        if (!temp->head->value->is_operand) {
            char c = temp->head->value->tail->chr;
            if (c == '(') {
                brackets--;
                check_operator = 0;
            }
            if (c == ')')
                brackets++;
            if (brackets || (c == '-' && deque_is_empty(exp)))
                continue;
            if ((c == '+' || c == '-') && type != PLUS_MINUS) {
                if (check_operator)
                    return 0;
                type = PLUS_MINUS;
                base = temp->head;
                check_operator = 1;
            }
            if ((c == '*' || c == '/') && type != PLUS_MINUS && type != MUL_DIV) {
                if (check_operator)
                    return 0;
                type = MUL_DIV;
                base = temp->head;
                check_operator = 1;
            }
            if (c == '^' && type != PLUS_MINUS && type != MUL_DIV && type != POWER) {
                if (check_operator)
                    return 0;
                type = POWER;
                base = temp->head;
                check_operator = 1;
            }
            if (c == ')')
                check_operator = 0;
        } else check_operator = 0;
    }

    while (temp->head != base) {
        deque_push_front(deque_pop_back(temp), exp);
    }

    // Возвращение унарного минуса, удалённого на время парсинга
    if (minus_check == 1)
        deque_push_back(chr_string('-'), exp);

    tree->value = deque_pop_back(temp);
    tree->left = new_node(NULL);
    tree->left->parent = tree;
    tree->right = new_node(NULL);
    tree->right->parent = tree;

    //Рекурсивный парсинг полученных частей слева и справа от обработанного оператора,
    // Проверка на корректность полученных деревьев, их добавление в правый и левый узел данного дерева,
    // или их удаление в случае ошибки
    if (!(parse_expression(exp, tree->left) & parse_expression(temp, tree->right))) {
        if (tree->left->value == NULL) {
            erase_tree(tree->left);
            tree->left = NULL;
        }
        if (tree->right->value == NULL) {
            erase_tree(tree->right);
            tree->right = NULL;
        }
        return 0;
    }
    deque_erase(temp);
    return 1;
}

// Обработка многоэтажных дробей
void transform(BNode* exp) {
    // Первый случай (a/b)/c
    if (exp->value->head->chr == '/' && exp->left->value->head->chr == '/') {
        BNode *a = copy_tree(exp->left->left);
        BNode *b = copy_tree(exp->left->right);
        BNode *c = copy_tree(exp->right);

        erase_tree(exp->left);
        erase_tree(exp->right);

        exp->left = a;
        a->parent = exp;

        exp->right = new_node(chr_string('*'));
        exp->right->parent = exp;

        exp->right->left = b;
        b->parent = exp->right;

        exp->right->right = c;
        c->parent = exp->right;
    } else if (exp->value->head->chr == '/' && exp->right->value->head->chr == '/') {
        // Второй случай a/(b/c)
        BNode *a = copy_tree(exp->left);
        BNode *b = copy_tree(exp->right->left);
        BNode *c = copy_tree(exp->right->right);

        erase_tree(exp->left);
        erase_tree(exp->right);

        exp->value->head->chr = '*';

        exp->left = new_node(chr_string('/'));
        exp->left->parent = exp;

        exp->left->left = a;
        a->parent = exp->left;

        exp->left->right = b;
        b->parent = exp->left;

        exp->right = c;
        c->parent = exp;
    } else if (type_op(exp->value->head->chr) != NONE) {
        // Проход глубже по дереву, если в данном узле не выполнился ни один из случаев
        transform(exp->left);
        transform(exp->right);
    }
}

// Получение дека с выражением из его дерева
Deque *from_tree(BNode *exp) {
    Deque *res = deque_create();
    if (exp->value->head->chr != '\t')
        deque_push_front(copy_string(exp->value), res);
    if (exp->left == NULL) {
        if (exp->is_brackets_minus && exp->parent != NULL) {
            deque_push_back(chr_string('('), res);
            deque_push_front(chr_string(')'), res);
        }
        return res;
    }

    Deque *left = from_tree(exp->left);
    Deque *right = from_tree(exp->right);

    while (!deque_is_empty(left))
        deque_push_back(deque_pop_front(left), res);
    while (!deque_is_empty(right))
        deque_push_front(deque_pop_back(right), res);

    deque_erase(left);
    deque_erase(right);

    // Добавление скобок исходя из порядка операций +, - и *, /
    if (exp->parent != NULL) {
        if (type_op(exp->parent->value->head->chr) > type_op(exp->value->head->chr) ||
            (exp->parent->value->tail->chr == '-' && exp == exp->parent->right &&
             !type_op(exp->value->head->chr)) || (exp->value->head->chr == '*' &&
             exp->parent->value->head->chr == '/' && exp->parent->right == exp)) {
            deque_push_back(chr_string('('), res);
            deque_push_front(chr_string(')'), res);
        }
    }
    return res;
}