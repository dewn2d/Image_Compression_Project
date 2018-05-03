from pprint import pprint
from tools import create_indexes
import timeit
import dis


def main():
    """Body of program"""
    n = 6
    matrix = gen_zigazaga(n)
    pprint(matrix)

    # t = timeit.Timer(lambda: zigazaga(matrix))
    # t2 = timeit.Timer(lambda: zigazaga_alt(matrix))
    # print(t.timeit(number=100))
    # print(t2.timeit(number=100))
    print(zigazaga(matrix))
    print(zigazaga_alt(matrix))


def zigazaga(matrix):
    """Scan matrix of zigzag algorithm"""
    vector = []
    n = len(matrix) - 1
    i = 0
    j = 0

    for _ in range(n * 2):
        vector.append(matrix[i][j])

        if j == n:   # right border
            i += 1     # shift
            while i != n:   # diagonal passage
                vector.append(matrix[i][j])
                i += 1
                j -= 1
        elif i == 0:  # top border
            j += 1
            while j != 0:
                vector.append(matrix[i][j])
                i += 1
                j -= 1
        elif i == n:   # bottom border
            j += 1
            while j != n:
                vector.append(matrix[i][j])
                i -= 1
                j += 1
        elif j == 0:   # left border
            i += 1
            while i != 0:
                vector.append(matrix[i][j])
                i -= 1
                j += 1

    vector.append(matrix[i][j])
    return vector


def zigazaga_alt(matrix):
    """Alternative algorithm of zigzag scan"""
    vector = []
    n = len(matrix)
    indexes = create_indexes(n)
    for start, stop, desc in indexes:
        i_range = range(start, stop + desc, desc)
        j_range = reversed(i_range)
        vector += ([matrix[i][j] for i, j in zip(i_range, j_range)])
    return vector


def gen_zigazaga(n):
    """Genearate matrix in zigzag form"""
    matrix = [[0 for _ in range(n)] for _ in range(n)]
    value = 0

    n = len(matrix)
    indexes = create_indexes(n)
    for start, stop, desc in indexes:
        i_range = range(start, stop + desc, desc)
        j_range = reversed(i_range)
        for i, j in zip(i_range, j_range):
            value += 1
            matrix[i][j] = value
    return matrix


if __name__ == "__main__":
    main()
