import sys
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

path = "/home/human/University/aa/lab_01/benchmark/data_1_1000.csv"

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

lengths = x["length"] # type: ignore
# tlim = x["tlim"] # type: ignore
tlifm = x["tlifm"] # type: ignore
tdlifm = x["tdlifm"] # type: ignore
tdlr = x["tdlr"] # type: ignore
tdlrc = x["tdlrc"] # type: ignore

fig, ax = plt.subplots()

# ax.plot(lengths, tlim, label='Левенштейн итеративный (оптимизация по памяти)') # type: ignore
ax.plot(lengths, tlifm, label='Левенштейн итеративный', marker='^') # type: ignore
ax.plot(lengths, tdlrc, label='Дамерау-Левенштейн рекурсивный (с кешированием)', marker='X') # type: ignore
ax.plot(lengths, tdlifm, label='Дамерау-Левенштейн итеративный', marker='o') # type: ignore
ax.plot(lengths, tdlr, label='Дамерау-Левенштейн рекурсивный', marker='s') # type: ignore

ax.set_xlabel('Длина строк в символах') # type: ignore
ax.set_ylabel('Время выполнения, нс') # type: ignore
# ax.set_title('') # type: ignore

# m = max(tlim.to_list() + tlifm.to_list() + tdlifm.to_list() + tdlrc.to_list()) + 1000 # type: ignore
# m = max(tlifm.to_list() + tdlifm.to_list() + tdlrc.to_list()) + 1000 # type: ignore

# ax.set_ylim(0, m) # type: ignore
ax.legend() # type: ignore

plt.yscale('log')

plt.grid()
plt.show()
