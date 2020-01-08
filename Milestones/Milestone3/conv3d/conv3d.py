import math
import numpy as np


def conv3d(inputs, filters):
    results = []

    for i_filter in filters:

        padding = math.floor(len(filters[0]) / 2)
        size = len(inputs[0])

        result = []

        for i, i_elem in enumerate(inputs):
            for j, j_elem in enumerate(i_elem):
                for k, k_elem in enumerate(j_elem):

                    obj = inputs[i - padding : i + padding][j - padding : j + padding][k - padding : k + padding] 

                    result[i][j][k] = kernel_filter(obj, i_filter)

        results.append(result)



def kernel_filter(obj, i_filter):
    return np.inner(obj, i_filter) 
