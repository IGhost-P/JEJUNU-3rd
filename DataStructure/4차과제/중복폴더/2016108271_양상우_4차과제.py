'''
첨부한 화일(8장(이진트리)-응용예제-p311-312.zip ) )에서 설명하는 파이썬 코드(프로그램)을 아래의 요구사항에 맞게 수정하여 파이썬 Anaconda환경의 Spyder(또는 IDLE환경)을 사용하여서 작성하고 실행시킨 후, 
화면을 캡쳐하거나 찍어서 이미지화일(*.png 또는 *.jpg화일,  이미지 화일 제출이 안될 떄는 이미지 화일을 아래한글 또는 MS워드 화일에 포함시켜 제출) 제출

요구사항

1. 지정폴더 이름(예를 들면, 'C:/Programs Files/Common Files/')은 입력으로 받을 것(input() 함수 사용)

2. 코드 내 모든 변수이름에는 본인 학번 뒷 2자리 붙일 것

   예) 학번이 2020103278 인 경우

           root => root_78 

3. 캡쳐한 화면 이미지 화일에는 Spyder 윈도창의 편집기(왼쪽)창, Console창(오른쪽 아래)이 전부 보이도록 하여야 함 

(또는 IDLE환경의 스크립트모드, 대화모드 전부 보이도록 함) 

4. 프로그램이 성공적으로 실행되어서  첨부화일 [실행결과] 처럼 나타나야 함

5. 수정이 미흡할 경우, 제출하지 않은 것으로 처리함
'''


# class TreeNode():
#     def __init__(self):
#         self.left_71 = None
#         self.data_71 = None
#         self.right_71 = None


# memory_71 = []
# fnameAry_71 = []

# folderName_71 = input()
# for dirName_71, suDirList_71, fnames_71 in os.walk(folderName_71):
#     for fname_71 in fnames_71:
#         fnameAry_71.append(fname_71)

# node_71 = TreeNode()
# node_71.data_71 = fnameAry_71[0]
# root_71 = node_71
# memory_71.append(node_71)

# dupNameAry_71 = []

# for name_71 in fnameAry_71[1:]:
#     node_71 = TreeNode()
#     node_71.data_71 = name_71

# current_71 = root_71

# while True:
#     if name_71 == current_71.data_71:
#         dupNameAry_71.append(name_71)
#         break
#     if name_71 < current_71.data_71:
#         if current_71.left_71 == None:
#             current_71.left_71 = node_71
#             memory_71.append(node_71)
#             break
#         current_71 = current_71.left_71
#     else:
#         if current_71.right_71 == None:
#             current_71.right_71 = node_71
#             memory_71.append(node_71)
#             break
#         current_71 = current_71.right_71

# dupNameAry_71 = list(set(dupNameAry_71))

# print(folderName_71, '및 그 하위 디렉터리의 중복된 파일 목록 -->')
# print(dupNameAry_71)

import os


class TreeNode():
    def __init__(self):
        self.left = None
        self.data = None
        self.right = None


memory = []
root = None
fnameAry = []

folderName = 'C:/Programs Files/Common Files/'
for dirName, subDirList, fnames in os.walk(folderName):
    for fname in fnames:
        fnameAry.append(fname)
node = TreeNode()
node.data = fnameAry[0]
root = node
memory.append(node)

dupNameAry = []

for name in fnameAry[1:]:
    node = TreeNode()
    node.data = name
    current = root

    while True:
        if name == current.data:
            dupNameAry.append(name)
            break
        if name < current.data:
            if current.left == None:
                current.left = node
                memory.append(node)
                break
            current = current.left
        else:
            if current.right == None:
                current.right = node
                memory.append(node)
                break
            current = current.right
dupNameAry = list(set(dupNameAry))

print(folderName, '및 그 하위 디렉터리의 중복된 파일 목록 -->')
print(dupNameAry)
