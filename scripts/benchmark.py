import subprocess
import time
import pandas as pd

from generate_process import gen_process_list
from graph import gen_gfx


# res = [sche_0[fit_alg0[], ...], ...]
results = [ [], [], [] ]

sche_type = ['FIFO', 'Round Robin', 'Shortest Job First']
fit_alg = ['FirstFit', 'BestFit', 'WorstFit']

colors = ['red', 'blue', 'green']

process_list = gen_process_list()

for scheduler in range(3):
    for fit in range(3):
        options = f'{scheduler} {fit}'

        for i in range(10):
            process_in = ''
            for p in range(i+1):
                process_in = f'{process_in} {process_list[p]}'
           
            #   ejecutar
            start = time.time()

            subprocess.run([
                "./tests/final_test/final_test",
                f'{options}{process_in}'
            ])

            end = time.time()

            #   añadir resultados
            results[scheduler].append({
                'fit_algorithm': fit_alg[fit],
                'n_process': i + 1,
                'time': end - start
            })


#   Generar csv y graficas
for scheduler in range(3):
    pd.DataFrame(results[scheduler]).to_csv(
        f'./docs/results/{sche_type[scheduler]}.csv',
        index=False
    )

    tiempos = [
        [ d['time'] for d in results[scheduler] if d.get('fit_algorithm') == fit_alg[0] ],
        [ d['time'] for d in results[scheduler] if d.get('fit_algorithm') == fit_alg[1] ],
        [ d['time'] for d in results[scheduler] if d.get('fit_algorithm') == fit_alg[2] ]
    ]

    gen_gfx(
        sche_type[scheduler],
        tiempos,
        fit_alg,
        colors
    )

