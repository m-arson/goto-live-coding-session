def split_r(s):
    s = s.strip().split(":")
    return [list(map(int, i.split(","))) for i in s]

N_PLAYER = 2
N_LIFE = 2
print("Input filename :", end=" ");

filename = input()

Players = []
Livestock = []
counter = []

with open(filename, "r") as f:
    M = int(f.readline())
    if not 0 < M < 100:
        f.close()
    
    for i in range(N_PLAYER):
        Players.append([["_"] * M for _ in range(M)])
        Livestock.append([[N_LIFE] * M for _ in range(M)])
    
    S = int(f.readline())

    if not 0 < S <= M**2/2:
        f.close()

    for i in range(N_PLAYER):
        tmp = split_r(f.readline())
        for tmp_ in tmp:
            Players[i][tmp_[0]][tmp_[1]] = "B"

    T = int(f.readline())

    if not 0 < T < 100:
        f.close()

    for i in range(N_PLAYER):
        count = 0
        tmp = split_r(f.readline())
        for tmp_ in tmp:
            if Players[N_PLAYER-1-i][tmp_[0]][tmp_[1]] == "B":
                if Livestock[N_PLAYER-1-i][tmp_[0]][tmp_[1]] > 1:
                    Livestock[N_PLAYER-1-i][tmp_[0]][tmp_[1]] = Livestock[N_PLAYER-1-i][tmp_[0]][tmp_[1]] - 1
                else:
                    Players[N_PLAYER-1-i][tmp_[0]][tmp_[1]] = "X"
                    count = count + 1
            else:
                Players[N_PLAYER-1-i][tmp_[0]][tmp_[1]] = "O"
        counter.append(count)

for inx, players in enumerate(Players):
    print(f"Player{inx+1}")
    for player in players:
        for item in player:
            print(item, end=" ")
        print()
    print()

for inx, count  in enumerate(counter):
    print(f"P{inx+1}:{count}")
if counter[0] > counter[1]:
    print("Player 1 wins")

elif counter[0] < counter[1]:
    print("Player 2 wins")
else:
    print("Is is a draw")
