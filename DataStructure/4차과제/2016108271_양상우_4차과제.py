
import os


class TreeNode():
    def __init__(self):
        self.left_71 = None
        self.data_71 = None
        self.right_71 = None


memory_71 = []
root_71 = None
fnameAry_71 = []

folderName_71 = input()  # '/Users/sangwuuyang/Documents/GitHub/JEJUNU-3rd/DataStructure'
for dirName_71, subDirList_71, fnames_71 in os.walk(folderName_71):
    for fname_71 in fnames_71:
        fnameAry_71.append(fname_71)
print(fnameAry_71[0])
node_71 = TreeNode()
node_71.data_71 = fnameAry_71[0]
root_71 = node_71
memory_71.append(node_71)

dupNameAry_71 = []

for name_71 in fnameAry_71[1:]:
    node_71 = TreeNode()
    node_71.data_71 = name_71
    current_71 = root_71

    while True:
        if name_71 == current_71.data_71:
            dupNameAry_71.append(name_71)
            break
        if name_71 < current_71.data_71:
            if current_71.left_71 == None:
                current_71.left_71 = node_71
                memory_71.append(node_71)
                break
            current_71 = current_71.left_71
        else:
            if current_71.right_71 == None:
                current_71.right_71 = node_71
                memory_71.append(node_71)
                break
            current_71 = current_71.right_71
dupNameAry_71 = list(set(dupNameAry_71))

print("2016108271 양상우 4차시 과제")
print(folderName_71, '및 그 하위 디렉터리의 중복된 파일 목록 ')
print(dupNameAry_71)
