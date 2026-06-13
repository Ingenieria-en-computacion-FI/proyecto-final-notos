import matplotlib.pyplot as plt


def gen_gfx(title, times, names, colors):
    x = range(10)

    plt.figure(figsize=(8, 5))

    #	Hacer la grafica
    for y, lab, col in zip(times, names, colors):
        plt.plot(x, y, label=lab, color=col)

    #   Datos de la grafica
    plt.title(title)

    plt.xlabel('N° procesos')
    plt.ylabel('Tiempo')

    plt.xticks(x)
    plt.grid(True)
    plt.legend()

    #	Generar PNG
    plt.tight_layout()
    plt.savefig(f'./docs/results/scheduler_{title}.png')
    plt.close()


