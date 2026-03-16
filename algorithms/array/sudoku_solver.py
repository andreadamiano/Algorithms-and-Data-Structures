def check(board: list, ch: chr, x: int, y: int) -> bool:

    for i in range(9):
        if ch in board[y][i]: return False   #check in the current row 
        if ch in board[i][x]: return False   #check in the current column 
        if ch in board[(i // 3) + (y // 3)*3][(i % 3) + (x // 3)*3]: return False  #check current box

    return True


def solve(board: list) -> None:
    solve_sudoku(board, 0)

def solve_sudoku(board: list, current_cell: int, cells: int = 81) -> bool:
    for i in range(current_cell, cells):
        y = i // 9
        x = i % 9

        if board[y][x] == ".":
            
            #try to insert a number between 1 and 9
            for number in range(1, 10):
                ch = f"{number}"
                if check(board, ch, x, y):
                    board[y][x] = ch
                    if solve_sudoku(board, i+1):
                        return True
                    else:
                        board[y][x] = "."

            return False

    return True



if __name__ == "__main__":
    board = [["5","3",".",".","7",".",".",".","."],
             ["6",".",".","1","9","5",".",".","."],
             [".","9","8",".",".",".",".","6","."],
             ["8",".",".",".","6",".",".",".","3"],
             ["4",".",".","8",".","3",".",".","1"],
             ["7",".",".",".","2",".",".",".","6"],
             [".","6",".",".",".",".","2","8","."],
             [".",".",".","4","1","9",".",".","5"],
             [".",".",".",".","8",".",".","7","9"]]
    
    solve(board)
    print(board)