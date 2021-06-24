import os
import string
import sys


def RenameFiles(path):
    parents = os.listdir(path)
    for parent in parents:
        child = os.path.join(path, parent)
        if os.path.isdir(child):
            RenameFiles(child)
        else:
            filename = os.path.splitext(parent)[0]
            sufix = os.path.splitext(parent)[1]
            if sufix in ['.cfg','.downloading']:
                # print(child)
                os.remove(child)
            # if len(filename) > 27:
            #     filename = filename[:-27]
            # file = filename+sufix
            # file = os.path.join(path, file)
            # os.rename(child, file)
            # print(child,'\n->\n',file)

path = input('请输入路径:')
RenameFiles(path)
