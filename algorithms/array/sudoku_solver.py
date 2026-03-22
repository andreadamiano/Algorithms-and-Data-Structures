def check(board: list, ch: chr, x: int, y: int) -> bool:

    for i in range(9):
        if ch in board[y][i]: return False   #check in the current row 
        if ch in board[i][x]: return False   #check in the current column 
        if ch in board[(i // 3) + (y // 3)*3][(i % 3) + (x // 3)*3]: return False  #check current box

    return True

def preprocess(board: list[list[str]]):
    rows = [set() for _ in range(9)]
    cols = [set() for _ in range(9)]
    boxes = [set() for _ in range(9)]
    empty_cells = set()

    for i in range(81):
        y = i // 9
        x = i % 9
        val = board[y][x]

        if val != ".":
            rows[y].add(val)
            cols[x].add(val)
            boxes[((i % 9) // 3) + (i // 27) * 3].add(val)

        else:
            empty_cells.add(i)

    return rows, cols, boxes, empty_cells


def solve(board: list) -> None:
    rows, cols, boxes, empty_cells = preprocess(board)

    def solve_sudoku(board: list) -> bool:

        for i in empty_cells:
            y = i // 9
            x = i % 9
            box_index = ((i % 9) // 3) + (i // 27) * 3

            if board[y][x] == ".":
                
                #try to insert a number between 1 and 9
                for number in "123456789":
                    if number not in cols[x] and number not in rows[y] and number not in boxes[box_index]:
                        board[y][x] = number
                        rows[y].add(number)
                        cols[x].add(number)
                        boxes[box_index].add(number)
                        empty_cells.remove(i)
                        if solve_sudoku(board):
                            return True
                        
                        #backtracking
                        board[y][x] = "."
                        rows[y].remove(number)
                        cols[x].remove(number)
                        boxes[box_index].remove(number)
                        empty_cells.add(i)

                return False

        return True
    
    solve_sudoku(board)



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
    
    # board = [[".",".",".",".",".",".",".",".","."],[".","9",".",".","1",".",".","3","."],[".",".","6",".","2",".","7",".","."],[".",".",".","3",".","4",".",".","."],["2","1",".",".",".",".",".","9","8"],[".",".",".",".",".",".",".",".","."],[".",".","2","5",".","6","4",".","."],[".","8",".",".",".",".",".","1","."],[".",".",".",".",".",".",".",".","."]]
    
    solve(board)
    print(board)