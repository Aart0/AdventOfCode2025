from icecream import ic

#FILE_NAME = "in_files/d7_in_test.txt"
FILE_NAME = "in_files/d7_in_real.txt"
EMPTY = '.'
START = 'S'
SPLITTER = '^'
BEAM = '|'

def main():
    matrix = file_to_matrix(FILE_NAME)
    part_1_result = beam_spliter(matrix)
    ic(part_1_result)


def beam_spliter(matrix):
    rows = len(matrix)
    cols = len(matrix[0])
    split_counter = 0

    for row in range(rows-1):
        for col in range(cols):
            
            if (matrix[row][col] == START):
                print("WE STARTED BABY!!!\n")
                matrix[row+1][col] = BEAM
            if (matrix[row][col] == BEAM and matrix[row+1][col] == EMPTY): 
                matrix[row+1][col] = BEAM
            if (matrix[row][col] == BEAM and matrix[row+1][col]== SPLITTER):
                if(col != cols and col != 0):
                    matrix[row+1][col+1],matrix[row+1][col-1]= BEAM, BEAM
                    split_counter+=1
    
    return split_counter

    

def file_to_matrix(file_name):
    try:
        with open(file_name) as file:
            lines = [list(line.strip('\n')) for line in file]
        return lines
    except OSError as problem:
        print(f"you got an error: {problem}")
        return []


if __name__ == "__main__":
    main()
