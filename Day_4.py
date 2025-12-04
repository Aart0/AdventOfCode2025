from icecream import ic

#FILE_NAME = "in_files/d4_in_test.txt"
FILE_NAME = "in_files/d4_in_real.txt"
MATRIX_SIZE = 139 + 2 
BAD_CHAR = "@"
GOOD_CHAR = "."

def file_to_matrix(file_name):
    try:
        with open(file_name) as input_file:
            file_matrix = []
            file_matrix.append([GOOD_CHAR] * MATRIX_SIZE)
            
            for line in input_file:
                clean_line = line.replace("\n","")
                row = [GOOD_CHAR]  
                for char in clean_line:
                    row.append(char)
                row.append(GOOD_CHAR)  
                file_matrix.append(row)
            
            file_matrix.append([GOOD_CHAR] * MATRIX_SIZE)
            return file_matrix
            
    except OSError as problem:
        print(f"ERROR! we have a problem: {problem}")

def bad_checker(matrix, i ,j):
    flag = 0
    neighbors = [
            (i-1, j-1), (i, j-1), (i+1, j-1),
            (i-1, j), (i+1, j),
            (i-1, j+1), (i, j+1), (i+1, j+1)
            ]
    if matrix[i][j] == BAD_CHAR:
        bad_counter = 0
        for ni, nj in neighbors:
            if matrix[ni][nj] == BAD_CHAR:
                bad_counter += 1
      
        if bad_counter < 4:
            flag = 1 
    return flag
            
def second_part(matrix):
    change_counter = 0
    prev_change_counter = -1
    
    while prev_change_counter != change_counter:
        prev_change_counter = change_counter
        old_matrix = [row[:] for row in matrix]
        
        for i in range(MATRIX_SIZE):
            for j in range(MATRIX_SIZE):
                if bad_checker(old_matrix, i, j):
                       if old_matrix[i][j] == BAD_CHAR and matrix[i][j] == BAD_CHAR:
                            matrix[i][j] = GOOD_CHAR
                            change_counter += 1
    
    return change_counter

def row_counter(matrix):
    real_counter = 0 
    for i in range(MATRIX_SIZE):
        for j in range(MATRIX_SIZE):
            real_counter = real_counter + bad_checker(matrix, i, j)
    return(real_counter)          

def main():
    matrix = file_to_matrix(FILE_NAME)
    bad_amount = row_counter(matrix)
    change_amount = second_part(matrix) 
    ic(bad_amount)
    ic(change_amount)

if __name__ == "__main__":
    main()

