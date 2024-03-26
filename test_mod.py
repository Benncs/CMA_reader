import sys
import os

def get_transition_matrix(F):
    n_compartments = F.shape[0]
    M = np.zeros_like(F)
    for i in range(n_compartments):
        for j in range(n_compartments):
            if i != j:
                M[i, j] = F[i, j]
            else:
                sum_except_diagonal = np.sum(F[i, :]) - F[i, i]
                M[i, i] = -sum_except_diagonal
    return M

# Add the path to the module to sys.path
sys.path.append("./builddir")
import numpy as np 
# Now you can import your module
import cma_read

liq_flow = cma_read.read("../BIREM_generate/out/flowL.raw")
#gaz_flow = cma_read.read("../BIREM_generate/out/flowG.raw")


#g = cma_read.read_scalar("../BIREM_generate/out/vofL.raw")
#h = cma_read.read_scalar("../BIREM_generate/out/vofG.raw")

#eps = h/(g+h)

np.set_printoptions(precision=2, suppress=True)
ll = liq_flow.transpose()
m = get_transition_matrix(liq_flow)

neighbor = []
for i in range(len(m[0])):
    neighbor.append(np.where(m[:,i]!=0)[0])

print(neighbor)
