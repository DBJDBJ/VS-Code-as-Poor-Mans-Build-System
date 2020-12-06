@echo on & title=dbj runner

@setlocal

@rem ~ n -- remove quotes arround param n

@echo 1 = [%1]
@echo 2 = [%~2]
@echo 3 = [%3]
@echo 4 = [%4]
@echo 5 = [%5]
@echo 6 = [%6]
@echo 7 = [%7]
@echo 8 = [%8]

%1 %~2 %~3

