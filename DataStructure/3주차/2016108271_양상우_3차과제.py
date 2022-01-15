
import random
import math

# 클래스와 함수 선언 부분


class Node_71():
    def __init__(self):
        self.data = None
        self.link = None


def printStores_71(start_71):
    current_71 = start_71
    if current_71 == None:
        return

    while current_71.link_71 != head_71:
        current_71 = current_71.link_71
        x_71, y_71 = current_71.data_71[1:]
        print(current_71.data_71[0], '편의점, 거리:',
              math.sqrt(x_71*x_71+y_71*y_71))
    print()


def makeStoreList_71(store_71):
    global memory_71, head_71, current_71, pre_71

    node_71 = Node_71()
    node_71.data_71 = store_71
    memory_71.append(node_71)

    if head_71 == None:
        head_71 = node_71
        node_71.link_71 = head_71
        return

    # 새 편의점이 첫번째 편의점보다 가까우면 첫 편의점으로 만듦
    nodeX_71, nodeY_71 = node_71.data_71[1:]
    nodeDist_71 = math.sqrt(nodeX_71*nodeX_71 + nodeY_71*nodeY_71)
    headX_71, headY_71 = head_71.data_71[1:]
    headDist_71 = math.sqrt(headX_71*headX_71 + headY_71*headY_71)

    if headDist_71 < nodeDist_71:
        node_71.link_71 = head_71
        last_71 = head_71
        while last_71.link_71 != head_71:
            last_71 = last_71.link_71
        last_71.link_71 = node_71
        head_71 = node_71
        return

    current_71 = head_71
    while current_71.link_71 != head_71:
        pre_71 = current_71
        current_71 = current_71.link_71
        currX_71, currY_71 = current_71.data_71[1:]
        currDist_71 = math.sqrt(currX_71*currX_71 + currY_71*currY_71)
        if currDist_71 > nodeDist_71:
            pre_71.link_71 = node_71
            node_71.link_71 = current_71
            return

    current_71.link_71 = node_71
    node_71.link_71 = head_71


# 전역 변수 선언 부분
memory_71 = []
head_71, current_71, pre_71 = None, None, None

# 메인 코드 부분
if __name__ == "__main__":

    storeArray_71 = []
    storeName_71 = 'A'
    for _ in range(10):
        store_71 = (storeName_71, random.randint(
            1, 100), random.randint(1, 100))
        storeArray_71.append(store_71)
        storeName_71 = chr(ord(storeName_71) + 1)
    for store_71 in storeArray_71:
        makeStoreList_71(store_71)

    printStores_71(head_71)
