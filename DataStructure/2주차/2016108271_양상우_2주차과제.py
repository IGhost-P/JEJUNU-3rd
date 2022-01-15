# 함수 선언 부분 #
def find_and_insert_data_71(friend_71, k_count_71):
    findPos_71 = -1
    for i_71 in range(len(katok_71)):
        pair_71 = katok_71[i_71]
        if k_count_71 >= pair_71[1]:
            findPos_71 = i_71
            break
    if findPos_71 == -1:
        findPos_71 = len(katok_71)

    insert_data_71(findPos_71, (friend_71, k_count_71))


def insert_data_71(position_71, friend_71):
    if position_71 < 0 or position_71 > len(katok_71):
        print("데이터를 삽입할 범위를 벗어났습니다.")
        return

    katok_71.append(None)
    kLen_71 = len(katok_71)

    for i_71 in range(kLen_71 - 1, position_71, -1):
        katok_71[i_71] = katok_71[i_71-1]
        katok_71[i_71-1] = None

    katok_71[position_71] = friend_71


# 전역 변수 선언 부분
katok_71 = [('다현', 200), ('정연', 150), ('쯔위', 90), ('사나', 30), ('지효', 15)]

if __name__ == "__main__":

    while True:
        data_71 = input("추가할 친구-->")
        count_71 = int(input("카톡 횟수 -->"))
        find_and_insert_data_71(data_71, count_71)
        print(katok_71)
