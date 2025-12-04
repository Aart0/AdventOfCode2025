from os import waitpid
from icecream import ic

#FILE_NAME = "in_files/d4_in_test.txt"
FILE_NAME = "in_files/d4_in_real.txt"
MATRIX_SIZE = 139 + 2 
BAD_CHAR = "@"
GOOD_CHAR = "."

def file_to_matrix(file_name):
    try:
        with open(file_name) as input_file:
            start_row = []
            file_matrix = [] 
            for _ in range(MATRIX_SIZE):
                start_row.append(".")
            file_matrix.append(start_row)

            for line in input_file:
                clean_line = line.replace("\n","")
                row = []
                row.append(".")
                for char in clean_line:
                    row.append(char)
                row.append(".")
                file_matrix.append(row)
           
            file_matrix.append(start_row)

            return (file_matrix) 
    except OSError as problem:
        print(f"ERROR! we have a problem: {problem}")

def row_counter(matrix):
    real_counter = 0 
    for i in range(MATRIX_SIZE):
        for j in range(MATRIX_SIZE):
            if matrix[i][j] == BAD_CHAR:
                bad_counter = 0
                if matrix[i-1][j-1] == BAD_CHAR:
                    bad_counter = bad_counter + 1
                if matrix[i][j-1] == BAD_CHAR:
                    bad_counter = bad_counter + 1
                if matrix[i+1][j-1] == BAD_CHAR:
                    bad_counter = bad_counter + 1
                if matrix[i-1][j] == BAD_CHAR:
                    bad_counter = bad_counter + 1
                if matrix[i+1][j] == BAD_CHAR:
                    bad_counter = bad_counter + 1
                if matrix[i-1][j+1] == BAD_CHAR:
                    bad_counter = bad_counter + 1
                if matrix[i][j+1] == BAD_CHAR:
                    bad_counter = bad_counter + 1
                if matrix[i+1][j+1] == BAD_CHAR:
                    bad_counter = bad_counter + 1
                if bad_counter < 4:
                    real_counter = real_counter + 1
    return(real_counter)          


def main():
    matrix = file_to_matrix(FILE_NAME)
    amount = row_counter(matrix)
    ic(matrix)
    ic(amount)

if __name__ == "__main__":
    main()

