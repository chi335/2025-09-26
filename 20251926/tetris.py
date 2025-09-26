import time
import random
import os
import msvcrt # Windows에서 키 입력을 바로 읽기 위해 사용

# ----------------------------------------------------
# 1. 게임 설정
# ----------------------------------------------------

# 보드 크기 (표준 테트리스는 10x20)
BOARD_WIDTH = 10
BOARD_HEIGHT = 20

# 블록 모양 정의 (4x4 격자 내에서 'X'는 블록, '.'는 빈 공간을 의미)
TETROMINOES = {
    'I': [['....',
           'XXXX',
           '....',
           '....'],
          ['.X..',
           '.X..',
           '.X..',
           '.X..']],
    'J': [['X...',
           'XXX.',
           '....',
           '....'],
          ['.XX.',
           '.X..',
           '.X..',
           '....'],
          ['XXX.',
           '..X.',
           '....',
           '....'],
          ['.X..',
           '.X..',
           'XX..',
           '....']],
    'L': [['..X.',
           'XXX.',
           '....',
           '....'],
          ['.X..',
           '.X..',
           '.XX.',
           '....'],
          ['XXX.',
           'X...',
           '....',
           '....'],
          ['XX..',
           '.X..',
           '.X..',
           '....']],
    'O': [['.XX.',
           '.XX.',
           '....',
           '....']],
    'S': [['.XX.',
           'XX..',
           '....',
           '....'],
          ['X...',
           'XX..',
           '.X..',
           '....']],
    'T': [['.X..',
           'XXX.',
           '....',
           '....'],
          ['.X..',
           '.XX.',
           '.X..',
           '....'],
          ['XXX.',
           '.X..',
           '....',
           '....'],
          ['.X..',
           'XX..',
           '.X..',
           '....']],
    'Z': [['XX..',
           '.XX.',
           '....',
           '....'],
          ['.X..',
           'XX..',
           'X...',
           '....']]
}

TETROMINO_KEYS = list(TETROMINOES.keys())
BLOCK_CHAR = '■'   # 블록을 나타낼 문자
EMPTY_CHAR = '□'   # 빈 공간을 나타낼 문자
BORDER_CHAR = '█'  # 경계를 나타낼 문자
GHOST_CHAR = '░'   # 고스트 블록을 나타낼 문자

# ----------------------------------------------------
# 2. 게임 상태 클래스
# ----------------------------------------------------

class TetrisGame:
    def __init__(self):
        self.board = [[EMPTY_CHAR] * BOARD_WIDTH for _ in range(BOARD_HEIGHT)]
        self.current_piece_key = None # 현재 조각의 키 ('I', 'J' 등)
        self.current_piece = None
        self.piece_x = 0
        self.piece_y = 0
        self.piece_rotation = 0
        self.score = 0
        self.game_over = False
        
        # --- [추가된 기능 관련 변수] ---
        self.next_piece_key = random.choice(TETROMINO_KEYS) # 다음 블록 키
        self.hold_piece_key = None # 홀드된 블록 키
        self.can_hold = True # 현재 블록이 고정되기 전에 홀드할 수 있는지 여부
        # ------------------------------------

        # 초기 블록 설정
        self.new_piece(initial=True)

    def new_piece(self, initial=False):
        """새로운 테트리스 조각을 생성합니다."""
        # 다음 블록을 현재 블록으로 가져옵니다.
        self.current_piece_key = self.next_piece_key
        self.current_piece = TETROMINOES[self.current_piece_key]
        self.piece_rotation = 0
        
        # 다음 블록을 새로 랜덤 생성합니다.
        if initial:
            # 초기화 시에는 바로 다음 블록까지 랜덤 생성
            self.next_piece_key = random.choice(TETROMINO_KEYS)
        else:
            # 다음 블록 키 랜덤 생성
            self.next_piece_key = random.choice(TETROMINO_KEYS) 

        # 중앙 상단에 배치
        self.piece_x = BOARD_WIDTH // 2 - 2
        self.piece_y = 0
        
        # 새 조각이 생성되자마자 충돌하면 게임 오버
        if self.check_collision(0, 0, 0):
            self.game_over = True

    def swap_hold_piece(self):
        """현재 조각을 홀드 조각과 교체합니다."""
        if not self.can_hold:
            return False # 이미 홀드 사용함

        # 현재 블록을 임시로 저장
        temp_piece_key = self.current_piece_key
        
        if self.hold_piece_key is None:
            # 홀드 공간이 비어있으면 다음 블록을 즉시 생성합니다.
            self.current_piece_key = self.next_piece_key
            self.current_piece = TETROMINOES[self.current_piece_key]
            self.next_piece_key = random.choice(TETROMINO_KEYS)
        else:
            # 홀드된 블록이 있으면 그 블록으로 교체합니다.
            self.current_piece_key = self.hold_piece_key
            self.current_piece = TETROMINOES[self.current_piece_key]

        # 홀드 공간 업데이트
        self.hold_piece_key = temp_piece_key
        
        # 교체 후 초기 위치로 설정
        self.piece_rotation = 0
        self.piece_x = BOARD_WIDTH // 2 - 2
        self.piece_y = 0
        
        self.can_hold = False # 홀드 사용했으므로 잠금
        return True

    def get_rotated_piece(self, rotation_offset=0):
        """현재 회전 상태에 해당하는 조각의 모양을 반환합니다."""
        rot_index = (self.piece_rotation + rotation_offset) % len(self.current_piece)
        return self.current_piece[rot_index]

    def check_collision(self, dx, dy, d_rot):
        """주어진 이동(dx, dy) 및 회전(d_rot) 후에 충돌이 발생하는지 확인합니다."""
        piece = self.get_rotated_piece(d_rot)
        for y in range(4):
            for x in range(4):
                if piece[y][x] == 'X':
                    board_x = self.piece_x + x + dx
                    board_y = self.piece_y + y + dy
                    
                    # 1. 경계 충돌 검사
                    if board_x < 0 or board_x >= BOARD_WIDTH or board_y >= BOARD_HEIGHT:
                        return True
                    # 2. 바닥 아래로 이동하는 경우
                    if board_y < 0: # 보드 위쪽으로 나가는 건 허용
                        continue
                    # 3. 이미 쌓인 블록과의 충돌 검사
                    if board_y < BOARD_HEIGHT and self.board[board_y][board_x] != EMPTY_CHAR:
                        return True
        return False
    
    def get_ghost_y(self):
        """블록이 닿게 될 최종 y 좌표를 계산합니다."""
        dy = 0
        while not self.check_collision(0, dy + 1, 0):
            dy += 1
        return self.piece_y + dy

    def move_piece(self, dx, dy):
        """조각을 이동시키고 성공 여부를 반환합니다."""
        if not self.check_collision(dx, dy, 0):
            self.piece_x += dx
            self.piece_y += dy
            return True
        return False

    def rotate_piece(self):
        """조각을 회전시키고 성공 여부를 반환합니다."""
        if not self.check_collision(0, 0, 1):
            self.piece_rotation = (self.piece_rotation + 1) % len(self.current_piece)
            return True
        return False

    def lock_piece(self):
        """조각을 보드에 고정하고 새 조각을 생성합니다."""
        piece = self.get_rotated_piece()
        for y in range(4):
            for x in range(4):
                if piece[y][x] == 'X':
                    board_x = self.piece_x + x
                    board_y = self.piece_y + y
                    if 0 <= board_y < BOARD_HEIGHT and 0 <= board_x < BOARD_WIDTH:
                        self.board[board_y][board_x] = BLOCK_CHAR
        
        self.clear_lines()
        
        # 블록 고정 후 새 블록 생성 시 can_hold 플래그 리셋
        self.can_hold = True
        self.new_piece()
        
        

    def clear_lines(self):
        """가득 찬 줄을 지우고 점수를 업데이트합니다."""
        lines_cleared = 0
        new_board = []
        for row in self.board:
            # 줄이 가득 찼는지 확인 (EMPTY_CHAR가 없는 경우)
            if EMPTY_CHAR not in row:
                lines_cleared += 1
            else:
                new_board.append(row)

        # 지워진 줄 수만큼 빈 줄을 보드 상단에 추가
        for _ in range(lines_cleared):
            new_board.insert(0, [EMPTY_CHAR] * BOARD_WIDTH)
        
        self.board = new_board
        
        # 점수 계산 (단순화된 점수 부여)
        if lines_cleared > 0:
            self.score += [0, 10, 30, 50, 80][lines_cleared] # 1줄:10, 2줄:30, 3줄:50, 4줄:80

    def draw_board(self):
        """현재 게임 상태를 콘솔에 출력합니다."""
        # 콘솔 화면을 지웁니다.
        os.system('cls' if os.name == 'nt' else 'clear') 

        output = ""
        
        # 제목 및 점수
        output += "---------------------------------\n"
        output += f" TETRIS - Score: {self.score}\n"
        output += "---------------------------------\n"

        display_board = [row[:] for row in self.board]

        if self.current_piece and not self.game_over:
            piece = self.get_rotated_piece()
            
            # 1. 고스트 조각 그리기
            ghost_y = self.get_ghost_y()
            for y in range(4):
                for x in range(4):
                    if piece[y][x] == 'X':
                        board_x = self.piece_x + x
                        board_y = ghost_y + y
                        if 0 <= board_y < BOARD_HEIGHT and 0 <= board_x < BOARD_WIDTH and self.board[board_y][board_x] == EMPTY_CHAR:
                            if board_y != self.piece_y + y:
                                display_board[board_y][board_x] = GHOST_CHAR

            # 2. 현재 떨어지는 조각 그리기
            for y in range(4):
                for x in range(4):
                    if piece[y][x] == 'X':
                        board_x = self.piece_x + x
                        board_y = self.piece_y + y
                        if 0 <= board_y < BOARD_HEIGHT and 0 <= board_x < BOARD_WIDTH:
                            # 이미 고스트 조각이 있는 위치에 현재 조각을 겹쳐 그립니다.
                            display_board[board_y][board_x] = BLOCK_CHAR
        
        # 보드 출력 및 사이드 정보 출력 통합
        for i in range(BOARD_HEIGHT):
            board_line = BORDER_CHAR + " " + " ".join(display_board[i]) + " " + BORDER_CHAR
            side_info = ""

            # 홀드 블록 표시 (상단 4줄)
            if i == 1:
                side_info += " [HOLD (C)] "
            elif 2 <= i <= 5:
                # 홀드된 블록의 모양을 가져옵니다.
                hold_piece_shape = TETROMINOES.get(self.hold_piece_key, [['....', '....', '....', '....']])[0]
                # 블록 문자 크기를 맞추기 위해 4x4 그리드에서 공백을 사용하여 표시
                side_info += f"  {' '.join([BLOCK_CHAR if c == 'X' else ' ' for c in hold_piece_shape[i-2]])}  "
            
            # 다음 블록 표시 (중간 4줄)
            elif i == 8:
                side_info += " [NEXT] "
            elif 9 <= i <= 12:
                # 다음 블록의 모양을 가져옵니다.
                next_piece_shape = TETROMINOES.get(self.next_piece_key, [['....', '....', '....', '....']])[0]
                side_info += f"  {' '.join([BLOCK_CHAR if c == 'X' else ' ' for c in next_piece_shape[i-9]])}  "

            output += board_line + side_info + "\n"

        # 바닥 경계 출력
        output += BORDER_CHAR + " " + " ".join([BORDER_CHAR] * BOARD_WIDTH) + " " + BORDER_CHAR + "\n"
        
        if self.game_over:
            output += "\n--- GAME OVER! ---"
            output += "\n (Press any key to exit)"

        print(output)

# ----------------------------------------------------
# 3. 게임 루프 및 입력 처리
# ----------------------------------------------------

def handle_input(game):
    """키 입력을 처리하고 소프트 드롭 상태를 반환합니다. (Windows msvcrt 사용)."""
    is_soft_drop = False # 소프트 드롭 상태를 저장할 변수 초기화

    if msvcrt.kbhit(): # 키가 눌렸는지 확인
        key = msvcrt.getch() # 키 입력을 즉시 읽음
        
        # 방향키 입력 처리 (방향키는 보통 2바이트 입력)
        if key == b'\xe0': # 특수 키 (방향키 등의 시작)
            key = msvcrt.getch() # 두 번째 바이트 읽기
            if key == b'H': # UP (회전)
                game.rotate_piece()
            elif key == b'P': # DOWN (부드러운 하강)
                is_soft_drop = True # 소프트 드롭 상태 플래그 설정
                game.move_piece(0, 1) # 아래로 이동은 여전히 필요
            elif key == b'K': # LEFT (왼쪽 이동)
                game.move_piece(-1, 0)
            elif key == b'M': # RIGHT (오른쪽 이동)
                game.move_piece(1, 0) # <--- 누락된 코드를 포함하여 올바르게 종료

        
        # 스페이스바 (하드 드롭)
        elif key == b' ': 
            while game.move_piece(0, 1):
                pass # 블록이 바닥에 닿을 때까지 계속 내립니다.
            game.lock_piece()
            
        # 'C' 키 (홀드 기능)
        elif key in [b'c', b'C']: 
            game.swap_hold_piece()

    return is_soft_drop # 소프트 드롭 상태 반환

def game_loop():
    """메인 게임 루프"""
    game = TetrisGame()
    
    fall_time = 0
    FALL_SPEED_NORMAL = 0.5    # 일반 하강 속도 (초)
    FALL_SPEED_SOFT = 0.05     # 소프트 드롭 속도 (초) <-- 가속 속도

    while not game.game_over:
        start_time = time.time()
        
        # 1. 입력 처리
        is_soft_drop = handle_input(game) # 소프트 드롭 상태를 받음

        # 2. 자동 하강 처리
        current_time = time.time()
        # 입력 처리 시간만큼 fall_time에 더해 줍니다.
        fall_time += (current_time - start_time) 
        
        # 현재 적용할 하강 속도 결정
        # 소프트 드롭 키가 눌렸으면 FALL_SPEED_SOFT를 사용
        temp_fall_speed = FALL_SPEED_SOFT if is_soft_drop else FALL_SPEED_NORMAL
        
        if fall_time >= temp_fall_speed: # temp_fall_speed에 따라 블록 떨어지는 시간 결정
            fall_time = 0
            # 아래로 이동 시도
            if not game.move_piece(0, 1):
                # 이동에 실패하면 고정하고 새 조각 생성
                game.lock_piece()
        
        # 3. 화면 그리기
        game.draw_board()

        # 4. 루프 속도 제어
        # 다음 프레임까지 잠시 대기 (약 30FPS를 가정하여 1/30초 대기)
        sleep_time = 1/30 - (time.time() - current_time)
        if sleep_time > 0:
            time.sleep(sleep_time)

    # 게임 오버 화면 표시 후 종료 대기
    game.draw_board()
    msvcrt.getch() # 키 입력 대기

if __name__ == "__main__":
    game_loop()