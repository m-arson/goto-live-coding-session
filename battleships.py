print("Input Filename: ")
filename = input()

print()

P = []
counter = []

with open(filename, "r") as f:
	M = int(f.readline())

	for _ in range(2):
		P.append([["_"] * M for _ in range(M)])

	S = int(f.readline())
	for i in range(2):
		S = [list(map(int, i.split(","))) for i in f.readline().strip().split(":")]
		for s in S:
			P[i][s[0]][s[1]] = "B"

	T = int(f.readline())

	for i in range(2):
		count = 0
		T = [list(map(int, i.split(","))) for i in f.readline().strip().split(":")]
		for t in T:
			if P[1-i][t[0]][t[1]] == "B":
				P[1-i][t[0]][t[1]] = "X"
				count = count + 1
			else:
				P[1-i][t[0]][t[1]] = "O"
		counter.append(count)

for inx, players in enumerate(P):
	print(f"Player{inx+1}")
	for player in players:
		for item in player:
			print(item, end=" ")
		print()
	print()
print()

for i,count in enumerate(counter):
	print(f"P{i+1}:{count}")
if counter[0] > counter[1]:
	print("Player1 Win")
elif counter[0] < counter[1]:
	print("Player2 Win")
else:
	print("It is a Draw")
