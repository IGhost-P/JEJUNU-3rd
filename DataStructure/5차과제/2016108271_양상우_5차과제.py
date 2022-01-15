import random
import sys
# maximum recursion depth exceeded while calling a Python object 에러가 나서 변경
sys.setrecursionlimit(100000)
## 함수 선언 부분 ##


def qsort_71(data_71):
    if len(data_71) <= 1:
        return data_71
    # 1보다 크다면 ~?
        # 사전 작업
    left_71, right_71 = list(), list()
    pivot_71 = data_71[len(data_71)//2]

    # 데이터의 끝까지 비교, 피벗을 기준으로 왼쪽 오른쪽을 나눔
    for index_71 in range(1, len(data_71)):
        if pivot_71 > data_71[index_71]:  # 왼쪽에 있어야하는 조건
            left_71.append(data_71[index_71])
        else:  # 오른쪽에 있어야하는 조건
            right_71.append(data_71[index_71])
    # 재귀 호출로 마무리 -> 맨위의 len(data) <=1이 될때까지 => 끝날때까지 재귀호출됨
    return qsort_71(left_71) + [pivot_71] + qsort_71(right_71)


## 전역 변수 선언 부분 ##
#dataAry = [188, 150, 168,  162, 105, 120,  177,  50]
dataAry_71 = [120, 120, 188, 150, 168, 50, 50, 162, 105, 120,  177,  50]

## 메인 코드 부분 ##
print("----------2016108271 양상우 5차시 과제----------")
print('정렬 전 -->', dataAry_71)
new_dataAry_71 = qsort_71(dataAry_71)
print('정렬 후 -->', new_dataAry_71)
