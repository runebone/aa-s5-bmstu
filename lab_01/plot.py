import sys
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

# path = "/home/human/University/aa/lab_01/benchmark/data_1_1000.csv"
path = "/home/human/University/aa/lab_01/benchmark/data_10k.csv"

if len(sys.argv) > 1:
    path = sys.argv[1]

reader = pd.read_csv(path)

df = pd.DataFrame(reader)
x = df.groupby("length").mean().reset_index()

def f(value):
    if value == -1:
        return np.nan
    return value

x["tdlr"] = x["tdlr"].apply(f) # type: ignore // For LSP
x["ndlr"] = x["ndlr"].apply(f) # type: ignore // For LSP
x["sdlr"] = x["sdlr"].apply(f) # type: ignore // For LSP

lengths = x["length"] # type: ignore
tlim   = x["tlim"] # type: ignore
tlifm  = x["tlifm"] # type: ignore
tdlifm = x["tdlifm"] # type: ignore
tdlr   = x["tdlr"] # type: ignore
tdlrc  = x["tdlrc"] # type: ignore

# length,tlim,tlifm,tdlifm,tdlr,tdlrc,slim,slifm,sdlifm,ndlr,sdlr,ndlrc,sdlrc,hlim,hlifm,hdlifm,hdlr,hdlrc
slim   = x["slim"] # type: ignore
slifm  = x["slifm"] # type: ignore
sdlifm = x["sdlifm"] # type: ignore
sdlifm = x["sdlifm"] # type: ignore
sdlr   = x["sdlr"] # type: ignore
sdlrc  = x["sdlrc"] # type: ignore

ndlr   = x["ndlr"] # type: ignore
ndlrc  = x["ndlrc"] # type: ignore

hlim   = x["hlim"] # type: ignore
hlifm  = x["hlifm"] # type: ignore
hdlifm = x["hdlifm"] # type: ignore
hdlifm = x["hdlifm"] # type: ignore
hdlr   = x["hdlr"] # type: ignore
hdlrc  = x["hdlrc"] # type: ignore

fig, ax = plt.subplots()

# ax.plot(lengths, tlim, label='Левенштейн итерационный (оптимизация по памяти)') # type: ignore

# Time
ax.plot(lengths, tlifm, label='Левенштейн итерационный', marker='^') # type: ignore
ax.plot(lengths, tdlrc, label='Дамерау-Левенштейн рекурсивный (с кешированием)', marker='X') # type: ignore
ax.plot(lengths, tdlifm, label='Дамерау-Левенштейн итерационный', marker='o') # type: ignore
ax.plot(lengths, tdlr, label='Дамерау-Левенштейн рекурсивный', marker='s') # type: ignore
ax.set_xlabel('Длина строк в символах') # type: ignore
ax.set_ylabel('Время выполнения, нс') # type: ignore
ax.legend() # type: ignore

# # Stack
# ax.plot(lengths, slifm, label='Левенштейн итерационный', marker='^') # type: ignore
# ax.plot(lengths, sdlrc, label='Дамерау-Левенштейн рекурсивный (с кешированием)', marker='X') # type: ignore
# ax.plot(lengths, sdlifm, label='Дамерау-Левенштейн итерационный', marker='o') # type: ignore
# ax.plot(lengths, sdlr, label='Дамерау-Левенштейн рекурсивный', marker='s') # type: ignore
# ax.set_xlabel('Длина строк в символах') # type: ignore
# ax.set_ylabel('Максимальная высота стека, байт') # type: ignore
# ax.legend() # type: ignore

# # Recursion
# ax.plot(lengths, ndlrc, label='Дамерау-Левенштейн рекурсивный (с кешированием)', marker='X') # type: ignore
# ax.plot(lengths, ndlr, label='Дамерау-Левенштейн рекурсивный', marker='s') # type: ignore
# ax.set_xlabel('Длина строк в символах') # type: ignore
# ax.set_ylabel('Количество рекурсивных вызовов') # type: ignore
# ax.legend() # type: ignore

# # Heap
# ax.plot(lengths, hlifm, label='Левенштейн итерационный', marker='^') # type: ignore
# ax.plot(lengths, hdlrc, label='Дамерау-Левенштейн рекурсивный (с кешированием)', marker='X') # type: ignore
# ax.plot(lengths, hdlifm, label='Дамерау-Левенштейн итерационный', marker='o') # type: ignore
# ax.plot(lengths, hdlr, label='Дамерау-Левенштейн рекурсивный', marker='s') # type: ignore
# ax.set_xlabel('Длина строк в символах') # type: ignore
# ax.set_ylabel('Выделено памяти в куче, байт') # type: ignore
# ax.legend() # type: ignore

plt.yscale('log')

plt.grid()
plt.show()
