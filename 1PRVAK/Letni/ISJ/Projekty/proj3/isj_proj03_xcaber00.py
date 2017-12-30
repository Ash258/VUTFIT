#!/usr/bin/env python3


def first_task():
    singular = ['goose', 'man', 'child']
    plural = ['geese', 'men', 'children']
    # {'goose':'geese', 'man':'men', 'child':'children'}
    sing2plur = {s: p for s, p in zip(singular, plural)}
    # inversion using zip
    plur2sing = dict(zip(plural, singular))
    return plur2sing == {'geese': 'goose', 'men': 'man', 'children': 'child'}


def second_task():
    word2vect = {'king': [3, 1], 'queen': [6, 3], 'uncle': [4, 3], 'aunt': [8, 9]}
    vect2word = {tuple(v): k for (k, v) in word2vect.items()}  # word2vect.values()
    return sum(k[1] for k in vect2word) == 16


def pro_pripomenuti():
    a = [1, 2, 3]
    b = [1, 2, 3]
    print(a == b)
    print(id(a))
    print(id(b))
    print(a is b)
    a.append(4)
    print(id(a))
    print(a == b)
    print(repr(a))
    try:
        di = {a: 42}
    except Exception as e:
        print(e)


# pro_pripomenuti()


class MyList(list):
    def __hash__(self):
        return hash(tuple(sorted(self)))


def third_task():
    a = MyList([1, 2, 3])
    b = MyList([1, 2, 3])
    di = {a: 42}
    li = list(di)
    b_in_di = b in di
    b_in_li = b in li
    a.append(4)
    a_in_di = a in di
    a_in_li = a in li
    return b_in_di and b_in_li and not a_in_di and a_in_li


if first_task():
    print('funguje')
else:
    print('nefunguje')
if second_task():
    print('funguje')
else:
    print('nefunguje')
if third_task():
    print('funguje')
else:
    print('nefunguje')
