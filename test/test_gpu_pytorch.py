import torch
import time

def main():
    while True:
        sizes = torch.randint(10, 200, (3,))
        matrix_a = torch.rand((sizes[0], sizes[1]), device="cuda")
        matrix_b = torch.rand((sizes[1], sizes[2]), device="cuda")
        result = torch.matmul(matrix_a, matrix_b)
        sum = result.sum()
        result /= sum
        print(sum)
        time.sleep(0.05)

if __name__ == "__main__":
    main()
