"""
Print a right angle triangle of base "size"
"""
size = int(input("Enter a number: "))
lines = ["#"*i for i in range(1, size+1)]
print(*lines, sep='\n')
