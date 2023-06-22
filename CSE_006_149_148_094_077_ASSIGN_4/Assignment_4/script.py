import matplotlib.pyplot as plt
## Enter File path here
file_path = 'DataForSize-3.dat'
with open(file_path, 'r') as f:
    lines = f.readlines()
col1 = []
col2 = []
col3 = []
col4 = []
col5 = []
col6 = []
for line in lines:
    values = line.split()
    col1.append(float(values[0]))
    col2.append(float(values[1]))
    col3.append(float(values[2]))
    col4.append(float(values[3]))
    col5.append(float(values[4]))
    col6.append(float(values[5]))
fig, axs = plt.subplots(5, 1, figsize=(12, 20))

axs[0].plot(col1, col2, 'bo')
axs[0].set_xlabel('No of threads')
axs[0].set_ylabel('Throughput')
axs[0].set_title("100C-0I-0D")

axs[1].plot(col1, col3, 'ro')
axs[1].set_xlabel('No of threads')
axs[1].set_ylabel('Throughput')
axs[1].set_title("70C-20I-10D")

axs[2].plot(col1, col4, 'go')
axs[2].set_xlabel('No of threads')
axs[2].set_ylabel('Throughput')
axs[2].set_title("50C-25I-25D")


axs[3].plot(col1, col5, 'yo')
axs[3].set_xlabel('No of threads')
axs[3].set_ylabel('Throughput')
axs[3].set_title("30C-35I-35D)")

axs[4].plot(col1, col6, 'yo')
axs[4].set_xlabel('No of threads')
axs[4].set_ylabel('Throughput')
axs[4].set_title("0C-50I-50D")

fig.tight_layout()

## Save the figure with the name
plt.savefig("Key Range - 2 x 10^7.pdf", format="pdf", bbox_inches="tight")