import subprocess
import time
import pandas as pd

from generate_process import gen_process_list


results = []

sche_type = ['FIFO', 'Round Robin', 'Shortest Job First']
fit_alg = ['FirstFit', 'BestFit', 'WorstFit']

process_list = gen_process_list()

for scheduler in range(3):
    for fit in range(3):
        args = f'{scheduler} {fit}{process_list}'
        start = time.time()

        subprocess.run([
            "./tests/final_test/final_test",
            args
        ])

        end = time.time()

        results.append({
            'scheduler_type': sche_type[scheduler],
            'fit_algorithm': fit_alg[fit],
            'time': end - start
        })


pd.DataFrame(results).to_csv(
    "./docs/csv/benchmark.csv",
    index=False
)


