from icecream import ic

#FILE_NAME = "in_files/d6_in_test.txt"
FILE_NAME = "in_files/d6_in_real.txt"


def main():
    matrix, readed_lines, line_len = file_to_matrix(FILE_NAME)
    sum = matrix_to_calculator(matrix,readed_lines, line_len)
    ic(sum)
    ic(second_part(FILE_NAME))

def file_to_matrix(file_name):
    readed_lines = 0
    try:
        with open(file_name) as file:
            file_matrix = []
            
            for line in file:
                clean_line = line.replace("\n", "").split()
                row = []
                readed_lines+= 1 
                line_len = len(clean_line)
                for num in clean_line:
                    row.append(num)
                file_matrix.append(row)

            return file_matrix, readed_lines, line_len

    except OSError as problem:
        print(f"ERROR! the problem: {problem}")
        return [], 0, 0


def matrix_to_calculator(matrix, readed_lines, line_len): #PART 1
    total_sum = 0
    for j in range(line_len):
        if (matrix[readed_lines-1][j] == '+'):
            total_sum += column_sum(matrix, j)             
        if (matrix[readed_lines-1][j] == '*'):
            total_sum += column_multiply(matrix, j)
    return total_sum 

def column_sum(matrix, j):
    sum = 0
    for row in range(len(matrix)-1):
        sum += int(matrix[row][j])
    return sum
    
def column_multiply(matrix, j):
    sum = 1 
    for row in range(len(matrix)-1):
        sum *= int(matrix[row][j])
    return sum

def second_part(filepath): # SECOND TRY FOR SECOND PART USING STRING MANIPULATIONS (HEAVILY INSPIRED BY REDDIT USER: u/CDninja)
    try:
        with open(filepath) as file:
            lines = [list(line.strip('\n'))[::-1] for line in file]
        
        operators = ''.join(lines[-1]).split()
        columns = [''.join(col).strip() for col in zip(*lines[:-1])]
        joined = '|'.join(columns)
        problems = [problem.split('|') for problem in joined.split('||')]
        ic(problems)  #debug 
        total = 0
        for i in range(len(problems)):
            numbers = [int(num) for num in problems[i]]  
            operator = operators[i]
            
            if operator == '+':
                result = sum(numbers)
            elif operator == '*':
                result = 1
                for num in numbers:
                    result *= num
            else:
                result = 0
            
            total += result
        
        return total
    
    except OSError as problem:
        print(f"ERROR! the problem: {problem}")
        return 0


if __name__ == "__main__":
    main()


