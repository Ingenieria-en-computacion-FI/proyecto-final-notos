from random import randint


def gen_process_list():
    process_list = []

    for i in range(10):
        process = f'{i},{randint(1, 20)},{randint(10, 500)},{randint(0,3)},{randint(0, 3)}'

        process_list.append(process)

    return process_list


