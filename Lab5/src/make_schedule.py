import matplotlib.pyplot as plt


with open("../DATA/benchmark.txt") as f:
    lines = f.readlines()

data = {}

for line in lines:
    size = ""
    time = ""
    space = False
    
    for ch in line:
        
        if ch == '\n':
            break

        if ch != ' ' and not space:
            size += ch
            continue

        if ch == ' ':
            space = True
            continue

        if ch != ' ' and space:
            time += ch
            continue

    size = int(size)
    time = float(time)
    data[size] = time


sizes = []
times = []
for sz, tm in data.items():
    sizes.append(sz)
    times.append(tm)
    
fig, ax = plt.subplots()
ax.plot(sizes, times, marker='o')
ax.set_xlabel("Размер графа", fontsize=12)
ax.set_ylabel("Время работы алгоритма", fontsize=12)
ax.grid(True, linestyle=':', alpha=0.6)
plt.show()

